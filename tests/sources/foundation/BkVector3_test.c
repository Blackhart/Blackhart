// Unity headers.
#include <unity.h>

// Blackhart headers.
#include "blackhart.h"

// Test headers
#include "foundation/BkVector3_test.h"

static float const ERROR_LIMIT = 0.00001f;

// ~~~~~ Def(PUBLIC) ~~~~~

void BkVector3_RunTests(void)
{
	RUN_TEST(BkVector3_Zero_test);
	RUN_TEST(BkVector3_FromXYZ_test);
	RUN_TEST(BkVector3_Set_test);
	RUN_TEST(BkVector3_Copy_test);
	RUN_TEST(BkVector3_Assign_test);
	RUN_TEST(BkVector3_Negate_test);
	RUN_TEST(BkVector3_Mul_Real_test);
	RUN_TEST(BkVector3_Div_Real_test);
	RUN_TEST(BkVector3_Add_BkVector3_test);
	RUN_TEST(BkVector3_Sub_BkVector3_test);
	RUN_TEST(BkVector3_Magnitude_test);
	RUN_TEST(BkVector3_Normalize_test);
	RUN_TEST(BkVector3_Dot_test);
	RUN_TEST(BkVector3_AbsDot_test);
	RUN_TEST(BkVector3_Cross_test);
	RUN_TEST(BkVector3_Angle_test);
	RUN_TEST(BkVector3_Lerp_test);
	RUN_TEST(BkVector3_Max_test);
	RUN_TEST(BkVector3_Min_test);
}

void BkVector3_Zero_test(void)
{
	struct BkVector3 v = BkVector3_Zero();

	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)v.x, (float)0.0);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)v.y, (float)0.0);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)v.z, (float)0.0);
}

void	BkVector3_FromXYZ_test(void)
{
	struct BkVector3 v = BkVector3_FromXYZ(BK_REAL(1), BK_REAL(2.0), BK_REAL(4.5));

	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)v.x, (float)1.0);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)v.y, (float)2.0);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)v.z, (float)4.5);
}

void BkVector3_Set_test(void)
{
	struct BkVector3 v = BkVector3_Zero();

	BkVector3_Set(&v, BK_REAL(1.0), BK_REAL(2.0), BK_REAL(4.0));

	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)v.x, (float)1.0);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)v.y, (float)2.0);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)v.z, (float)4.0);
}

void BkVector3_Copy_test(void)
{
	struct BkVector3 v = BkVector3_Zero();

	BkVector3_Set(&v, BK_REAL(1.0), BK_REAL(2.0), BK_REAL(4.0));

	struct BkVector3 out = BkVector3_Copy(&v);

	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)out.x, (float)1.0);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)out.y, (float)2.0);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)out.z, (float)4.0);
}

void BkVector3_Assign_test(void)
{
	struct BkVector3 v = BkVector3_Zero();

	BkVector3_Set(&v, BK_REAL(1.0), BK_REAL(2.0), BK_REAL(4.0));

	struct BkVector3 out;

	BkVector3_Assign(&out, &v);

	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)out.x, (float)1.0);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)out.y, (float)2.0);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)out.z, (float)4.0);
}

void BkVector3_Negate_test(void)
{
	struct BkVector3 v = BkVector3_Zero();

	BkVector3_Set(&v, BK_REAL(2.0), BK_REAL(4.0), BK_REAL(8.0));

	v = BkVector3_Negate(&v);

	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)v.x, (float)-2.0);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)v.y, (float)-4.0);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)v.z, (float)-8.0);
}

void BkVector3_Mul_Real_test(void)
{
	struct BkVector3 v = BkVector3_Zero();

	BkVector3_Set(&v, BK_REAL(1.0), BK_REAL(2.0), BK_REAL(3.0));

	v = BkVector3_Mul_Real(&v, 2.0);

	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)v.x, (float)1.0 * (float)2.0);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)v.y, (float)2.0 * (float)2.0);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)v.z, (float)3.0 * (float)2.0);

	BkVector3_Set(&v, BK_REAL(-5.4), BK_REAL(0.0), BK_REAL(3.0));

	v = BkVector3_Mul_Real(&v, BK_REAL(-3.0));

	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)v.x, (float)-5.4 * (float)-3.0);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)v.y, (float)0.0 * (float)-3.0);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)v.z, (float)3.0 * (float)-3.0);
}

void BkVector3_Div_Real_test(void)
{
	struct BkVector3 v = BkVector3_Zero();

	BkVector3_Set(&v, BK_REAL(4.7), BK_REAL(-6.0), BK_REAL(8.0));

	v = BkVector3_Div_Real(&v, BK_REAL(2.0));

	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)v.x, (float)4.7 / (float)2.0);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)v.y, (float)-6.0 / (float)2.0);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)v.z, (float)8.0 / (float)2.0);
}

void BkVector3_Add_BkVector3_test(void)
{
	struct BkVector3 a = BkVector3_Zero();
	struct BkVector3 b = BkVector3_Zero();
	
	BkVector3_Set(&a, BK_REAL(1.0), BK_REAL(2.0), BK_REAL(3.0));
	BkVector3_Set(&b, BK_REAL(4.0), BK_REAL(5.0), BK_REAL(6.0));

	struct BkVector3 out = BkVector3_Add_BkVector3(&a, &b);

	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)out.x, (float)5.0);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)out.y, (float)7.0);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)out.z, (float)9.0);
}

void BkVector3_Sub_BkVector3_test(void)
{
	struct BkVector3 a = BkVector3_Zero();
	struct BkVector3 b = BkVector3_Zero();

	BkVector3_Set(&a, BK_REAL(1.0), BK_REAL(2.0), BK_REAL(3.0));
	BkVector3_Set(&b, BK_REAL(4.0), BK_REAL(5.0), BK_REAL(6.0));

	struct BkVector3 out = BkVector3_Sub_BkVector3(&a, &b);

	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)out.x, (float)-3.0);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)out.y, (float)-3.0);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)out.z, (float)-3.0);
}

void BkVector3_Magnitude_test(void)
{
	struct BkVector3 v = BkVector3_Zero();

	BkVector3_Set(&v, BK_REAL(5.0), BK_REAL(-4.0), BK_REAL(7.0));

	real out = BkVector3_Magnitude(&v);

	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)out, (float)sqrt(90.0));
}

void BkVector3_Normalize_test(void)
{
	struct BkVector3 v = BkVector3_Zero();

	BkVector3_Set(&v, BK_REAL(12.0), BK_REAL(-5.0), BK_REAL(8.0));

	struct BkVector3 out = BkVector3_Normalize(&v);

	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)out.x, (float)12.0 / (float)sqrt(233));
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)out.y, (float)-5.0 / (float)sqrt(233));
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)out.z, (float)8.0 / (float)sqrt(233));

	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)BkVector3_Magnitude(&out), (float)1.0);
}

void BkVector3_Dot_test(void)
{
	struct BkVector3 a = BkVector3_Zero();
	struct BkVector3 b = BkVector3_Zero();

	BkVector3_Set(&a, BK_REAL(3.0), BK_REAL(-2.0), BK_REAL(7.0));
	BkVector3_Set(&b, BK_REAL(0.0), BK_REAL(4.0), BK_REAL(-1.0));

	real out = BkVector3_Dot(&a, &b);

	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)out, (float)-15.0);
}

void BkVector3_AbsDot_test(void)
{
	struct BkVector3 a = BkVector3_Zero();
	struct BkVector3 b = BkVector3_Zero();

	BkVector3_Set(&a, BK_REAL(3.0), BK_REAL(-2.0), BK_REAL(7.0));
	BkVector3_Set(&b, BK_REAL(0.0), BK_REAL(4.0), BK_REAL(-1.0));

	real out = BkVector3_AbsDot(&a, &b);

	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)out, (float)15.0);
}

void BkVector3_Cross_test(void)
{
	struct BkVector3 a = BkVector3_Zero();
	struct BkVector3 b = BkVector3_Zero();

	BkVector3_Set(&a, BK_REAL(1.0), BK_REAL(3.0), BK_REAL(4.0));
	BkVector3_Set(&b, BK_REAL(2.0), BK_REAL(-5.0), BK_REAL(8.0));

	struct BkVector3 out = BkVector3_Cross(&a, &b);

	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)out.x, (float)44.0);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)out.y, (float)0.0);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)out.z, (float)-11.0);
}

void BkVector3_Angle_test(void)
{
	struct BkVector3 a = BkVector3_Zero();
	struct BkVector3 b = BkVector3_Zero();

	a.x = BK_REAL(1.0);
	b.y = BK_REAL(1.0);

	real out = BkVector3_Angle(&a, &b);

	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)out, (float)90.0);
}

void BkVector3_Lerp_test(void)
{
	struct BkVector3 a = BkVector3_Zero();
	struct BkVector3 b = BkVector3_Zero();

	BkVector3_Set(&b, BK_REAL(1.0), BK_REAL(2.0), BK_REAL(4.0));

	struct BkVector3 out = BkVector3_Lerp(&a, &b, BK_REAL(0.0));

	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)out.x, (float)0.0);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)out.y, (float)0.0);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)out.z, (float)0.0);

	out = BkVector3_Lerp(&a, &b, BK_REAL(1.0));

	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)out.x, (float)1.0);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)out.y, (float)2.0);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)out.z, (float)4.0);

	out = BkVector3_Lerp(&a, &b, BK_REAL(0.5));

	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)out.x, (float)0.5);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)out.y, (float)1.0);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)out.z, (float)2.0);

	out = BkVector3_Lerp(&b, &a, BK_REAL(0.5));

	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)out.x, (float)0.5);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)out.y, (float)1.0);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)out.z, (float)2.0);

	out = BkVector3_Lerp(&b, &b, BK_REAL(0.5));

	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)out.x, (float)1.0);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)out.y, (float)2.0);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)out.z, (float)4.0);
}

void BkVector3_Max_test(void)
{
	struct BkVector3 a = BkVector3_Zero();
	struct BkVector3 b = BkVector3_Zero();

	BkVector3_Set(&b, BK_REAL(1.0), BK_REAL(2.0), BK_REAL(4.0));

	struct BkVector3 out = BkVector3_Max(&a, &b);

	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)out.x, (float)1.0);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)out.y, (float)2.0);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)out.z, (float)4.0);
}

void BkVector3_Min_test(void)
{
	struct BkVector3 a = BkVector3_Zero();
	struct BkVector3 b = BkVector3_Zero();

	BkVector3_Set(&b, BK_REAL(1.0), BK_REAL(2.0), BK_REAL(4.0));

	struct BkVector3 out = BkVector3_Min(&a, &b);

	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)out.x, (float)0.0);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)out.y, (float)0.0);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)out.z, (float)0.0);
}