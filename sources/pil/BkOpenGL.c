#include "pil\BkOpenGL.h"
#include "core\BkShader.h"

#include "pil\__BkOpenGL.h"

// ~~~~~ Dcl(INTERNAL) ~~~~~

static GLuint	__BkOpenGL_VertexArrayObject = 0;

// ~~~~~ Def(ALL) ~~~~~

BkResult	_BkOpenGL_Initialize(void)
{
	GLenum	lResult = GLEW_OK; // 4 bytes

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

void	_BkOpenGL_Render(void* pBufferAPI, void* pMaterialAPI)
{
	assert(!BK_ISNULL(pBufferAPI));
	assert(!BK_ISNULL(pMaterialAPI));

	static real const	lClearColor[4] = { 0.0f, 0.0f, 0.0f, 1.0f }; // Float precision: 16 bytes | Double precision: 32 bytes
	
	glClearBufferfv(GL_COLOR, 0, lClearColor);

	glUseProgram(((BkOpenGLProgram*)pMaterialAPI)->programID);
	
	BkOpenGLBuffer*	lpOpenGLBuffer = pBufferAPI; // 4 bytes
	glBindBuffer(GL_ARRAY_BUFFER, lpOpenGLBuffer->bufferID);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);
	
	glDrawArrays(GL_TRIANGLES, 0, 3);

	glDisableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void	_BkOpenGL_CreateShader(void** ppShaderAPI, BkShaderType const Type, char const* pShaderContent)
{
	assert(!BK_ISNULL(ppShaderAPI));
	assert(!BK_ISNULL(pShaderContent));
	assert(Type == _BK_PIXEL_SHADER_ || Type == _BK_VERTEX_SHADER_);

	BkOpenGLShader*	lpShader = malloc(sizeof(BkOpenGLShader)); // 4 bytes
	if (lpShader == NULL)
		BkDie(BK_ERROR_LOCATION "Memory system failed to allocate memory");

	if (Type == _BK_VERTEX_SHADER_)
		lpShader->shaderID = glCreateShader(GL_VERTEX_SHADER);
	else if (Type == _BK_PIXEL_SHADER_)
		lpShader->shaderID = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(lpShader->shaderID, 1, &pShaderContent, NULL);
	glCompileShader(lpShader->shaderID);

	*ppShaderAPI = lpShader;
}

void	_BkOpenGL_ReleaseShader(void** ppShaderAPI)
{
	assert(!BK_ISNULL(ppShaderAPI));
	assert(!BK_ISNULL(*ppShaderAPI));

	BkOpenGLShader*	lpShader = *ppShaderAPI; // 4 bytes

	glDeleteShader(lpShader->shaderID);

	free(*ppShaderAPI);
	*ppShaderAPI = NULL;
}

void	_BkOpenGL_CreateShaderProgram(void** ppMaterialAPI, void* pVertexShaderAPI, void* pPixelShaderAPI)
{
	assert(!BK_ISNULL(ppMaterialAPI));
	assert(!BK_ISNULL(pVertexShaderAPI));
	assert(!BK_ISNULL(pPixelShaderAPI));

	BkOpenGLShader*		lPixelShader = pPixelShaderAPI; // 4 bytes
	BkOpenGLShader*		lVertexShader = pVertexShaderAPI; // 4 bytes

	BkOpenGLProgram*	lpProgram = malloc(sizeof(BkOpenGLProgram)); // 4 bytes
	if (BK_ISNULL(lpProgram))
		BkDie(BK_ERROR_LOCATION "Memory system failed to allocate memory block");

	lpProgram->programID = glCreateProgram();
	glAttachShader(lpProgram->programID, lVertexShader->shaderID);
	glAttachShader(lpProgram->programID, lPixelShader->shaderID);
	glLinkProgram(lpProgram->programID);

	*ppMaterialAPI = lpProgram;
}

void	_BkOpenGL_ReleaseShaderProgram(void** ppMaterialAPI)
{
	assert(!BK_ISNULL(ppMaterialAPI));
	assert(!BK_ISNULL(*ppMaterialAPI));

	BkOpenGLProgram*	lProgram = *ppMaterialAPI; // 4 bytes

	glDeleteProgram(lProgram->programID);

	free(*ppMaterialAPI);
	*ppMaterialAPI = NULL;
}

void	_BkOpenGL_CreateBuffer(void** ppBufferAPI, uint32 const Size, void const* pData)
{
	assert(!BK_ISNULL(ppBufferAPI));

	*ppBufferAPI = malloc(sizeof(BkOpenGLBuffer));
	if (BK_ISNULL(*ppBufferAPI))
		BkDie(BK_ERROR_LOCATION "Memory system failed to allocate memory block");

	BkOpenGLBuffer*	lpBuffer = *ppBufferAPI; // 4 bytes

	glGenBuffers(1, &lpBuffer->bufferID);
	glBindBuffer(GL_ARRAY_BUFFER, lpBuffer->bufferID);
	glBufferData(GL_ARRAY_BUFFER, Size, pData, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void	_BkOpenGL_ReleaseBuffer(void** ppBufferAPI)
{
	assert(!BK_ISNULL(ppBufferAPI));
	assert(!BK_ISNULL(*ppBufferAPI));

	BkOpenGLBuffer*	lpBuffer = *ppBufferAPI; // 4 bytes

	glDeleteBuffers(1, &lpBuffer->bufferID);

	free(*ppBufferAPI);
	*ppBufferAPI = NULL;
}