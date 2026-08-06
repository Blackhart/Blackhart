// Unity headers.
#include <unity.h>

// Blackhart headers.
#include "blackhart.h"

// Test headers.
#include "foundation/BkAABB_test.h"

static float const ERROR_LIMIT = 0.00001f;

// ~~~~~ Def(PUBLIC) ~~~~~

void BkAABB_RunTests(void) {
  RUN_TEST(BkAABB_Zero_test);
  RUN_TEST(BkAABB_FromMinMax_test);
  RUN_TEST(BkAABB_FromPoints_test);
  RUN_TEST(BkAABB_FromPoints_Empty_test);
  RUN_TEST(BkAABB_IncludePoint_test);
  RUN_TEST(BkAABB_Center_test);
  RUN_TEST(BkAABB_Size_test);
  RUN_TEST(BkAABB_Union_test);
}

void BkAABB_Zero_test(void) {
  struct BkAABB aabb = BkAABB_Zero();

  TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)aabb.min.x, (float)0.0);
  TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)aabb.min.y, (float)0.0);
  TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)aabb.min.z, (float)0.0);
  TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)aabb.max.x, (float)0.0);
  TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)aabb.max.y, (float)0.0);
  TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)aabb.max.z, (float)0.0);
}

void BkAABB_FromMinMax_test(void) {
  struct BkPoint3 min = BkPoint3_FromXYZ(BK_REAL(-1), BK_REAL(0), BK_REAL(2));
  struct BkPoint3 max = BkPoint3_FromXYZ(BK_REAL(3), BK_REAL(4), BK_REAL(5));
  struct BkAABB aabb = BkAABB_FromMinMax(&min, &max);

  TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)aabb.min.x, (float)-1.0);
  TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)aabb.min.y, (float)0.0);
  TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)aabb.min.z, (float)2.0);
  TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)aabb.max.x, (float)3.0);
  TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)aabb.max.y, (float)4.0);
  TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)aabb.max.z, (float)5.0);
}

void BkAABB_FromPoints_test(void) {
  struct BkPoint3 points[3];
  points[0] = BkPoint3_FromXYZ(BK_REAL(1), BK_REAL(2), BK_REAL(3));
  points[1] = BkPoint3_FromXYZ(BK_REAL(-4), BK_REAL(8), BK_REAL(0));
  points[2] = BkPoint3_FromXYZ(BK_REAL(2), BK_REAL(-1), BK_REAL(7));

  struct BkAABB aabb = BkAABB_FromPoints(points, 3);

  TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)aabb.min.x, (float)-4.0);
  TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)aabb.min.y, (float)-1.0);
  TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)aabb.min.z, (float)0.0);
  TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)aabb.max.x, (float)2.0);
  TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)aabb.max.y, (float)8.0);
  TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)aabb.max.z, (float)7.0);
}

void BkAABB_FromPoints_Empty_test(void) {
  struct BkAABB aabb = BkAABB_FromPoints(NULL, 0);
  TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)aabb.min.x, (float)0.0);
  TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)aabb.max.x, (float)0.0);
}

void BkAABB_IncludePoint_test(void) {
  struct BkPoint3 p0 = BkPoint3_FromXYZ(BK_REAL(1), BK_REAL(1), BK_REAL(1));
  struct BkAABB aabb = BkAABB_FromMinMax(&p0, &p0);

  struct BkPoint3 p1 = BkPoint3_FromXYZ(BK_REAL(-2), BK_REAL(3), BK_REAL(0));
  BkAABB_IncludePoint(&aabb, &p1);

  TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)aabb.min.x, (float)-2.0);
  TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)aabb.min.y, (float)1.0);
  TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)aabb.min.z, (float)0.0);
  TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)aabb.max.x, (float)1.0);
  TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)aabb.max.y, (float)3.0);
  TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)aabb.max.z, (float)1.0);
}

void BkAABB_Center_test(void) {
  struct BkPoint3 min = BkPoint3_FromXYZ(BK_REAL(0), BK_REAL(0), BK_REAL(0));
  struct BkPoint3 max = BkPoint3_FromXYZ(BK_REAL(2), BK_REAL(4), BK_REAL(6));
  struct BkAABB aabb = BkAABB_FromMinMax(&min, &max);
  struct BkPoint3 c = BkAABB_Center(&aabb);

  TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)c.x, (float)1.0);
  TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)c.y, (float)2.0);
  TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)c.z, (float)3.0);
}

void BkAABB_Size_test(void) {
  struct BkPoint3 min = BkPoint3_FromXYZ(BK_REAL(1), BK_REAL(2), BK_REAL(3));
  struct BkPoint3 max = BkPoint3_FromXYZ(BK_REAL(4), BK_REAL(6), BK_REAL(3));
  struct BkAABB aabb = BkAABB_FromMinMax(&min, &max);
  struct BkVector3 s = BkAABB_Size(&aabb);

  TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)s.x, (float)3.0);
  TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)s.y, (float)4.0);
  TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)s.z, (float)0.0);
}

void BkAABB_Union_test(void) {
  struct BkPoint3 a_min = BkPoint3_FromXYZ(BK_REAL(0), BK_REAL(0), BK_REAL(0));
  struct BkPoint3 a_max = BkPoint3_FromXYZ(BK_REAL(1), BK_REAL(1), BK_REAL(1));
  struct BkPoint3 b_min =
      BkPoint3_FromXYZ(BK_REAL(-2), BK_REAL(0.5), BK_REAL(-1));
  struct BkPoint3 b_max =
      BkPoint3_FromXYZ(BK_REAL(0.5), BK_REAL(3), BK_REAL(2));
  struct BkAABB a = BkAABB_FromMinMax(&a_min, &a_max);
  struct BkAABB b = BkAABB_FromMinMax(&b_min, &b_max);
  struct BkAABB u = BkAABB_Union(&a, &b);

  TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)u.min.x, (float)-2.0);
  TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)u.min.y, (float)0.0);
  TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)u.min.z, (float)-1.0);
  TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)u.max.x, (float)1.0);
  TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)u.max.y, (float)3.0);
  TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)u.max.z, (float)2.0);
}
