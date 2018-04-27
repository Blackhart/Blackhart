// Unity headers.
#include <unity.h>

// Blackhart headers.
#include "blackhart.h"

// Test headers
#include "foundation/BkQueue_test.h"

// ~~~~~ Def(PUBLIC) ~~~~~

void BkQueue_RunTests(void)
{
	RUN_TEST(BkQueue_Initialize_test);
	RUN_TEST(BkQueue_Push_test);
	RUN_TEST(BkQueue_Empty_test);
	RUN_TEST(BkQueue_Size_test);
	RUN_TEST(BkQueue_Pop_test);
	RUN_TEST(BkQueue_Front_test);
	RUN_TEST(BkQueue_Back_test);
	RUN_TEST(BkQueue_Clear_test);
}

void BkQueue_Initialize_test(void)
{
	struct BkQueue queue;

	BkQueue_Initialize(&queue);

	TEST_ASSERT_NULL(queue.list);
	TEST_ASSERT_EQUAL(BkQueue_Size(&queue), 0);
}

void BkQueue_Push_test(void)
{
	struct BkQueue queue;

	BkQueue_Initialize(&queue);

	const int8 val1 = 1;
	const int8 val2 = 2;

	BkQueue_Push(&queue, (void*)&val1);

	TEST_ASSERT_EQUAL(BkQueue_Size(&queue), 1);
	TEST_ASSERT_EQUAL(*((int8*)(BkQueue_Back(&queue))), 1);

	BkQueue_Push(&queue, (void*)&val2);

	TEST_ASSERT_EQUAL(BkQueue_Size(&queue), 2);
	TEST_ASSERT_EQUAL(*((int8*)(BkQueue_Back(&queue))), 2);

	BkQueue_Clear(&queue);
}

void BkQueue_Empty_test(void)
{
	struct BkQueue queue;

	BkQueue_Initialize(&queue);

	TEST_ASSERT_TRUE(BkQueue_Empty(&queue));

	const int8 val1 = 1;
	const int8 val2 = 2;

	BkQueue_Push(&queue, (void*)&val1);
	BkQueue_Push(&queue, (void*)&val2);

	TEST_ASSERT_FALSE(BkQueue_Empty(&queue));

	BkQueue_Clear(&queue);
}

void BkQueue_Size_test(void)
{
	struct BkQueue queue;

	BkQueue_Initialize(&queue);

	TEST_ASSERT_EQUAL(BkQueue_Size(&queue), 0);

	const int8 val1 = 1;
	const int8 val2 = 2;

	BkQueue_Push(&queue, (void*)&val1);

	TEST_ASSERT_EQUAL(BkQueue_Size(&queue), 1);

	BkQueue_Push(&queue, (void*)&val2);

	TEST_ASSERT_EQUAL(BkQueue_Size(&queue), 2);

	BkQueue_Pop(&queue);

	TEST_ASSERT_EQUAL(BkQueue_Size(&queue), 1);

	BkQueue_Pop(&queue);

	TEST_ASSERT_EQUAL(BkQueue_Size(&queue), 0);

	BkQueue_Pop(&queue);

	TEST_ASSERT_EQUAL(BkQueue_Size(&queue), 0);

	BkQueue_Clear(&queue);
}

void BkQueue_Pop_test(void)
{
	struct BkQueue queue;

	BkQueue_Initialize(&queue);

	const int8 val1 = 1;
	const int8 val2 = 2;

	BkQueue_Push(&queue, (void*)&val1);
	BkQueue_Push(&queue, (void*)&val2);

	BkQueue_Pop(&queue);

	TEST_ASSERT_EQUAL(BkQueue_Size(&queue), 1);
	TEST_ASSERT_EQUAL(*((int8*)(BkQueue_Front(&queue))), 2);

	BkQueue_Pop(&queue);

	TEST_ASSERT_EQUAL(BkQueue_Size(&queue), 0);
	TEST_ASSERT_NULL(BkQueue_Front(&queue));

	BkQueue_Pop(&queue);

	TEST_ASSERT_EQUAL(BkQueue_Size(&queue), 0);
	TEST_ASSERT_NULL(BkQueue_Front(&queue));

	BkQueue_Clear(&queue);
}

void BkQueue_Front_test(void)
{
	struct BkQueue queue;

	BkQueue_Initialize(&queue);

	TEST_ASSERT_NULL(BkQueue_Front(&queue));

	const int8 val1 = 1;
	const int8 val2 = 2;

	BkQueue_Push(&queue, (void*)&val1);
	
	TEST_ASSERT_EQUAL(*((int8*)(BkQueue_Front(&queue))), 1);

	BkQueue_Push(&queue, (void*)&val2);
	
	TEST_ASSERT_EQUAL(*((int8*)(BkQueue_Front(&queue))), 1);

	BkQueue_Pop(&queue);

	TEST_ASSERT_EQUAL(*((int8*)(BkQueue_Front(&queue))), 2);

	BkQueue_Pop(&queue);

	TEST_ASSERT_NULL(BkQueue_Front(&queue));

	BkQueue_Clear(&queue);
}

void BkQueue_Back_test(void)
{
	struct BkQueue queue;

	BkQueue_Initialize(&queue);

	TEST_ASSERT_NULL(BkQueue_Back(&queue));

	const int8 val1 = 1;
	const int8 val2 = 2;

	BkQueue_Push(&queue, (void*)&val1);
	
	TEST_ASSERT_EQUAL(*((int8*)(BkQueue_Back(&queue))), 1);

	BkQueue_Push(&queue, (void*)&val2);

	TEST_ASSERT_EQUAL(*((int8*)(BkQueue_Back(&queue))), 2);

	BkQueue_Pop(&queue);

	TEST_ASSERT_EQUAL(*((int8*)(BkQueue_Back(&queue))), 2);

	BkQueue_Pop(&queue);

	TEST_ASSERT_NULL(BkQueue_Back(&queue));

	BkQueue_Clear(&queue);
}

void BkQueue_Clear_test(void)
{
	struct BkQueue queue;

	BkQueue_Initialize(&queue);

	const int8 val1 = 1;
	const int8 val2 = 2;

	BkQueue_Push(&queue, (void*)&val1);
	BkQueue_Push(&queue, (void*)&val2);

	BkQueue_Clear(&queue);

	TEST_ASSERT_TRUE(BkQueue_Empty(&queue));
	TEST_ASSERT_NULL(BkQueue_Front(&queue));
}