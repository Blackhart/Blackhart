#include "core\BkArray.h"

#include "renderer\hardware\__BkOpenGL.h"
#include "renderer\hardware\__BkOpenGLBuffer.h"
#include "renderer\hardware\__BkOpenGLShader.h"

// ~~~~~ Dcl(INTERNAL) ~~~~~

static GLuint				__BkOpenGL_VertexArrayObject = 0;
static struct BkOpenGLShaderProgram*	__BkOpenGL_ShaderProgram = NULL;
static struct BkOpenGLShader*		__BkOpenGL_VertexShader = NULL;
static struct BkOpenGLShader*		__BkOpenGL_PixelShader = NULL;
static struct BkOpenGLBuffer*		__BkOpenGL_Buffer = NULL;

// ~~~~~ Def(ALL) ~~~~~

BkResult	_BkOpenGL_Initialize(void)
{
	// Initialize GLEW
	GLenum result = GLEW_OK;

	result = glewInit();
	if (result != GLEW_OK)
		BkDie(BK_ERROR_LOCATION "Glew error : %s\nFailed to initialize OpenGL!", glewGetErrorString(result));

	// Create VAO
	glGenVertexArrays(1, &__BkOpenGL_VertexArrayObject);
	glBindVertexArray(__BkOpenGL_VertexArrayObject);

	// Create vertex shader
	__BkOpenGL_VertexShader = _BkOpenGL_CreateShader("../../../shaders/vertex.glsl", _BK_VERTEX_SHADER_);
	if (BK_ISNULL(__BkOpenGL_VertexShader))
	{
		glDeleteVertexArrays(1, &__BkOpenGL_VertexArrayObject);
		return BK_FAILURE;
	}

	// Create fragment shader
	__BkOpenGL_PixelShader = _BkOpenGL_CreateShader("../../../shaders/pixel.glsl", _BK_PIXEL_SHADER_);
	if (BK_ISNULL(__BkOpenGL_PixelShader))
	{
		_BkOpenGL_ReleaseShader(&__BkOpenGL_VertexShader);
		glDeleteVertexArrays(1, &__BkOpenGL_VertexArrayObject);
		return BK_FAILURE;
	}

	// Create material
	__BkOpenGL_ShaderProgram = _BkOpenGL_CreateShaderProgram(__BkOpenGL_VertexShader, __BkOpenGL_PixelShader);
	if (BK_ISNULL(__BkOpenGL_ShaderProgram))
	{
		_BkOpenGL_ReleaseShader(&__BkOpenGL_VertexShader);
		_BkOpenGL_ReleaseShader(&__BkOpenGL_PixelShader);
		glDeleteVertexArrays(1, &__BkOpenGL_VertexArrayObject);
		return BK_FAILURE;
	}

	_BkOpenGL_ReleaseShader(&__BkOpenGL_VertexShader);
	_BkOpenGL_ReleaseShader(&__BkOpenGL_PixelShader);

	// Create vertex buffer containing a simple triangle
	real const vertices[12] = { 0.25f, -0.25f, 0.5f, 1.0f, -0.25f, -0.25f, 0.5f, 1.0f, 0.25f, 0.25f, 0.5f, 1.0f };

	__BkOpenGL_Buffer = _BkOpenGL_CreateBuffer(12 * sizeof(real), vertices);
	if (BK_ISNULL(__BkOpenGL_Buffer))
	{
		_BkOpenGL_ReleaseShaderProgram(&__BkOpenGL_ShaderProgram);
		glDeleteVertexArrays(1, &__BkOpenGL_VertexArrayObject);
		return BK_FAILURE;
	}

	glBindBuffer(GL_ARRAY_BUFFER, __BkOpenGL_Buffer->id);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	return BK_SUCCESS;
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

void	_BkOpenGL_Render(void)
{
	static real const clear_color[4] = { 0.0f, 0.0f, 0.0f, 1.0f };

	glClearBufferfv(GL_COLOR, 0, clear_color);

	glUseProgram(__BkOpenGL_ShaderProgram->id);

	glDrawArrays(GL_TRIANGLES, 0, 3);
}