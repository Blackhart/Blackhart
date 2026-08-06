// Standard headers.
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

// Unity headers.
#include <unity.h>

// Blackhart headers.
#include "foundation/BkArray.h"
#include "foundation/BkColor3.h"
#include "foundation/BkPly.h"
#include "foundation/BkPoint3.h"

// Test headers.
#include "foundation/BkPly_test.h"

// ~~~~~ Def(INTERNAL) ~~~~~

static char const* __BkPly_WriteTempFile(char const* basename,
                                         char const* contents) {
  static char path[512];

  snprintf(path, sizeof(path), "/tmp/%s", basename);

  FILE* file = fopen(path, "w");
  TEST_ASSERT_NOT_NULL(file);
  fputs(contents, file);
  fclose(file);

  return path;
}

static void __BkPly_RemoveFile(char const* path) {
  if (path != NULL) remove(path);
}

static void __BkPly_ReleaseLoadedArray(struct BkArray* array) {
  if (array == NULL) return;

  BkArray_Destroy(array);
  free(array);
}

// ~~~~~ Def(PUBLIC) ~~~~~

void BkPly_RunTests(void) {
  RUN_TEST(BkPly_LoadPoints_NullFilename_test);
  RUN_TEST(BkPly_LoadPoints_FileDoesNotExist_test);
  RUN_TEST(BkPly_LoadPoints_NoPermission_test);
  RUN_TEST(BkPly_LoadPoints_NotAPly_test);
  RUN_TEST(BkPly_LoadPoints_NoHeader_test);
  RUN_TEST(BkPly_LoadPoints_NoVertices_test);
  RUN_TEST(BkPly_LoadColors_Absent_test);
  RUN_TEST(BkPly_LoadColors_Present_test);
}

void BkPly_LoadPoints_NullFilename_test(void) {
  struct BkArray* points = _BkPly_LoadPoints(NULL);

  TEST_ASSERT_NULL(points);
}

void BkPly_LoadPoints_FileDoesNotExist_test(void) {
  struct BkArray* points =
      _BkPly_LoadPoints("/tmp/blackhart_ply_missing_file.ply");

  TEST_ASSERT_NULL(points);
}

void BkPly_LoadPoints_NoPermission_test(void) {
  char const* path = __BkPly_WriteTempFile(
      "blackhart_ply_noperm.ply",
      "ply\nformat ascii 1.0\nelement vertex 1\nproperty float x\nproperty "
      "float y\nproperty float z\nend_header\n0 0 0\n");

  TEST_ASSERT_EQUAL_INT(0, chmod(path, 0));

  struct BkArray* points = _BkPly_LoadPoints(path);

  chmod(path, 0600);
  __BkPly_RemoveFile(path);

  TEST_ASSERT_NULL(points);
}

void BkPly_LoadPoints_NotAPly_test(void) {
  char const* path = __BkPly_WriteTempFile("blackhart_ply_invalid.txt",
                                           "this is not a ply file\n");

  struct BkArray* points = _BkPly_LoadPoints(path);

  __BkPly_RemoveFile(path);

  TEST_ASSERT_NULL(points);
}

void BkPly_LoadPoints_NoHeader_test(void) {
  char const* path =
      __BkPly_WriteTempFile("blackhart_ply_noheader.ply",
                            "ply\nformat ascii 1.0\nelement vertex 1\nproperty "
                            "float x\nproperty float y\nproperty float z\n");

  struct BkArray* points = _BkPly_LoadPoints(path);

  __BkPly_RemoveFile(path);

  TEST_ASSERT_NULL(points);
}

void BkPly_LoadPoints_NoVertices_test(void) {
  char const* path = __BkPly_WriteTempFile("blackhart_ply_novertices.ply",
                                           "ply\n"
                                           "format ascii 1.0\n"
                                           "element vertex 0\n"
                                           "property float x\n"
                                           "property float y\n"
                                           "property float z\n"
                                           "end_header\n");

  struct BkArray* points = _BkPly_LoadPoints(path);

  __BkPly_RemoveFile(path);
  __BkPly_ReleaseLoadedArray(points);

  TEST_ASSERT_NULL(points);
}

void BkPly_LoadColors_Absent_test(void) {
  char const* path = __BkPly_WriteTempFile("blackhart_ply_nocolor.ply",
                                           "ply\n"
                                           "format ascii 1.0\n"
                                           "element vertex 1\n"
                                           "property float x\n"
                                           "property float y\n"
                                           "property float z\n"
                                           "end_header\n"
                                           "1 2 3\n");

  struct BkArray* colors = _BkPly_LoadColors(path);
  __BkPly_RemoveFile(path);

  TEST_ASSERT_NULL(colors);
}

void BkPly_LoadColors_Present_test(void) {
  char const* path = __BkPly_WriteTempFile("blackhart_ply_colors.ply",
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
                                           "0 0 0 255 0 0\n"
                                           "1 0 0 0 128 255\n");

  struct BkArray* points = _BkPly_LoadPoints(path);
  struct BkArray* colors = _BkPly_LoadColors(path);
  __BkPly_RemoveFile(path);

  TEST_ASSERT_NOT_NULL(points);
  TEST_ASSERT_NOT_NULL(colors);
  TEST_ASSERT_EQUAL_UINT(2, (unsigned)BkArray_Size((*points)));
  TEST_ASSERT_EQUAL_UINT(2, (unsigned)BkArray_Size((*colors)));

  struct BkPoint3 const* pts = (struct BkPoint3 const*)points->data;
  struct BkColor3 const* cols = (struct BkColor3 const*)colors->data;

  TEST_ASSERT_EQUAL_UINT(255, cols[0].r);
  TEST_ASSERT_EQUAL_UINT(0, cols[0].g);
  TEST_ASSERT_EQUAL_UINT(0, cols[0].b);
  TEST_ASSERT_EQUAL_UINT(0, cols[1].r);
  TEST_ASSERT_EQUAL_UINT(128, cols[1].g);
  TEST_ASSERT_EQUAL_UINT(255, cols[1].b);
  TEST_ASSERT_FLOAT_WITHIN(0.00001f, (float)pts[1].x, (float)1.0);

  __BkPly_ReleaseLoadedArray(points);
  __BkPly_ReleaseLoadedArray(colors);
}
