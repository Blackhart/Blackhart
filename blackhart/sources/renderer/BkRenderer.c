// Standard library headers.
#include <stdlib.h>
#include <time.h>
#include <string.h>

// Glew library headers.
#include <GL\glew.h>

// blackhart headers.
#include "foundation\BkCamera.h"
#include "renderer\BkRenderer.h"
#include "foundation\BkError.h"
#include "foundation\BkString.h"
#include "foundation\BkFileSystem.h"
#include "renderer\BkBuffer.h"
#include "renderer\BkShader.h"

// ~~~~~ Def(INTERNAL) ~~~~~

static GLuint                       __BkVertexArrayObject = 0;
static struct BkShaderProgram*      __BkShaderProgram = NULL;
static struct BkShader*             __BkVertexShader = NULL;
static struct BkShader*             __BkGeometryShader = NULL;
static struct BkShader*             __BkPixelShader = NULL;
static struct BkBuffer*             __BkBuffer = NULL;
static real*                        __points = NULL;
static size_t const                 __nb_points = 100000;

void    _BkRender_Initialize(void)
{
    // Initialize GLEW
    GLenum result = GLEW_OK;

    result = glewInit();
    BK_ERROR(result != GLEW_OK, BkString_CreateFormatted("Glew error : %s\nFailed to initialize OpenGL!", glewGetErrorString(result)));

    // Create VAO
    glGenVertexArrays(1, &__BkVertexArrayObject);
    glBindVertexArray(__BkVertexArrayObject);

    char* path = malloc((strlen(BK_DEFAULT_SHADER_PATH) + 15) * sizeof(char));
    BK_ERROR(BK_ISNULL(path), "Memory system has failed to allocate memory block");

    // Create vertex shader
    BkFileSystem_CombinePath(path, BK_DEFAULT_SHADER_PATH, "vertex.glsl");
    __BkVertexShader = _BkShader_Create(path, _BK_VERTEX_SHADER_);

    // Create fragment shader
    BkFileSystem_CombinePath(path, BK_DEFAULT_SHADER_PATH, "pixel.glsl");
    __BkPixelShader = _BkShader_Create(path, _BK_PIXEL_SHADER_);

    free(path);

    // Create material
    __BkShaderProgram = _BkShaderProgram_Create();
    _BkShaderProgram_AttachShader(__BkShaderProgram, __BkVertexShader);
    _BkShaderProgram_AttachShader(__BkShaderProgram, __BkPixelShader);
    _BkShaderProgram_Compile(__BkShaderProgram);

    _BkShader_Release(&__BkVertexShader);
    _BkShader_Release(&__BkPixelShader);

    __points = malloc((__nb_points * 3) * sizeof(real));

    /* initialize random seed: */
    srand((unsigned int)time(NULL));

    for (size_t i = 0; i < __nb_points * 3; i += 3)
    {
        __points[i] = BK_REAL(((rand() % 1001) / 1000.0) * 2 - 1);
        __points[i + 1] = BK_REAL(((rand() % 1001) / 1000.0) * 2 - 1);
        __points[i + 2] = BK_REAL(((rand() % 1001) / 1000.0) * 2 - 1);
    }

    __BkBuffer = _BkBuffer_Create(__nb_points * 3 * sizeof(real), __points);

    free(__points);

    glBindBuffer(GL_ARRAY_BUFFER, __BkBuffer->id);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void    _BkRender_Uninitialize(void)
{
    // Release vertex buffer
    _BkBuffer_Release(&__BkBuffer);

    // Release the shader program and his shaders
    _BkShaderProgram_Release(&__BkShaderProgram);

    // Release the vertex array object
    glDeleteVertexArrays(1, &__BkVertexArrayObject);
}

// ~~~~~ Def(PUBLIC) ~~~~~

void	BkRender(struct BkCamera* camera)
{
    static real const background[4] = { BK_REAL(0), BK_REAL(0), BK_REAL(0), BK_REAL(1) };

    glClearBufferfv(GL_COLOR, 0, background);

    glUseProgram(__BkShaderProgram->id);

    struct BkMatrix4x4 const v = BkCamera_ViewMatrix(camera);
    struct BkMatrix4x4 const pv = BkMatrix4x4_Mul_BkMatrix4x4(BkCamera_Projection(camera), &v);

    struct BkMatrix4x4 m1 = BkMatrix4x4_Translation_XYZ(BK_REAL(0), BK_REAL(0), BK_REAL(0));
    struct BkMatrix4x4 pvm = BkMatrix4x4_Mul_BkMatrix4x4(&pv, &m1);

    glUniformMatrix4fv(glGetUniformLocation(__BkShaderProgram->id, "uni_mvp"), 1, GL_TRUE, &(pvm.m11));

    glDrawArrays(GL_POINTS, 0, (GLsizei)__nb_points);
}