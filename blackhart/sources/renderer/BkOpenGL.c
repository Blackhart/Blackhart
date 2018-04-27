// Standard library headers.
#include <stdlib.h>
#include <time.h>
#include <string.h>

// Glew library headers.
#include <GL\glew.h>

// blackhart headers.
#include "foundation\BkCamera.h"
#include "foundation\BkError.h"
#include "foundation\BkString.h"
#include "foundation\BkFileSystem.h"
#include "renderer\BkOpenGL.h"
#include "renderer\BkOpenGLBuffer.h"
#include "renderer\BkOpenGLShader.h"

// ~~~~~ Def(INTERNAL) ~~~~~

static GLuint                           __BkOpenGL_VertexArrayObject = 0;
static struct BkOpenGLShaderProgram*    __BkOpenGL_ShaderProgram = NULL;
static struct BkOpenGLShader*           __BkOpenGL_VertexShader = NULL;
static struct BkOpenGLShader*           __BkOpenGL_PixelShader = NULL;
static struct BkOpenGLBuffer*           __BkOpenGL_Buffer = NULL;

static real*        __points = NULL;
static size_t const __nb_points = 100000;

void	_BkOpenGL_Initialize(void)
{
	// Initialize GLEW
	GLenum result = GLEW_OK;

	result = glewInit();
    BK_ERROR(result != GLEW_OK, BkString_CreateFormatted("Glew error : %s\nFailed to initialize OpenGL!", glewGetErrorString(result)));

	// Create VAO
	glGenVertexArrays(1, &__BkOpenGL_VertexArrayObject);
	glBindVertexArray(__BkOpenGL_VertexArrayObject);

	char* path = malloc((strlen(BK_DEFAULT_SHADER_PATH) + 15) * sizeof(char));
    BK_ERROR(BK_ISNULL(path), "Memory system has failed to allocate memory block")

	// Create vertex shader
	BkFileSystem_CombinePath(path, BK_DEFAULT_SHADER_PATH, "vertex.glsl");
	__BkOpenGL_VertexShader = _BkOpenGL_CreateShader(path, _BK_VERTEX_SHADER_);

	// Create fragment shader
	BkFileSystem_CombinePath(path, BK_DEFAULT_SHADER_PATH, "pixel.glsl");
	__BkOpenGL_PixelShader = _BkOpenGL_CreateShader(path, _BK_PIXEL_SHADER_);

    free(path);

	// Create material
	__BkOpenGL_ShaderProgram = _BkOpenGL_CreateShaderProgram(__BkOpenGL_VertexShader, __BkOpenGL_PixelShader);

	_BkOpenGL_ReleaseShader(&__BkOpenGL_VertexShader);
	_BkOpenGL_ReleaseShader(&__BkOpenGL_PixelShader);

    __points = malloc((__nb_points * 3) * sizeof(real));

	/* initialize random seed: */
	srand((unsigned int)time(NULL));

	for (size_t i = 0; i < __nb_points * 3; i += 3)
	{
		__points[i] = BK_REAL(((rand() % 1001) / 1000.0) * 2 - 1);
		__points[i + 1] = BK_REAL(((rand() % 1001) / 1000.0) * 2 - 1);
		__points[i + 2] = BK_REAL(((rand() % 1001) / 1000.0) * 2 - 1);
	}

	__BkOpenGL_Buffer = _BkOpenGL_CreateBuffer(__nb_points * 3 * sizeof(real), __points);

	free(__points);

	glBindBuffer(GL_ARRAY_BUFFER, __BkOpenGL_Buffer->id);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void	_BkOpenGL_Uninitialize(void)
{
	// Release vertex buffer
	_BkOpenGL_ReleaseBuffer(&__BkOpenGL_Buffer);

	// Release the shader program and his shaders
	_BkOpenGL_ReleaseShaderProgram(&__BkOpenGL_ShaderProgram);

	// Release the vertex array object
	glDeleteVertexArrays(1, &__BkOpenGL_VertexArrayObject);
}

void	_BkOpenGL_Render(struct BkCamera* camera)
{
	static real const background[4] = { 0.0f, 0.0f, 0.0f, 1.0f };

	glClearBufferfv(GL_COLOR, 0, background);

	glUseProgram(__BkOpenGL_ShaderProgram->id);

	struct BkMatrix4x4 const v = BkCamera_ViewMatrix(camera);
	struct BkMatrix4x4 const pv = BkMatrix4x4_Mul_BkMatrix4x4(BkCamera_Projection(camera), &v);

	struct BkMatrix4x4 m1 = BkMatrix4x4_Translation_XYZ(BK_REAL(0), BK_REAL(0), BK_REAL(0));
	struct BkMatrix4x4 pvm = BkMatrix4x4_Mul_BkMatrix4x4(&pv, &m1);

	glUniformMatrix4fv(glGetUniformLocation(__BkOpenGL_ShaderProgram->id, "uni_mvp"), 1, GL_TRUE, &(pvm.m11));

	glDrawArrays(GL_POINTS, 0, (GLsizei)__nb_points);
}