// Glew library headers.
#include <GL/glew.h>

// blackhart headers.
#include "foundation/BkCamera.h"
#include "foundation/BkError.h"
#include "foundation/BkProjection.h"
#include "renderer/BkGizmo.h"

// ~~~~~ Type Definitions ~~~~~

typedef struct __BkGizmoVertex {
  float x;
  float y;
  float z;
  float r;
  float g;
  float b;
} __BkGizmoVertex;

// ~~~~~ Def(INTERNAL) ~~~~~

static bool __BkGizmoVisible = true;
static bool __BkGizmoDirty = true;
static GLuint __BkGizmoVao = 0;
static GLuint __BkGizmoVbo = 0;
static GLsizei __BkGizmoVertexCount = 0;

static int const __BK_GIZMO_WIDGET_SIZE = 96;
static int const __BK_GIZMO_WIDGET_MARGIN = 14;
static real const __BK_GIZMO_CAMERA_DISTANCE = BK_REAL(2.75);
static real const __BK_GIZMO_FOV_DEG = BK_REAL(32);

static void __BkGizmo_DestroyMesh(void) {
  if (__BkGizmoVao != 0) {
    glDeleteVertexArrays(1, &__BkGizmoVao);
    __BkGizmoVao = 0;
  }
  if (__BkGizmoVbo != 0) {
    glDeleteBuffers(1, &__BkGizmoVbo);
    __BkGizmoVbo = 0;
  }
  __BkGizmoVertexCount = 0;
}

static void __BkGizmo_BuildMesh(void) {
  __BkGizmo_DestroyMesh();

  float const len = 1.0f;
  __BkGizmoVertex const verts[6] = {
      {0.0f, 0.0f, 0.0f, 0.90f, 0.25f, 0.25f},
      {len, 0.0f, 0.0f, 0.90f, 0.25f, 0.25f},
      {0.0f, 0.0f, 0.0f, 0.30f, 0.85f, 0.35f},
      {0.0f, len, 0.0f, 0.30f, 0.85f, 0.35f},
      {0.0f, 0.0f, 0.0f, 0.30f, 0.50f, 0.95f},
      {0.0f, 0.0f, len, 0.30f, 0.50f, 0.95f},
  };

  glGenVertexArrays(1, &__BkGizmoVao);
  glBindVertexArray(__BkGizmoVao);

  glGenBuffers(1, &__BkGizmoVbo);
  glBindBuffer(GL_ARRAY_BUFFER, __BkGizmoVbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(__BkGizmoVertex),
                        (void*)0);
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(__BkGizmoVertex),
                        (void*)(3 * sizeof(float)));

  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  __BkGizmoVertexCount = 6;
  __BkGizmoDirty = false;
}

void _BkGizmo_Initialize(void) { __BkGizmoDirty = true; }

void _BkGizmo_Uninitialize(void) { __BkGizmo_DestroyMesh(); }

void _BkGizmo_SetVisible(bool visible) { __BkGizmoVisible = visible; }

bool _BkGizmo_IsVisible(void) { return __BkGizmoVisible; }

void _BkGizmo_Draw(BkCamera* camera, int uni_mvp) {
  BK_ASSERT(BK_ISNULL(camera));

  if (!__BkGizmoVisible) {
    return;
  }

  if (__BkGizmoDirty || __BkGizmoVao == 0) {
    __BkGizmo_BuildMesh();
  }

  if (__BkGizmoVertexCount == 0) {
    return;
  }

  GLint viewport[4] = {0, 0, 0, 0};
  glGetIntegerv(GL_VIEWPORT, viewport);

  int const size = __BK_GIZMO_WIDGET_SIZE;
  int const margin = __BK_GIZMO_WIDGET_MARGIN;
  int const widget_x = viewport[0] + margin;
  int const widget_y = viewport[1] + margin;

  if (widget_x + size > viewport[0] + viewport[2] ||
      widget_y + size > viewport[1] + viewport[3]) {
    return;
  }

  // Orientation-only view: strip camera translation, then pull back so the
  // unit axes at the origin are visible in the corner projection.
  struct BkMatrix4x4 view = BkCamera_ViewMatrix(camera);
  view.m14 = BK_REAL(0);
  view.m24 = BK_REAL(0);
  view.m34 = BK_REAL(0);

  struct BkMatrix4x4 const pull = BkMatrix4x4_Translation_XYZ(
      BK_REAL(0), BK_REAL(0), -__BK_GIZMO_CAMERA_DISTANCE);
  struct BkMatrix4x4 const v = BkMatrix4x4_Mul_BkMatrix4x4(&pull, &view);
  struct BkMatrix4x4 const proj = BkProjection_Perspective(
      __BK_GIZMO_FOV_DEG, BK_REAL(1), BK_REAL(0.1), BK_REAL(10));
  struct BkMatrix4x4 const mvp = BkMatrix4x4_Mul_BkMatrix4x4(&proj, &v);

  GLboolean const depth_was_enabled = glIsEnabled(GL_DEPTH_TEST);
  GLfloat previous_width = 1.0f;
  glGetFloatv(GL_LINE_WIDTH, &previous_width);

  glEnable(GL_SCISSOR_TEST);
  glScissor(widget_x, widget_y, size, size);
  glClear(GL_DEPTH_BUFFER_BIT);
  glDisable(GL_SCISSOR_TEST);

  glViewport(widget_x, widget_y, size, size);
  glEnable(GL_DEPTH_TEST);
  glLineWidth(2.5f);

  glUniformMatrix4fv((GLint)uni_mvp, 1, GL_TRUE, &(mvp.m11));
  glBindVertexArray(__BkGizmoVao);
  glDrawArrays(GL_LINES, 0, __BkGizmoVertexCount);
  glBindVertexArray(0);

  glLineWidth(previous_width);
  glViewport(viewport[0], viewport[1], viewport[2], viewport[3]);
  if (!depth_was_enabled) {
    glDisable(GL_DEPTH_TEST);
  }
}
