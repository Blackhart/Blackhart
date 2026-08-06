// Glew library headers.
#include <GL/glew.h>

// blackhart headers.
#include "foundation/BkError.h"
#include "foundation/BkMatrix4x4.h"
#include "foundation/BkPoint3.h"
#include "renderer/BkDebugDraw.h"

// ~~~~~ Type Definitions ~~~~~

typedef struct __BkDebugVertex {
  float x;
  float y;
  float z;
  float r;
  float g;
  float b;
} __BkDebugVertex;

// ~~~~~ Def(INTERNAL) ~~~~~

static GLuint __BkDebugVao = 0;
static GLuint __BkDebugVbo = 0;

static real const __BK_DEBUG_AXIS_LEN_MIN = BK_REAL(0.001);

static void __BkDebugDraw_EnsureGpu(void) {
  if (__BkDebugVao != 0) {
    return;
  }

  glGenVertexArrays(1, &__BkDebugVao);
  glBindVertexArray(__BkDebugVao);

  glGenBuffers(1, &__BkDebugVbo);
  glBindBuffer(GL_ARRAY_BUFFER, __BkDebugVbo);
  glBufferData(GL_ARRAY_BUFFER, 24 * sizeof(__BkDebugVertex), NULL,
               GL_DYNAMIC_DRAW);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(__BkDebugVertex),
                        (void*)0);
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(__BkDebugVertex),
                        (void*)(3 * sizeof(float)));

  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

static void __BkDebugDraw_UploadAndDraw(__BkDebugVertex const* verts,
                                        GLsizei vertex_count,
                                        struct BkMatrix4x4 const* mvp,
                                        int uni_mvp) {
  __BkDebugDraw_EnsureGpu();

  glUniformMatrix4fv((GLint)uni_mvp, 1, GL_TRUE, &(mvp->m11));

  glBindVertexArray(__BkDebugVao);
  glBindBuffer(GL_ARRAY_BUFFER, __BkDebugVbo);
  glBufferSubData(GL_ARRAY_BUFFER, 0,
                  (GLsizeiptr)(vertex_count * sizeof(__BkDebugVertex)), verts);
  glDrawArrays(GL_LINES, 0, vertex_count);
  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

static void __BkDebugDraw_PushLine(__BkDebugVertex* verts, size_t* count,
                                   struct BkPoint3 const* a,
                                   struct BkPoint3 const* b, float r, float g,
                                   float bcol) {
  verts[*count].x = (float)a->x;
  verts[*count].y = (float)a->y;
  verts[*count].z = (float)a->z;
  verts[*count].r = r;
  verts[*count].g = g;
  verts[*count].b = bcol;
  ++(*count);

  verts[*count].x = (float)b->x;
  verts[*count].y = (float)b->y;
  verts[*count].z = (float)b->z;
  verts[*count].r = r;
  verts[*count].g = g;
  verts[*count].b = bcol;
  ++(*count);
}

void _BkDebugDraw_Initialize(void) {
  __BkDebugVao = 0;
  __BkDebugVbo = 0;
}

void _BkDebugDraw_Uninitialize(void) {
  if (__BkDebugVao != 0) {
    glDeleteVertexArrays(1, &__BkDebugVao);
    __BkDebugVao = 0;
  }
  if (__BkDebugVbo != 0) {
    glDeleteBuffers(1, &__BkDebugVbo);
    __BkDebugVbo = 0;
  }
}

void _BkDebugDraw_Axes(struct BkMatrix4x4 const* pv, int uni_mvp,
                       struct BkTransform* transform, real length) {
  BK_ASSERT(BK_ISNULL(pv));
  BK_ASSERT(BK_ISNULL(transform));

  if (length < __BK_DEBUG_AXIS_LEN_MIN) {
    length = __BK_DEBUG_AXIS_LEN_MIN;
  }

  struct BkMatrix4x4 const* model = BkTransform_Matrix(transform);
  struct BkMatrix4x4 const mvp = BkMatrix4x4_Mul_BkMatrix4x4(pv, model);

  struct BkPoint3 const o = {BK_REAL(0), BK_REAL(0), BK_REAL(0)};
  struct BkPoint3 const x = {length, BK_REAL(0), BK_REAL(0)};
  struct BkPoint3 const y = {BK_REAL(0), length, BK_REAL(0)};
  struct BkPoint3 const z = {BK_REAL(0), BK_REAL(0), length};

  __BkDebugVertex verts[6];
  size_t count = 0;
  __BkDebugDraw_PushLine(verts, &count, &o, &x, 0.90f, 0.25f, 0.25f);
  __BkDebugDraw_PushLine(verts, &count, &o, &y, 0.30f, 0.85f, 0.35f);
  __BkDebugDraw_PushLine(verts, &count, &o, &z, 0.30f, 0.50f, 0.95f);

  GLfloat previous_width = 1.0f;
  glGetFloatv(GL_LINE_WIDTH, &previous_width);
  glLineWidth(2.0f);
  __BkDebugDraw_UploadAndDraw(verts, (GLsizei)count, &mvp, uni_mvp);
  glLineWidth(previous_width);
}

void _BkDebugDraw_Aabb(struct BkMatrix4x4 const* pv, int uni_mvp,
                       struct BkAABB const* aabb) {
  BK_ASSERT(BK_ISNULL(pv));
  BK_ASSERT(BK_ISNULL(aabb));

  struct BkPoint3 const c000 = {aabb->min.x, aabb->min.y, aabb->min.z};
  struct BkPoint3 const c001 = {aabb->min.x, aabb->min.y, aabb->max.z};
  struct BkPoint3 const c010 = {aabb->min.x, aabb->max.y, aabb->min.z};
  struct BkPoint3 const c011 = {aabb->min.x, aabb->max.y, aabb->max.z};
  struct BkPoint3 const c100 = {aabb->max.x, aabb->min.y, aabb->min.z};
  struct BkPoint3 const c101 = {aabb->max.x, aabb->min.y, aabb->max.z};
  struct BkPoint3 const c110 = {aabb->max.x, aabb->max.y, aabb->min.z};
  struct BkPoint3 const c111 = {aabb->max.x, aabb->max.y, aabb->max.z};

  float const r = 0.95f;
  float const g = 0.75f;
  float const b = 0.20f;

  __BkDebugVertex verts[24];
  size_t count = 0;
  __BkDebugDraw_PushLine(verts, &count, &c000, &c100, r, g, b);
  __BkDebugDraw_PushLine(verts, &count, &c100, &c110, r, g, b);
  __BkDebugDraw_PushLine(verts, &count, &c110, &c010, r, g, b);
  __BkDebugDraw_PushLine(verts, &count, &c010, &c000, r, g, b);
  __BkDebugDraw_PushLine(verts, &count, &c001, &c101, r, g, b);
  __BkDebugDraw_PushLine(verts, &count, &c101, &c111, r, g, b);
  __BkDebugDraw_PushLine(verts, &count, &c111, &c011, r, g, b);
  __BkDebugDraw_PushLine(verts, &count, &c011, &c001, r, g, b);
  __BkDebugDraw_PushLine(verts, &count, &c000, &c001, r, g, b);
  __BkDebugDraw_PushLine(verts, &count, &c100, &c101, r, g, b);
  __BkDebugDraw_PushLine(verts, &count, &c110, &c111, r, g, b);
  __BkDebugDraw_PushLine(verts, &count, &c010, &c011, r, g, b);

  __BkDebugDraw_UploadAndDraw(verts, (GLsizei)count, pv, uni_mvp);
}
