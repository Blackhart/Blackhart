#include <cstdlib>
#include <gtest\gtest.h>

#include "../export/cpp/Blackhart.hpp"

TEST(BkQueue, BkQueue_Initialize)
{
	struct BkQueue queue;

	BkQueue_Initialize(&queue);

	EXPECT_TRUE(queue.list == NULL);
	EXPECT_EQ(BkQueue_Size(&queue), 0);
}

TEST(BkQueue, BkQueue_Push)
{
	struct BkQueue queue;

	BkQueue_Initialize(&queue);

	const int8 val1 = 1;
	const int8 val2 = 2;

	BkQueue_Push(&queue, (void*)&val1);

	EXPECT_EQ(BkQueue_Size(&queue), 1);
	EXPECT_EQ(*((int8*)(BkQueue_Back(&queue))), 1);

	BkQueue_Push(&queue, (void*)&val2);

	EXPECT_EQ(BkQueue_Size(&queue), 2);
	EXPECT_EQ(*((int8*)(BkQueue_Back(&queue))), 2);

	BkQueue_Clear(&queue);
}

TEST(BkQueue, BkQueue_Empty)
{
	struct BkQueue queue;

	BkQueue_Initialize(&queue);

	EXPECT_TRUE(BkQueue_Empty(&queue));

	const int8 val1 = 1;
	const int8 val2 = 2;

	BkQueue_Push(&queue, (void*)&val1);
	BkQueue_Push(&queue, (void*)&val2);

	EXPECT_FALSE(BkQueue_Empty(&queue));

	BkQueue_Clear(&queue);
}

TEST(BkQueue, BkQueue_Size)
{
	struct BkQueue queue;

	BkQueue_Initialize(&queue);

	EXPECT_EQ(BkQueue_Size(&queue), 0);

	const int8 val1 = 1;
	const int8 val2 = 2;

	BkQueue_Push(&queue, (void*)&val1);

	EXPECT_EQ(BkQueue_Size(&queue), 1);

	BkQueue_Push(&queue, (void*)&val2);

	EXPECT_EQ(BkQueue_Size(&queue), 2);

	BkQueue_Pop(&queue);

	EXPECT_EQ(BkQueue_Size(&queue), 1);

	BkQueue_Pop(&queue);

	EXPECT_EQ(BkQueue_Size(&queue), 0);

	BkQueue_Pop(&queue);

	EXPECT_EQ(BkQueue_Size(&queue), 0);

	BkQueue_Clear(&queue);
}

TEST(BkQueue, BkQueue_Pop)
{
	struct BkQueue queue;

	BkQueue_Initialize(&queue);

	const int8 val1 = 1;
	const int8 val2 = 2;

	BkQueue_Push(&queue, (void*)&val1);
	BkQueue_Push(&queue, (void*)&val2);

	BkQueue_Pop(&queue);

	EXPECT_EQ(BkQueue_Size(&queue), 1);
	EXPECT_EQ(*((int8*)(BkQueue_Front(&queue))), 2);

	BkQueue_Pop(&queue);

	EXPECT_EQ(BkQueue_Size(&queue), 0);
	EXPECT_TRUE(BkQueue_Front(&queue) == NULL);

	BkQueue_Pop(&queue);

	EXPECT_EQ(BkQueue_Size(&queue), 0);
	EXPECT_TRUE(BkQueue_Front(&queue) == NULL);

	BkQueue_Clear(&queue);
}

TEST(BkQueue, BkQueue_Front)
{
	struct BkQueue queue;

	BkQueue_Initialize(&queue);

	EXPECT_TRUE(BkQueue_Front(&queue) == NULL);

	const int8 val1 = 1;
	const int8 val2 = 2;

	BkQueue_Push(&queue, (void*)&val1);
	
	EXPECT_EQ(*((int8*)(BkQueue_Front(&queue))), 1);

	BkQueue_Push(&queue, (void*)&val2);
	
	EXPECT_EQ(*((int8*)(BkQueue_Front(&queue))), 1);

	BkQueue_Pop(&queue);

	EXPECT_EQ(*((int8*)(BkQueue_Front(&queue))), 2);

	BkQueue_Pop(&queue);

	EXPECT_TRUE(BkQueue_Front(&queue) == NULL);

	BkQueue_Clear(&queue);
}

TEST(BkQueue, BkQueue_Back)
{
	struct BkQueue queue;

	BkQueue_Initialize(&queue);

	EXPECT_TRUE(BkQueue_Back(&queue) == NULL);

	const int8 val1 = 1;
	const int8 val2 = 2;

	BkQueue_Push(&queue, (void*)&val1);
	
	EXPECT_EQ(*((int8*)(BkQueue_Back(&queue))), 1);

	BkQueue_Push(&queue, (void*)&val2);

	EXPECT_EQ(*((int8*)(BkQueue_Back(&queue))), 2);

	BkQueue_Pop(&queue);

	EXPECT_EQ(*((int8*)(BkQueue_Back(&queue))), 2);

	BkQueue_Pop(&queue);

	EXPECT_TRUE(BkQueue_Back(&queue) == NULL);

	BkQueue_Clear(&queue);
}

TEST(BkQueue, BkQueue_Clear)
{
	struct BkQueue queue;

	BkQueue_Initialize(&queue);

	const int8 val1 = 1;
	const int8 val2 = 2;

	BkQueue_Push(&queue, (void*)&val1);
	BkQueue_Push(&queue, (void*)&val2);

	BkQueue_Clear(&queue);

	EXPECT_TRUE(BkQueue_Empty(&queue));
	EXPECT_TRUE(BkQueue_Front(&queue) == NULL);
}