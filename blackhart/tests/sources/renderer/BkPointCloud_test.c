// Standard headers.
#include <stdio.h>
#include <stdlib.h>

// Unity headers.
#include <unity.h>

// Blackhart headers.
#include "blackhart.h"
#include "renderer/BkPointCloud.h"

// Test headers.
#include "renderer/BkPointCloud_test.h"

static float const ERROR_LIMIT = 0.00001f;

static char const* const __BkPointCloud_ValidPly =
    "ply\n"
    "format ascii 1.0\n"
    "element vertex 3\n"
    "property float x\n"
    "property float y\n"
    "property float z\n"
    "end_header\n"
    "0 0 0\n"
    "1 2 3\n"
    "-1 4 -2\n";

// ~~~~~ Def(INTERNAL) ~~~~~

static char const* __BkPointCloud_WriteTempPly(char const* basename,
                                               char const* contents) {
  static char path[512];

  snprintf(path, sizeof(path), "/tmp/%s", basename);

  FILE* file = fopen(path, "w");
  TEST_ASSERT_NOT_NULL(file);
  fputs(contents, file);
  fclose(file);

  return path;
}

static void __BkPointCloud_RemoveFile(char const* path) {
  if (path != NULL) {
    remove(path);
  }
}

// ~~~~~ Def(PUBLIC) ~~~~~

void BkPointCloud_RunTests(void) {
  RUN_TEST(BkPointCloud_CreateFromPlyFile_Success_test);
  RUN_TEST(BkPointCloud_CreateFromPlyFile_NullFilename_test);
  RUN_TEST(BkPointCloud_CreateFromPlyFile_MissingFile_test);
  RUN_TEST(BkPointCloud_CreateFromPlyFile_InvalidPly_test);
  RUN_TEST(BkPointCloud_GetPoints_Contents_test);
  RUN_TEST(BkPointCloud_GetAABB_MatchesPoints_test);
  RUN_TEST(BkPointCloud_Release_SetsNull_test);
}

void BkPointCloud_CreateFromPlyFile_Success_test(void) {
  char const* path = __BkPointCloud_WriteTempPly("blackhart_pointcloud_ok.ply",
                                                 __BkPointCloud_ValidPly);

  BkPointCloud* cloud = BkPointCloud_CreateFromPlyFile(path);
  __BkPointCloud_RemoveFile(path);

  TEST_ASSERT_NOT_NULL(cloud);
  TEST_ASSERT_EQUAL_UINT(3, (unsigned)BkPointCloud_GetCount(cloud));
  TEST_ASSERT_NOT_NULL(BkPointCloud_GetPoints(cloud));

  BkPointCloud_Release(&cloud);
  TEST_ASSERT_NULL(cloud);
}

void BkPointCloud_CreateFromPlyFile_NullFilename_test(void) {
  TEST_ASSERT_NULL(BkPointCloud_CreateFromPlyFile(NULL));
}

void BkPointCloud_CreateFromPlyFile_MissingFile_test(void) {
  TEST_ASSERT_NULL(
      BkPointCloud_CreateFromPlyFile("/tmp/blackhart_pointcloud_missing.ply"));
}

void BkPointCloud_CreateFromPlyFile_InvalidPly_test(void) {
  char const* path = __BkPointCloud_WriteTempPly(
      "blackhart_pointcloud_invalid.ply", "this is not a ply file\n");

  BkPointCloud* cloud = BkPointCloud_CreateFromPlyFile(path);
  __BkPointCloud_RemoveFile(path);

  TEST_ASSERT_NULL(cloud);
}

void BkPointCloud_GetPoints_Contents_test(void) {
  char const* path = __BkPointCloud_WriteTempPly(
      "blackhart_pointcloud_points.ply", __BkPointCloud_ValidPly);

  BkPointCloud* cloud = BkPointCloud_CreateFromPlyFile(path);
  __BkPointCloud_RemoveFile(path);
  TEST_ASSERT_NOT_NULL(cloud);

  BkPoint3 const* points = BkPointCloud_GetPoints(cloud);
  TEST_ASSERT_NOT_NULL(points);

  TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)points[0].x, (float)0.0);
  TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)points[0].y, (float)0.0);
  TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)points[0].z, (float)0.0);
  TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)points[1].x, (float)1.0);
  TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)points[1].y, (float)2.0);
  TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)points[1].z, (float)3.0);
  TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)points[2].x, (float)-1.0);
  TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)points[2].y, (float)4.0);
  TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)points[2].z, (float)-2.0);

  BkPointCloud_Release(&cloud);
}

void BkPointCloud_GetAABB_MatchesPoints_test(void) {
  char const* path = __BkPointCloud_WriteTempPly(
      "blackhart_pointcloud_aabb.ply", __BkPointCloud_ValidPly);

  BkPointCloud* cloud = BkPointCloud_CreateFromPlyFile(path);
  __BkPointCloud_RemoveFile(path);
  TEST_ASSERT_NOT_NULL(cloud);

  BkAABB aabb = BkPointCloud_GetAABB(cloud);
  TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)aabb.min.x, (float)-1.0);
  TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)aabb.min.y, (float)0.0);
  TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)aabb.min.z, (float)-2.0);
  TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)aabb.max.x, (float)1.0);
  TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)aabb.max.y, (float)4.0);
  TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)aabb.max.z, (float)3.0);

  struct BkPoint3 center = BkAABB_Center(&aabb);
  TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)center.x, (float)0.0);
  TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)center.y, (float)2.0);
  TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)center.z, (float)0.5);

  BkPointCloud_Release(&cloud);
}

void BkPointCloud_Release_SetsNull_test(void) {
  char const* path =
      __BkPointCloud_WriteTempPly("blackhart_pointcloud_release.ply",
                                  "ply\n"
                                  "format ascii 1.0\n"
                                  "element vertex 1\n"
                                  "property float x\n"
                                  "property float y\n"
                                  "property float z\n"
                                  "end_header\n"
                                  "0 0 0\n");

  BkPointCloud* cloud = BkPointCloud_CreateFromPlyFile(path);
  __BkPointCloud_RemoveFile(path);
  TEST_ASSERT_NOT_NULL(cloud);

  BkPointCloud_Release(&cloud);
  TEST_ASSERT_NULL(cloud);
}
