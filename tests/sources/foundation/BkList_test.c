// Unity headers.
#include <unity.h>

// Blackhart headers.
#include "blackhart.h"

// Test headers
#include "foundation/BkList_test.h"

// ~~~~~ Def(PUBLIC) ~~~~~

void BkList_RunTests(void)
{
	RUN_TEST(BkList_Empty_test);
	RUN_TEST(BkList_Data_test);
	RUN_TEST(BkList_Front_test);
	RUN_TEST(BkList_Back_test);
	RUN_TEST(BkList_Size_test);
	RUN_TEST(BkList_Clear_test);
	RUN_TEST(BkList_Get_test);
	RUN_TEST(BkList_Insert_test);
	RUN_TEST(BkList_Erase_test);
	RUN_TEST(BkList_EraseLink_test);
	RUN_TEST(BkList_PushFront_test);
	RUN_TEST(BkList_PushBack_test);
	RUN_TEST(BkList_PopFront_test);
	RUN_TEST(BkList_PopBack_test);
}

void BkList_Empty_test(void)
{
	struct BkList* lpList = NULL;

	TEST_ASSERT_TRUE(BkList_Empty(lpList));

	lpList = BkList_PushBack(lpList, NULL);

	TEST_ASSERT_FALSE(BkList_Empty(lpList));

	BkList_Clear(lpList);
}

void BkList_Data_test(void)
{
	struct BkList* lpList = NULL;
	uint32 lNumber = 5;

	lpList = BkList_PushBack(lpList, &lNumber);

	uint32* lResult = (uint32*)BkList_Data(lpList);

	TEST_ASSERT_EQUAL(*lResult, lNumber);

	BkList_Clear(lpList);
}

void BkList_Front_test(void)
{
	uint32 lValue1 = 5;
	uint32 lValue2 = 10;
	uint32 lValue3 = 15;

	struct BkList* lpList1 = NULL;
	struct BkList* lpList2 = NULL;

	lpList1 = BkList_PushBack(lpList1, &lValue1);
	lpList1 = BkList_PushBack(lpList1, &lValue2);
	lpList1 = BkList_PushBack(lpList1, &lValue3);

	lpList1 = BkList_Front(lpList1);
	lpList2 = BkList_Front(lpList2);

	uint32* lResult = (uint32*)BkList_Data(lpList1);

	TEST_ASSERT_EQUAL(*lResult, lValue1);
	TEST_ASSERT_NULL(lpList2);

	BkList_Clear(lpList1);
}

void BkList_Back_test(void)
{
	uint32 lValue1 = 5;
	uint32 lValue2 = 10;
	uint32 lValue3 = 15;

	struct BkList* lpList1 = NULL;
	struct BkList* lpList2 = NULL;

	lpList1 = BkList_PushBack(lpList1, &lValue1);
	lpList1 = BkList_PushBack(lpList1, &lValue2);
	lpList1 = BkList_PushBack(lpList1, &lValue3);

	lpList1 = BkList_Back(lpList1);
	lpList2 = BkList_Back(lpList2);

	uint32* lResult = (uint32*)BkList_Data(lpList1);

	TEST_ASSERT_EQUAL(*lResult, lValue3);
	TEST_ASSERT_NULL(lpList2);

	BkList_Clear(lpList1);
}

void BkList_Size_test(void)
{
	uint32 lValue1 = 5;
	uint32 lValue2 = 10;
	uint32 lValue3 = 15;

	struct BkList* lpList1 = NULL;

	lpList1 = BkList_PushBack(lpList1, &lValue1);
	lpList1 = BkList_PushBack(lpList1, &lValue2);
	lpList1 = BkList_PushBack(lpList1, &lValue3);

	TEST_ASSERT_EQUAL(BkList_Size(lpList1), 3);

	BkList_Clear(lpList1);
}

void BkList_Clear_test(void)
{
	uint32 lValue1 = 5;
	uint32 lValue2 = 10;
	uint32 lValue3 = 15;

	struct BkList* lpList1 = NULL;

	lpList1 = BkList_PushBack(lpList1, &lValue1);
	lpList1 = BkList_PushBack(lpList1, &lValue2);
	lpList1 = BkList_PushBack(lpList1, &lValue3);

	BkList_Clear(lpList1);
	lpList1 = NULL;

	TEST_ASSERT_EQUAL(BkList_Size(lpList1), 0);
}

void BkList_Get_test(void)
{
	uint32 lValue1 = 5;
	uint32 lValue2 = 10;
	uint32 lValue3 = 15;

	struct BkList* lpList1 = NULL;

	lpList1 = BkList_PushBack(lpList1, &lValue1);
	lpList1 = BkList_PushBack(lpList1, &lValue2);
	lpList1 = BkList_PushBack(lpList1, &lValue3);

	uint32* lResult = NULL;

	lpList1 = BkList_Get(lpList1, 0);
	lResult = (uint32*)BkList_Data(lpList1);
	TEST_ASSERT_EQUAL(*lResult, lValue1);

	lpList1 = BkList_Get(lpList1, 2);
	lResult = (uint32*)BkList_Data(lpList1);
	TEST_ASSERT_EQUAL(*lResult, lValue3);

	lpList1 = BkList_Get(lpList1, 1);
	lResult = (uint32*)BkList_Data(lpList1);
	TEST_ASSERT_EQUAL(*lResult, lValue2);

	TEST_ASSERT_EQUAL(BkList_Get(lpList1, 500), NULL);

	BkList_Clear(lpList1);
}

void BkList_Insert_test(void)
{
	uint32 lValue1 = 5;
	uint32 lValue2 = 10;
	uint32 lValue3 = 15;

	struct BkList* lpList1 = NULL;

	lpList1 = BkList_Insert(lpList1, &lValue1, 0);
	lpList1 = BkList_Insert(lpList1, &lValue2, 0);
	lpList1 = BkList_Insert(lpList1, &lValue3, 1);
	lpList1 = BkList_Insert(lpList1, &lValue3, 10);

	uint32* lResult = NULL;

	lpList1 = BkList_Get(lpList1, 0);
	lResult = (uint32*)BkList_Data(lpList1);
	TEST_ASSERT_EQUAL(*lResult, lValue2);

	lpList1 = BkList_Get(lpList1, 1);
	lResult = (uint32*)BkList_Data(lpList1);
	TEST_ASSERT_EQUAL(*lResult, lValue3);

	lpList1 = BkList_Get(lpList1, 2);
	lResult = (uint32*)BkList_Data(lpList1);
	TEST_ASSERT_EQUAL(*lResult, lValue1);

	lpList1 = BkList_Get(lpList1, 3);
	lResult = (uint32*)BkList_Data(lpList1);
	TEST_ASSERT_EQUAL(*lResult, lValue3);

	BkList_Clear(lpList1);
}

void BkList_Erase_test(void)
{
	uint32 lValue1 = 5;
	uint32 lValue2 = 10;
	uint32 lValue3 = 15;

	struct BkList* lpList1 = NULL;

	lpList1 = BkList_PushBack(lpList1, &lValue1);
	lpList1 = BkList_PushBack(lpList1, &lValue2);
	lpList1 = BkList_PushBack(lpList1, &lValue3);

	uint32* lResult = NULL;

	lpList1 = BkList_Erase(lpList1, &lValue2);

	lpList1 = BkList_Get(lpList1, 0);
	lResult = (uint32*)BkList_Data(lpList1);
	TEST_ASSERT_EQUAL(*lResult, lValue1);
	TEST_ASSERT_EQUAL(BkList_Size(lpList1), 2);

	lpList1 = BkList_Get(lpList1, 1);
	lResult = (uint32*)BkList_Data(lpList1);
	TEST_ASSERT_EQUAL(*lResult, lValue3);

	lpList1 = BkList_Erase(lpList1, &lValue1);

	lpList1 = BkList_Get(lpList1, 0);
	lResult = (uint32*)BkList_Data(lpList1);
	TEST_ASSERT_EQUAL(*lResult, lValue3);
	TEST_ASSERT_EQUAL(BkList_Size(lpList1), 1);

	lpList1 = BkList_Erase(lpList1, &lValue3);

	TEST_ASSERT_NULL(lpList1);
	TEST_ASSERT_EQUAL(BkList_Size(lpList1), 0);

	BkList_Clear(lpList1);
}

void BkList_EraseLink_test(void)
{
	uint32 lValue1 = 5;
	uint32 lValue2 = 10;
	uint32 lValue3 = 15;
	uint32 lValue4 = 20;
	uint32 lValue5 = 15;

	struct BkList* lpList1 = NULL;

	lpList1 = BkList_PushBack(lpList1, &lValue1);
	lpList1 = BkList_PushBack(lpList1, &lValue2);
	lpList1 = BkList_PushBack(lpList1, &lValue3);
	lpList1 = BkList_PushBack(lpList1, &lValue4);
	lpList1 = BkList_PushBack(lpList1, &lValue5);

	struct BkList* node = BkList_Get(lpList1, 1);

	lpList1 = BkList_EraseLink(node);

	uint32* r = (uint32*)BkList_Data(BkList_Get(lpList1, 1));
	TEST_ASSERT_NOT_NULL(r);
	TEST_ASSERT_EQUAL(lValue3, *r);

	node = BkList_Get(lpList1, 1);

	lpList1 = BkList_EraseLink(node);

	r = (uint32*)BkList_Data(BkList_Get(lpList1, 1));
	TEST_ASSERT_NOT_NULL(r);
	TEST_ASSERT_EQUAL(lValue4, *r);

	r = (uint32*)BkList_Data(BkList_Get(lpList1, 2));
	TEST_ASSERT_NOT_NULL(r);
	TEST_ASSERT_EQUAL(lValue5, *r);

	BkList_Clear(lpList1);
}

void BkList_PushFront_test(void)
{
	uint32 lValue1 = 5;
	uint32 lValue2 = 10;
	uint32 lValue3 = 15;

	struct BkList* lpList1 = NULL;

	uint32* lResult = NULL;

	lpList1 = BkList_PushFront(lpList1, &lValue1);

	lpList1 = BkList_Front(lpList1);
	lResult = (uint32*)BkList_Data(lpList1);
	TEST_ASSERT_EQUAL(*lResult, lValue1);

	lpList1 = BkList_PushFront(lpList1, &lValue2);

	lpList1 = BkList_Front(lpList1);
	lResult = (uint32*)BkList_Data(lpList1);
	TEST_ASSERT_EQUAL(*lResult, lValue2);

	lpList1 = BkList_PushFront(lpList1, &lValue3);

	lpList1 = BkList_Front(lpList1);
	lResult = (uint32*)BkList_Data(lpList1);
	TEST_ASSERT_EQUAL(*lResult, lValue3);

	BkList_Clear(lpList1);
}

void BkList_PushBack_test(void)
{
	uint32 lValue1 = 5;
	uint32 lValue2 = 10;
	uint32 lValue3 = 15;

	struct BkList* lpList1 = NULL;

	uint32* lResult = NULL;

	lpList1 = BkList_PushBack(lpList1, &lValue1);

	lpList1 = BkList_Back(lpList1);
	lResult = (uint32*)BkList_Data(lpList1);
	TEST_ASSERT_EQUAL(*lResult, lValue1);

	lpList1 = BkList_PushBack(lpList1, &lValue2);

	lpList1 = BkList_Back(lpList1);
	lResult = (uint32*)BkList_Data(lpList1);
	TEST_ASSERT_EQUAL(*lResult, lValue2);

	lpList1 = BkList_PushBack(lpList1, &lValue3);

	lpList1 = BkList_Back(lpList1);
	lResult = (uint32*)BkList_Data(lpList1);
	TEST_ASSERT_EQUAL(*lResult, lValue3);

	BkList_Clear(lpList1);
}

void BkList_PopFront_test(void)
{
	uint32 lValue1 = 5;
	uint32 lValue2 = 10;
	uint32 lValue3 = 15;

	struct BkList* lpList1 = NULL;

	lpList1 = BkList_PushBack(lpList1, &lValue1);
	lpList1 = BkList_PushBack(lpList1, &lValue2);
	lpList1 = BkList_PushBack(lpList1, &lValue3);

	uint32* lResult = NULL;

	lpList1 = BkList_PopFront(lpList1);

	lpList1 = BkList_Front(lpList1);
	lResult = (uint32*)BkList_Data(lpList1);
	TEST_ASSERT_EQUAL(*lResult, lValue2);

	lpList1 = BkList_PopFront(lpList1);

	lpList1 = BkList_Front(lpList1);
	lResult = (uint32*)BkList_Data(lpList1);
	TEST_ASSERT_EQUAL(*lResult, lValue3);

	lpList1 = BkList_PopFront(lpList1);

	TEST_ASSERT_NULL(lpList1);

	BkList_Clear(lpList1);
}

void BkList_PopBack_test(void)
{
	uint32 lValue1 = 5;
	uint32 lValue2 = 10;
	uint32 lValue3 = 15;

	struct BkList* lpList1 = NULL;

	lpList1 = BkList_PushBack(lpList1, &lValue1);
	lpList1 = BkList_PushBack(lpList1, &lValue2);
	lpList1 = BkList_PushBack(lpList1, &lValue3);

	uint32* lResult = NULL;

	lpList1 = BkList_PopBack(lpList1);

	lpList1 = BkList_Back(lpList1);
	lResult = (uint32*)BkList_Data(lpList1);
	TEST_ASSERT_EQUAL(*lResult, lValue2);

	lpList1 = BkList_PopBack(lpList1);

	lpList1 = BkList_Back(lpList1);
	lResult = (uint32*)BkList_Data(lpList1);
	TEST_ASSERT_EQUAL(*lResult, lValue1);

	lpList1 = BkList_PopBack(lpList1);

	TEST_ASSERT_NULL(lpList1);

	BkList_Clear(lpList1);
}