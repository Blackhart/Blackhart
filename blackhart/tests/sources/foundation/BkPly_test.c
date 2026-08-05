// Standard headers.
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

// Unity headers.
#include <unity.h>

// Blackhart headers.
#include "foundation/BkArray.h"
#include "foundation/BkPly.h"

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

static void __BkPly_ReleaseLoadedPoints(struct BkArray* points) {
  if (points == NULL) return;

  BkArray_Destroy(points);
  free(points);
}

// ~~~~~ Def(PUBLIC) ~~~~~

void BkPly_RunTests(void) {
  RUN_TEST(BkPly_LoadPoints_NullFilename_test);
  RUN_TEST(BkPly_LoadPoints_FileDoesNotExist_test);
  RUN_TEST(BkPly_LoadPoints_NoPermission_test);
  RUN_TEST(BkPly_LoadPoints_NotAPly_test);
  RUN_TEST(BkPly_LoadPoints_NoHeader_test);
  RUN_TEST(BkPly_LoadPoints_NoVertices_test);
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
  __BkPly_ReleaseLoadedPoints(points);

  TEST_ASSERT_NULL(points);
}
