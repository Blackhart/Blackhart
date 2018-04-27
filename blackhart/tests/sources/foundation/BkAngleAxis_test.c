// Unity headers.
#include <unity.h>

// Blackhart headers.
#include "blackhart.h"

// Test headers.
#include "foundation/BkAngleAxis_test.h"

static float const ERROR_LIMIT = 0.00001f;

// ~~~~~ Def(PUBLIC) ~~~~~

void	BkAngleAxis_RunTests(void)
{
	RUN_TEST(BkAngleAxis_FromAngleAxis_test);
	RUN_TEST(BkAngleAxis_SetAngle_test);
	RUN_TEST(BkAngleAxis_SetAxis_test);
}

void	BkAngleAxis_FromAngleAxis_test(void)
{
	struct BkVector3 axis = BkVector3_FromXYZ(BK_REAL(1), BK_REAL(1), BK_REAL(0));

	struct BkAngleAxis ea = BkAngleAxis_FromAngleAxis(BK_REAL(45), &axis);

	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)1, (float)ea.axis.x);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)1, (float)ea.axis.y);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)0, (float)ea.axis.z);
}

void	BkAngleAxis_SetAngle_test(void)
{
	struct BkAngleAxis ea;

	BkAngleAxis_SetAngle(&ea, BK_REAL(45));

	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)45, (float)ea.angle);
}

void	BkAngleAxis_SetAxis_test(void)
{
	struct BkVector3 axis = BkVector3_FromXYZ(BK_REAL(1), BK_REAL(1), BK_REAL(0));

	struct BkAngleAxis ea;

	BkAngleAxis_SetAxis(&ea, &axis);

	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)1, (float)ea.axis.x);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)1, (float)ea.axis.y);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)0, (float)ea.axis.z);
}