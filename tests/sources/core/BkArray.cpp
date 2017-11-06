#include <gtest\gtest.h>

#include "../export/cpp/Blackhart.hpp"

TEST(BkArray, BkArray_Initialize)
{
	BkArray array;

	BkArray_Initialize(&array, sizeof(int));

	EXPECT_EQ(array.data_size, sizeof(int));

	BkArray_Destroy(&array);
}

TEST(BkArray, BkArray_Reserve)
{
	BkArray array;

	BkArray_Initialize(&array, sizeof(int));
	BkArray_Reserve(&array, 10);

	EXPECT_EQ(BkArray_Capacity(array), 10);

	BkArray_Destroy(&array);
}

TEST(BkArray, BkArray_PushBack)
{
	BkArray array1;

	BkArray_Initialize(&array1, sizeof(uint32));

	uint32 a = 50;
	uint32 b = 100;
	uint32 c = 150;

	BkArray_PushBack(array1, a);
	BkArray_PushBack(array1, b);
	BkArray_PushBack(array1, c);

	EXPECT_EQ(BkArray_At(array1, uint32, 0), a);
	EXPECT_EQ(BkArray_At(array1, uint32, 1), b);

	c += a;

	EXPECT_NE(BkArray_At(array1, uint32, 2), c);

	BkArray array2;

	BkArray_Initialize(&array2, sizeof(uint32*));

	uint32* d = &a;
	uint32* e = &b;
	uint32* f = &c;

	BkArray_PushBack(array2, d);
	BkArray_PushBack(array2, e);
	BkArray_PushBack(array2, f);

	EXPECT_EQ(BkArray_At(array2, uint32*, 0), d);
	EXPECT_EQ(*BkArray_At(array2, uint32*, 1), *e);
	EXPECT_EQ(BkArray_At(array2, uint32*, 2), f);

	c += b;

	EXPECT_EQ(*BkArray_At(array2, uint32*, 2), *f);

	BkArray_Destroy(&array1);
	BkArray_Destroy(&array2);
}

TEST(BkArray, BkArray_Clear)
{
	BkArray array;

	BkArray_Initialize(&array, sizeof(uint32));

	uint32 a = 50;
	uint32 b = 100;
	uint32 c = 150;

	BkArray_PushBack(array, a);
	BkArray_PushBack(array, b);
	BkArray_PushBack(array, c);

	BkArray_Clear(&array);

	EXPECT_EQ(BkArray_Size(array), 0);
	EXPECT_NE(BkArray_Capacity(array), 0);
	EXPECT_FALSE(array.data == NULL);

	BkArray_Destroy(&array);
}

TEST(BkArray, BkArray_Destroy)
{
	BkArray array;

	BkArray_Initialize(&array, sizeof(uint32));

	uint32 a = 50;
	uint32 b = 100;
	uint32 c = 150;

	BkArray_PushBack(array, a);
	BkArray_PushBack(array, b);
	BkArray_PushBack(array, c);

	BkArray_Destroy(&array);

	EXPECT_EQ(BkArray_Size(array), 0);
	EXPECT_EQ(BkArray_Capacity(array), 0);
	EXPECT_TRUE(array.data == nullptr);
}

TEST(BkArray, BkArray_Erase)
{
	BkArray array;

	BkArray_Initialize(&array, sizeof(uint32));

	uint32 a = 50;
	uint32 b = 100;
	uint32 c = 150;

	BkArray_PushBack(array, a);
	BkArray_PushBack(array, b);
	BkArray_PushBack(array, c);

	BkArray_Erase(&array, 0);

	EXPECT_EQ(BkArray_At(array, uint32, 0), c);
	EXPECT_EQ(BkArray_Size(array), 2);
	EXPECT_EQ(BkArray_Capacity(array), 4);

	BkArray_Erase(&array, 1);

	EXPECT_EQ(BkArray_At(array, uint32, 0), c);
	EXPECT_EQ(BkArray_Size(array), 1);
	EXPECT_EQ(BkArray_Capacity(array), 4);

	BkArray_Erase(&array, 0);

	EXPECT_EQ(BkArray_Size(array), 0);
	EXPECT_EQ(BkArray_Capacity(array), 4);
	EXPECT_FALSE(array.data == NULL);

	BkArray_Destroy(&array);
}

TEST(BkArray, BkArray_PopBack)
{
	BkArray array;

	BkArray_Initialize(&array, sizeof(uint32));

	uint32 a = 50;
	uint32 b = 100;
	uint32 c = 150;

	BkArray_PushBack(array, a);
	BkArray_PushBack(array, b);
	BkArray_PushBack(array, c);

	BkArray_PopBack(&array);

	EXPECT_EQ(BkArray_At(array, uint32, 0), a);
	EXPECT_EQ(BkArray_At(array, uint32, 1), b);
	EXPECT_EQ(BkArray_Size(array), 2);
	EXPECT_EQ(BkArray_Capacity(array), 4);

	BkArray_PopBack(&array);

	EXPECT_EQ(BkArray_At(array, uint32, 0), a);
	EXPECT_EQ(BkArray_Size(array), 1);
	EXPECT_EQ(BkArray_Capacity(array), 4);

	BkArray_PopBack(&array);

	EXPECT_EQ(BkArray_Size(array), 0);
	EXPECT_EQ(BkArray_Capacity(array), 4);
	EXPECT_FALSE(array.data == NULL);

	BkArray_Destroy(&array);
}

TEST(BkArray, BkArray_Insert)
{
	BkArray array;

	BkArray_Initialize(&array, sizeof(uint32));

	uint32 a = 50;
	uint32 b = 100;
	uint32 c = 150;

	BkArray_Insert(array, 0, a);

	EXPECT_EQ(BkArray_At(array, uint32, 0), a);
	EXPECT_EQ(BkArray_Size(array), 1);
	EXPECT_EQ(BkArray_Capacity(array), 4);

	BkArray_Insert(array, 0, b);

	EXPECT_EQ(BkArray_At(array, uint32, 0), b);
	EXPECT_EQ(BkArray_At(array, uint32, 1), a);
	EXPECT_EQ(BkArray_Size(array), 2);
	EXPECT_EQ(BkArray_Capacity(array), 4);

	BkArray_Insert(array, 10, b);

	EXPECT_EQ(BkArray_At(array, uint32, 0), b);
	EXPECT_EQ(BkArray_At(array, uint32, 1), a);
	EXPECT_EQ(BkArray_Size(array), 2);
	EXPECT_EQ(BkArray_Capacity(array), 4);

	BkArray_Insert(array, 2, c);

	EXPECT_EQ(BkArray_At(array, uint32, 0), b);
	EXPECT_EQ(BkArray_At(array, uint32, 1), a);
	EXPECT_EQ(BkArray_At(array, uint32, 2), c);
	EXPECT_EQ(BkArray_Size(array), 3);
	EXPECT_EQ(BkArray_Capacity(array), 4);

	BkArray_Insert(array, 2, b);

	EXPECT_EQ(BkArray_At(array, uint32, 0), b);
	EXPECT_EQ(BkArray_At(array, uint32, 1), a);
	EXPECT_EQ(BkArray_At(array, uint32, 2), b);
	EXPECT_EQ(BkArray_At(array, uint32, 3), c);
	EXPECT_EQ(BkArray_Size(array), 4);
	EXPECT_EQ(BkArray_Capacity(array), 4);

	BkArray_Insert(array, 0, c);

	EXPECT_EQ(BkArray_At(array, uint32, 0), c);
	EXPECT_EQ(BkArray_At(array, uint32, 1), a);
	EXPECT_EQ(BkArray_At(array, uint32, 2), b);
	EXPECT_EQ(BkArray_At(array, uint32, 3), c);
	EXPECT_EQ(BkArray_At(array, uint32, 4), b);
	EXPECT_EQ(BkArray_Size(array), 5);
	EXPECT_EQ(BkArray_Capacity(array), 8);

	BkArray_Destroy(&array);
}

TEST(BkArray, BkArray_Resize)
{
	BkArray array;

	BkArray_Initialize(&array, sizeof(uint32));

	uint32 a = 50;
	uint32 b = 100;
	uint32 c = 150;

	BkArray_Resize(array, 4, a);

	EXPECT_EQ(BkArray_At(array, uint32, 0), a);
	EXPECT_EQ(BkArray_At(array, uint32, 1), a);
	EXPECT_EQ(BkArray_At(array, uint32, 2), a);
	EXPECT_EQ(BkArray_At(array, uint32, 3), a);
	EXPECT_EQ(BkArray_Size(array), 4);
	EXPECT_EQ(BkArray_Capacity(array), 8);

	BkArray_Resize(array, 2, b);

	EXPECT_EQ(BkArray_At(array, uint32, 0), a);
	EXPECT_EQ(BkArray_At(array, uint32, 1), a);
	EXPECT_EQ(BkArray_Size(array), 2);
	EXPECT_EQ(BkArray_Capacity(array), 8);

	BkArray_Resize(array, 2, c);

	EXPECT_EQ(BkArray_At(array, uint32, 0), a);
	EXPECT_EQ(BkArray_At(array, uint32, 1), a);
	EXPECT_EQ(BkArray_Size(array), 2);
	EXPECT_EQ(BkArray_Capacity(array), 8);

	BkArray_Destroy(&array);
}