// Standard headers.
#include <stdlib.h>

// Blackhart headers.
#include "foundation/BkError.h"
#include "foundation/BkList.h"
#include "renderer/BkGpuCache.h"
#include "renderer/BkGpuPointCloud.h"

// ~~~~~ Type Definitions ~~~~~

typedef struct BkGpuCacheEntry {
  BkPointCloud const* cloud;
  BkGpuPointCloud* gpu;
  bool dirty;
} BkGpuCacheEntry;

struct BkGpuCache {
  struct BkList* entries;
};

// ~~~~~ Def(INTERNAL) ~~~~~

static struct BkList* __BkGpuCache_FindLink(BkGpuCache const* cache,
                                            BkPointCloud const* cloud) {
  struct BkList* it = BkList_Front(cache->entries);
  while (!BkList_Empty(it)) {
    BkGpuCacheEntry* entry = (BkGpuCacheEntry*)BkList_Data(it);
    if (entry->cloud == cloud) {
      return it;
    }
    it = BkList_Next(it);
  }
  return NULL;
}

static void __BkGpuCache_ReleaseEntry(BkGpuCacheEntry* entry) {
  if (entry == NULL) {
    return;
  }

  if (entry->gpu != NULL) {
    _BkGpuPointCloud_Release(&entry->gpu);
  }

  free(entry);
}

BkGpuCache* _BkGpuCache_Create(void) {
  BkGpuCache* cache = malloc(sizeof(BkGpuCache));
  BK_ERROR(BK_ISNULL(cache),
           ((struct BkErrorInfo){
               .what = "Cannot create GPU cache",
               .why = "Out of memory while allocating BkGpuCache",
               .how = "Free memory and retry",
               .result = "_BkGpuCache_Create returned NULL",
           }),
           NULL);

  cache->entries = NULL;
  return cache;
}

void _BkGpuCache_Destroy(BkGpuCache** cache) {
  BK_ASSERT(BK_ISNULL(cache));
  BK_ASSERT(BK_ISNULL(*cache));

  _BkGpuCache_Clear(*cache);
  free(*cache);
  *cache = NULL;
}

BkGpuPointCloud* _BkGpuCache_GetOrUpload(BkGpuCache* cache,
                                         BkPointCloud const* cloud) {
  BK_ERROR(BK_ISNULL(cache),
           ((struct BkErrorInfo){
               .what = "Cannot resolve GPU point cloud",
               .why = "cache argument is NULL",
               .how = "Create a cache with _BkGpuCache_Create first",
               .result = "_BkGpuCache_GetOrUpload returned NULL",
           }),
           NULL);

  BK_ERROR(BK_ISNULL(cloud),
           ((struct BkErrorInfo){
               .what = "Cannot resolve GPU point cloud",
               .why = "cloud argument is NULL",
               .how = "Pass a valid BkPointCloud",
               .result = "_BkGpuCache_GetOrUpload returned NULL",
           }),
           NULL);

  struct BkList* link = __BkGpuCache_FindLink(cache, cloud);
  if (!BkList_Empty(link)) {
    BkGpuCacheEntry* entry = (BkGpuCacheEntry*)BkList_Data(link);
    entry->dirty = false;
    return entry->gpu;
  }

  BkGpuPointCloud* gpu = _BkGpuPointCloud_Upload(cloud);
  BK_ERROR(BK_ISNULL(gpu),
           ((struct BkErrorInfo){
               .what = "Cannot resolve GPU point cloud",
               .why = "_BkGpuPointCloud_Upload failed",
               .how = "Check OpenGL context and point cloud content",
               .result = "_BkGpuCache_GetOrUpload returned NULL",
           }),
           NULL);

  BkGpuCacheEntry* entry = malloc(sizeof(BkGpuCacheEntry));
  if (BK_ISNULL(entry)) {
    _BkGpuPointCloud_Release(&gpu);
    BK_ERROR(true,
             ((struct BkErrorInfo){
                 .what = "Cannot cache GPU point cloud",
                 .why = "Out of memory while allocating BkGpuCacheEntry",
                 .how = "Free memory and retry",
                 .result = "_BkGpuCache_GetOrUpload returned NULL",
             }),
             NULL);
  }

  entry->cloud = cloud;
  entry->gpu = gpu;
  entry->dirty = false;
  cache->entries = BkList_PushBack(cache->entries, entry);
  return gpu;
}

void _BkGpuCache_MarkDirty(BkGpuCache* cache, BkPointCloud const* cloud) {
  if (BK_ISNULL(cache) || BK_ISNULL(cloud)) {
    return;
  }

  struct BkList* link = __BkGpuCache_FindLink(cache, cloud);
  if (BkList_Empty(link)) {
    return;
  }

  BkGpuCacheEntry* entry = (BkGpuCacheEntry*)BkList_Data(link);
  entry->dirty = true;
}

void _BkGpuCache_FlushDirty(BkGpuCache* cache) {
  BK_ASSERT(BK_ISNULL(cache));

  struct BkList* it = BkList_Front(cache->entries);
  while (!BkList_Empty(it)) {
    struct BkList* next = BkList_Next(it);
    BkGpuCacheEntry* entry = (BkGpuCacheEntry*)BkList_Data(it);

    if (entry->dirty) {
      __BkGpuCache_ReleaseEntry(entry);
      cache->entries = BkList_EraseLink(it);
    }

    it = next;
  }
}

void _BkGpuCache_Remove(BkGpuCache* cache, BkPointCloud const* cloud) {
  BK_ASSERT(BK_ISNULL(cache));

  if (BK_ISNULL(cloud)) {
    return;
  }

  struct BkList* link = __BkGpuCache_FindLink(cache, cloud);
  if (BkList_Empty(link)) {
    return;
  }

  BkGpuCacheEntry* entry = (BkGpuCacheEntry*)BkList_Data(link);
  __BkGpuCache_ReleaseEntry(entry);
  cache->entries = BkList_EraseLink(link);
}

void _BkGpuCache_Clear(BkGpuCache* cache) {
  BK_ASSERT(BK_ISNULL(cache));

  struct BkList* it = BkList_Front(cache->entries);
  while (!BkList_Empty(it)) {
    struct BkList* next = BkList_Next(it);
    BkGpuCacheEntry* entry = (BkGpuCacheEntry*)BkList_Data(it);
    __BkGpuCache_ReleaseEntry(entry);
    it = next;
  }

  BkList_Clear(cache->entries);
  cache->entries = NULL;
}

bool _BkGpuCache_HasEntry(BkGpuCache const* cache, BkPointCloud const* cloud) {
  if (BK_ISNULL(cache) || BK_ISNULL(cloud)) {
    return false;
  }

  return !BkList_Empty(__BkGpuCache_FindLink(cache, cloud));
}

bool _BkGpuCache_IsDirty(BkGpuCache const* cache, BkPointCloud const* cloud) {
  if (BK_ISNULL(cache) || BK_ISNULL(cloud)) {
    return false;
  }

  struct BkList* link = __BkGpuCache_FindLink(cache, cloud);
  if (BkList_Empty(link)) {
    return false;
  }

  return ((BkGpuCacheEntry*)BkList_Data(link))->dirty;
}
