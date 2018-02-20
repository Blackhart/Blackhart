// Unity headers.
#include <unity.h>

// Blackhart headers.
#include "blackhart.h"

// Test headers
#include "foundation/BkQuaternion_test.h"

static float const ERROR_LIMIT = 0.00001f;

// ~~~~~ Def(PUBLIC) ~~~~~

void	BkQuaternion_RunTests(void)
{
	RUN_TEST(BkQuaternion_Identity_test);
	RUN_TEST(BkQuaternion_FromAngleAxis_test);
	RUN_TEST(BkQuaternion_FromEulerAngles_test);
	RUN_TEST(BkQuaternion_FromBkMatrix4x4_test);
	RUN_TEST(BkQuaternion_Mul_BkQuaternion_test);
	RUN_TEST(BkQuaternion_Copy_test);
	RUN_TEST(BkQuaternion_Set_test);
	RUN_TEST(BkQuaternion_Normalized_test);
	RUN_TEST(BkQuaternion_Normalize_test);
	RUN_TEST(BkQuaternion_Negated_test);
	RUN_TEST(BkQuaternion_Negate_test);
	RUN_TEST(BkQuaternion_Magnitude_test);
	RUN_TEST(BkQuaternion_Conjugated_test);
	RUN_TEST(BkQuaternion_Conjugate_test);
	RUN_TEST(BkQuaternion_Inversed_test);
	RUN_TEST(BkQuaternion_Inverse_test);
	RUN_TEST(BkQuaternion_Difference_test);
	RUN_TEST(BkQuaternion_Dot_test);
}

void	BkQuaternion_Identity_test(void)
{
	struct BkQuaternion q = BkQuaternion_Identity();

	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)1, (float)q.w);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)0, (float)q.x);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)0, (float)q.y);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)0, (float)q.z);
}

void	BkQuaternion_FromAngleAxis_test(void)
{
	struct BkVector3 v;
	BkVector3_Set(&v, BK_REAL(1), BK_REAL(1), BK_REAL(1));
	v = BkVector3_Normalize(&v);

	struct BkAngleAxis aa;
	BkAngleAxis_SetAngle(&aa, BK_REAL(90));
	BkAngleAxis_SetAxis(&aa, &v);

	struct BkQuaternion q = BkQuaternion_FromAngleAxis(&aa);

	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)0.7071068, (float)q.w);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)0.4082483, (float)q.x);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)0.4082483, (float)q.y);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)0.4082483, (float)q.z);
}

void	BkQuaternion_FromEulerAngles_test(void)
{
	struct BkEulerAngles ea;
	BkEulerAngles_Set(&ea, BK_REAL(180), BK_REAL(90), BK_REAL(0));

	struct BkQuaternion q = BkQuaternion_FromEulerAngles(&ea);

	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)0, (float)q.w);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)0.7071068, (float)q.x);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)0, (float)q.y);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)-0.7071068, (float)q.z);
}

void	BkQuaternion_FromBkMatrix4x4_test(void)
{
	struct BkEulerAngles ea;
	BkEulerAngles_Set(&ea, BK_REAL(180), BK_REAL(90), BK_REAL(0));

	struct BkMatrix4x4 m = BkMatrix4x4_FromBkEulerAngles(&ea);

	struct BkQuaternion q = BkQuaternion_FromBkMatrix4x4(&m);

	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)0, (float)q.w);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)-0.7071068, (float)q.x);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)0, (float)q.y);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)0.7071068, (float)q.z);
}

void	BkQuaternion_Mul_BkQuaternion_test()
{
	struct BkEulerAngles ea1;
	BkEulerAngles_Set(&ea1, BK_REAL(180), BK_REAL(90), BK_REAL(0));

	struct BkEulerAngles ea2;
	BkEulerAngles_Set(&ea2, BK_REAL(45), BK_REAL(45), BK_REAL(45));

	struct BkQuaternion q1 = BkQuaternion_FromEulerAngles(&ea1);
	struct BkQuaternion q2 = BkQuaternion_FromEulerAngles(&ea2);

	struct BkQuaternion res = BkQuaternion_Mul_BkQuaternion(&q1, &q2);

	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)-0.191341758, (float)res.w);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)0.732537806, (float)res.x);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)-0.461939812, (float)res.y);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)-0.461939752, (float)res.z);
}

void	BkQuaternion_Copy_test(void)
{
	struct BkEulerAngles ea;
	BkEulerAngles_Set(&ea, BK_REAL(180), BK_REAL(90), BK_REAL(0));

	struct BkQuaternion q = BkQuaternion_FromEulerAngles(&ea);

	struct BkQuaternion res = BkQuaternion_Copy(&q);

	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)0, (float)res.w);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)0.707106769, (float)res.x);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)0, (float)res.y);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)-0.707106769, (float)res.z);
}

void	BkQuaternion_Set_test(void)
{
	struct BkQuaternion q;
	BkQuaternion_Set(&q, BK_REAL(1), BK_REAL(3), BK_REAL(10), BK_REAL(40));

	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)1, (float)q.w);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)3, (float)q.x);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)10, (float)q.y);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)40, (float)q.z);
}

void	BkQuaternion_Normalized_test(void)
{
	struct BkQuaternion q;
	BkQuaternion_Set(&q, BK_REAL(1), BK_REAL(2), BK_REAL(3), BK_REAL(4));

	BkQuaternion_Normalized(&q);

	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)0.182574183, (float)q.w);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)0.365148365, (float)q.x);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)0.547722518, (float)q.y);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)0.730296731, (float)q.z);
}

void	BkQuaternion_Normalize_test(void)
{
	struct BkQuaternion q;
	BkQuaternion_Set(&q, BK_REAL(1), BK_REAL(2), BK_REAL(3), BK_REAL(4));

	q = BkQuaternion_Normalize(&q);

	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)0.182574183, (float)q.w);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)0.365148365, (float)q.x);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)0.547722518, (float)q.y);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)0.730296731, (float)q.z);
}

void	BkQuaternion_Negated_test(void)
{
	struct BkQuaternion q;
	BkQuaternion_Set(&q, BK_REAL(1), BK_REAL(2), BK_REAL(3), BK_REAL(4));

	BkQuaternion_Negated(&q);

	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)-1, (float)q.w);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)-2, (float)q.x);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)-3, (float)q.y);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)-4, (float)q.z);
}

void	BkQuaternion_Negate_test(void)
{
	struct BkQuaternion q;
	BkQuaternion_Set(&q, BK_REAL(1), BK_REAL(2), BK_REAL(3), BK_REAL(4));

	q = BkQuaternion_Negate(&q);

	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)-1, (float)q.w);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)-2, (float)q.x);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)-3, (float)q.y);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)-4, (float)q.z);
}

void	BkQuaternion_Magnitude_test(void)
{
	struct BkQuaternion q;
	BkQuaternion_Set(&q, BK_REAL(1), BK_REAL(2), BK_REAL(3), BK_REAL(4));

	real const magnitude = BkQuaternion_Magnitude(&q);

	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)5.47722578, (float)magnitude);
}

void	BkQuaternion_Conjugated_test(void)
{
	struct BkQuaternion q;
	BkQuaternion_Set(&q, BK_REAL(1), BK_REAL(2), BK_REAL(3), BK_REAL(4));

	BkQuaternion_Conjugated(&q);

	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)1, (float)q.w);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)-2, (float)q.x);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)-3, (float)q.y);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)-4, (float)q.z);
}

void	BkQuaternion_Conjugate_test(void)
{
	struct BkQuaternion q;
	BkQuaternion_Set(&q, BK_REAL(1), BK_REAL(2), BK_REAL(3), BK_REAL(4));

	q = BkQuaternion_Conjugate(&q);

	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)1, (float)q.w);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)-2, (float)q.x);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)-3, (float)q.y);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)-4, (float)q.z);
}

void	BkQuaternion_Inversed_test(void)
{
	struct BkQuaternion q;
	BkQuaternion_Set(&q, BK_REAL(1), BK_REAL(2), BK_REAL(3), BK_REAL(4));

	BkQuaternion_Inversed(&q);

	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)0.182574183, (float)q.w);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)-0.365148365, (float)q.x);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)-0.547722518, (float)q.y);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)-0.730296731, (float)q.z);
}

void	BkQuaternion_Inverse_test(void)
{
	struct BkQuaternion q;
	BkQuaternion_Set(&q, BK_REAL(1), BK_REAL(2), BK_REAL(3), BK_REAL(4));

	q = BkQuaternion_Inverse(&q);

	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)0.182574183, (float)q.w);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)-0.365148365, (float)q.x);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)-0.547722518, (float)q.y);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)-0.730296731, (float)q.z);
}

void	BkQuaternion_Difference_test(void)
{
	struct BkEulerAngles ea1;
	BkEulerAngles_Set(&ea1, BK_REAL(180), BK_REAL(90), BK_REAL(0));

	struct BkEulerAngles ea2;
	BkEulerAngles_Set(&ea2, BK_REAL(180), BK_REAL(90), BK_REAL(0));

	struct BkQuaternion q1 = BkQuaternion_FromEulerAngles(&ea1);
	struct BkQuaternion q2 = BkQuaternion_FromEulerAngles(&ea2);

	struct BkQuaternion res = BkQuaternion_Difference(&q1, &q2);

	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)1, (float)res.w);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)0, (float)res.x);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)0, (float)res.y);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)0, (float)res.z);
}

void	BkQuaternion_Dot_test(void)
{
	struct BkEulerAngles ea1;
	BkEulerAngles_Set(&ea1, BK_REAL(180), BK_REAL(90), BK_REAL(0));

	struct BkEulerAngles ea2;
	BkEulerAngles_Set(&ea2, BK_REAL(45), BK_REAL(45), BK_REAL(45));

	struct BkQuaternion q1 = BkQuaternion_FromEulerAngles(&ea1);
	struct BkQuaternion q2 = BkQuaternion_FromEulerAngles(&ea2);

	real const dot = BkQuaternion_Dot(&q1, &q2);

	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)0.191342, (float)dot);
}