// Standard headers.
#include <stdio.h>
#include <stdlib.h>

// Unity headers.
#include <unity.h>

// Blackhart headers.
#include "blackhart.h"
#include "renderer/BkPointCloud.h"
#include "renderer/BkScene.h"

// Test headers.
#include "renderer/BkScene_test.h"

// ~~~~~ Def(INTERNAL) ~~~~~

static char const* __BkScene_WriteTempPly(char const* basename) {
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

static void __BkScene_RemoveFile(char const* path) {
  if (path != NULL) {
    remove(path);
  }
}

static BkPointCloud* __BkScene_LoadTempCloud(char const* basename) {
  char const* path = __BkScene_WriteTempPly(basename);
  BkPointCloud* cloud = BkPointCloud_CreateFromPlyFile(path);
  __BkScene_RemoveFile(path);
  TEST_ASSERT_NOT_NULL(cloud);
  return cloud;
}

// ~~~~~ Def(PUBLIC) ~~~~~

void BkScene_RunTests(void) {
  RUN_TEST(BkScene_CreateRelease_test);
  RUN_TEST(BkScene_AddGetRemoveCloud_test);
  RUN_TEST(BkScene_RemoveCloud_NotInScene_test);
  RUN_TEST(BkScene_GetCloud_OutOfRange_test);
  RUN_TEST(BkScene_Release_DoesNotFreeClouds_test);
}

void BkScene_CreateRelease_test(void) {
  BkScene* scene = BkScene_Create();
  TEST_ASSERT_NOT_NULL(scene);
  TEST_ASSERT_EQUAL_UINT(0, (unsigned)BkScene_GetCloudCount(scene));
  TEST_ASSERT_NULL(BkScene_GetCloud(scene, 0));

  BkScene_Release(&scene);
  TEST_ASSERT_NULL(scene);
}

void BkScene_AddGetRemoveCloud_test(void) {
  BkScene* scene = BkScene_Create();
  BkPointCloud* a = __BkScene_LoadTempCloud("blackhart_scene_a.ply");
  BkPointCloud* b = __BkScene_LoadTempCloud("blackhart_scene_b.ply");

  BkScene_AddCloud(scene, a);
  BkScene_AddCloud(scene, b);
  TEST_ASSERT_EQUAL_UINT(2, (unsigned)BkScene_GetCloudCount(scene));
  TEST_ASSERT_EQUAL_PTR(a, BkScene_GetCloud(scene, 0));
  TEST_ASSERT_EQUAL_PTR(b, BkScene_GetCloud(scene, 1));
  TEST_ASSERT_NULL(BkScene_GetCloud(scene, 2));

  /* RemoveCloud also MarkDirty on renderer cache (NULL if not initialized). */
  BkScene_RemoveCloud(scene, a);
  TEST_ASSERT_EQUAL_UINT(1, (unsigned)BkScene_GetCloudCount(scene));
  TEST_ASSERT_EQUAL_PTR(b, BkScene_GetCloud(scene, 0));

  BkScene_RemoveCloud(scene, b);
  TEST_ASSERT_EQUAL_UINT(0, (unsigned)BkScene_GetCloudCount(scene));

  BkPointCloud_Release(&a);
  BkPointCloud_Release(&b);
  BkScene_Release(&scene);
}

void BkScene_RemoveCloud_NotInScene_test(void) {
  BkScene* scene = BkScene_Create();
  BkPointCloud* cloud = __BkScene_LoadTempCloud("blackhart_scene_orphan.ply");

  BkScene_RemoveCloud(scene, cloud);
  TEST_ASSERT_EQUAL_UINT(0, (unsigned)BkScene_GetCloudCount(scene));

  BkPointCloud_Release(&cloud);
  BkScene_Release(&scene);
}

void BkScene_GetCloud_OutOfRange_test(void) {
  BkScene* scene = BkScene_Create();
  BkPointCloud* cloud = __BkScene_LoadTempCloud("blackhart_scene_range.ply");

  BkScene_AddCloud(scene, cloud);
  TEST_ASSERT_NULL(BkScene_GetCloud(scene, 1));
  TEST_ASSERT_NULL(BkScene_GetCloud(scene, 99));

  BkScene_RemoveCloud(scene, cloud);
  BkPointCloud_Release(&cloud);
  BkScene_Release(&scene);
}

void BkScene_Release_DoesNotFreeClouds_test(void) {
  BkScene* scene = BkScene_Create();
  BkPointCloud* cloud = __BkScene_LoadTempCloud("blackhart_scene_owned.ply");

  BkScene_AddCloud(scene, cloud);
  BkScene_Release(&scene);

  /* Cloud must still be usable after the scene is released. */
  TEST_ASSERT_EQUAL_UINT(1, (unsigned)BkPointCloud_GetCount(cloud));
  BkPointCloud_Release(&cloud);
}
