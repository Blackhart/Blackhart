#include "core\BkError.h"

#include "renderer\hardware\__BkOpenGLBuffer.h"

// ~~~~~ Def(ALL) ~~~~~

BkOpenGLBuffer*	_BkOpenGL_CreateBuffer(uint32 const Size, void const* pData)
{
	BkOpenGLBuffer* lOpenGLBuffer = malloc(sizeof(BkOpenGLBuffer));
	if (BK_ISNULL(lOpenGLBuffer))
		BkDie(BK_ERROR_LOCATION "Memory system failed to allocate memory block");

	glGenBuffers(1, &lOpenGLBuffer->bufferID);
	glBindBuffer(GL_ARRAY_BUFFER, lOpenGLBuffer->bufferID);
	glBufferData(GL_ARRAY_BUFFER, Size, pData, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	return lOpenGLBuffer;
}

void	_BkOpenGL_ReleaseBuffer(BkOpenGLBuffer** ppOpenGLBuffer)
{
	assert(!BK_ISNULL(ppOpenGLBuffer));
	assert(!BK_ISNULL(*ppOpenGLBuffer));

	glDeleteBuffers(1, &(*ppOpenGLBuffer)->bufferID);

	free(*ppOpenGLBuffer);
	*ppOpenGLBuffer = NULL;
}