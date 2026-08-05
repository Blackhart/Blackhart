// Standard headers.
#include <stdlib.h>

// Glew headers.
#include <GL/glew.h>

// Blackhart headers.
#include "foundation/BkError.h"
#include "foundation/BkPoint3.h"
#include "renderer/BkBuffer.h"
#include "renderer/BkGpuPointCloud.h"
#include "renderer/BkPointCloud.h"

// ~~~~~ Type Definitions ~~~~~

struct BkGpuPointCloud {
  GLuint vao;
  BkBuffer* buffer;
  size_t count;
};

// ~~~~~ Def(INTERNAL) ~~~~~

BkGpuPointCloud* _BkGpuPointCloud_Upload(BkPointCloud const* cloud) {
  BK_ERROR(BK_ISNULL(cloud),
           ((struct BkErrorInfo){
               .what = "Cannot upload point cloud to GPU",
               .why = "cloud argument is NULL",
               .how = "Pass a valid BkPointCloud created from PLY or data",
               .result = "_BkGpuPointCloud_Upload returned NULL",
           }),
           NULL);

  size_t const count = BkPointCloud_GetCount(cloud);
  BK_ERROR(count == 0,
           ((struct BkErrorInfo){
               .what = "Cannot upload point cloud to GPU",
               .why = "Point cloud has zero points",
               .how = "Load a PLY with at least one vertex",
               .result = "_BkGpuPointCloud_Upload returned NULL",
           }),
           NULL);

  BkPoint3 const* points = BkPointCloud_GetPoints(cloud);
  BK_ERROR(BK_ISNULL(points),
           ((struct BkErrorInfo){
               .what = "Cannot upload point cloud to GPU",
               .why = "BkPointCloud_GetPoints returned NULL",
               .how = "Ensure the point cloud was loaded successfully",
               .result = "_BkGpuPointCloud_Upload returned NULL",
           }),
           NULL);

  BkGpuPointCloud* gpu = malloc(sizeof(BkGpuPointCloud));
  BK_ERROR(BK_ISNULL(gpu),
           ((struct BkErrorInfo){
               .what = "Cannot allocate GPU point cloud",
               .why = "Out of memory while allocating BkGpuPointCloud",
               .how = "Free memory and retry",
               .result = "_BkGpuPointCloud_Upload returned NULL",
           }),
           NULL);

  gpu->count = count;
  gpu->vao = 0;
  gpu->buffer = NULL;

  size_t const bytes = count * sizeof(BkPoint3);
  gpu->buffer = _BkBuffer_Create(bytes, points);
  if (BK_ISNULL(gpu->buffer)) {
    free(gpu);
    BK_ERROR(true,
             ((struct BkErrorInfo){
                 .what = "Cannot create point cloud VBO",
                 .why = "_BkBuffer_Create failed",
                 .how = "Check OpenGL context and available GPU memory",
                 .result = "_BkGpuPointCloud_Upload returned NULL",
             }),
             NULL);
  }

  glGenVertexArrays(1, &gpu->vao);
  glBindVertexArray(gpu->vao);

  glBindBuffer(GL_ARRAY_BUFFER, (GLuint)_BkBuffer_GetId(gpu->buffer));
#ifdef __BK_DOUBLE_PRECISION_FLOATING_POINT
  glVertexAttribPointer(0, 3, GL_DOUBLE, GL_FALSE, sizeof(BkPoint3), NULL);
#else
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(BkPoint3), NULL);
#endif
  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  return gpu;
}

void _BkGpuPointCloud_Release(BkGpuPointCloud** gpu) {
  BK_ASSERT(BK_ISNULL(gpu));
  BK_ASSERT(BK_ISNULL(*gpu));

  if ((*gpu)->vao != 0) {
    glDeleteVertexArrays(1, &(*gpu)->vao);
    (*gpu)->vao = 0;
  }

  if ((*gpu)->buffer != NULL) {
    _BkBuffer_Release(&(*gpu)->buffer);
  }

  free(*gpu);
  *gpu = NULL;
}

void _BkGpuPointCloud_Render(BkGpuPointCloud const* gpu) {
  BK_ASSERT(BK_ISNULL(gpu));
  BK_ASSERT(gpu->vao == 0);
  BK_ASSERT(gpu->count == 0);

  glBindVertexArray(gpu->vao);
  glDrawArrays(GL_POINTS, 0, (GLsizei)gpu->count);
  glBindVertexArray(0);
}
