// Standard headers.
#include <stdlib.h>

// Blackhart headers.
#include "foundation/BkError.h"
#include "foundation/BkList.h"
#include "renderer/BkGpuCache.h"
#include "renderer/BkRenderer.h"
#include "renderer/BkScene.h"

// ~~~~~ Type Definitions ~~~~~

struct BkScene {
  struct BkList* clouds;
};

// ~~~~~ Def(PUBLIC) ~~~~~

BkScene* BkScene_Create(void) {
  BkScene* scene = malloc(sizeof(BkScene));
  BK_ERROR(BK_ISNULL(scene),
           ((struct BkErrorInfo){
               .what = "Cannot create scene",
               .why = "Out of memory while allocating BkScene",
               .how = "Free memory and retry",
               .result = "BkScene_Create returned NULL",
           }),
           NULL);

  scene->clouds = NULL;
  return scene;
}

void BkScene_Release(BkScene** scene) {
  BK_ASSERT(BK_ISNULL(scene));
  BK_ASSERT(BK_ISNULL(*scene));

  BkList_Clear((*scene)->clouds);
  (*scene)->clouds = NULL;

  free(*scene);
  *scene = NULL;
}

void BkScene_AddCloud(BkScene* scene, BkPointCloud* cloud) {
  BK_ASSERT(BK_ISNULL(scene));
  BK_ASSERT(BK_ISNULL(cloud));

  scene->clouds = BkList_PushBack(scene->clouds, cloud);
}

void BkScene_RemoveCloud(BkScene* scene, BkPointCloud* cloud) {
  BK_ASSERT(BK_ISNULL(scene));

  scene->clouds = BkList_Erase(scene->clouds, cloud);
  _BkGpuCache_MarkDirty(_BkRender_GetGpuCache(), cloud);
}

size_t BkScene_GetCloudCount(BkScene const* scene) {
  BK_ASSERT(BK_ISNULL(scene));
  return (size_t)BkList_Size(scene->clouds);
}

BkPointCloud* BkScene_GetCloud(BkScene const* scene, size_t const index) {
  BK_ASSERT(BK_ISNULL(scene));

  struct BkList* link = BkList_Get(scene->clouds, (uint32)index);
  if (BkList_Empty(link)) {
    return NULL;
  }

  return (BkPointCloud*)BkList_Data(link);
}
