// Unity headers.
#include <unity.h>

// Blackhart headers.
#include "blackhart.h"

// Test headers.
#include "foundation/BkColor3_test.h"

// ~~~~~ Def(PUBLIC) ~~~~~

void BkColor3_RunTests(void) {
  RUN_TEST(BkColor3_White_test);
  RUN_TEST(BkColor3_FromRGB_test);
}

void BkColor3_White_test(void) {
  struct BkColor3 const c = BkColor3_White();

  TEST_ASSERT_EQUAL_UINT(255, c.r);
  TEST_ASSERT_EQUAL_UINT(255, c.g);
  TEST_ASSERT_EQUAL_UINT(255, c.b);
}

void BkColor3_FromRGB_test(void) {
  struct BkColor3 const c = BkColor3_FromRGB(10, 20, 30);

  TEST_ASSERT_EQUAL_UINT(10, c.r);
  TEST_ASSERT_EQUAL_UINT(20, c.g);
  TEST_ASSERT_EQUAL_UINT(30, c.b);
}
