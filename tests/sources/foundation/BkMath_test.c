// Unity headers.
#include <unity.h>

// Blackhart headers.
#include "blackhart.h"

// Test headers.
#include "foundation/BkMath_test.h"

static float const ERROR_LIMIT = 0.00001f;

// ~~~~~ Def(PUBLIC) ~~~~~

void BkMath_RunTests(void)
{
	RUN_TEST(BkMath_PI_test);
	RUN_TEST(BkMath_DegToRad_test);
	RUN_TEST(BkMath_RadToDeg_test);
	RUN_TEST(BkMath_CosFromSin_test);
	RUN_TEST(BkMath_SinFromCos_test);
	RUN_TEST(BkMath_TanFromSinCos_test);
}

void BkMath_PI_test(void)
{
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)3.141592653589793238462643383279502884197169399375105820974, (float)BK_PI);
}

void BkMath_DegToRad_test(void)
{
	real deg;
	real rad;

	deg = BK_REAL(0);
	rad = BK_REAL(0);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)rad, (float)BkMath_DegToRad(deg));

	deg = BK_REAL(90);
	rad = BK_PI / BK_REAL(2);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)rad, (float)BkMath_DegToRad(deg));

	deg = BK_REAL(180);
	rad = BK_PI;
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)rad, (float)BkMath_DegToRad(deg));

	deg = BK_REAL(270);
	rad = BK_REAL(3) * BK_PI / BK_REAL(2);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)rad, (float)BkMath_DegToRad(deg));

	deg = BK_REAL(360);
	rad = BK_REAL(2) * BK_PI;
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)rad, (float)BkMath_DegToRad(deg));
}

void BkMath_RadToDeg_test(void)
{
	real deg;
	real rad;

	deg = BK_REAL(0);
	rad = BK_REAL(0);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)deg, (float)BkMath_RadToDeg(rad));

	deg = BK_REAL(90);
	rad = BK_PI / BK_REAL(2);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)deg, (float)BkMath_RadToDeg(rad));

	deg = BK_REAL(180);
	rad = BK_PI;
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)deg, (float)BkMath_RadToDeg(rad));

	deg = BK_REAL(270);
	rad = BK_REAL(3) * BK_PI / BK_REAL(2);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)deg, (float)BkMath_RadToDeg(rad));

	deg = BK_REAL(360);
	rad = BK_REAL(2) * BK_PI;
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)deg, (float)BkMath_RadToDeg(rad));
}

void BkMath_CosFromSin_test(void)
{
	real cos;
	real sin;

	cos = BK_REAL(0);
	sin = BK_REAL(1);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)sin, (float)BkMath_CosFromSin(cos));

	cos = BK_REAL(0.5);
	sin = BK_REAL(sqrt(3.0)) / BK_REAL(2);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)sin, (float)BkMath_CosFromSin(cos));

	cos = BK_REAL(sqrt(2.0)) / BK_REAL(2);
	sin = BK_REAL(sqrt(2.0)) / BK_REAL(2);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)sin, (float)BkMath_CosFromSin(cos));

	cos = BK_REAL(sqrt(3.0)) / BK_REAL(2);
	sin = BK_REAL(0.5);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)sin, (float)BkMath_CosFromSin(cos));

	cos = BK_REAL(1);
	sin = BK_REAL(0);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)sin, (float)BkMath_CosFromSin(cos));
}

void BkMath_SinFromCos_test(void)
{
	real cos;
	real sin;

	cos = BK_REAL(0);
	sin = BK_REAL(1);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)sin, (float)BkMath_SinFromCos(cos));

	cos = BK_REAL(0.5);
	sin = BK_REAL(sqrt(3.0)) / BK_REAL(2);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)sin, (float)BkMath_SinFromCos(cos));

	cos = BK_REAL(sqrt(2.0)) / BK_REAL(2);
	sin = BK_REAL(sqrt(2.0)) / BK_REAL(2);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)sin, (float)BkMath_SinFromCos(cos));

	cos = BK_REAL(sqrt(3.0)) / BK_REAL(2);
	sin = BK_REAL(0.5);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)sin, (float)BkMath_SinFromCos(cos));

	cos = BK_REAL(1);
	sin = BK_REAL(0);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)sin, (float)BkMath_SinFromCos(cos));
}

void BkMath_TanFromSinCos_test(void)
{
	real cos;
	real sin;

	cos = BK_REAL(0);
	sin = BK_REAL(1);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)0, (float)BkMath_TanFromSinCos(sin, cos));

	cos = BK_REAL(0.5);
	sin = BK_REAL(sqrt(3.0)) / BK_REAL(2);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)sqrt(3.0), (float)BkMath_TanFromSinCos(sin, cos));

	cos = BK_REAL(sqrt(2.0)) / BK_REAL(2);
	sin = BK_REAL(sqrt(2.0)) / BK_REAL(2);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)1, (float)BkMath_TanFromSinCos(sin, cos));

	cos = BK_REAL(sqrt(3.0)) / BK_REAL(2);
	sin = BK_REAL(0.5);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)(1.0 / sqrt(3.0)), (float)BkMath_TanFromSinCos(sin, cos));

	cos = BK_REAL(1);
	sin = BK_REAL(0);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)0, (float)BkMath_TanFromSinCos(sin, cos));
}