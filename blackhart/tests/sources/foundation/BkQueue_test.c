// Unity headers.
#include <unity.h>

// Blackhart headers.
#include "blackhart.h"

// Test headers
#include "foundation/BkQueue_test.h"

// ~~~~~ Def(PUBLIC) ~~~~~

void BkQueue_Create_test(void) {
  BkQueue* queue = BkQueue_Create();
  TEST_ASSERT_NOT_NULL(queue);
  TEST_ASSERT_EQUAL(0, BkQueue_Size(queue));
  TEST_ASSERT_TRUE(BkQueue_Empty(queue));
  TEST_ASSERT_NULL(BkQueue_Front(queue));
  TEST_ASSERT_NULL(BkQueue_Back(queue));

  BkQueue_Release(&queue);
  TEST_ASSERT_NULL(queue);
}

void BkQueue_Push_test(void) {
  BkQueue* queue = BkQueue_Create();
  TEST_ASSERT_NOT_NULL(queue);

  const int8 val1 = 1;
  const int8 val2 = 2;

  BkQueue_Push(queue, (void*)&val1);
  TEST_ASSERT_EQUAL(1, BkQueue_Size(queue));
  TEST_ASSERT_EQUAL(1, *((int8*)BkQueue_Back(queue)));

  BkQueue_Push(queue, (void*)&val2);
  TEST_ASSERT_EQUAL(2, BkQueue_Size(queue));
  TEST_ASSERT_EQUAL(2, *((int8*)BkQueue_Back(queue)));

  BkQueue_Release(&queue);
}

void BkQueue_Empty_test(void) {
  BkQueue* queue = BkQueue_Create();
  TEST_ASSERT_NOT_NULL(queue);
  TEST_ASSERT_TRUE(BkQueue_Empty(queue));

  const int8 val1 = 1;
  const int8 val2 = 2;

  BkQueue_Push(queue, (void*)&val1);
  BkQueue_Push(queue, (void*)&val2);
  TEST_ASSERT_FALSE(BkQueue_Empty(queue));

  BkQueue_Release(&queue);
}

void BkQueue_Size_test(void) {
  BkQueue* queue = BkQueue_Create();
  TEST_ASSERT_NOT_NULL(queue);
  TEST_ASSERT_EQUAL(0, BkQueue_Size(queue));

  const int8 val1 = 1;
  const int8 val2 = 2;

  BkQueue_Push(queue, (void*)&val1);
  TEST_ASSERT_EQUAL(1, BkQueue_Size(queue));

  BkQueue_Push(queue, (void*)&val2);
  TEST_ASSERT_EQUAL(2, BkQueue_Size(queue));

  BkQueue_Pop(queue);
  TEST_ASSERT_EQUAL(1, BkQueue_Size(queue));

  BkQueue_Pop(queue);
  TEST_ASSERT_EQUAL(0, BkQueue_Size(queue));

  BkQueue_Pop(queue);
  TEST_ASSERT_EQUAL(0, BkQueue_Size(queue));

  BkQueue_Release(&queue);
}

void BkQueue_Pop_test(void) {
  BkQueue* queue = BkQueue_Create();
  TEST_ASSERT_NOT_NULL(queue);

  const int8 val1 = 1;
  const int8 val2 = 2;

  BkQueue_Push(queue, (void*)&val1);
  BkQueue_Push(queue, (void*)&val2);

  BkQueue_Pop(queue);
  TEST_ASSERT_EQUAL(1, BkQueue_Size(queue));
  TEST_ASSERT_EQUAL(2, *((int8*)BkQueue_Front(queue)));

  BkQueue_Pop(queue);
  TEST_ASSERT_EQUAL(0, BkQueue_Size(queue));
  TEST_ASSERT_NULL(BkQueue_Front(queue));

  BkQueue_Pop(queue);
  TEST_ASSERT_EQUAL(0, BkQueue_Size(queue));
  TEST_ASSERT_NULL(BkQueue_Front(queue));

  BkQueue_Release(&queue);
}

void BkQueue_Front_test(void) {
  BkQueue* queue = BkQueue_Create();
  TEST_ASSERT_NOT_NULL(queue);
  TEST_ASSERT_NULL(BkQueue_Front(queue));

  const int8 val1 = 1;
  const int8 val2 = 2;

  BkQueue_Push(queue, (void*)&val1);
  TEST_ASSERT_EQUAL(1, *((int8*)BkQueue_Front(queue)));

  BkQueue_Push(queue, (void*)&val2);
  TEST_ASSERT_EQUAL(1, *((int8*)BkQueue_Front(queue)));

  BkQueue_Pop(queue);
  TEST_ASSERT_EQUAL(2, *((int8*)BkQueue_Front(queue)));

  BkQueue_Pop(queue);
  TEST_ASSERT_NULL(BkQueue_Front(queue));

  BkQueue_Release(&queue);
}

void BkQueue_Back_test(void) {
  BkQueue* queue = BkQueue_Create();
  TEST_ASSERT_NOT_NULL(queue);
  TEST_ASSERT_NULL(BkQueue_Back(queue));

  const int8 val1 = 1;
  const int8 val2 = 2;

  BkQueue_Push(queue, (void*)&val1);
  TEST_ASSERT_EQUAL(1, *((int8*)BkQueue_Back(queue)));

  BkQueue_Push(queue, (void*)&val2);
  TEST_ASSERT_EQUAL(2, *((int8*)BkQueue_Back(queue)));

  BkQueue_Pop(queue);
  TEST_ASSERT_EQUAL(2, *((int8*)BkQueue_Back(queue)));

  BkQueue_Pop(queue);
  TEST_ASSERT_NULL(BkQueue_Back(queue));

  BkQueue_Release(&queue);
}

void BkQueue_Clear_test(void) {
  BkQueue* queue = BkQueue_Create();
  TEST_ASSERT_NOT_NULL(queue);

  const int8 val1 = 1;
  const int8 val2 = 2;

  BkQueue_Push(queue, (void*)&val1);
  BkQueue_Push(queue, (void*)&val2);

  BkQueue_Clear(queue);

  TEST_ASSERT_TRUE(BkQueue_Empty(queue));
  TEST_ASSERT_NULL(BkQueue_Front(queue));

  BkQueue_Release(&queue);
}

void BkQueue_RunTests(void) {
  RUN_TEST(BkQueue_Create_test);
  RUN_TEST(BkQueue_Push_test);
  RUN_TEST(BkQueue_Empty_test);
  RUN_TEST(BkQueue_Size_test);
  RUN_TEST(BkQueue_Pop_test);
  RUN_TEST(BkQueue_Front_test);
  RUN_TEST(BkQueue_Back_test);
  RUN_TEST(BkQueue_Clear_test);
}
