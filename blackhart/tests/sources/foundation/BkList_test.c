// Unity headers.
#include <unity.h>

// Blackhart headers.
#include "blackhart.h"

// Test headers
#include "foundation/BkList_test.h"

// ~~~~~ Def(PUBLIC) ~~~~~

void BkList_Empty_test(void) {
  BkList* list = BkList_Create();
  TEST_ASSERT_NOT_NULL(list);

  TEST_ASSERT_TRUE(BkList_Empty(list));

  BkList_PushBack(list, NULL);
  TEST_ASSERT_FALSE(BkList_Empty(list));

  BkList_Release(&list);
}

void BkList_Front_test(void) {
  uint32 lValue1 = 5;
  uint32 lValue2 = 10;
  uint32 lValue3 = 15;

  BkList* list = BkList_Create();
  TEST_ASSERT_NOT_NULL(list);
  TEST_ASSERT_NULL(BkList_Front(list));

  BkList_PushBack(list, &lValue1);
  BkList_PushBack(list, &lValue2);
  BkList_PushBack(list, &lValue3);

  TEST_ASSERT_EQUAL(lValue1, *(uint32*)BkList_Front(list));

  BkList_Release(&list);
}

void BkList_Back_test(void) {
  uint32 lValue1 = 5;
  uint32 lValue2 = 10;
  uint32 lValue3 = 15;

  BkList* list = BkList_Create();
  TEST_ASSERT_NOT_NULL(list);
  TEST_ASSERT_NULL(BkList_Back(list));

  BkList_PushBack(list, &lValue1);
  BkList_PushBack(list, &lValue2);
  BkList_PushBack(list, &lValue3);

  TEST_ASSERT_EQUAL(lValue3, *(uint32*)BkList_Back(list));

  BkList_Release(&list);
}

void BkList_Size_test(void) {
  uint32 lValue1 = 5;
  uint32 lValue2 = 10;
  uint32 lValue3 = 15;

  BkList* list = BkList_Create();
  TEST_ASSERT_NOT_NULL(list);
  TEST_ASSERT_EQUAL(0, BkList_Size(list));

  BkList_PushBack(list, &lValue1);
  BkList_PushBack(list, &lValue2);
  BkList_PushBack(list, &lValue3);

  TEST_ASSERT_EQUAL(3, BkList_Size(list));

  BkList_Release(&list);
}

void BkList_Clear_test(void) {
  uint32 lValue1 = 5;
  uint32 lValue2 = 10;
  uint32 lValue3 = 15;

  BkList* list = BkList_Create();
  TEST_ASSERT_NOT_NULL(list);

  BkList_PushBack(list, &lValue1);
  BkList_PushBack(list, &lValue2);
  BkList_PushBack(list, &lValue3);

  BkList_Clear(list);

  TEST_ASSERT_EQUAL(0, BkList_Size(list));
  TEST_ASSERT_TRUE(BkList_Empty(list));
  TEST_ASSERT_NULL(BkList_Front(list));

  BkList_Release(&list);
}

void BkList_Get_test(void) {
  uint32 lValue1 = 5;
  uint32 lValue2 = 10;
  uint32 lValue3 = 15;

  BkList* list = BkList_Create();
  TEST_ASSERT_NOT_NULL(list);

  BkList_PushBack(list, &lValue1);
  BkList_PushBack(list, &lValue2);
  BkList_PushBack(list, &lValue3);

  TEST_ASSERT_EQUAL(lValue1, *(uint32*)BkList_Get(list, 0));
  TEST_ASSERT_EQUAL(lValue3, *(uint32*)BkList_Get(list, 2));
  TEST_ASSERT_EQUAL(lValue2, *(uint32*)BkList_Get(list, 1));
  TEST_ASSERT_NULL(BkList_Get(list, 500));

  BkList_Release(&list);
}

void BkList_Insert_test(void) {
  uint32 lValue1 = 5;
  uint32 lValue2 = 10;
  uint32 lValue3 = 15;

  BkList* list = BkList_Create();
  TEST_ASSERT_NOT_NULL(list);

  BkList_Insert(list, &lValue1, 0);
  BkList_Insert(list, &lValue2, 0);
  BkList_Insert(list, &lValue3, 1);
  BkList_Insert(list, &lValue3, 10);

  TEST_ASSERT_EQUAL(lValue2, *(uint32*)BkList_Get(list, 0));
  TEST_ASSERT_EQUAL(lValue3, *(uint32*)BkList_Get(list, 1));
  TEST_ASSERT_EQUAL(lValue1, *(uint32*)BkList_Get(list, 2));
  TEST_ASSERT_EQUAL(lValue3, *(uint32*)BkList_Get(list, 3));

  BkList_Release(&list);
}

void BkList_Erase_test(void) {
  uint32 lValue1 = 5;
  uint32 lValue2 = 10;
  uint32 lValue3 = 15;

  BkList* list = BkList_Create();
  TEST_ASSERT_NOT_NULL(list);

  BkList_PushBack(list, &lValue1);
  BkList_PushBack(list, &lValue2);
  BkList_PushBack(list, &lValue3);

  BkList_Erase(list, &lValue2);
  TEST_ASSERT_EQUAL(lValue1, *(uint32*)BkList_Get(list, 0));
  TEST_ASSERT_EQUAL(2, BkList_Size(list));
  TEST_ASSERT_EQUAL(lValue3, *(uint32*)BkList_Get(list, 1));

  BkList_Erase(list, &lValue1);
  TEST_ASSERT_EQUAL(lValue3, *(uint32*)BkList_Get(list, 0));
  TEST_ASSERT_EQUAL(1, BkList_Size(list));

  BkList_Erase(list, &lValue3);
  TEST_ASSERT_EQUAL(0, BkList_Size(list));

  BkList_Release(&list);
}

void BkList_EraseNode_test(void) {
  uint32 lValue1 = 5;
  uint32 lValue2 = 10;
  uint32 lValue3 = 15;
  uint32 lValue4 = 20;
  uint32 lValue5 = 15;

  BkList* list = BkList_Create();
  TEST_ASSERT_NOT_NULL(list);

  BkList_PushBack(list, &lValue1);
  BkList_PushBack(list, &lValue2);
  BkList_PushBack(list, &lValue3);
  BkList_PushBack(list, &lValue4);
  BkList_PushBack(list, &lValue5);

  BkListNode* node = BkList_GetNode(list, 1);
  BkList_EraseNode(list, node);

  TEST_ASSERT_EQUAL(lValue3, *(uint32*)BkList_Get(list, 1));

  node = BkList_GetNode(list, 1);
  BkList_EraseNode(list, node);

  TEST_ASSERT_EQUAL(lValue4, *(uint32*)BkList_Get(list, 1));
  TEST_ASSERT_EQUAL(lValue5, *(uint32*)BkList_Get(list, 2));

  BkList_Release(&list);
}

void BkList_PushFront_test(void) {
  uint32 lValue1 = 5;
  uint32 lValue2 = 10;
  uint32 lValue3 = 15;

  BkList* list = BkList_Create();
  TEST_ASSERT_NOT_NULL(list);

  BkList_PushFront(list, &lValue1);
  TEST_ASSERT_EQUAL(lValue1, *(uint32*)BkList_Front(list));

  BkList_PushFront(list, &lValue2);
  TEST_ASSERT_EQUAL(lValue2, *(uint32*)BkList_Front(list));

  BkList_PushFront(list, &lValue3);
  TEST_ASSERT_EQUAL(lValue3, *(uint32*)BkList_Front(list));

  BkList_Release(&list);
}

void BkList_PushBack_test(void) {
  uint32 lValue1 = 5;
  uint32 lValue2 = 10;
  uint32 lValue3 = 15;

  BkList* list = BkList_Create();
  TEST_ASSERT_NOT_NULL(list);

  BkList_PushBack(list, &lValue1);
  TEST_ASSERT_EQUAL(lValue1, *(uint32*)BkList_Back(list));

  BkList_PushBack(list, &lValue2);
  TEST_ASSERT_EQUAL(lValue2, *(uint32*)BkList_Back(list));

  BkList_PushBack(list, &lValue3);
  TEST_ASSERT_EQUAL(lValue3, *(uint32*)BkList_Back(list));

  BkList_Release(&list);
}

void BkList_PopFront_test(void) {
  uint32 lValue1 = 5;
  uint32 lValue2 = 10;
  uint32 lValue3 = 15;

  BkList* list = BkList_Create();
  TEST_ASSERT_NOT_NULL(list);

  BkList_PushBack(list, &lValue1);
  BkList_PushBack(list, &lValue2);
  BkList_PushBack(list, &lValue3);

  BkList_PopFront(list);
  TEST_ASSERT_EQUAL(lValue2, *(uint32*)BkList_Front(list));

  BkList_PopFront(list);
  TEST_ASSERT_EQUAL(lValue3, *(uint32*)BkList_Front(list));

  BkList_PopFront(list);
  TEST_ASSERT_TRUE(BkList_Empty(list));
  TEST_ASSERT_NULL(BkList_Front(list));

  BkList_Release(&list);
}

void BkList_PopBack_test(void) {
  uint32 lValue1 = 5;
  uint32 lValue2 = 10;
  uint32 lValue3 = 15;

  BkList* list = BkList_Create();
  TEST_ASSERT_NOT_NULL(list);

  BkList_PushBack(list, &lValue1);
  BkList_PushBack(list, &lValue2);
  BkList_PushBack(list, &lValue3);

  BkList_PopBack(list);
  TEST_ASSERT_EQUAL(lValue2, *(uint32*)BkList_Back(list));

  BkList_PopBack(list);
  TEST_ASSERT_EQUAL(lValue1, *(uint32*)BkList_Back(list));

  BkList_PopBack(list);
  TEST_ASSERT_TRUE(BkList_Empty(list));
  TEST_ASSERT_NULL(BkList_Back(list));

  BkList_Release(&list);
}

void BkList_RunTests(void) {
  RUN_TEST(BkList_Empty_test);
  RUN_TEST(BkList_Front_test);
  RUN_TEST(BkList_Back_test);
  RUN_TEST(BkList_Size_test);
  RUN_TEST(BkList_Clear_test);
  RUN_TEST(BkList_Get_test);
  RUN_TEST(BkList_Insert_test);
  RUN_TEST(BkList_Erase_test);
  RUN_TEST(BkList_EraseNode_test);
  RUN_TEST(BkList_PushFront_test);
  RUN_TEST(BkList_PushBack_test);
  RUN_TEST(BkList_PopFront_test);
  RUN_TEST(BkList_PopBack_test);
}
