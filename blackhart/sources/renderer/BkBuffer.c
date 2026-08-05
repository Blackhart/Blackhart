// Standard headers.
#include <stdlib.h>

// Glew headers.
#include <GL/glew.h>

// blackhart headers.
#include "foundation/BkError.h"
#include "renderer/BkBuffer.h"

// ~~~~~ Type Definitions ~~~~~

struct BkBuffer {
  GLuint id;
};

// ~~~~~ Def(INTERNAL) ~~~~~

BkBuffer* _BkBuffer_Create(size_t const size, void const* data) {
  BK_ASSERT(size == 0);
  BK_ASSERT(BK_ISNULL(data));

  BkBuffer* buffer = malloc(sizeof(BkBuffer));
  BK_FATAL(BK_ISNULL(buffer),
           ((struct BkErrorInfo){
               .what = "Fatal error",
               .why = "Memory system failed to allocate memory block",
               .result = "Process aborted",
           }));

  glGenBuffers(1, &(buffer->id));
  glBindBuffer(GL_ARRAY_BUFFER, buffer->id);
  glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);

  glBindBuffer(GL_ARRAY_BUFFER, 0);

  return buffer;
}

void _BkBuffer_Release(BkBuffer** buffer) {
  BK_ASSERT(BK_ISNULL(buffer));
  BK_ASSERT(BK_ISNULL(*buffer));

  glDeleteBuffers(1, &((*buffer)->id));

  free(*buffer);
  *buffer = NULL;
}

uint32 _BkBuffer_GetId(BkBuffer const* buffer) {
  BK_ASSERT(BK_ISNULL(buffer));
  return (uint32)buffer->id;
}
