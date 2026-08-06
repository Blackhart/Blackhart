// Standard headers.
#include <stdlib.h>

// Glew headers.
#include <GL/glew.h>

// Blackhart headers.
#include "foundation/BkColor3.h"
#include "foundation/BkError.h"
#include "foundation/BkPoint3.h"
#include "renderer/BkBuffer.h"
#include "renderer/BkGpuPointCloud.h"
#include "renderer/BkPointCloud.h"

// ~~~~~ Type Definitions ~~~~~

struct BkGpuPointCloud {
  GLuint vao;
  BkBuffer* points;
  BkBuffer* colors;
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
  gpu->points = NULL;
  gpu->colors = NULL;

  size_t const point_bytes = count * sizeof(BkPoint3);
  gpu->points = _BkBuffer_Create(point_bytes, points);
  if (BK_ISNULL(gpu->points)) {
    free(gpu);
    BK_ERROR(true,
             ((struct BkErrorInfo){
                 .what = "Cannot create point cloud points VBO",
                 .why = "_BkBuffer_Create failed for points",
                 .how = "Check OpenGL context and available GPU memory",
                 .result = "_BkGpuPointCloud_Upload returned NULL",
             }),
             NULL);
  }

  BkColor3 const* src_colors = BkPointCloud_GetColors(cloud);
  BkColor3* fallback_colors = NULL;
  BkColor3 const* upload_colors = src_colors;

  if (BK_ISNULL(upload_colors)) {
    fallback_colors = malloc(count * sizeof(BkColor3));
    if (BK_ISNULL(fallback_colors)) {
      _BkBuffer_Release(&gpu->points);
      free(gpu);
      BK_ERROR(true,
               ((struct BkErrorInfo){
                   .what = "Cannot allocate fallback colors",
                   .why = "Out of memory while filling white colors",
                   .how = "Free memory and retry",
                   .result = "_BkGpuPointCloud_Upload returned NULL",
               }),
               NULL);
    }

    struct BkColor3 const white = BkColor3_White();
    for (size_t i = 0; i < count; ++i) {
      fallback_colors[i] = white;
    }
    upload_colors = fallback_colors;
  }

  size_t const color_bytes = count * sizeof(BkColor3);
  gpu->colors = _BkBuffer_Create(color_bytes, upload_colors);
  free(fallback_colors);

  if (BK_ISNULL(gpu->colors)) {
    _BkBuffer_Release(&gpu->points);
    free(gpu);
    BK_ERROR(true,
             ((struct BkErrorInfo){
                 .what = "Cannot create point cloud color VBO",
                 .why = "_BkBuffer_Create failed for colors",
                 .how = "Check OpenGL context and available GPU memory",
                 .result = "_BkGpuPointCloud_Upload returned NULL",
             }),
             NULL);
  }

  glGenVertexArrays(1, &gpu->vao);
  glBindVertexArray(gpu->vao);

  glBindBuffer(GL_ARRAY_BUFFER, (GLuint)_BkBuffer_GetId(gpu->points));
#ifdef __BK_DOUBLE_PRECISION_FLOATING_POINT
  glVertexAttribPointer(0, 3, GL_DOUBLE, GL_FALSE, sizeof(BkPoint3), NULL);
#else
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(BkPoint3), NULL);
#endif
  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, (GLuint)_BkBuffer_GetId(gpu->colors));
  glVertexAttribPointer(1, 3, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(BkColor3),
                        NULL);
  glEnableVertexAttribArray(1);

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

  if ((*gpu)->points != NULL) {
    _BkBuffer_Release(&(*gpu)->points);
  }

  if ((*gpu)->colors != NULL) {
    _BkBuffer_Release(&(*gpu)->colors);
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
