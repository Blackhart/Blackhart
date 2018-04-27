// Standard headers.
#include <stdlib.h>

// Glew headers.
#include <GL\glew.h>

// blackhart headers.
#include "foundation\BkError.h"
#include "renderer\BkOpenGLBuffer.h"

// ~~~~~ Def(INTERNAL) ~~~~~

struct BkOpenGLBuffer*	_BkOpenGL_CreateBuffer(size_t const size, void const* data)
{
    struct BkOpenGLBuffer* opengl_buffer = malloc(sizeof(struct BkOpenGLBuffer));
    BK_ERROR(BK_ISNULL(opengl_buffer), "Memory system failed to allocate memory block");

	glGenBuffers(1, &opengl_buffer->id);
	glBindBuffer(GL_ARRAY_BUFFER, opengl_buffer->id);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	return opengl_buffer;
}

void	_BkOpenGL_ReleaseBuffer(struct BkOpenGLBuffer** opengl_buffer)
{
	BK_ASSERT(BK_ISNULL(opengl_buffer));
	BK_ASSERT(BK_ISNULL(*opengl_buffer));

	glDeleteBuffers(1, &(*opengl_buffer)->id);

	free(*opengl_buffer);
	*opengl_buffer = NULL;
}