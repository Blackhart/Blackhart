#include <gtest\gtest.h>

#include "../export/cpp/Blackhart.hpp"

TEST(BkVector, BkVector_Initialize)
{
	BkVector vector;

	BkVector_Initialize(&vector, sizeof(int));

	EXPECT_EQ(vector.data_size, sizeof(int));

	BkVector_Destroy(&vector);
}

TEST(BkVector, BkVector_Reserve)
{
	BkVector vector;

	BkVector_Initialize(&vector, sizeof(int));
	BkVector_Reserve(&vector, 10);

	EXPECT_EQ(BkVector_Capacity(vector), 10);

	BkVector_Destroy(&vector);
}

TEST(BkVector, BkVector_PushBack)
{
	BkVector vector1;

	BkVector_Initialize(&vector1, sizeof(uint32));

	uint32 a = 50;
	uint32 b = 100;
	uint32 c = 150;

	BkVector_PushBack(vector1, a);
	BkVector_PushBack(vector1, b);
	BkVector_PushBack(vector1, c);

	EXPECT_EQ(BkVector_At(vector1, uint32, 0), a);
	EXPECT_EQ(BkVector_At(vector1, uint32, 1), b);

	c += a;

	EXPECT_NE(BkVector_At(vector1, uint32, 2), c);

	BkVector vector2;

	BkVector_Initialize(&vector2, sizeof(uint32*));

	uint32* d = &a;
	uint32* e = &b;
	uint32* f = &c;

	BkVector_PushBack(vector2, d);
	BkVector_PushBack(vector2, e);
	BkVector_PushBack(vector2, f);

	EXPECT_EQ(BkVector_At(vector2, uint32*, 0), d);
	EXPECT_EQ(*BkVector_At(vector2, uint32*, 1), *e);
	EXPECT_EQ(BkVector_At(vector2, uint32*, 2), f);

	c += b;

	EXPECT_EQ(*BkVector_At(vector2, uint32*, 2), *f);

	BkVector_Destroy(&vector1);
	BkVector_Destroy(&vector2);
}

TEST(BkVector, BkVector_Clear)
{
	BkVector vector;

	BkVector_Initialize(&vector, sizeof(uint32));

	uint32 a = 50;
	uint32 b = 100;
	uint32 c = 150;

	BkVector_PushBack(vector, a);
	BkVector_PushBack(vector, b);
	BkVector_PushBack(vector, c);

	BkVector_Clear(&vector);

	EXPECT_EQ(BkVector_Size(vector), 0);
	EXPECT_NE(BkVector_Capacity(vector), 0);
	EXPECT_FALSE(vector.data == NULL);

	BkVector_Destroy(&vector);
}

TEST(BkVector, BkVector_Destroy)
{
	BkVector vector;

	BkVector_Initialize(&vector, sizeof(uint32));

	uint32 a = 50;
	uint32 b = 100;
	uint32 c = 150;

	BkVector_PushBack(vector, a);
	BkVector_PushBack(vector, b);
	BkVector_PushBack(vector, c);

	BkVector_Destroy(&vector);

	EXPECT_EQ(BkVector_Size(vector), 0);
	EXPECT_EQ(BkVector_Capacity(vector), 0);
	EXPECT_TRUE(vector.data == nullptr);
}

TEST(BkVector, BkVector_Erase)
{
	BkVector vector;

	BkVector_Initialize(&vector, sizeof(uint32));

	uint32 a = 50;
	uint32 b = 100;
	uint32 c = 150;

	BkVector_PushBack(vector, a);
	BkVector_PushBack(vector, b);
	BkVector_PushBack(vector, c);

	BkVector_Erase(&vector, 0);

	EXPECT_EQ(BkVector_At(vector, uint32, 0), c);
	EXPECT_EQ(BkVector_Size(vector), 2);
	EXPECT_EQ(BkVector_Capacity(vector), 4);

	BkVector_Erase(&vector, 1);

	EXPECT_EQ(BkVector_At(vector, uint32, 0), c);
	EXPECT_EQ(BkVector_Size(vector), 1);
	EXPECT_EQ(BkVector_Capacity(vector), 4);

	BkVector_Erase(&vector, 0);

	EXPECT_EQ(BkVector_Size(vector), 0);
	EXPECT_EQ(BkVector_Capacity(vector), 4);
	EXPECT_FALSE(vector.data == NULL);

	BkVector_Destroy(&vector);
}

TEST(BkVector, BkVector_PopBack)
{
	BkVector vector;

	BkVector_Initialize(&vector, sizeof(uint32));

	uint32 a = 50;
	uint32 b = 100;
	uint32 c = 150;

	BkVector_PushBack(vector, a);
	BkVector_PushBack(vector, b);
	BkVector_PushBack(vector, c);

	BkVector_PopBack(&vector);

	EXPECT_EQ(BkVector_At(vector, uint32, 0), a);
	EXPECT_EQ(BkVector_At(vector, uint32, 1), b);
	EXPECT_EQ(BkVector_Size(vector), 2);
	EXPECT_EQ(BkVector_Capacity(vector), 4);

	BkVector_PopBack(&vector);

	EXPECT_EQ(BkVector_At(vector, uint32, 0), a);
	EXPECT_EQ(BkVector_Size(vector), 1);
	EXPECT_EQ(BkVector_Capacity(vector), 4);

	BkVector_PopBack(&vector);

	EXPECT_EQ(BkVector_Size(vector), 0);
	EXPECT_EQ(BkVector_Capacity(vector), 4);
	EXPECT_FALSE(vector.data == NULL);

	BkVector_Destroy(&vector);
}

TEST(BkVector, BkVector_Insert)
{
	BkVector vector;

	BkVector_Initialize(&vector, sizeof(uint32));

	uint32 a = 50;
	uint32 b = 100;
	uint32 c = 150;

	BkVector_Insert(vector, 0, a);

	EXPECT_EQ(BkVector_At(vector, uint32, 0), a);
	EXPECT_EQ(BkVector_Size(vector), 1);
	EXPECT_EQ(BkVector_Capacity(vector), 4);

	BkVector_Insert(vector, 0, b);

	EXPECT_EQ(BkVector_At(vector, uint32, 0), b);
	EXPECT_EQ(BkVector_At(vector, uint32, 1), a);
	EXPECT_EQ(BkVector_Size(vector), 2);
	EXPECT_EQ(BkVector_Capacity(vector), 4);

	BkVector_Insert(vector, 10, b);

	EXPECT_EQ(BkVector_At(vector, uint32, 0), b);
	EXPECT_EQ(BkVector_At(vector, uint32, 1), a);
	EXPECT_EQ(BkVector_Size(vector), 2);
	EXPECT_EQ(BkVector_Capacity(vector), 4);

	BkVector_Insert(vector, 2, c);

	EXPECT_EQ(BkVector_At(vector, uint32, 0), b);
	EXPECT_EQ(BkVector_At(vector, uint32, 1), a);
	EXPECT_EQ(BkVector_At(vector, uint32, 2), c);
	EXPECT_EQ(BkVector_Size(vector), 3);
	EXPECT_EQ(BkVector_Capacity(vector), 4);

	BkVector_Insert(vector, 2, b);

	EXPECT_EQ(BkVector_At(vector, uint32, 0), b);
	EXPECT_EQ(BkVector_At(vector, uint32, 1), a);
	EXPECT_EQ(BkVector_At(vector, uint32, 2), b);
	EXPECT_EQ(BkVector_At(vector, uint32, 3), c);
	EXPECT_EQ(BkVector_Size(vector), 4);
	EXPECT_EQ(BkVector_Capacity(vector), 4);

	BkVector_Insert(vector, 0, c);

	EXPECT_EQ(BkVector_At(vector, uint32, 0), c);
	EXPECT_EQ(BkVector_At(vector, uint32, 1), a);
	EXPECT_EQ(BkVector_At(vector, uint32, 2), b);
	EXPECT_EQ(BkVector_At(vector, uint32, 3), c);
	EXPECT_EQ(BkVector_At(vector, uint32, 4), b);
	EXPECT_EQ(BkVector_Size(vector), 5);
	EXPECT_EQ(BkVector_Capacity(vector), 8);

	BkVector_Destroy(&vector);
}

TEST(BkVector, BkVector_Resize)
{
	BkVector vector;

	BkVector_Initialize(&vector, sizeof(uint32));

	uint32 a = 50;
	uint32 b = 100;
	uint32 c = 150;

	BkVector_Resize(vector, 4, a);

	EXPECT_EQ(BkVector_At(vector, uint32, 0), a);
	EXPECT_EQ(BkVector_At(vector, uint32, 1), a);
	EXPECT_EQ(BkVector_At(vector, uint32, 2), a);
	EXPECT_EQ(BkVector_At(vector, uint32, 3), a);
	EXPECT_EQ(BkVector_Size(vector), 4);
	EXPECT_EQ(BkVector_Capacity(vector), 8);

	BkVector_Resize(vector, 2, b);

	EXPECT_EQ(BkVector_At(vector, uint32, 0), a);
	EXPECT_EQ(BkVector_At(vector, uint32, 1), a);
	EXPECT_EQ(BkVector_Size(vector), 2);
	EXPECT_EQ(BkVector_Capacity(vector), 8);

	BkVector_Resize(vector, 2, c);

	EXPECT_EQ(BkVector_At(vector, uint32, 0), a);
	EXPECT_EQ(BkVector_At(vector, uint32, 1), a);
	EXPECT_EQ(BkVector_Size(vector), 2);
	EXPECT_EQ(BkVector_Capacity(vector), 8);

	BkVector_Destroy(&vector);
}