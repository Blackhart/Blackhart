// Unity headers.
#include <unity.h>

// Blackhart headers.
#include "blackhart.h"

// Test headers
#include "foundation/BkEulerAngles_test.h"

static float const ERROR_LIMIT = 0.00001f;

// ~~~~~ Def(PUBLIC) ~~~~~

void	BkEulerAngles_RunTests(void)
{
	RUN_TEST(BkEulerAngles_FromXYZ_test);
	RUN_TEST(BkEulerAngles_FromBkQuaternion_test);
	RUN_TEST(BkEulerAngles_FromBkMatrix4x4_test);
	RUN_TEST(BkEulerAngles_Set_test);
}

void	BkEulerAngles_FromXYZ_test(void)
{
	struct BkEulerAngles ea = BkEulerAngles_FromXYZ(BK_REAL(45), BK_REAL(90), BK_REAL(180));

	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)45, (float)ea.x);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)90, (float)ea.y);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)180, (float)ea.z);
}

void	BkEulerAngles_FromBkQuaternion_test(void)
{
	struct BkEulerAngles ea = BkEulerAngles_FromXYZ(BK_REAL(0), BK_REAL(45), BK_REAL(0));

	struct BkQuaternion q = BkQuaternion_FromEulerAngles(&ea);

	ea = BkEulerAngles_FromBkQuaternion(&q);

	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)0, (float)ea.x);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)45, (float)ea.y);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)0, (float)ea.z);
}

void	BkEulerAngles_FromBkMatrix4x4_test(void)
{
	struct BkEulerAngles ea = BkEulerAngles_FromXYZ(BK_REAL(0), BK_REAL(0), BK_REAL(45));

	struct BkMatrix4x4 m = BkMatrix4x4_FromBkEulerAngles(&ea);

	ea = BkEulerAngles_FromBkMatrix4x4(&m);

	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)0, (float)ea.x);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)0, (float)ea.y);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)45, (float)ea.z);
}

void	BkEulerAngles_Set_test(void)
{
	struct BkEulerAngles ea;
	
	BkEulerAngles_Set(&ea, BK_REAL(45), BK_REAL(90), BK_REAL(180));

	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)45, (float)ea.x);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)90, (float)ea.y);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)180, (float)ea.z);
}