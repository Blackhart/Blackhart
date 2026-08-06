// Standard library headers.
#include <math.h>
#include <stdlib.h>

// Glew library headers.
#include <GL/glew.h>

// blackhart headers.
#include "foundation/BkError.h"
#include "renderer/BkGrid.h"

// ~~~~~ Type Definitions ~~~~~

typedef struct __BkGridVertex {
  float x;
  float y;
  float z;
  float r;
  float g;
  float b;
} __BkGridVertex;

// ~~~~~ Def(INTERNAL) ~~~~~

static bool __BkGridVisible = true;
static real __BkGridCellSize = BK_REAL(1);
static bool __BkGridDirty = true;
static GLuint __BkGridVao = 0;
static GLuint __BkGridVbo = 0;
static GLsizei __BkGridVertexCount = 0;

static real const __BK_GRID_CELL_SIZE_MIN = BK_REAL(0.01);
static real const __BK_GRID_EXTENT = BK_REAL(10);

static void __BkGrid_DestroyMesh(void) {
  if (__BkGridVao != 0) {
    glDeleteVertexArrays(1, &__BkGridVao);
    __BkGridVao = 0;
  }
  if (__BkGridVbo != 0) {
    glDeleteBuffers(1, &__BkGridVbo);
    __BkGridVbo = 0;
  }
  __BkGridVertexCount = 0;
}

static void __BkGrid_PushLine(__BkGridVertex* verts, size_t* count, float x0,
                              float y0, float z0, float x1, float y1, float z1,
                              float r, float g, float b) {
  verts[*count].x = x0;
  verts[*count].y = y0;
  verts[*count].z = z0;
  verts[*count].r = r;
  verts[*count].g = g;
  verts[*count].b = b;
  ++(*count);

  verts[*count].x = x1;
  verts[*count].y = y1;
  verts[*count].z = z1;
  verts[*count].r = r;
  verts[*count].g = g;
  verts[*count].b = b;
  ++(*count);
}

static void __BkGrid_BuildMesh(void) {
  __BkGrid_DestroyMesh();

  real const cell = __BkGridCellSize;
  real const extent = __BK_GRID_EXTENT;

  size_t const lines_per_axis = (size_t)((extent * BK_REAL(2)) / cell) + 3;
  size_t const max_verts = lines_per_axis * 2 * 2;

  __BkGridVertex* verts = malloc(max_verts * sizeof(__BkGridVertex));
  BK_FATAL(BK_ISNULL(verts),
           ((struct BkErrorInfo){
               .what = "Fatal error",
               .why = "Memory system has failed to allocate memory block",
               .result = "Process aborted",
           }));

  size_t count = 0;
  float const dark_r = 0.22f;
  float const dark_g = 0.22f;
  float const dark_b = 0.24f;
  float const axis_r = 0.45f;
  float const axis_g = 0.45f;
  float const axis_b = 0.48f;

  for (real t = -extent; t <= extent + cell * BK_REAL(0.5); t += cell) {
    if (count + 4 > max_verts) {
      break;
    }
    float const ft = (float)t;
    int const on_axis = (fabs((double)t) < (double)(cell * BK_REAL(0.001)));
    float const r = on_axis ? axis_r : dark_r;
    float const g = on_axis ? axis_g : dark_g;
    float const b = on_axis ? axis_b : dark_b;

    __BkGrid_PushLine(verts, &count, (float)-extent, 0.0f, ft, (float)extent,
                      0.0f, ft, r, g, b);
    __BkGrid_PushLine(verts, &count, ft, 0.0f, (float)-extent, ft, 0.0f,
                      (float)extent, r, g, b);
  }

  glGenVertexArrays(1, &__BkGridVao);
  glBindVertexArray(__BkGridVao);

  glGenBuffers(1, &__BkGridVbo);
  glBindBuffer(GL_ARRAY_BUFFER, __BkGridVbo);
  glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr)(count * sizeof(__BkGridVertex)),
               verts, GL_STATIC_DRAW);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(__BkGridVertex),
                        (void*)0);
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(__BkGridVertex),
                        (void*)(3 * sizeof(float)));

  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  free(verts);
  __BkGridVertexCount = (GLsizei)count;
  __BkGridDirty = false;
}

void _BkGrid_Initialize(void) { __BkGridDirty = true; }

void _BkGrid_Uninitialize(void) { __BkGrid_DestroyMesh(); }

void _BkGrid_SetVisible(bool visible) { __BkGridVisible = visible; }

bool _BkGrid_IsVisible(void) { return __BkGridVisible; }

void _BkGrid_SetCellSize(real cell_size) {
  if (cell_size < __BK_GRID_CELL_SIZE_MIN) {
    cell_size = __BK_GRID_CELL_SIZE_MIN;
  }
  if (cell_size != __BkGridCellSize) {
    __BkGridCellSize = cell_size;
    __BkGridDirty = true;
  }
}

real _BkGrid_GetCellSize(void) { return __BkGridCellSize; }

void _BkGrid_Draw(struct BkMatrix4x4 const* pv, int uni_mvp) {
  BK_ASSERT(BK_ISNULL(pv));

  if (!__BkGridVisible) {
    return;
  }

  if (__BkGridDirty || __BkGridVao == 0) {
    __BkGrid_BuildMesh();
  }

  if (__BkGridVertexCount == 0) {
    return;
  }

  glUniformMatrix4fv((GLint)uni_mvp, 1, GL_TRUE, &(pv->m11));
  glBindVertexArray(__BkGridVao);
  glDrawArrays(GL_LINES, 0, __BkGridVertexCount);
  glBindVertexArray(0);
}
