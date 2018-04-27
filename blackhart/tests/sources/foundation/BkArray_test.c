// Unity headers.
#include <unity.h>

// Blackhart headers.
#include "blackhart.h"

// Test headers.
#include "foundation/BkArray_test.h"

// ~~~~~ Def(PUBLIC) ~~~~~

void BkArray_RunTests(void)
{
	RUN_TEST(BkArray_Initialize_test);
	RUN_TEST(BkArray_Reserve_test);
	RUN_TEST(BkArray_PushBack_test);
	RUN_TEST(BkArray_Clear_test);
	RUN_TEST(BkArray_Destroy_test);
	RUN_TEST(BkArray_Erase_test);
	RUN_TEST(BkArray_PopBack_test);
	RUN_TEST(BkArray_Insert_test);
	RUN_TEST(BkArray_Resize_test);
}

void BkArray_Initialize_test(void)
{
	struct BkArray array;

	BkArray_Initialize(&array, sizeof(int));

	TEST_ASSERT_EQUAL(array.data_size, sizeof(int));

	BkArray_Destroy(&array);
}

void BkArray_Reserve_test(void)
{
	struct BkArray array;

	BkArray_Initialize(&array, sizeof(int));
	BkArray_Reserve(&array, 10);

	TEST_ASSERT_EQUAL(BkArray_Capacity(array), 10);

	BkArray_Destroy(&array);
}

void BkArray_PushBack_test(void)
{
	struct BkArray array1;

	BkArray_Initialize(&array1, sizeof(uint32));

	uint32 a = 50;
	uint32 b = 100;
	uint32 c = 150;

	BkArray_PushBack(array1, a);
	BkArray_PushBack(array1, b);
	BkArray_PushBack(array1, c);

	TEST_ASSERT_EQUAL(BkArray_At(array1, uint32, 0), a);
	TEST_ASSERT_EQUAL(BkArray_At(array1, uint32, 1), b);

	c += a;

	TEST_ASSERT_NOT_EQUAL(BkArray_At(array1, uint32, 2), c);

	struct BkArray array2;

	BkArray_Initialize(&array2, sizeof(uint32*));

	uint32* d = &a;
	uint32* e = &b;
	uint32* f = &c;

	BkArray_PushBack(array2, d);
	BkArray_PushBack(array2, e);
	BkArray_PushBack(array2, f);

	TEST_ASSERT_EQUAL(BkArray_At(array2, uint32*, 0), d);
	TEST_ASSERT_EQUAL(*BkArray_At(array2, uint32*, 1), *e);
	TEST_ASSERT_EQUAL(BkArray_At(array2, uint32*, 2), f);

	c += b;

	TEST_ASSERT_EQUAL(*BkArray_At(array2, uint32*, 2), *f);

	BkArray_Destroy(&array1);
	BkArray_Destroy(&array2);
}

void BkArray_Clear_test(void)
{
	struct BkArray array;

	BkArray_Initialize(&array, sizeof(uint32));

	uint32 a = 50;
	uint32 b = 100;
	uint32 c = 150;

	BkArray_PushBack(array, a);
	BkArray_PushBack(array, b);
	BkArray_PushBack(array, c);

	BkArray_Clear(&array);

	TEST_ASSERT_EQUAL(BkArray_Size(array), 0);
	TEST_ASSERT_NOT_EQUAL(BkArray_Capacity(array), 0);
	TEST_ASSERT_NOT_NULL(array.data);

	BkArray_Destroy(&array);
}

void BkArray_Destroy_test(void)
{
	struct BkArray array;

	BkArray_Initialize(&array, sizeof(uint32));

	uint32 a = 50;
	uint32 b = 100;
	uint32 c = 150;

	BkArray_PushBack(array, a);
	BkArray_PushBack(array, b);
	BkArray_PushBack(array, c);

	BkArray_Destroy(&array);

	TEST_ASSERT_EQUAL(BkArray_Size(array), 0);
	TEST_ASSERT_EQUAL(BkArray_Capacity(array), 0);
	TEST_ASSERT_NULL(array.data);
}

void BkArray_Erase_test(void)
{
	struct BkArray array;

	BkArray_Initialize(&array, sizeof(uint32));

	uint32 a = 50;
	uint32 b = 100;
	uint32 c = 150;

	BkArray_PushBack(array, a);
	BkArray_PushBack(array, b);
	BkArray_PushBack(array, c);

	BkArray_Erase(&array, 0);

	TEST_ASSERT_EQUAL(BkArray_At(array, uint32, 0), c);
	TEST_ASSERT_EQUAL(BkArray_Size(array), 2);
	TEST_ASSERT_EQUAL(BkArray_Capacity(array), 4);

	BkArray_Erase(&array, 1);

	TEST_ASSERT_EQUAL(BkArray_At(array, uint32, 0), c);
	TEST_ASSERT_EQUAL(BkArray_Size(array), 1);
	TEST_ASSERT_EQUAL(BkArray_Capacity(array), 4);

	BkArray_Erase(&array, 0);

	TEST_ASSERT_EQUAL(BkArray_Size(array), 0);
	TEST_ASSERT_EQUAL(BkArray_Capacity(array), 4);
	TEST_ASSERT_NOT_NULL(array.data);

	BkArray_Destroy(&array);
}

void BkArray_PopBack_test(void)
{
	struct BkArray array;

	BkArray_Initialize(&array, sizeof(uint32));

	uint32 a = 50;
	uint32 b = 100;
	uint32 c = 150;

	BkArray_PushBack(array, a);
	BkArray_PushBack(array, b);
	BkArray_PushBack(array, c);

	BkArray_PopBack(&array);

	TEST_ASSERT_EQUAL(BkArray_At(array, uint32, 0), a);
	TEST_ASSERT_EQUAL(BkArray_At(array, uint32, 1), b);
	TEST_ASSERT_EQUAL(BkArray_Size(array), 2);
	TEST_ASSERT_EQUAL(BkArray_Capacity(array), 4);

	BkArray_PopBack(&array);

	TEST_ASSERT_EQUAL(BkArray_At(array, uint32, 0), a);
	TEST_ASSERT_EQUAL(BkArray_Size(array), 1);
	TEST_ASSERT_EQUAL(BkArray_Capacity(array), 4);

	BkArray_PopBack(&array);

	TEST_ASSERT_EQUAL(BkArray_Size(array), 0);
	TEST_ASSERT_EQUAL(BkArray_Capacity(array), 4);
	TEST_ASSERT_NOT_NULL(array.data);

	BkArray_Destroy(&array);
}

void BkArray_Insert_test(void)
{
	struct BkArray array;

	BkArray_Initialize(&array, sizeof(uint32));

	uint32 a = 50;
	uint32 b = 100;
	uint32 c = 150;

	BkArray_Insert(array, 0, a);

	TEST_ASSERT_EQUAL(BkArray_At(array, uint32, 0), a);
	TEST_ASSERT_EQUAL(BkArray_Size(array), 1);
	TEST_ASSERT_EQUAL(BkArray_Capacity(array), 4);

	BkArray_Insert(array, 0, b);

	TEST_ASSERT_EQUAL(BkArray_At(array, uint32, 0), b);
	TEST_ASSERT_EQUAL(BkArray_At(array, uint32, 1), a);
	TEST_ASSERT_EQUAL(BkArray_Size(array), 2);
	TEST_ASSERT_EQUAL(BkArray_Capacity(array), 4);

	BkArray_Insert(array, 2, c);

	TEST_ASSERT_EQUAL(BkArray_At(array, uint32, 0), b);
	TEST_ASSERT_EQUAL(BkArray_At(array, uint32, 1), a);
	TEST_ASSERT_EQUAL(BkArray_At(array, uint32, 2), c);
	TEST_ASSERT_EQUAL(BkArray_Size(array), 3);
	TEST_ASSERT_EQUAL(BkArray_Capacity(array), 4);

	BkArray_Insert(array, 2, b);

	TEST_ASSERT_EQUAL(BkArray_At(array, uint32, 0), b);
	TEST_ASSERT_EQUAL(BkArray_At(array, uint32, 1), a);
	TEST_ASSERT_EQUAL(BkArray_At(array, uint32, 2), b);
	TEST_ASSERT_EQUAL(BkArray_At(array, uint32, 3), c);
	TEST_ASSERT_EQUAL(BkArray_Size(array), 4);
	TEST_ASSERT_EQUAL(BkArray_Capacity(array), 4);

	BkArray_Insert(array, 0, c);

	TEST_ASSERT_EQUAL(BkArray_At(array, uint32, 0), c);
	TEST_ASSERT_EQUAL(BkArray_At(array, uint32, 1), a);
	TEST_ASSERT_EQUAL(BkArray_At(array, uint32, 2), b);
	TEST_ASSERT_EQUAL(BkArray_At(array, uint32, 3), c);
	TEST_ASSERT_EQUAL(BkArray_At(array, uint32, 4), b);
	TEST_ASSERT_EQUAL(BkArray_Size(array), 5);
	TEST_ASSERT_EQUAL(BkArray_Capacity(array), 8);

	BkArray_Destroy(&array);
}

void BkArray_Resize_test(void)
{
	struct BkArray array;

	BkArray_Initialize(&array, sizeof(uint32));

	uint32 a = 50;
	uint32 b = 100;
	uint32 c = 150;

	BkArray_Resize(array, 4, a);

	TEST_ASSERT_EQUAL(BkArray_At(array, uint32, 0), a);
	TEST_ASSERT_EQUAL(BkArray_At(array, uint32, 1), a);
	TEST_ASSERT_EQUAL(BkArray_At(array, uint32, 2), a);
	TEST_ASSERT_EQUAL(BkArray_At(array, uint32, 3), a);
	TEST_ASSERT_EQUAL(BkArray_Size(array), 4);
	TEST_ASSERT_EQUAL(BkArray_Capacity(array), 8);

	BkArray_Resize(array, 2, b);

	TEST_ASSERT_EQUAL(BkArray_At(array, uint32, 0), a);
	TEST_ASSERT_EQUAL(BkArray_At(array, uint32, 1), a);
	TEST_ASSERT_EQUAL(BkArray_Size(array), 2);
	TEST_ASSERT_EQUAL(BkArray_Capacity(array), 8);

	BkArray_Resize(array, 2, c);

	TEST_ASSERT_EQUAL(BkArray_At(array, uint32, 0), a);
	TEST_ASSERT_EQUAL(BkArray_At(array, uint32, 1), a);
	TEST_ASSERT_EQUAL(BkArray_Size(array), 2);
	TEST_ASSERT_EQUAL(BkArray_Capacity(array), 8);

	BkArray_Destroy(&array);
}