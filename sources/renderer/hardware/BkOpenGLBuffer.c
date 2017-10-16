#include "core\BkError.h"

#include "renderer\hardware\__BkOpenGLBuffer.h"

// ~~~~~ Def(ALL) ~~~~~

struct BkOpenGLBuffer*	_BkOpenGL_CreateBuffer(uint32 const size, void const* data)
{
	struct BkOpenGLBuffer* opengl_buffer = malloc(sizeof(struct BkOpenGLBuffer));
	if (BK_ISNULL(opengl_buffer))
		BkDie(BK_ERROR_LOCATION "Memory system failed to allocate memory block");

	glGenBuffers(1, &opengl_buffer->id);
	glBindBuffer(GL_ARRAY_BUFFER, opengl_buffer->id);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	return opengl_buffer;
}

void	_BkOpenGL_ReleaseBuffer(struct BkOpenGLBuffer** opengl_buffer)
{
	assert(!BK_ISNULL(opengl_buffer));
	assert(!BK_ISNULL(*opengl_buffer));

	glDeleteBuffers(1, &(*opengl_buffer)->id);

	free(*opengl_buffer);
	*opengl_buffer = NULL;
}