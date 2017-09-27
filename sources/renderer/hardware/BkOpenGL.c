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
	GLenum	lResult = GLEW_OK;

	lResult = glewInit();
	if (lResult != GLEW_OK)
		BkDie(BK_ERROR_LOCATION "Glew error : %s\nFailed to initialize OpenGL!", glewGetErrorString(lResult));

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
	static real const	lClearColor[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
	
	glClearBufferfv(GL_COLOR, 0, lClearColor);

	// Create vertex shader
	BkOpenGLShader* lVertexShader = _BkOpenGL_CreateShader("../../../shaders/vertex.glsl", _BK_VERTEX_SHADER_);
	if (BK_ISNULL(lVertexShader))
		goto EXIT;

	// Create fragment shader
	BkOpenGLShader* lPixelShader = _BkOpenGL_CreateShader("../../../shaders/pixel.glsl", _BK_PIXEL_SHADER_);
	if (BK_ISNULL(lPixelShader))
		goto RENDERER_RELEASE_VERTEX_SHADER;

	// Create material
	BkOpenGLShaderProgram*	lpShaderProgram = _BkOpenGL_CreateShaderProgram(lVertexShader, lPixelShader);
	if (BK_ISNULL(lpShaderProgram))
		goto RENDERER_RELEASE_PIXEL_SHADER;

	glUseProgram(lpShaderProgram->programID);
	
	BkSimpleLinkedList const* lList = BkScene_GetEntities();
	BkOpenGLBuffer* lOpenGLBuffer = NULL;
	real* lVertices = NULL;

	while (lList != NULL)
	{
		lVertices = ((BkGeometry*)((BkEntity*)lList->elem)->geometry)->vertices;

		lOpenGLBuffer = _BkOpenGL_CreateBuffer(12 * sizeof(real*), lVertices);
		if (BK_ISNULL(lOpenGLBuffer))
			goto RENDERER_RELEASE_MATERIAL;

		glBindBuffer(GL_ARRAY_BUFFER, lOpenGLBuffer->bufferID);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, NULL);
		glEnableVertexAttribArray(0);

		glDrawArrays(GL_TRIANGLES, 0, 3);

		glDisableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		_BkOpenGL_ReleaseBuffer(&lOpenGLBuffer);

		lList = lList->next;
	}

RENDERER_RELEASE_MATERIAL:
	_BkOpenGL_ReleaseShaderProgram(&lpShaderProgram);

RENDERER_RELEASE_PIXEL_SHADER:
	_BkOpenGL_ReleaseShader(&lPixelShader);

RENDERER_RELEASE_VERTEX_SHADER:
	_BkOpenGL_ReleaseShader(&lVertexShader);

EXIT:
	return;
}