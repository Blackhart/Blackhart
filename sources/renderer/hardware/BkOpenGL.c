#include "core\BkList.h"
#include "core\BkScene.h"
#include "core\BkEntity.h"
#include "core\BkGeometry.h"

#include "renderer\hardware\__BkOpenGL.h"
#include "renderer\hardware\__BkOpenGLBuffer.h"
#include "renderer\hardware\__BkOpenGLShader.h"

// ~~~~~ Dcl(INTERNAL) ~~~~~

static GLuint	__BkOpenGL_VertexArrayObject = 0;

// ~~~~~ Def(ALL) ~~~~~

BkResult	_BkOpenGL_Initialize(void)
{
	GLenum result = GLEW_OK;

	result = glewInit();
	if (result != GLEW_OK)
		BkDie(BK_ERROR_LOCATION "Glew error : %s\nFailed to initialize OpenGL!", glewGetErrorString(result));

	glGenVertexArrays(1, &__BkOpenGL_VertexArrayObject);
	glBindVertexArray(__BkOpenGL_VertexArrayObject);

	return BK_SUCCESS;
}

void	_BkOpenGL_Uninitialize(void)
{
	glDeleteVertexArrays(1, &__BkOpenGL_VertexArrayObject);
}

void	_BkOpenGL_Render(void)
{
	static real const clear_color[4] = { 0.0f, 0.0f, 0.0f, 1.0f };

	glClearBufferfv(GL_COLOR, 0, clear_color);

	// Create vertex shader
	struct BkOpenGLShader* vertex_shader = _BkOpenGL_CreateShader("../../../shaders/vertex.glsl", _BK_VERTEX_SHADER_);
	if (BK_ISNULL(vertex_shader))
		goto EXIT;

	// Create fragment shader
	struct BkOpenGLShader* pixel_shader = _BkOpenGL_CreateShader("../../../shaders/pixel.glsl", _BK_PIXEL_SHADER_);
	if (BK_ISNULL(pixel_shader))
		goto RENDERER_RELEASE_VERTEX_SHADER;

	// Create material
	struct BkOpenGLShaderProgram* shader_program = _BkOpenGL_CreateShaderProgram(vertex_shader, pixel_shader);
	if (BK_ISNULL(shader_program))
		goto RENDERER_RELEASE_PIXEL_SHADER;

	glUseProgram(shader_program->id);

	struct BkList const* list = BkScene_GetEntities();
	struct BkOpenGLBuffer* opengl_buffer = NULL;
	real* vertices = NULL;

	while (list != NULL)
	{
		vertices = ((struct BkGeometry*)((struct BkEntity*)list->data)->geometry)->vertices;

		opengl_buffer = _BkOpenGL_CreateBuffer(12 * sizeof(real*), vertices);
		if (BK_ISNULL(opengl_buffer))
			goto RENDERER_RELEASE_MATERIAL;

		glBindBuffer(GL_ARRAY_BUFFER, opengl_buffer->id);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, NULL);
		glEnableVertexAttribArray(0);

		glDrawArrays(GL_TRIANGLES, 0, 3);

		glDisableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		_BkOpenGL_ReleaseBuffer(&opengl_buffer);

		list = list->next;
	}

RENDERER_RELEASE_MATERIAL:
	_BkOpenGL_ReleaseShaderProgram(&shader_program);

RENDERER_RELEASE_PIXEL_SHADER:
	_BkOpenGL_ReleaseShader(&pixel_shader);

RENDERER_RELEASE_VERTEX_SHADER:
	_BkOpenGL_ReleaseShader(&vertex_shader);

EXIT:
	return;
}