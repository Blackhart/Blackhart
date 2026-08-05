// Standard headers.
#include <stdio.h>
#include <stdlib.h>

// Unity headers.
#include <unity.h>

// Blackhart headers.
#include "blackhart.h"
#include "renderer/BkGpuCache.h"
#include "renderer/BkPointCloud.h"

// Test headers.
#include "renderer/BkGpuCache_test.h"

// ~~~~~ Def(INTERNAL) ~~~~~

static char const* __BkGpuCache_WriteTempPly(char const* basename) {
  static char path[512];

  snprintf(path, sizeof(path), "/tmp/%s", basename);

  FILE* file = fopen(path, "w");
  TEST_ASSERT_NOT_NULL(file);
  fputs(
      "ply\n"
      "format ascii 1.0\n"
      "element vertex 1\n"
      "property float x\n"
      "property float y\n"
      "property float z\n"
      "end_header\n"
      "0 0 0\n",
      file);
  fclose(file);

  return path;
}

static void __BkGpuCache_RemoveFile(char const* path) {
  if (path != NULL) {
    remove(path);
  }
}

static BkPointCloud* __BkGpuCache_LoadTempCloud(char const* basename) {
  char const* path = __BkGpuCache_WriteTempPly(basename);
  BkPointCloud* cloud = BkPointCloud_CreateFromPlyFile(path);
  __BkGpuCache_RemoveFile(path);
  TEST_ASSERT_NOT_NULL(cloud);
  return cloud;
}

// ~~~~~ Def(PUBLIC) ~~~~~

void BkGpuCache_RunTests(void) {
  RUN_TEST(BkGpuCache_CreateDestroy_test);
  RUN_TEST(BkGpuCache_HasEntry_Empty_test);
  RUN_TEST(BkGpuCache_MarkDirty_NoEntry_test);
  RUN_TEST(BkGpuCache_MarkDirty_NullArgs_test);
  RUN_TEST(BkGpuCache_FlushDirty_Empty_test);
  RUN_TEST(BkGpuCache_Remove_NoEntry_test);
  RUN_TEST(BkGpuCache_Clear_Empty_test);
  RUN_TEST(BkGpuCache_Query_NullArgs_test);
}

void BkGpuCache_CreateDestroy_test(void) {
  BkGpuCache* cache = _BkGpuCache_Create();
  TEST_ASSERT_NOT_NULL(cache);

  _BkGpuCache_Destroy(&cache);
  TEST_ASSERT_NULL(cache);
}

void BkGpuCache_HasEntry_Empty_test(void) {
  BkGpuCache* cache = _BkGpuCache_Create();
  BkPointCloud* cloud =
      __BkGpuCache_LoadTempCloud("blackhart_gpucache_empty.ply");

  TEST_ASSERT_FALSE(_BkGpuCache_HasEntry(cache, cloud));
  TEST_ASSERT_FALSE(_BkGpuCache_IsDirty(cache, cloud));

  BkPointCloud_Release(&cloud);
  _BkGpuCache_Destroy(&cache);
}

void BkGpuCache_MarkDirty_NoEntry_test(void) {
  BkGpuCache* cache = _BkGpuCache_Create();
  BkPointCloud* cloud =
      __BkGpuCache_LoadTempCloud("blackhart_gpucache_nodirty.ply");

  _BkGpuCache_MarkDirty(cache, cloud);

  TEST_ASSERT_FALSE(_BkGpuCache_HasEntry(cache, cloud));
  TEST_ASSERT_FALSE(_BkGpuCache_IsDirty(cache, cloud));

  BkPointCloud_Release(&cloud);
  _BkGpuCache_Destroy(&cache);
}

void BkGpuCache_MarkDirty_NullArgs_test(void) {
  BkGpuCache* cache = _BkGpuCache_Create();
  BkPointCloud* cloud =
      __BkGpuCache_LoadTempCloud("blackhart_gpucache_null.ply");

  _BkGpuCache_MarkDirty(NULL, cloud);
  _BkGpuCache_MarkDirty(cache, NULL);
  _BkGpuCache_MarkDirty(NULL, NULL);

  TEST_ASSERT_FALSE(_BkGpuCache_HasEntry(cache, cloud));
  TEST_ASSERT_FALSE(_BkGpuCache_IsDirty(cache, cloud));

  BkPointCloud_Release(&cloud);
  _BkGpuCache_Destroy(&cache);
}

void BkGpuCache_FlushDirty_Empty_test(void) {
  BkGpuCache* cache = _BkGpuCache_Create();
  BkPointCloud* cloud =
      __BkGpuCache_LoadTempCloud("blackhart_gpucache_flush.ply");

  _BkGpuCache_FlushDirty(cache);

  TEST_ASSERT_FALSE(_BkGpuCache_HasEntry(cache, cloud));

  BkPointCloud_Release(&cloud);
  _BkGpuCache_Destroy(&cache);
}

void BkGpuCache_Remove_NoEntry_test(void) {
  BkGpuCache* cache = _BkGpuCache_Create();
  BkPointCloud* cloud =
      __BkGpuCache_LoadTempCloud("blackhart_gpucache_remove.ply");

  _BkGpuCache_Remove(cache, cloud);
  _BkGpuCache_Remove(cache, NULL);

  TEST_ASSERT_FALSE(_BkGpuCache_HasEntry(cache, cloud));

  BkPointCloud_Release(&cloud);
  _BkGpuCache_Destroy(&cache);
}

void BkGpuCache_Clear_Empty_test(void) {
  BkGpuCache* cache = _BkGpuCache_Create();
  BkPointCloud* cloud =
      __BkGpuCache_LoadTempCloud("blackhart_gpucache_clear.ply");

  _BkGpuCache_Clear(cache);

  TEST_ASSERT_FALSE(_BkGpuCache_HasEntry(cache, cloud));

  BkPointCloud_Release(&cloud);
  _BkGpuCache_Destroy(&cache);
}

void BkGpuCache_Query_NullArgs_test(void) {
  BkPointCloud* cloud =
      __BkGpuCache_LoadTempCloud("blackhart_gpucache_query.ply");

  TEST_ASSERT_FALSE(_BkGpuCache_HasEntry(NULL, cloud));
  TEST_ASSERT_FALSE(_BkGpuCache_HasEntry(NULL, NULL));
  TEST_ASSERT_FALSE(_BkGpuCache_IsDirty(NULL, cloud));
  TEST_ASSERT_FALSE(_BkGpuCache_IsDirty(NULL, NULL));

  BkGpuCache* cache = _BkGpuCache_Create();
  TEST_ASSERT_FALSE(_BkGpuCache_HasEntry(cache, NULL));
  TEST_ASSERT_FALSE(_BkGpuCache_IsDirty(cache, NULL));

  _BkGpuCache_Destroy(&cache);
  BkPointCloud_Release(&cloud);
}
