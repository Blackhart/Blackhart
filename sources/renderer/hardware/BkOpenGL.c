// Standard headers.
#include <stdlib.h>
#include <string.h>

// Glew headers.
#include <GL\glew.h>

// Blackhart.foundation headers.
#include "foundation\BkError.h"
#include "foundation\BkString.h"
#include "foundation\BkFileSystem.h"
#include "foundation\BkCamera.h"

// Blackhart.renderer headers.
#include "renderer\hardware\__BkOpenGL.h"
#include "renderer\hardware\__BkOpenGLBuffer.h"
#include "renderer\hardware\__BkOpenGLShader.h"

// ~~~~~ Def(INTERNAL) ~~~~~

static GLuint				__BkOpenGL_VertexArrayObject = 0;
static struct BkOpenGLShaderProgram*	__BkOpenGL_ShaderProgram = NULL;
static struct BkOpenGLShader*		__BkOpenGL_VertexShader = NULL;
static struct BkOpenGLShader*		__BkOpenGL_PixelShader = NULL;
static struct BkOpenGLBuffer*		__BkOpenGL_Buffer = NULL;

void	_BkOpenGL_Initialize(void)
{
	BkError_PushContext("In OpenGL Initialization");

	// Initialize GLEW
	GLenum result = GLEW_OK;

	result = glewInit();
	BK_ERROR(result != GLEW_OK, BkString_CreateFormatted("Glew error : %s\nFailed to initialize OpenGL!", glewGetErrorString(result)));

	// Create VAO
	glGenVertexArrays(1, &__BkOpenGL_VertexArrayObject);
	glBindVertexArray(__BkOpenGL_VertexArrayObject);

	char* path = malloc((strlen(BK_DEFAULT_SHADER_PATH) + 15) * sizeof(char));
	BK_ERROR(BK_ISNULL(path), "Memory system has failed to allocate memory block");

	// Create vertex shader
	BkFileSystem_CombinePath(path, BK_DEFAULT_SHADER_PATH, "vertex.glsl");
	__BkOpenGL_VertexShader = _BkOpenGL_CreateShader(path, _BK_VERTEX_SHADER_);

	// Create fragment shader
	BkFileSystem_CombinePath(path, BK_DEFAULT_SHADER_PATH, "pixel.glsl");
	__BkOpenGL_PixelShader = _BkOpenGL_CreateShader(path, _BK_PIXEL_SHADER_);

	// Create material
	__BkOpenGL_ShaderProgram = _BkOpenGL_CreateShaderProgram(__BkOpenGL_VertexShader, __BkOpenGL_PixelShader);

	_BkOpenGL_ReleaseShader(&__BkOpenGL_VertexShader);
	_BkOpenGL_ReleaseShader(&__BkOpenGL_PixelShader);

	// Create vertex buffer containing a simple triangle
	real const vertices[108] = { 
		-1.0f,-1.0f,1.0f, // triangle 1 : begin
		-1.0f,-1.0f, -1.0f,
		-1.0f, 1.0f, -1.0f, // triangle 1 : end
		1.0f, 1.0f,1.0f, // triangle 2 : begin
		-1.0f,-1.0f,1.0f,
		-1.0f, 1.0f,1.0f, // triangle 2 : end
		1.0f,-1.0f, -1.0f,
		-1.0f,-1.0f,1.0f,
		1.0f,-1.0f,1.0f,
		1.0f, 1.0f,1.0f,
		1.0f,-1.0f,1.0f,
		-1.0f,-1.0f,1.0f,
		-1.0f,-1.0f,1.0f,
		-1.0f, 1.0f, -1.0f,
		-1.0f, 1.0f,1.0f,
		1.0f,-1.0f, -1.0f,
		-1.0f,-1.0f, -1.0f,
		-1.0f,-1.0f,1.0f,
		-1.0f, 1.0f, -1.0f,
		-1.0f,-1.0f, -1.0f,
		1.0f,-1.0f, -1.0f,
		1.0f, 1.0f, -1.0f,
		1.0f,-1.0f,1.0f,
		1.0f, 1.0f,1.0f,
		1.0f,-1.0f,1.0f,
		1.0f, 1.0f, -1.0f,
		1.0f,-1.0f, -1.0f,
		1.0f, 1.0f, -1.0f,
		1.0f, 1.0f,1.0f,
		-1.0f, 1.0f,1.0f,
		1.0f, 1.0f, -1.0f,
		-1.0f, 1.0f,1.0f,
		-1.0f, 1.0f, -1.0f,
		1.0f, 1.0f, -1.0f,
		-1.0f, 1.0f, -1.0f,
		1.0f,-1.0f, -1.0f
	};

	__BkOpenGL_Buffer = _BkOpenGL_CreateBuffer(108 * sizeof(real), vertices);

	glBindBuffer(GL_ARRAY_BUFFER, __BkOpenGL_Buffer->id);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	BkError_PopContext();
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
	static real const clear_color[4] = { 0.0f, 0.0f, 0.0f, 1.0f };

	glClearBufferfv(GL_COLOR, 0, clear_color);

	glUseProgram(__BkOpenGL_ShaderProgram->id);

	struct BkMatrix4x4 mvp = BkMatrix4x4_Mul_BkMatrix4x4(&(camera->projection), &(camera->transform.world_to_cam));

	glUniformMatrix4fv(glGetUniformLocation(__BkOpenGL_ShaderProgram->id, "uni_mvp"), 1, GL_TRUE, &(mvp.m11));

	glDrawArrays(GL_TRIANGLES, 0, 36);
}