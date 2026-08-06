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
  RUN_TEST(BkPointCloud_GetWorldAABB_Identity_test);
  RUN_TEST(BkPointCloud_GetWorldAABB_AfterSetPosition_test);
  RUN_TEST(BkPointCloud_GetWorldAABB_AfterSetOrientation_test);
  RUN_TEST(BkPointCloud_Colors_Absent_test);
  RUN_TEST(BkPointCloud_Colors_Present_test);
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

void BkPointCloud_GetWorldAABB_Identity_test(void) {
  char const* path = __BkPointCloud_WriteTempPly(
      "blackhart_pointcloud_world_id.ply", __BkPointCloud_ValidPly);

  BkPointCloud* cloud = BkPointCloud_CreateFromPlyFile(path);
  __BkPointCloud_RemoveFile(path);
  TEST_ASSERT_NOT_NULL(cloud);

  BkAABB const local = BkPointCloud_GetAABB(cloud);
  BkAABB const world = BkPointCloud_GetWorldAABB(cloud);

  TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)local.min.x, (float)world.min.x);
  TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)local.min.y, (float)world.min.y);
  TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)local.min.z, (float)world.min.z);
  TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)local.max.x, (float)world.max.x);
  TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)local.max.y, (float)world.max.y);
  TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)local.max.z, (float)world.max.z);

  TEST_ASSERT_NOT_NULL(BkPointCloud_GetTransform(cloud));

  BkPointCloud_Release(&cloud);
}

void BkPointCloud_GetWorldAABB_AfterSetPosition_test(void) {
  char const* path = __BkPointCloud_WriteTempPly(
      "blackhart_pointcloud_world_pos.ply", __BkPointCloud_ValidPly);

  BkPointCloud* cloud = BkPointCloud_CreateFromPlyFile(path);
  __BkPointCloud_RemoveFile(path);
  TEST_ASSERT_NOT_NULL(cloud);

  struct BkPoint3 const position = {
      .x = BK_REAL(5), .y = BK_REAL(-1), .z = BK_REAL(2)};
  BkPointCloud_SetPosition(cloud, &position);

  BkAABB const world = BkPointCloud_GetWorldAABB(cloud);
  TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)world.min.x, (float)4.0);
  TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)world.min.y, (float)-1.0);
  TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)world.min.z, (float)0.0);
  TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)world.max.x, (float)6.0);
  TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)world.max.y, (float)3.0);
  TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)world.max.z, (float)5.0);

  BkAABB const local = BkPointCloud_GetAABB(cloud);
  TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)local.min.x, (float)-1.0);
  TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)local.max.x, (float)1.0);

  BkPointCloud_Release(&cloud);
}

void BkPointCloud_GetWorldAABB_AfterSetOrientation_test(void) {
  char const* path =
      __BkPointCloud_WriteTempPly("blackhart_pointcloud_world_ori.ply",
                                  "ply\n"
                                  "format ascii 1.0\n"
                                  "element vertex 2\n"
                                  "property float x\n"
                                  "property float y\n"
                                  "property float z\n"
                                  "end_header\n"
                                  "0 0 0\n"
                                  "1 0 0\n");

  BkPointCloud* cloud = BkPointCloud_CreateFromPlyFile(path);
  __BkPointCloud_RemoveFile(path);
  TEST_ASSERT_NOT_NULL(cloud);

  struct BkVector3 const axis = {
      .x = BK_REAL(0), .y = BK_REAL(0), .z = BK_REAL(1)};
  struct BkAngleAxis const aa = BkAngleAxis_FromAngleAxis(BK_REAL(90), &axis);
  struct BkQuaternion const q = BkQuaternion_FromAngleAxis(&aa);
  BkPointCloud_SetOrientation(cloud, &q);

  BkAABB const world = BkPointCloud_GetWorldAABB(cloud);
  /* Local segment (0,0,0)-(1,0,0) rotated 90° around Z → (0,0,0)-(0,1,0) */
  TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)world.min.x, (float)0.0);
  TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)world.min.y, (float)0.0);
  TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)world.min.z, (float)0.0);
  TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)world.max.x, (float)0.0);
  TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)world.max.y, (float)1.0);
  TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)world.max.z, (float)0.0);

  BkPointCloud_Release(&cloud);
}

void BkPointCloud_Colors_Absent_test(void) {
  char const* path = __BkPointCloud_WriteTempPly(
      "blackhart_pointcloud_nocolor.ply", __BkPointCloud_ValidPly);

  BkPointCloud* cloud = BkPointCloud_CreateFromPlyFile(path);
  __BkPointCloud_RemoveFile(path);
  TEST_ASSERT_NOT_NULL(cloud);

  TEST_ASSERT_FALSE(BkPointCloud_HasColors(cloud));
  TEST_ASSERT_NULL(BkPointCloud_GetColors(cloud));

  BkPointCloud_Release(&cloud);
}

void BkPointCloud_Colors_Present_test(void) {
  char const* path =
      __BkPointCloud_WriteTempPly("blackhart_pointcloud_color.ply",
                                  "ply\n"
                                  "format ascii 1.0\n"
                                  "element vertex 2\n"
                                  "property float x\n"
                                  "property float y\n"
                                  "property float z\n"
                                  "property uchar red\n"
                                  "property uchar green\n"
                                  "property uchar blue\n"
                                  "end_header\n"
                                  "0 0 0 10 20 30\n"
                                  "1 0 0 40 50 60\n");

  BkPointCloud* cloud = BkPointCloud_CreateFromPlyFile(path);
  __BkPointCloud_RemoveFile(path);
  TEST_ASSERT_NOT_NULL(cloud);

  TEST_ASSERT_TRUE(BkPointCloud_HasColors(cloud));
  BkColor3 const* colors = BkPointCloud_GetColors(cloud);
  TEST_ASSERT_NOT_NULL(colors);
  TEST_ASSERT_EQUAL_UINT(10, colors[0].r);
  TEST_ASSERT_EQUAL_UINT(20, colors[0].g);
  TEST_ASSERT_EQUAL_UINT(30, colors[0].b);
  TEST_ASSERT_EQUAL_UINT(40, colors[1].r);
  TEST_ASSERT_EQUAL_UINT(50, colors[1].g);
  TEST_ASSERT_EQUAL_UINT(60, colors[1].b);

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
