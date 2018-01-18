// Unity headers.
#include <unity.h>

// Blackhart headers.
#include "blackhart.h"

// Test headers
#include "foundation/BkPoint3_test.h"

static float const ERROR_LIMIT = 0.00001f;

// ~~~~~ Def(PUBLIC) ~~~~~

void BkPoint3_RunTests(void)
{
	RUN_TEST(BkPoint3_Zero_test);
	RUN_TEST(BkPoint3_FromXYZ_test);
	RUN_TEST(BkPoint3_Set_test);
	RUN_TEST(BkPoint3_Copy_test);
	RUN_TEST(BkPoint3_Assign_test);
	RUN_TEST(BkPoint3_Add_BkVector3_test);
	RUN_TEST(BkPoint3_Sub_BkVector3_test);
	RUN_TEST(BkPoint3_Sub_BkPoint3_test);
	RUN_TEST(BkPoint3_Lerp_test);
	RUN_TEST(BkPoint3_Distance_test);
}

void BkPoint3_Zero_test(void)
{
	struct BkPoint3 p = BkPoint3_Zero();

	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)p.x, (float)0.0);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)p.y, (float)0.0);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)p.z, (float)0.0);
}

void	BkPoint3_FromXYZ_test(void)
{
	struct BkPoint3 p = BkPoint3_FromXYZ(BK_REAL(1), BK_REAL(2), BK_REAL(4.5));

	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)p.x, (float)1.0);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)p.y, (float)2.0);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)p.z, (float)4.5);
}

void BkPoint3_Set_test(void)
{
	struct BkPoint3 p = BkPoint3_Zero();

	BkPoint3_Set(&p, BK_REAL(1), BK_REAL(2), BK_REAL(4));

	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)p.x, (float)1.0);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)p.y, (float)2.0);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)p.z, (float)4.0);
}

void BkPoint3_Copy_test(void)
{
	struct BkPoint3 p = BkPoint3_Zero();

	BkPoint3_Set(&p, BK_REAL(1), BK_REAL(2), BK_REAL(4));

	struct BkPoint3 out = BkPoint3_Copy(&p);

	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)out.x, (float)1.0);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)out.y, (float)2.0);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)out.z, (float)4.0);
}

void BkPoint3_Assign_test(void)
{
	struct BkPoint3 p = BkPoint3_Zero();

	BkPoint3_Set(&p, BK_REAL(1), BK_REAL(2), BK_REAL(4));

	struct BkPoint3 out;

	BkPoint3_Assign(&out, &p);

	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)out.x, (float)1.0);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)out.y, (float)2.0);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)out.z, (float)4.0);
}

void BkPoint3_Add_BkVector3_test(void)
{
	struct BkPoint3 a = BkPoint3_Zero();
	struct BkVector3 b = BkVector3_Zero();

	BkPoint3_Set(&a, BK_REAL(1), BK_REAL(2), BK_REAL(3));
	BkVector3_Set(&b, BK_REAL(4), BK_REAL(5), BK_REAL(6));

	struct BkPoint3 out = BkPoint3_Add_BkVector3(&a, &b);

	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)out.x, (float)5.0);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)out.y, (float)7.0);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)out.z, (float)9.0);
}

void BkPoint3_Sub_BkVector3_test(void)
{
	struct BkPoint3 a = BkPoint3_Zero();
	struct BkVector3 b = BkVector3_Zero();

	BkPoint3_Set(&a, BK_REAL(1), BK_REAL(2), BK_REAL(3));
	BkVector3_Set(&b, BK_REAL(4), BK_REAL(5), BK_REAL(6));

	struct BkPoint3 out = BkPoint3_Sub_BkVector3(&a, &b);

	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)out.x, (float)-3.0);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)out.y, (float)-3.0);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)out.z, (float)-3.0);
}

void BkPoint3_Sub_BkPoint3_test(void)
{
	struct BkPoint3 a = BkPoint3_Zero();
	struct BkPoint3 b = BkPoint3_Zero();

	a.x = BK_REAL(2); a.y = BK_REAL(4); a.z = BK_REAL(8);
	b.x = BK_REAL(1); b.y = BK_REAL(3); b.z = BK_REAL(5);

	struct BkVector3 v = BkPoint3_Sub_BkPoint3(&a, &b);

	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)v.x, (float)1.0);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)v.y, (float)1.0);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)v.z, (float)3.0);
}

void BkPoint3_Lerp_test(void)
{
	struct BkPoint3 a = BkPoint3_Zero();
	struct BkPoint3 b = BkPoint3_Zero();

	BkPoint3_Set(&b, BK_REAL(1), BK_REAL(2), BK_REAL(4));

	struct BkPoint3 out = BkPoint3_Lerp(&a, &b, BK_REAL(0));

	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)out.x, (float)0.0);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)out.y, (float)0.0);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)out.z, (float)0.0);

	out = BkPoint3_Lerp(&a, &b, BK_REAL(1));

	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)out.x, (float)1.0);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)out.y, (float)2.0);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)out.z, (float)4.0);

	out = BkPoint3_Lerp(&a, &b, BK_REAL(0.5));

	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)out.x, (float)0.5);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)out.y, (float)1.0);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)out.z, (float)2.0);

	out = BkPoint3_Lerp(&b, &a, BK_REAL(0.5));

	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)out.x, (float)0.5);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)out.y, (float)1.0);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)out.z, (float)2.0);

	out = BkPoint3_Lerp(&b, &b, BK_REAL(0.5));

	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)out.x, (float)1.0);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)out.y, (float)2.0);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)out.z, (float)4.0);
}

void BkPoint3_Distance_test(void)
{
	struct BkPoint3 a = BkPoint3_Zero();
	struct BkPoint3 b = BkPoint3_Zero();

	BkPoint3_Set(&a, BK_REAL(5), BK_REAL(0), BK_REAL(0));
	BkPoint3_Set(&b, BK_REAL(-1), BK_REAL(8), BK_REAL(0));

	real d = BkPoint3_Distance(&a, &b);

	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)d, (float)10.0);
}