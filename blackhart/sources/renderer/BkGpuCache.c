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
  BkList* entries;
};

// ~~~~~ Def(INTERNAL) ~~~~~

static BkListNode* __BkGpuCache_FindNode(BkGpuCache const* cache,
                                         BkPointCloud const* cloud) {
  BkListNode* it = BkList_Begin((BkList*)cache->entries);
  while (it != NULL) {
    BkGpuCacheEntry* entry = (BkGpuCacheEntry*)BkList_NodeData(it);
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

  cache->entries = BkList_Create();
  if (BK_ISNULL(cache->entries)) {
    free(cache);
    return NULL;
  }

  return cache;
}

void _BkGpuCache_Destroy(BkGpuCache** cache) {
  BK_ASSERT(BK_ISNULL(cache));
  BK_ASSERT(BK_ISNULL(*cache));

  _BkGpuCache_Clear(*cache);
  BkList_Release(&(*cache)->entries);
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

  BkListNode* link = __BkGpuCache_FindNode(cache, cloud);
  if (link != NULL) {
    BkGpuCacheEntry* entry = (BkGpuCacheEntry*)BkList_NodeData(link);
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
  BkList_PushBack(cache->entries, entry);
  return gpu;
}

void _BkGpuCache_MarkDirty(BkGpuCache* cache, BkPointCloud const* cloud) {
  if (BK_ISNULL(cache) || BK_ISNULL(cloud)) {
    return;
  }

  BkListNode* link = __BkGpuCache_FindNode(cache, cloud);
  if (link == NULL) {
    return;
  }

  BkGpuCacheEntry* entry = (BkGpuCacheEntry*)BkList_NodeData(link);
  entry->dirty = true;
}

void _BkGpuCache_FlushDirty(BkGpuCache* cache) {
  BK_ASSERT(BK_ISNULL(cache));

  BkListNode* it = BkList_Begin(cache->entries);
  while (it != NULL) {
    BkGpuCacheEntry* entry = (BkGpuCacheEntry*)BkList_NodeData(it);

    if (entry->dirty) {
      __BkGpuCache_ReleaseEntry(entry);
      it = BkList_EraseNode(cache->entries, it);
    } else {
      it = BkList_Next(it);
    }
  }
}

void _BkGpuCache_Remove(BkGpuCache* cache, BkPointCloud const* cloud) {
  BK_ASSERT(BK_ISNULL(cache));

  if (BK_ISNULL(cloud)) {
    return;
  }

  BkListNode* link = __BkGpuCache_FindNode(cache, cloud);
  if (link == NULL) {
    return;
  }

  BkGpuCacheEntry* entry = (BkGpuCacheEntry*)BkList_NodeData(link);
  __BkGpuCache_ReleaseEntry(entry);
  BkList_EraseNode(cache->entries, link);
}

void _BkGpuCache_Clear(BkGpuCache* cache) {
  BK_ASSERT(BK_ISNULL(cache));

  BkListNode* it = BkList_Begin(cache->entries);
  while (it != NULL) {
    BkListNode* next = BkList_Next(it);
    BkGpuCacheEntry* entry = (BkGpuCacheEntry*)BkList_NodeData(it);
    __BkGpuCache_ReleaseEntry(entry);
    it = next;
  }

  BkList_Clear(cache->entries);
}

bool _BkGpuCache_HasEntry(BkGpuCache const* cache, BkPointCloud const* cloud) {
  if (BK_ISNULL(cache) || BK_ISNULL(cloud)) {
    return false;
  }

  return __BkGpuCache_FindNode(cache, cloud) != NULL;
}

bool _BkGpuCache_IsDirty(BkGpuCache const* cache, BkPointCloud const* cloud) {
  if (BK_ISNULL(cache) || BK_ISNULL(cloud)) {
    return false;
  }

  BkListNode* link = __BkGpuCache_FindNode(cache, cloud);
  if (link == NULL) {
    return false;
  }

  return ((BkGpuCacheEntry*)BkList_NodeData(link))->dirty;
}
