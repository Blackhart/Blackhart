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
  RUN_TEST(BkPointCloud_GetAABB_Identity_test);
  RUN_TEST(BkPointCloud_GetAABB_AfterSetPosition_test);
  RUN_TEST(BkPointCloud_GetAABB_AfterSetOrientation_test);
  RUN_TEST(BkPointCloud_GetAABB_TightAfterOrientation_test);
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

  /* File AABB center is (0, 2, 0.5); points are stored relative to it. */
  BkPoint3 const* points = BkPointCloud_GetPoints(cloud);
  TEST_ASSERT_NOT_NULL(points);

  TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)points[0].x, (float)0.0);
  TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)points[0].y, (float)-2.0);
  TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)points[0].z, (float)-0.5);
  TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)points[1].x, (float)1.0);
  TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)points[1].y, (float)0.0);
  TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)points[1].z, (float)2.5);
  TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)points[2].x, (float)-1.0);
  TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)points[2].y, (float)2.0);
  TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)points[2].z, (float)-2.5);

  struct BkPoint3 const* pos = &BkPointCloud_GetTransform(cloud)->position;
  TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)pos->x, (float)0.0);
  TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)pos->y, (float)2.0);
  TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)pos->z, (float)0.5);

  BkPointCloud_Release(&cloud);
}

void BkPointCloud_GetAABB_Identity_test(void) {
  char const* path = __BkPointCloud_WriteTempPly(
      "blackhart_pointcloud_aabb_id.ply", __BkPointCloud_ValidPly);

  BkPointCloud* cloud = BkPointCloud_CreateFromPlyFile(path);
  __BkPointCloud_RemoveFile(path);
  TEST_ASSERT_NOT_NULL(cloud);

  /* World AABB matches original file bounds despite model-space recenter. */
  BkAABB const aabb = BkPointCloud_GetAABB(cloud);
  TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)aabb.min.x, (float)-1.0);
  TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)aabb.min.y, (float)0.0);
  TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)aabb.min.z, (float)-2.0);
  TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)aabb.max.x, (float)1.0);
  TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)aabb.max.y, (float)4.0);
  TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)aabb.max.z, (float)3.0);

  TEST_ASSERT_NOT_NULL(BkPointCloud_GetTransform(cloud));

  BkPointCloud_Release(&cloud);
}

void BkPointCloud_GetAABB_AfterSetPosition_test(void) {
  char const* path = __BkPointCloud_WriteTempPly(
      "blackhart_pointcloud_aabb_pos.ply", __BkPointCloud_ValidPly);

  BkPointCloud* cloud = BkPointCloud_CreateFromPlyFile(path);
  __BkPointCloud_RemoveFile(path);
  TEST_ASSERT_NOT_NULL(cloud);

  struct BkPoint3 const position = {
      .x = BK_REAL(5), .y = BK_REAL(-1), .z = BK_REAL(2)};
  BkPointCloud_SetPosition(cloud, &position);

  BkAABB const aabb = BkPointCloud_GetAABB(cloud);
  TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)aabb.min.x, (float)4.0);
  TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)aabb.min.y, (float)-3.0);
  TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)aabb.min.z, (float)-0.5);
  TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)aabb.max.x, (float)6.0);
  TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)aabb.max.y, (float)1.0);
  TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)aabb.max.z, (float)4.5);

  BkPointCloud_Release(&cloud);
}

void BkPointCloud_GetAABB_AfterSetOrientation_test(void) {
  char const* path =
      __BkPointCloud_WriteTempPly("blackhart_pointcloud_aabb_ori.ply",
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

  /* Local (-0.5,0,0)-(0.5,0,0), pivot at (0.5,0,0), rot 90° Z. */
  BkAABB const aabb = BkPointCloud_GetAABB(cloud);
  TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)aabb.min.x, (float)0.5);
  TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)aabb.min.y, (float)-0.5);
  TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)aabb.min.z, (float)0.0);
  TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)aabb.max.x, (float)0.5);
  TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)aabb.max.y, (float)0.5);
  TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)aabb.max.z, (float)0.0);

  BkPointCloud_Release(&cloud);
}

void BkPointCloud_GetAABB_TightAfterOrientation_test(void) {
  /* L-shape: model-space box has an empty corner that must not inflate AABB. */
  char const* path =
      __BkPointCloud_WriteTempPly("blackhart_pointcloud_aabb_tight.ply",
                                  "ply\n"
                                  "format ascii 1.0\n"
                                  "element vertex 3\n"
                                  "property float x\n"
                                  "property float y\n"
                                  "property float z\n"
                                  "end_header\n"
                                  "0 0 0\n"
                                  "2 0 0\n"
                                  "0 2 0\n");

  BkPointCloud* cloud = BkPointCloud_CreateFromPlyFile(path);
  __BkPointCloud_RemoveFile(path);
  TEST_ASSERT_NOT_NULL(cloud);

  struct BkVector3 const axis = {
      .x = BK_REAL(0), .y = BK_REAL(0), .z = BK_REAL(1)};
  struct BkAngleAxis const aa = BkAngleAxis_FromAngleAxis(BK_REAL(45), &axis);
  struct BkQuaternion const q = BkQuaternion_FromAngleAxis(&aa);
  BkPointCloud_SetOrientation(cloud, &q);

  size_t const count = BkPointCloud_GetCount(cloud);
  BkPoint3 const* local_pts = BkPointCloud_GetPoints(cloud);
  struct BkMatrix4x4 const* model =
      BkTransform_Matrix(BkPointCloud_GetTransform(cloud));

  struct BkPoint3 world_pts[3];
  for (size_t i = 0; i < count; ++i) {
    world_pts[i] = BkMatrix4x4_Mul_BkPoint3(model, &local_pts[i]);
  }
  BkAABB const expected = BkAABB_FromPoints(world_pts, count);
  BkAABB const aabb = BkPointCloud_GetAABB(cloud);

  TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)expected.min.x,
                           (float)aabb.min.x);
  TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)expected.min.y,
                           (float)aabb.min.y);
  TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)expected.min.z,
                           (float)aabb.min.z);
  TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)expected.max.x,
                           (float)aabb.max.x);
  TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)expected.max.y,
                           (float)aabb.max.y);
  TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)expected.max.z,
                           (float)aabb.max.z);

  /* Inflated OBB-corner AABB must be strictly larger on at least one axis. */
  BkAABB const model_extents = BkAABB_FromPoints(local_pts, count);
  struct BkPoint3 corners[8] = {
      {model_extents.min.x, model_extents.min.y, model_extents.min.z},
      {model_extents.max.x, model_extents.min.y, model_extents.min.z},
      {model_extents.min.x, model_extents.max.y, model_extents.min.z},
      {model_extents.max.x, model_extents.max.y, model_extents.min.z},
      {model_extents.min.x, model_extents.min.y, model_extents.max.z},
      {model_extents.max.x, model_extents.min.y, model_extents.max.z},
      {model_extents.min.x, model_extents.max.y, model_extents.max.z},
      {model_extents.max.x, model_extents.max.y, model_extents.max.z},
  };
  for (size_t i = 0; i < 8; ++i) {
    corners[i] = BkMatrix4x4_Mul_BkPoint3(model, &corners[i]);
  }
  BkAABB const inflated = BkAABB_FromPoints(corners, 8);
  real const tight_span = (aabb.max.x - aabb.min.x) +
                          (aabb.max.y - aabb.min.y) + (aabb.max.z - aabb.min.z);
  real const inflated_span = (inflated.max.x - inflated.min.x) +
                             (inflated.max.y - inflated.min.y) +
                             (inflated.max.z - inflated.min.z);
  TEST_ASSERT_TRUE(inflated_span > tight_span + BK_REAL(0.01));

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
