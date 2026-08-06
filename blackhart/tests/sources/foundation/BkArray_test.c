// Unity headers.
#include <unity.h>

// Blackhart headers.
#include "blackhart.h"

// Test headers.
#include "foundation/BkArray_test.h"

// ~~~~~ Def(PUBLIC) ~~~~~

void BkArray_RunTests(void) {
  RUN_TEST(BkArray_Create_test);
  RUN_TEST(BkArray_Reserve_test);
  RUN_TEST(BkArray_PushBack_test);
  RUN_TEST(BkArray_Clear_test);
  RUN_TEST(BkArray_Release_test);
  RUN_TEST(BkArray_Erase_test);
  RUN_TEST(BkArray_PopBack_test);
  RUN_TEST(BkArray_Insert_test);
  RUN_TEST(BkArray_Resize_test);
}

void BkArray_Create_test(void) {
  BkArray* array = BkArray_Create((uint8)sizeof(int));
  TEST_ASSERT_NOT_NULL(array);
  TEST_ASSERT_EQUAL_UINT(sizeof(int), BkArray_DataSize(array));
  TEST_ASSERT_EQUAL_UINT(0, (unsigned)BkArray_Size(array));
  TEST_ASSERT_EQUAL_UINT(0, (unsigned)BkArray_Capacity(array));
  TEST_ASSERT_NULL(BkArray_Data(array));

  BkArray_Release(&array);
  TEST_ASSERT_NULL(array);
}

void BkArray_Reserve_test(void) {
  BkArray* array = BkArray_Create((uint8)sizeof(int));
  TEST_ASSERT_NOT_NULL(array);

  BkArray_Reserve(array, 10);
  TEST_ASSERT_EQUAL_UINT(10, (unsigned)BkArray_Capacity(array));

  BkArray_Release(&array);
}

void BkArray_PushBack_test(void) {
  BkArray* array1 = BkArray_Create((uint8)sizeof(uint32));
  TEST_ASSERT_NOT_NULL(array1);

  uint32 a = 50;
  uint32 b = 100;
  uint32 c = 150;

  BkArray_PushBack(array1, a);
  BkArray_PushBack(array1, b);
  BkArray_PushBack(array1, c);

  TEST_ASSERT_EQUAL_UINT(a, BkArray_At(array1, uint32, 0));
  TEST_ASSERT_EQUAL_UINT(b, BkArray_At(array1, uint32, 1));

  c += a;
  TEST_ASSERT_NOT_EQUAL(c, BkArray_At(array1, uint32, 2));

  BkArray* array2 = BkArray_Create((uint8)sizeof(uint32*));
  TEST_ASSERT_NOT_NULL(array2);

  uint32* d = &a;
  uint32* e = &b;
  uint32* f = &c;

  BkArray_PushBack(array2, d);
  BkArray_PushBack(array2, e);
  BkArray_PushBack(array2, f);

  TEST_ASSERT_EQUAL_PTR(d, BkArray_At(array2, uint32*, 0));
  TEST_ASSERT_EQUAL_UINT(*e, *BkArray_At(array2, uint32*, 1));
  TEST_ASSERT_EQUAL_PTR(f, BkArray_At(array2, uint32*, 2));

  c += b;
  TEST_ASSERT_EQUAL_UINT(*f, *BkArray_At(array2, uint32*, 2));

  BkArray_Release(&array1);
  BkArray_Release(&array2);
}

void BkArray_Clear_test(void) {
  BkArray* array = BkArray_Create((uint8)sizeof(uint32));
  TEST_ASSERT_NOT_NULL(array);

  uint32 a = 50;
  uint32 b = 100;
  uint32 c = 150;

  BkArray_PushBack(array, a);
  BkArray_PushBack(array, b);
  BkArray_PushBack(array, c);

  BkArray_Clear(array);

  TEST_ASSERT_EQUAL_UINT(0, (unsigned)BkArray_Size(array));
  TEST_ASSERT_NOT_EQUAL(0, (unsigned)BkArray_Capacity(array));
  TEST_ASSERT_NOT_NULL(BkArray_Data(array));

  BkArray_Release(&array);
}

void BkArray_Release_test(void) {
  BkArray* array = BkArray_Create((uint8)sizeof(uint32));
  TEST_ASSERT_NOT_NULL(array);

  uint32 a = 50;
  uint32 b = 100;
  uint32 c = 150;

  BkArray_PushBack(array, a);
  BkArray_PushBack(array, b);
  BkArray_PushBack(array, c);

  BkArray_Release(&array);
  TEST_ASSERT_NULL(array);
}

void BkArray_Erase_test(void) {
  BkArray* array = BkArray_Create((uint8)sizeof(uint32));
  TEST_ASSERT_NOT_NULL(array);

  uint32 a = 50;
  uint32 b = 100;
  uint32 c = 150;

  BkArray_PushBack(array, a);
  BkArray_PushBack(array, b);
  BkArray_PushBack(array, c);

  BkArray_Erase(array, 0);

  TEST_ASSERT_EQUAL_UINT(c, BkArray_At(array, uint32, 0));
  TEST_ASSERT_EQUAL_UINT(2, (unsigned)BkArray_Size(array));
  TEST_ASSERT_EQUAL_UINT(4, (unsigned)BkArray_Capacity(array));

  BkArray_Erase(array, 1);

  TEST_ASSERT_EQUAL_UINT(c, BkArray_At(array, uint32, 0));
  TEST_ASSERT_EQUAL_UINT(1, (unsigned)BkArray_Size(array));
  TEST_ASSERT_EQUAL_UINT(4, (unsigned)BkArray_Capacity(array));

  BkArray_Erase(array, 0);

  TEST_ASSERT_EQUAL_UINT(0, (unsigned)BkArray_Size(array));
  TEST_ASSERT_EQUAL_UINT(4, (unsigned)BkArray_Capacity(array));
  TEST_ASSERT_NOT_NULL(BkArray_Data(array));

  BkArray_Release(&array);
}

void BkArray_PopBack_test(void) {
  BkArray* array = BkArray_Create((uint8)sizeof(uint32));
  TEST_ASSERT_NOT_NULL(array);

  uint32 a = 50;
  uint32 b = 100;
  uint32 c = 150;

  BkArray_PushBack(array, a);
  BkArray_PushBack(array, b);
  BkArray_PushBack(array, c);

  BkArray_PopBack(array);

  TEST_ASSERT_EQUAL_UINT(a, BkArray_At(array, uint32, 0));
  TEST_ASSERT_EQUAL_UINT(b, BkArray_At(array, uint32, 1));
  TEST_ASSERT_EQUAL_UINT(2, (unsigned)BkArray_Size(array));
  TEST_ASSERT_EQUAL_UINT(4, (unsigned)BkArray_Capacity(array));

  BkArray_PopBack(array);

  TEST_ASSERT_EQUAL_UINT(a, BkArray_At(array, uint32, 0));
  TEST_ASSERT_EQUAL_UINT(1, (unsigned)BkArray_Size(array));
  TEST_ASSERT_EQUAL_UINT(4, (unsigned)BkArray_Capacity(array));

  BkArray_PopBack(array);

  TEST_ASSERT_EQUAL_UINT(0, (unsigned)BkArray_Size(array));
  TEST_ASSERT_EQUAL_UINT(4, (unsigned)BkArray_Capacity(array));
  TEST_ASSERT_NOT_NULL(BkArray_Data(array));

  BkArray_Release(&array);
}

void BkArray_Insert_test(void) {
  BkArray* array = BkArray_Create((uint8)sizeof(uint32));
  TEST_ASSERT_NOT_NULL(array);

  uint32 a = 50;
  uint32 b = 100;
  uint32 c = 150;

  BkArray_Insert(array, 0, a);

  TEST_ASSERT_EQUAL_UINT(a, BkArray_At(array, uint32, 0));
  TEST_ASSERT_EQUAL_UINT(1, (unsigned)BkArray_Size(array));
  TEST_ASSERT_EQUAL_UINT(4, (unsigned)BkArray_Capacity(array));

  BkArray_Insert(array, 0, b);

  TEST_ASSERT_EQUAL_UINT(b, BkArray_At(array, uint32, 0));
  TEST_ASSERT_EQUAL_UINT(a, BkArray_At(array, uint32, 1));
  TEST_ASSERT_EQUAL_UINT(2, (unsigned)BkArray_Size(array));
  TEST_ASSERT_EQUAL_UINT(4, (unsigned)BkArray_Capacity(array));

  BkArray_Insert(array, 2, c);

  TEST_ASSERT_EQUAL_UINT(b, BkArray_At(array, uint32, 0));
  TEST_ASSERT_EQUAL_UINT(a, BkArray_At(array, uint32, 1));
  TEST_ASSERT_EQUAL_UINT(c, BkArray_At(array, uint32, 2));
  TEST_ASSERT_EQUAL_UINT(3, (unsigned)BkArray_Size(array));
  TEST_ASSERT_EQUAL_UINT(4, (unsigned)BkArray_Capacity(array));

  BkArray_Insert(array, 2, b);

  TEST_ASSERT_EQUAL_UINT(b, BkArray_At(array, uint32, 0));
  TEST_ASSERT_EQUAL_UINT(a, BkArray_At(array, uint32, 1));
  TEST_ASSERT_EQUAL_UINT(b, BkArray_At(array, uint32, 2));
  TEST_ASSERT_EQUAL_UINT(c, BkArray_At(array, uint32, 3));
  TEST_ASSERT_EQUAL_UINT(4, (unsigned)BkArray_Size(array));
  TEST_ASSERT_EQUAL_UINT(4, (unsigned)BkArray_Capacity(array));

  BkArray_Insert(array, 0, c);

  TEST_ASSERT_EQUAL_UINT(c, BkArray_At(array, uint32, 0));
  TEST_ASSERT_EQUAL_UINT(a, BkArray_At(array, uint32, 1));
  TEST_ASSERT_EQUAL_UINT(b, BkArray_At(array, uint32, 2));
  TEST_ASSERT_EQUAL_UINT(c, BkArray_At(array, uint32, 3));
  TEST_ASSERT_EQUAL_UINT(b, BkArray_At(array, uint32, 4));
  TEST_ASSERT_EQUAL_UINT(5, (unsigned)BkArray_Size(array));
  TEST_ASSERT_EQUAL_UINT(8, (unsigned)BkArray_Capacity(array));

  BkArray_Release(&array);
}

void BkArray_Resize_test(void) {
  BkArray* array = BkArray_Create((uint8)sizeof(uint32));
  TEST_ASSERT_NOT_NULL(array);

  uint32 a = 50;
  uint32 b = 100;
  uint32 c = 150;

  BkArray_Resize(array, 4, a);

  TEST_ASSERT_EQUAL_UINT(a, BkArray_At(array, uint32, 0));
  TEST_ASSERT_EQUAL_UINT(a, BkArray_At(array, uint32, 1));
  TEST_ASSERT_EQUAL_UINT(a, BkArray_At(array, uint32, 2));
  TEST_ASSERT_EQUAL_UINT(a, BkArray_At(array, uint32, 3));
  TEST_ASSERT_EQUAL_UINT(4, (unsigned)BkArray_Size(array));
  TEST_ASSERT_EQUAL_UINT(8, (unsigned)BkArray_Capacity(array));

  BkArray_Resize(array, 2, b);

  TEST_ASSERT_EQUAL_UINT(a, BkArray_At(array, uint32, 0));
  TEST_ASSERT_EQUAL_UINT(a, BkArray_At(array, uint32, 1));
  TEST_ASSERT_EQUAL_UINT(2, (unsigned)BkArray_Size(array));
  TEST_ASSERT_EQUAL_UINT(8, (unsigned)BkArray_Capacity(array));

  BkArray_Resize(array, 2, c);

  TEST_ASSERT_EQUAL_UINT(a, BkArray_At(array, uint32, 0));
  TEST_ASSERT_EQUAL_UINT(a, BkArray_At(array, uint32, 1));
  TEST_ASSERT_EQUAL_UINT(2, (unsigned)BkArray_Size(array));
  TEST_ASSERT_EQUAL_UINT(8, (unsigned)BkArray_Capacity(array));

  BkArray_Release(&array);
}
