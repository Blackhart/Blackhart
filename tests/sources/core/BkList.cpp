#include <cstdlib>
#include <gtest\gtest.h>

#include "../export/cpp/Blackhart.hpp"

TEST(BkList, BkList_Empty)
{
	BkList* lpList = nullptr;

	EXPECT_TRUE(BkList_Empty(lpList));

	lpList = BkList_PushBack(lpList, NULL);

	EXPECT_FALSE(BkList_Empty(lpList));

	BkList_Clear(lpList);
}

TEST(BkList, BkList_Data)
{
	BkList* lpList = nullptr;
	uint32 lNumber = 5;

	lpList = BkList_PushBack(lpList, &lNumber);

	uint32* lResult = (uint32*)BkList_Data(lpList);

	EXPECT_EQ(*lResult, lNumber);

	BkList_Clear(lpList);
}

TEST(BkList, BkList_Front)
{
	uint32 lValue1 = 5;
	uint32 lValue2 = 10;
	uint32 lValue3 = 15;

	BkList* lpList1 = nullptr;
	BkList* lpList2 = nullptr;

	lpList1 = BkList_PushBack(lpList1, &lValue1);
	lpList1 = BkList_PushBack(lpList1, &lValue2);
	lpList1 = BkList_PushBack(lpList1, &lValue3);

	lpList1 = BkList_Front(lpList1);
	lpList2 = BkList_Front(lpList2);

	uint32* lResult = (uint32*)BkList_Data(lpList1);

	EXPECT_EQ(*lResult, lValue1);
	EXPECT_TRUE(lpList2 == nullptr);

	BkList_Clear(lpList1);
}

TEST(BkList, BkList_Back)
{
	uint32 lValue1 = 5;
	uint32 lValue2 = 10;
	uint32 lValue3 = 15;

	BkList* lpList1 = nullptr;
	BkList* lpList2 = nullptr;

	lpList1 = BkList_PushBack(lpList1, &lValue1);
	lpList1 = BkList_PushBack(lpList1, &lValue2);
	lpList1 = BkList_PushBack(lpList1, &lValue3);

	lpList1 = BkList_Back(lpList1);
	lpList2 = BkList_Back(lpList2);

	uint32* lResult = (uint32*)BkList_Data(lpList1);

	EXPECT_EQ(*lResult, lValue3);
	EXPECT_TRUE(lpList2 == nullptr);

	BkList_Clear(lpList1);
}

TEST(BkList, BkList_Size)
{
	uint32 lValue1 = 5;
	uint32 lValue2 = 10;
	uint32 lValue3 = 15;

	BkList* lpList1 = nullptr;

	lpList1 = BkList_PushBack(lpList1, &lValue1);
	lpList1 = BkList_PushBack(lpList1, &lValue2);
	lpList1 = BkList_PushBack(lpList1, &lValue3);

	EXPECT_EQ(BkList_Size(lpList1), 3);

	BkList_Clear(lpList1);
}

TEST(BkList, BkList_Clear)
{
	uint32 lValue1 = 5;
	uint32 lValue2 = 10;
	uint32 lValue3 = 15;

	BkList* lpList1 = nullptr;

	lpList1 = BkList_PushBack(lpList1, &lValue1);
	lpList1 = BkList_PushBack(lpList1, &lValue2);
	lpList1 = BkList_PushBack(lpList1, &lValue3);

	BkList_Clear(lpList1);
	lpList1 = nullptr;

	EXPECT_EQ(BkList_Size(lpList1), 0);
}

TEST(BkList, BkList_Get)
{
	uint32 lValue1 = 5;
	uint32 lValue2 = 10;
	uint32 lValue3 = 15;

	BkList* lpList1 = nullptr;

	lpList1 = BkList_PushBack(lpList1, &lValue1);
	lpList1 = BkList_PushBack(lpList1, &lValue2);
	lpList1 = BkList_PushBack(lpList1, &lValue3);

	uint32* lResult = nullptr;

	lpList1 = BkList_Get(lpList1, 0);
	lResult = (uint32*)BkList_Data(lpList1);
	EXPECT_EQ(*lResult, lValue1);

	lpList1 = BkList_Get(lpList1, 2);
	lResult = (uint32*)BkList_Data(lpList1);
	EXPECT_EQ(*lResult, lValue3);

	lpList1 = BkList_Get(lpList1, 1);
	lResult = (uint32*)BkList_Data(lpList1);
	EXPECT_EQ(*lResult, lValue2);

	EXPECT_EQ(BkList_Get(lpList1, 500), nullptr);

	BkList_Clear(lpList1);
}

TEST(BkList, BkList_Insert)
{
	uint32 lValue1 = 5;
	uint32 lValue2 = 10;
	uint32 lValue3 = 15;

	BkList* lpList1 = nullptr;

	lpList1 = BkList_Insert(lpList1, &lValue1, 0);
	lpList1 = BkList_Insert(lpList1, &lValue2, 0);
	lpList1 = BkList_Insert(lpList1, &lValue3, 1);
	lpList1 = BkList_Insert(lpList1, &lValue3, 10);

	uint32* lResult = nullptr;

	lpList1 = BkList_Get(lpList1, 0);
	lResult = (uint32*)BkList_Data(lpList1);
	EXPECT_EQ(*lResult, lValue2);

	lpList1 = BkList_Get(lpList1, 1);
	lResult = (uint32*)BkList_Data(lpList1);
	EXPECT_EQ(*lResult, lValue3);

	lpList1 = BkList_Get(lpList1, 2);
	lResult = (uint32*)BkList_Data(lpList1);
	EXPECT_EQ(*lResult, lValue1);

	lpList1 = BkList_Get(lpList1, 3);
	lResult = (uint32*)BkList_Data(lpList1);
	EXPECT_EQ(*lResult, lValue3);

	BkList_Clear(lpList1);
}

TEST(BkList, BkList_Erase)
{
	uint32 lValue1 = 5;
	uint32 lValue2 = 10;
	uint32 lValue3 = 15;

	BkList* lpList1 = nullptr;

	lpList1 = BkList_PushBack(lpList1, &lValue1);
	lpList1 = BkList_PushBack(lpList1, &lValue2);
	lpList1 = BkList_PushBack(lpList1, &lValue3);

	uint32* lResult = nullptr;

	lpList1 = BkList_Erase(lpList1, &lValue2);

	lpList1 = BkList_Get(lpList1, 0);
	lResult = (uint32*)BkList_Data(lpList1);
	EXPECT_EQ(*lResult, lValue1);
	EXPECT_EQ(BkList_Size(lpList1), 2);

	lpList1 = BkList_Get(lpList1, 1);
	lResult = (uint32*)BkList_Data(lpList1);
	EXPECT_EQ(*lResult, lValue3);

	lpList1 = BkList_Erase(lpList1, &lValue1);

	lpList1 = BkList_Get(lpList1, 0);
	lResult = (uint32*)BkList_Data(lpList1);
	EXPECT_EQ(*lResult, lValue3);
	EXPECT_EQ(BkList_Size(lpList1), 1);

	lpList1 = BkList_Erase(lpList1, &lValue3);

	EXPECT_EQ(lpList1, nullptr);
	EXPECT_EQ(BkList_Size(lpList1), 0);

	BkList_Clear(lpList1);
}

TEST(BkList, BkList_PushFront)
{
	uint32 lValue1 = 5;
	uint32 lValue2 = 10;
	uint32 lValue3 = 15;

	BkList* lpList1 = nullptr;

	uint32* lResult = nullptr;

	lpList1 = BkList_PushFront(lpList1, &lValue1);

	lpList1 = BkList_Front(lpList1);
	lResult = (uint32*)BkList_Data(lpList1);
	EXPECT_EQ(*lResult, lValue1);

	lpList1 = BkList_PushFront(lpList1, &lValue2);

	lpList1 = BkList_Front(lpList1);
	lResult = (uint32*)BkList_Data(lpList1);
	EXPECT_EQ(*lResult, lValue2);

	lpList1 = BkList_PushFront(lpList1, &lValue3);

	lpList1 = BkList_Front(lpList1);
	lResult = (uint32*)BkList_Data(lpList1);
	EXPECT_EQ(*lResult, lValue3);

	BkList_Clear(lpList1);
}

TEST(BkList, BkList_PushBack)
{
	uint32 lValue1 = 5;
	uint32 lValue2 = 10;
	uint32 lValue3 = 15;

	BkList* lpList1 = nullptr;

	uint32* lResult = nullptr;

	lpList1 = BkList_PushBack(lpList1, &lValue1);

	lpList1 = BkList_Back(lpList1);
	lResult = (uint32*)BkList_Data(lpList1);
	EXPECT_EQ(*lResult, lValue1);

	lpList1 = BkList_PushBack(lpList1, &lValue2);

	lpList1 = BkList_Back(lpList1);
	lResult = (uint32*)BkList_Data(lpList1);
	EXPECT_EQ(*lResult, lValue2);

	lpList1 = BkList_PushBack(lpList1, &lValue3);

	lpList1 = BkList_Back(lpList1);
	lResult = (uint32*)BkList_Data(lpList1);
	EXPECT_EQ(*lResult, lValue3);

	BkList_Clear(lpList1);
}

TEST(BkList, BkList_PopFront)
{
	uint32 lValue1 = 5;
	uint32 lValue2 = 10;
	uint32 lValue3 = 15;

	BkList* lpList1 = nullptr;

	lpList1 = BkList_PushBack(lpList1, &lValue1);
	lpList1 = BkList_PushBack(lpList1, &lValue2);
	lpList1 = BkList_PushBack(lpList1, &lValue3);

	uint32* lResult = nullptr;

	lpList1 = BkList_PopFront(lpList1);

	lpList1 = BkList_Front(lpList1);
	lResult = (uint32*)BkList_Data(lpList1);
	EXPECT_EQ(*lResult, lValue2);

	lpList1 = BkList_PopFront(lpList1);

	lpList1 = BkList_Front(lpList1);
	lResult = (uint32*)BkList_Data(lpList1);
	EXPECT_EQ(*lResult, lValue3);

	lpList1 = BkList_PopFront(lpList1);

	EXPECT_EQ(lpList1, nullptr);

	BkList_Clear(lpList1);
}

TEST(BkList, BkList_PopBack)
{
	uint32 lValue1 = 5;
	uint32 lValue2 = 10;
	uint32 lValue3 = 15;

	BkList* lpList1 = nullptr;

	lpList1 = BkList_PushBack(lpList1, &lValue1);
	lpList1 = BkList_PushBack(lpList1, &lValue2);
	lpList1 = BkList_PushBack(lpList1, &lValue3);

	uint32* lResult = nullptr;

	lpList1 = BkList_PopBack(lpList1);

	lpList1 = BkList_Back(lpList1);
	lResult = (uint32*)BkList_Data(lpList1);
	EXPECT_EQ(*lResult, lValue2);

	lpList1 = BkList_PopBack(lpList1);

	lpList1 = BkList_Back(lpList1);
	lResult = (uint32*)BkList_Data(lpList1);
	EXPECT_EQ(*lResult, lValue1);

	lpList1 = BkList_PopBack(lpList1);

	EXPECT_EQ(lpList1, nullptr);

	BkList_Clear(lpList1);
}