// Standard library headers.
#include <stdlib.h>
#include <string.h>

// Glew library headers.
#include <GL/glew.h>

// blackhart headers.
#include "foundation/BkCamera.h"
#include "foundation/BkError.h"
#include "foundation/BkFileSystem.h"
#include "foundation/BkString.h"
#include "renderer/BkGpuCache.h"
#include "renderer/BkGpuPointCloud.h"
#include "renderer/BkGizmo.h"
#include "renderer/BkGrid.h"
#include "renderer/BkPointCloud.h"
#include "renderer/BkRenderer.h"
#include "renderer/BkScene.h"
#include "renderer/BkShader.h"

// ~~~~~ Def(INTERNAL) ~~~~~

static BkShaderProgram* __BkShaderProgram = NULL;
static BkShader* __BkVertexShader = NULL;
static BkShader* __BkPixelShader = NULL;
static BkGpuCache* __BkGpuCache = NULL;
static real __BkPointSize = BK_REAL(2);

static real const __BK_POINT_SIZE_MIN = BK_REAL(1);
static real const __BK_POINT_SIZE_MAX = BK_REAL(32);

void _BkRender_Initialize(void) {
  // Initialize GLEW
  GLenum result = GLEW_OK;

  result = glewInit();
  BK_FATAL(
      result != GLEW_OK,
      ((struct BkErrorInfo){
          .what = "Cannot initialize OpenGL",
          .why = BkString_CreateFormatted("GLEW error: %s",
                                          glewGetErrorString(result)),
          .how =
              "Verify that a valid OpenGL context exists before BkInitialize",
          .result = "Process aborted",
      }));

  char* path = malloc((strlen(BK_DEFAULT_SHADER_PATH) + 15) * sizeof(char));
  BK_FATAL(BK_ISNULL(path),
           ((struct BkErrorInfo){
               .what = "Fatal error",
               .why = "Memory system has failed to allocate memory block",
               .result = "Process aborted",
           }));

  // Create vertex shader
  BkFileSystem_CombinePath(path, BK_DEFAULT_SHADER_PATH, "vertex.glsl");
  __BkVertexShader = _BkShader_Create(path, _BK_VERTEX_SHADER_);

  // Create fragment shader
  BkFileSystem_CombinePath(path, BK_DEFAULT_SHADER_PATH, "pixel.glsl");
  __BkPixelShader = _BkShader_Create(path, _BK_PIXEL_SHADER_);

  free(path);

  // Create material
  __BkShaderProgram = _BkShaderProgram_Create();
  _BkShaderProgram_AttachShader(__BkShaderProgram, __BkVertexShader);
  _BkShaderProgram_AttachShader(__BkShaderProgram, __BkPixelShader);
  _BkShaderProgram_Compile(__BkShaderProgram);

  _BkShader_Release(&__BkVertexShader);
  _BkShader_Release(&__BkPixelShader);

  __BkGpuCache = _BkGpuCache_Create();
  _BkGrid_Initialize();
  _BkGizmo_Initialize();

  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);
}

void _BkRender_Uninitialize(void) {
  _BkGizmo_Uninitialize();
  _BkGrid_Uninitialize();
  _BkGpuCache_Destroy(&__BkGpuCache);

  // Release the shader program and his shaders
  _BkShaderProgram_Release(&__BkShaderProgram);
}

BkGpuCache* _BkRender_GetGpuCache(void) { return __BkGpuCache; }

void BkRender_SetPointSize(real size) {
  if (size < __BK_POINT_SIZE_MIN) {
    size = __BK_POINT_SIZE_MIN;
  } else if (size > __BK_POINT_SIZE_MAX) {
    size = __BK_POINT_SIZE_MAX;
  }
  __BkPointSize = size;
}

real BkRender_GetPointSize(void) { return __BkPointSize; }

void BkRender_SetGridVisible(bool visible) { _BkGrid_SetVisible(visible); }

bool BkRender_IsGridVisible(void) { return _BkGrid_IsVisible(); }

void BkRender_SetGridCellSize(real cell_size) {
  _BkGrid_SetCellSize(cell_size);
}

real BkRender_GetGridCellSize(void) { return _BkGrid_GetCellSize(); }

void BkRender_SetGizmoVisible(bool visible) { _BkGizmo_SetVisible(visible); }

bool BkRender_IsGizmoVisible(void) { return _BkGizmo_IsVisible(); }

// ~~~~~ Def(PUBLIC) ~~~~~

void BkRender(BkScene* scene, BkCamera* camera) {
  static real const background[4] = {BK_REAL(0), BK_REAL(0), BK_REAL(0),
                                     BK_REAL(1)};

  BK_ASSERT(BK_ISNULL(scene));
  BK_ASSERT(BK_ISNULL(camera));

  if (!BK_ISNULL(__BkGpuCache)) {
    _BkGpuCache_FlushDirty(__BkGpuCache);
  }

  static GLfloat const clear_depth = 1.0f;

  glClearBufferfv(GL_COLOR, 0, background);
  glClearBufferfv(GL_DEPTH, 0, &clear_depth);

  GLuint const program = (GLuint)_BkShaderProgram_GetId(__BkShaderProgram);
  glUseProgram(program);

  struct BkMatrix4x4 const v = BkCamera_ViewMatrix(camera);
  struct BkMatrix4x4 const pv =
      BkMatrix4x4_Mul_BkMatrix4x4(BkCamera_Projection(camera), &v);

  GLint const uni_mvp = glGetUniformLocation(program, "uni_mvp");

  _BkGrid_Draw(&pv, (int)uni_mvp);

  glPointSize((GLfloat)__BkPointSize);

  size_t const cloud_count = BkScene_GetCloudCount(scene);
  for (size_t i = 0; i < cloud_count; ++i) {
    BkPointCloud* cloud = BkScene_GetCloud(scene, i);
    struct BkMatrix4x4 const* model =
        BkTransform_Matrix(BkPointCloud_GetTransform(cloud));
    struct BkMatrix4x4 const pvm = BkMatrix4x4_Mul_BkMatrix4x4(&pv, model);

    glUniformMatrix4fv(uni_mvp, 1, GL_TRUE, &(pvm.m11));

    BkGpuPointCloud* gpu = _BkGpuCache_GetOrUpload(__BkGpuCache, cloud);
    if (!BK_ISNULL(gpu)) {
      _BkGpuPointCloud_Render(gpu);
    }
  }

  // Corner orientation widget (after scene so it stays on top).
  _BkGizmo_Draw(camera, (int)uni_mvp);
}
