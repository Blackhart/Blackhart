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
#include "renderer/BkPointCloud.h"
#include "renderer/BkRenderer.h"
#include "renderer/BkScene.h"
#include "renderer/BkShader.h"

// ~~~~~ Def(INTERNAL) ~~~~~

static BkShaderProgram* __BkShaderProgram = NULL;
static BkShader* __BkVertexShader = NULL;
static BkShader* __BkPixelShader = NULL;
static BkGpuCache* __BkGpuCache = NULL;

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

  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);
}

void _BkRender_Uninitialize(void) {
  _BkGpuCache_Destroy(&__BkGpuCache);

  // Release the shader program and his shaders
  _BkShaderProgram_Release(&__BkShaderProgram);
}

BkGpuCache* _BkRender_GetGpuCache(void) { return __BkGpuCache; }

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

  glPointSize(2.0f);

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
}
