// Standard headers.
#include <stdlib.h>

// Glew headers.
#include <GL\glew.h>

// blackhart headers.
#include "foundation\BkError.h"
#include "renderer\BkBuffer.h"

// ~~~~~ Def(INTERNAL) ~~~~~

struct BkBuffer*	_BkBuffer_Create(size_t const size, void const* data)
{
    BK_ASSERT(size == 0);
    BK_ASSERT(BK_ISNULL(data));

    struct BkBuffer* buffer = malloc(sizeof(struct BkBuffer));
    BK_ERROR(BK_ISNULL(buffer), "Memory system failed to allocate memory block");

	glGenBuffers(1, &(buffer->id));
	glBindBuffer(GL_ARRAY_BUFFER, buffer->id);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	return buffer;
}

void	_BkBuffer_Release(struct BkBuffer** buffer)
{
	BK_ASSERT(BK_ISNULL(buffer));
	BK_ASSERT(BK_ISNULL(*buffer));

	glDeleteBuffers(1, &((*buffer)->id));

	free(*buffer);
	*buffer = NULL;
}