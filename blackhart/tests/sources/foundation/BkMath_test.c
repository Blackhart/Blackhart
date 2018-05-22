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
	RUN_TEST(BkMath_RadFromDeg_test);
	RUN_TEST(BkMath_DegFromRad_test);
	RUN_TEST(BkMath_CosFromSin_test);
	RUN_TEST(BkMath_SinFromCos_test);
	RUN_TEST(BkMath_TanFromSinCos_test);
	RUN_TEST(BkMath_Clamp_test);
}

void BkMath_PI_test(void)
{
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)3.141592653589793238462643383279502884197169399375105820974, (float)BK_PI);
}

void BkMath_RadFromDeg_test(void)
{
	real deg;
	real rad;

	deg = BK_REAL(0);
	rad = BK_REAL(0);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)rad, (float)BkMath_RadFromDeg(deg));

	deg = BK_REAL(90);
	rad = BK_PI / BK_REAL(2);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)rad, (float)BkMath_RadFromDeg(deg));

	deg = BK_REAL(180);
	rad = BK_PI;
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)rad, (float)BkMath_RadFromDeg(deg));

	deg = BK_REAL(270);
	rad = BK_REAL(3) * BK_PI / BK_REAL(2);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)rad, (float)BkMath_RadFromDeg(deg));

	deg = BK_REAL(360);
	rad = BK_REAL(2) * BK_PI;
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)rad, (float)BkMath_RadFromDeg(deg));
}

void BkMath_DegFromRad_test(void)
{
	real deg;
	real rad;

	deg = BK_REAL(0);
	rad = BK_REAL(0);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)deg, (float)BkMath_DegFromRad(rad));

	deg = BK_REAL(90);
	rad = BK_PI / BK_REAL(2);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)deg, (float)BkMath_DegFromRad(rad));

	deg = BK_REAL(180);
	rad = BK_PI;
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)deg, (float)BkMath_DegFromRad(rad));

	deg = BK_REAL(270);
	rad = BK_REAL(3) * BK_PI / BK_REAL(2);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)deg, (float)BkMath_DegFromRad(rad));

	deg = BK_REAL(360);
	rad = BK_REAL(2) * BK_PI;
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)deg, (float)BkMath_DegFromRad(rad));
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

void	BkMath_Clamp_test(void)
{
	real const min = BK_REAL(-2);
	real const max = BK_REAL(5);

	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)min, (float)BkMath_Clamp(BK_REAL(-3), min, max));
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)max, (float)BkMath_Clamp(BK_REAL(10), min, max));
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, 0.0f, (float)BkMath_Clamp(BK_REAL(0), min, max));
}