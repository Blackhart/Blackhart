#include "pil\BkFileSystem.h"

#include "core\BkString.h"

#include "renderer\hardware\__BkOpenGLShader.h"

// ~~~~~ Def(ALL) ~~~~~

BkOpenGLShader*	_BkOpenGL_CreateShader(char const* pPath, BkShaderType const Type)
{
	assert(!BK_ISNULL(pPath));

	BkStringBuf	lContentBuf; // 8 bytes

	BkStringBuf_Set(&lContentBuf, NULL);

	if (BK_ERROR(BkFileSystem_ReadFromPath(pPath, &(lContentBuf.buf), &(lContentBuf.bufSize))))
	{
		BkError(BK_ERROR_LOCATION "Failed to load shader from flux [ $%s$ ]");
		return NULL;
	}

	BkOpenGLShader*	lpShader = malloc(sizeof(BkOpenGLShader)); // 4 bytes
	if (lpShader == NULL)
		BkDie(BK_ERROR_LOCATION "Memory system failed to allocate memory");

	if (Type == _BK_VERTEX_SHADER_)
		lpShader->shaderID = glCreateShader(GL_VERTEX_SHADER);
	else if (Type == _BK_PIXEL_SHADER_)
		lpShader->shaderID = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(lpShader->shaderID, 1, &(lContentBuf.buf), NULL);
	glCompileShader(lpShader->shaderID);

	BkStringBuf_Release(&lContentBuf);

	return lpShader;
}

void	_BkOpenGL_ReleaseShader(BkOpenGLShader** ppShader)
{
	assert(!BK_ISNULL(ppShader));
	assert(!BK_ISNULL(*ppShader));

	glDeleteShader((*ppShader)->shaderID);

	free(*ppShader);
	*ppShader = NULL;
}

BkOpenGLShaderProgram*	_BkOpenGL_CreateShaderProgram(BkOpenGLShader* pVertexShader, BkOpenGLShader* pPixelShader)
{
	assert(!BK_ISNULL(pVertexShader));
	assert(!BK_ISNULL(pPixelShader));

	BkOpenGLShaderProgram*	lpProgram = malloc(sizeof(BkOpenGLShaderProgram)); // 4 bytes
	if (BK_ISNULL(lpProgram))
		BkDie(BK_ERROR_LOCATION "Memory system failed to allocate memory block");

	lpProgram->programID = glCreateProgram();
	glAttachShader(lpProgram->programID, pVertexShader->shaderID);
	glAttachShader(lpProgram->programID, pPixelShader->shaderID);
	glLinkProgram(lpProgram->programID);

	return lpProgram;
}

void	_BkOpenGL_ReleaseShaderProgram(BkOpenGLShaderProgram** ppShaderProgram)
{
	assert(!BK_ISNULL(ppShaderProgram));
	assert(!BK_ISNULL(*ppShaderProgram));

	glDeleteProgram((*ppShaderProgram)->programID);

	free(*ppShaderProgram);
	*ppShaderProgram = NULL;
}