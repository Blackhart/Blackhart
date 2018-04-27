// Unity headers.
#include <unity.h>

// Blackhart headers.
#include "blackhart.h"

// Test headers.
#include "foundation/BkMatrix4x4_test.h"

static float const ERROR_LIMIT = 0.00001f;

// ~~~~~ Def(PUBLIC) ~~~~~

void	BkMatrix4x4_RunTests(void)
{
	RUN_TEST(BkMatrix4x4_Identity_test);
	RUN_TEST(BkMatrix4x4_Copy_test);
	RUN_TEST(BkMatrix4x4_Assign_test);
	RUN_TEST(BkMatrix4x4_Transpose_test);
	RUN_TEST(BkMatrix4x4_Mul_real_test);
	RUN_TEST(BkMatrix4x4_Mul_BkMatrix4x4_test);
	RUN_TEST(BkMatrix4x4_Mul_BkVector3_test);
	RUN_TEST(BkMatrix4x4_Mul_BkPoint3_test);
	RUN_TEST(BkMatrix4x4_Mul_BkPoint4_test);
	RUN_TEST(BkMatrix4x4_Scaling_Uniform_test);
	RUN_TEST(BkMatrix4x4_Scaling_Nonuniform_test);
	RUN_TEST(BkMatrix4x4_Scaling_Axis_test);
	RUN_TEST(BkMatrix4x4_Translation_XYZ_test);
	RUN_TEST(BkMatrix4x4_Translation_BkVector3_test);
	RUN_TEST(BkMatrix4x4_Translation_BkPoint3_test);
	RUN_TEST(BkMatrix4x4_Determinant_test);
	RUN_TEST(BkMatrix4x4_Inverse_test);
	RUN_TEST(BkMatrix4x4_FromEulerAngles_test);
	RUN_TEST(BkMatrix4x4_FromAngleAxis_test);
	RUN_TEST(BkMatrix4x4_FromBkQuaternion_test);
}

void	BkMatrix4x4_Identity_test(void)
{
	struct BkMatrix4x4 m = BkMatrix4x4_Identity();

	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)m.m11, (float)1.0);   TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)m.m12, (float)0.0);   TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)m.m13, (float)0.0);   TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)m.m14, (float)0.0);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)m.m21, (float)0.0);   TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)m.m22, (float)1.0);   TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)m.m23, (float)0.0);   TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)m.m24, (float)0.0);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)m.m31, (float)0.0);   TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)m.m32, (float)0.0);   TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)m.m33, (float)1.0);   TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)m.m34, (float)0.0);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)m.m41, (float)0.0);   TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)m.m42, (float)0.0);   TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)m.m43, (float)0.0);   TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)m.m44, (float)1.0);
}

void	BkMatrix4x4_Copy_test(void)
{
	struct BkMatrix4x4 m1 = BkMatrix4x4_Identity();

	m1.m11 = BK_REAL(1.0);    m1.m12 = BK_REAL(2.0);    m1.m13 = BK_REAL(3.0);    m1.m14 = BK_REAL(4.0);
	m1.m21 = BK_REAL(5.0);    m1.m22 = BK_REAL(6.0);    m1.m23 = BK_REAL(7.0);    m1.m24 = BK_REAL(8.0);
	m1.m31 = BK_REAL(9.0);    m1.m32 = BK_REAL(10.0);   m1.m33 = BK_REAL(11.0);   m1.m34 = BK_REAL(12.0);
	m1.m41 = BK_REAL(13.0);   m1.m42 = BK_REAL(14.0);   m1.m43 = BK_REAL(15.0);   m1.m44 = BK_REAL(16.0);

	struct BkMatrix4x4 m = BkMatrix4x4_Copy(&m1);

	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)m.m11, (float)1.0);    TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)m.m12, (float)2.0);    TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)m.m13, (float)3.0);    TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)m.m14, (float)4.0);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)m.m21, (float)5.0);    TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)m.m22, (float)6.0);    TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)m.m23, (float)7.0);    TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)m.m24, (float)8.0);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)m.m31, (float)9.0);    TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)m.m32, (float)10.0);   TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)m.m33, (float)11.0);   TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)m.m34, (float)12.0);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)m.m41, (float)13.0);   TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)m.m42, (float)14.0);   TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)m.m43, (float)15.0);   TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)m.m44, (float)16.0);
}

void	BkMatrix4x4_Assign_test(void)
{
	struct BkMatrix4x4 m1 = BkMatrix4x4_Identity();

	m1.m11 = BK_REAL(1.0);    m1.m12 = BK_REAL(2.0);    m1.m13 = BK_REAL(3.0);    m1.m14 = BK_REAL(4.0);
	m1.m21 = BK_REAL(5.0);    m1.m22 = BK_REAL(6.0);    m1.m23 = BK_REAL(7.0);    m1.m24 = BK_REAL(8.0);
	m1.m31 = BK_REAL(9.0);    m1.m32 = BK_REAL(10.0);   m1.m33 = BK_REAL(11.0);   m1.m34 = BK_REAL(12.0);
	m1.m41 = BK_REAL(13.0);   m1.m42 = BK_REAL(14.0);   m1.m43 = BK_REAL(15.0);   m1.m44 = BK_REAL(16.0);

	struct BkMatrix4x4 m = BkMatrix4x4_Identity();

	BkMatrix4x4_Assign(&m, &m1);

	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)m.m11, (float)1.0);    TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)m.m12, (float)2.0);    TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)m.m13, (float)3.0);    TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)m.m14, (float)4.0);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)m.m21, (float)5.0);    TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)m.m22, (float)6.0);    TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)m.m23, (float)7.0);    TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)m.m24, (float)8.0);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)m.m31, (float)9.0);    TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)m.m32, (float)10.0);   TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)m.m33, (float)11.0);   TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)m.m34, (float)12.0);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)m.m41, (float)13.0);   TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)m.m42, (float)14.0);   TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)m.m43, (float)15.0);   TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)m.m44, (float)16.0);
}

void	BkMatrix4x4_Transpose_test(void)
{
	struct BkMatrix4x4 m = BkMatrix4x4_Identity();

	m = BkMatrix4x4_Transpose(&m);

	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)m.m11, (float)1.0);   TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)m.m12, (float)0.0);   TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)m.m13, (float)0.0);   TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)m.m14, (float)0.0);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)m.m21, (float)0.0);   TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)m.m22, (float)1.0);   TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)m.m23, (float)0.0);   TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)m.m24, (float)0.0);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)m.m31, (float)0.0);   TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)m.m32, (float)0.0);   TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)m.m33, (float)1.0);   TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)m.m34, (float)0.0);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)m.m41, (float)0.0);   TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)m.m42, (float)0.0);   TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)m.m43, (float)0.0);   TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)m.m44, (float)1.0);

	m.m11 = BK_REAL(1.0);    m.m12 = BK_REAL(2.0);    m.m13 = BK_REAL(3.0);    m.m14 = BK_REAL(4.0);
	m.m21 = BK_REAL(5.0);    m.m22 = BK_REAL(6.0);    m.m23 = BK_REAL(7.0);    m.m24 = BK_REAL(8.0);
	m.m31 = BK_REAL(9.0);    m.m32 = BK_REAL(10.0);   m.m33 = BK_REAL(11.0);   m.m34 = BK_REAL(12.0);
	m.m41 = BK_REAL(13.0);   m.m42 = BK_REAL(14.0);   m.m43 = BK_REAL(15.0);   m.m44 = BK_REAL(16.0);

	m = BkMatrix4x4_Transpose(&m);

	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)m.m11, (float)1.0);   TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)m.m12, (float)5.0);   TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)m.m13, (float)9.0);    TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)m.m14, (float)13.0);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)m.m21, (float)2.0);   TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)m.m22, (float)6.0);   TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)m.m23, (float)10.0);   TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)m.m24, (float)14.0);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)m.m31, (float)3.0);   TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)m.m32, (float)7.0);   TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)m.m33, (float)11.0);   TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)m.m34, (float)15.0);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)m.m41, (float)4.0);   TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)m.m42, (float)8.0);   TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)m.m43, (float)12.0);   TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)m.m44, (float)16.0);
}

void	BkMatrix4x4_Mul_real_test(void)
{
	struct BkMatrix4x4 m = BkMatrix4x4_Identity();

	m.m11 = BK_REAL(1.0);    m.m12 = BK_REAL(2.0);    m.m13 = BK_REAL(3.0);    m.m14 = BK_REAL(4.0);
	m.m21 = BK_REAL(5.0);    m.m22 = BK_REAL(6.0);    m.m23 = BK_REAL(7.0);    m.m24 = BK_REAL(8.0);
	m.m31 = BK_REAL(9.0);    m.m32 = BK_REAL(10.0);   m.m33 = BK_REAL(11.0);   m.m34 = BK_REAL(12.0);
	m.m41 = BK_REAL(13.0);   m.m42 = BK_REAL(14.0);   m.m43 = BK_REAL(15.0);   m.m44 = BK_REAL(16.0);

	m = BkMatrix4x4_Mul_real(&m, 2.0);

	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)m.m11, (float)2.0);    TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)m.m12, (float)4.0);    TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)m.m13, (float)6.0);    TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)m.m14, (float)8.0);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)m.m21, (float)10.0);   TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)m.m22, (float)12.0);   TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)m.m23, (float)14.0);   TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)m.m24, (float)16.0);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)m.m31, (float)18.0);   TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)m.m32, (float)20.0);   TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)m.m33, (float)22.0);   TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)m.m34, (float)24.0);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)m.m41, (float)26.0);   TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)m.m42, (float)28.0);   TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)m.m43, (float)30.0);   TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)m.m44, (float)32.0);
}

void	BkMatrix4x4_Mul_BkMatrix4x4_test(void)
{
	struct BkMatrix4x4 m1 = BkMatrix4x4_Identity();
	struct BkMatrix4x4 m2 = BkMatrix4x4_Identity();

	m1.m11 = BK_REAL(1.0);   m1.m12 = BK_REAL(-5.0);   m1.m13 = BK_REAL(3.0);    m1.m14 = BK_REAL(0.0);
	m1.m21 = BK_REAL(0.0);   m1.m22 = BK_REAL(-2.0);   m1.m23 = BK_REAL(6.0);    m1.m24 = BK_REAL(0.0);
	m1.m31 = BK_REAL(7.0);   m1.m32 = BK_REAL(2.0);    m1.m33 = BK_REAL(-4.0);   m1.m34 = BK_REAL(0.0);
	m1.m41 = BK_REAL(0.0);   m1.m42 = BK_REAL(0.0);    m1.m43 = BK_REAL(0.0);    m1.m44 = BK_REAL(1.0);

	m2.m11 = BK_REAL(-8.0);   m2.m12 = BK_REAL(6.0);   m2.m13 = BK_REAL(1.0);    m2.m14 = BK_REAL(0.0);
	m2.m21 = BK_REAL(7.0);    m2.m22 = BK_REAL(0.0);   m2.m23 = BK_REAL(-3.0);   m2.m24 = BK_REAL(0.0);
	m2.m31 = BK_REAL(2.0);    m2.m32 = BK_REAL(4.0);   m2.m33 = BK_REAL(5.0);    m2.m34 = BK_REAL(0.0);
	m2.m41 = BK_REAL(0.0);    m2.m42 = BK_REAL(0.0);   m2.m43 = BK_REAL(0.0);    m2.m44 = BK_REAL(1.0);

	struct BkMatrix4x4 m = BkMatrix4x4_Mul_BkMatrix4x4(&m1, &m2);

	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)m.m11, (float)-37.0);   TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)m.m12, (float)18.0);   TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)m.m13, (float)31.0);    TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)m.m14, (float)0.0);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)m.m21, (float)-2.0);    TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)m.m22, (float)24.0);   TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)m.m23, (float)36.0);    TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)m.m24, (float)0.0);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)m.m31, (float)-50.0);   TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)m.m32, (float)26.0);   TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)m.m33, (float)-19.0);   TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)m.m34, (float)0.0);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)m.m41, (float)0.0);     TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)m.m42, (float)0.0);    TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)m.m43, (float)0.0);     TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)m.m44, (float)1.0);
}

void	BkMatrix4x4_Mul_BkVector3_test(void)
{
	struct BkVector3 v = BkVector3_Zero();

	v.x = BK_REAL(1.0); v.y = BK_REAL(2.0); v.z = BK_REAL(4.0);

	struct BkMatrix4x4 m = BkMatrix4x4_Identity();

	m.m11 = BK_REAL(1.0);    m.m12 = BK_REAL(2.0);    m.m13 = BK_REAL(3.0);    m.m14 = BK_REAL(4.0);
	m.m21 = BK_REAL(5.0);    m.m22 = BK_REAL(6.0);    m.m23 = BK_REAL(7.0);    m.m24 = BK_REAL(8.0);
	m.m31 = BK_REAL(9.0);    m.m32 = BK_REAL(10.0);   m.m33 = BK_REAL(11.0);   m.m34 = BK_REAL(12.0);
	m.m41 = BK_REAL(13.0);   m.m42 = BK_REAL(14.0);   m.m43 = BK_REAL(15.0);   m.m44 = BK_REAL(16.0);

	v = BkMatrix4x4_Mul_BkVector3(&m, &v);

	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)v.x, (float)17.0);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)v.y, (float)45.0);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)v.z, (float)73.0);
}

void	BkMatrix4x4_Mul_BkPoint3_test(void)
{
	struct BkPoint3 p = BkPoint3_Zero();

	p.x = BK_REAL(1.0); p.y = BK_REAL(2.0); p.z = BK_REAL(4.0);

	struct BkMatrix4x4 m = BkMatrix4x4_Identity();

	m.m11 = BK_REAL(1.0);    m.m12 = BK_REAL(2.0);    m.m13 = BK_REAL(3.0);    m.m14 = BK_REAL(4.0);
	m.m21 = BK_REAL(5.0);    m.m22 = BK_REAL(6.0);    m.m23 = BK_REAL(7.0);    m.m24 = BK_REAL(8.0);
	m.m31 = BK_REAL(9.0);    m.m32 = BK_REAL(10.0);   m.m33 = BK_REAL(11.0);   m.m34 = BK_REAL(12.0);
	m.m41 = BK_REAL(13.0);   m.m42 = BK_REAL(14.0);   m.m43 = BK_REAL(15.0);   m.m44 = BK_REAL(16.0);

	p = BkMatrix4x4_Mul_BkPoint3(&m, &p);

	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)p.x, (float)21.0);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)p.y, (float)53.0);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)p.z, (float)85.0);
}

void	BkMatrix4x4_Mul_BkPoint4_test(void)
{
	struct BkPoint3 p = BkPoint3_Zero();

	p.x = BK_REAL(1.0); p.y = BK_REAL(2.0); p.z = BK_REAL(4.0);

	struct BkMatrix4x4 m = BkMatrix4x4_Identity();

	m.m11 = BK_REAL(1.0);   m.m12 = BK_REAL(2.0);    m.m13 = BK_REAL(3.0);    m.m14 = BK_REAL(4.0);
	m.m21 = BK_REAL(5.0);   m.m22 = BK_REAL(6.0);    m.m23 = BK_REAL(7.0);    m.m24 = BK_REAL(8.0);
	m.m31 = BK_REAL(9.0);   m.m32 = BK_REAL(10.0);   m.m33 = BK_REAL(11.0);   m.m34 = BK_REAL(12.0);
	m.m41 = BK_REAL(2.0);   m.m42 = BK_REAL(4.0);    m.m43 = BK_REAL(8.0);    m.m44 = BK_REAL(2.0);

	p = BkMatrix4x4_Mul_BkPoint4(&m, &p);

	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)p.x, (float)(21.0 / 44.0));
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)p.y, (float)(53.0 / 44.0));
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)p.z, (float)(85.0 / 44.0));
}

void	BkMatrix4x4_Scaling_Uniform_test(void)
{
	struct BkMatrix4x4 ms = BkMatrix4x4_Scaling_Uniform(BK_REAL(2.0));

	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)ms.m11, (float)2.0);   TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)ms.m12, (float)0.0);   TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)ms.m13, (float)0.0);   TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)ms.m14, (float)0.0);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)ms.m21, (float)0.0);   TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)ms.m22, (float)2.0);   TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)ms.m23, (float)0.0);   TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)ms.m24, (float)0.0);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)ms.m31, (float)0.0);   TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)ms.m32, (float)0.0);   TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)ms.m33, (float)2.0);   TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)ms.m34, (float)0.0);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)ms.m41, (float)0.0);   TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)ms.m42, (float)0.0);   TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)ms.m43, (float)0.0);   TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)ms.m44, (float)1.0);
}

void	BkMatrix4x4_Scaling_Nonuniform_test(void)
{
	struct BkMatrix4x4 ms = BkMatrix4x4_Scaling_Nonuniform(BK_REAL(2.0), BK_REAL(4.0), BK_REAL(6.0));

	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)ms.m11, (float)2.0);   TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)ms.m12, (float)0.0);   TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)ms.m13, (float)0.0);   TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)ms.m14, (float)0.0);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)ms.m21, (float)0.0);   TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)ms.m22, (float)4.0);   TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)ms.m23, (float)0.0);   TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)ms.m24, (float)0.0);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)ms.m31, (float)0.0);   TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)ms.m32, (float)0.0);   TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)ms.m33, (float)6.0);   TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)ms.m34, (float)0.0);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)ms.m41, (float)0.0);   TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)ms.m42, (float)0.0);   TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)ms.m43, (float)0.0);   TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)ms.m44, (float)1.0);
}

void	BkMatrix4x4_Scaling_Axis_test(void)
{
	struct BkVector3 axis = BkVector3_FromXYZ(BK_REAL(1), BK_REAL(0), BK_REAL(0));
	axis = BkVector3_Normalize(&axis);

	struct BkMatrix4x4 ms = BkMatrix4x4_Scaling_axis(&axis, BK_REAL(0.5));

	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)ms.m11, (float)0.5);   TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)ms.m12, (float)0.0);   TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)ms.m13, (float)0.0);   TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)ms.m14, (float)0.0);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)ms.m21, (float)0.0);   TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)ms.m22, (float)1.0);   TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)ms.m23, (float)0.0);   TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)ms.m24, (float)0.0);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)ms.m31, (float)0.0);   TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)ms.m32, (float)0.0);   TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)ms.m33, (float)1.0);   TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)ms.m34, (float)0.0);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)ms.m41, (float)0.0);   TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)ms.m42, (float)0.0);   TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)ms.m43, (float)0.0);   TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)ms.m44, (float)1.0);
}

void	BkMatrix4x4_Translation_XYZ_test(void)
{
	struct BkMatrix4x4 mt = BkMatrix4x4_Translation_XYZ(BK_REAL(2.0), BK_REAL(4.0), BK_REAL(8.0));

	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)mt.m11, (float)1.0);   TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)mt.m12, (float)0.0);   TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)mt.m13, (float)0.0);   TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)mt.m14, (float)2.0);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)mt.m21, (float)0.0);   TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)mt.m22, (float)1.0);   TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)mt.m23, (float)0.0);   TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)mt.m24, (float)4.0);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)mt.m31, (float)0.0);   TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)mt.m32, (float)0.0);   TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)mt.m33, (float)1.0);   TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)mt.m34, (float)8.0);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)mt.m41, (float)0.0);   TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)mt.m42, (float)0.0);   TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)mt.m43, (float)0.0);   TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)mt.m44, (float)1.0);
}

void	BkMatrix4x4_Translation_BkVector3_test(void)
{
	struct BkVector3 v;
	BkVector3_Set(&v, BK_REAL(2.0), BK_REAL(4.0), BK_REAL(8.0));

	struct BkMatrix4x4 mt = BkMatrix4x4_Translation_BkVector3(&v);

	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)mt.m11, (float)1.0);   TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)mt.m12, (float)0.0);   TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)mt.m13, (float)0.0);   TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)mt.m14, (float)2.0);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)mt.m21, (float)0.0);   TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)mt.m22, (float)1.0);   TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)mt.m23, (float)0.0);   TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)mt.m24, (float)4.0);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)mt.m31, (float)0.0);   TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)mt.m32, (float)0.0);   TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)mt.m33, (float)1.0);   TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)mt.m34, (float)8.0);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)mt.m41, (float)0.0);   TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)mt.m42, (float)0.0);   TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)mt.m43, (float)0.0);   TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)mt.m44, (float)1.0);
}

void	BkMatrix4x4_Translation_BkPoint3_test(void)
{
	struct BkPoint3 p;
	BkPoint3_Set(&p, BK_REAL(2.0), BK_REAL(4.0), BK_REAL(8.0));

	struct BkMatrix4x4 mt = BkMatrix4x4_Translation_BkPoint3(&p);

	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)mt.m11, (float)1.0);   TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)mt.m12, (float)0.0);   TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)mt.m13, (float)0.0);   TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)mt.m14, (float)2.0);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)mt.m21, (float)0.0);   TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)mt.m22, (float)1.0);   TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)mt.m23, (float)0.0);   TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)mt.m24, (float)4.0);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)mt.m31, (float)0.0);   TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)mt.m32, (float)0.0);   TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)mt.m33, (float)1.0);   TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)mt.m34, (float)8.0);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)mt.m41, (float)0.0);   TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)mt.m42, (float)0.0);   TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)mt.m43, (float)0.0);   TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)mt.m44, (float)1.0);
}

void	BkMatrix4x4_Determinant_test(void)
{
	struct BkMatrix4x4 m = BkMatrix4x4_Identity();

	m.m11 = BK_REAL(11.0);   m.m12 = BK_REAL(12.0);   m.m13 = BK_REAL(13.0);   m.m14 = BK_REAL(14.0);
	m.m21 = BK_REAL(21.0);   m.m22 = BK_REAL(22.0);   m.m23 = BK_REAL(23.0);   m.m24 = BK_REAL(24.0);
	m.m31 = BK_REAL(31.0);   m.m32 = BK_REAL(32.0);   m.m33 = BK_REAL(33.0);   m.m34 = BK_REAL(34.0);
	m.m41 = BK_REAL(41.0);   m.m42 = BK_REAL(42.0);   m.m43 = BK_REAL(43.0);   m.m44 = BK_REAL(44.0);

	real d = BkMatrix4x4_Determinant(&m);

	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)d, (float)0.0);

	m = BkMatrix4x4_Identity();

	m.m11 = BK_REAL(1.0);   m.m12 = BK_REAL(0.0);   m.m13 = BK_REAL(0.0);   m.m14 = BK_REAL(0.0);
	m.m21 = BK_REAL(1.0);   m.m22 = BK_REAL(1.0);   m.m23 = BK_REAL(0.0);   m.m24 = BK_REAL(0.0);
	m.m31 = BK_REAL(0.0);   m.m32 = BK_REAL(0.0);   m.m33 = BK_REAL(1.0);   m.m34 = BK_REAL(0.0);
	m.m41 = BK_REAL(0.0);   m.m42 = BK_REAL(0.0);   m.m43 = BK_REAL(0.0);   m.m44 = BK_REAL(1.0);

	d = BkMatrix4x4_Determinant(&m);

	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)d, (float)1.0);
}

void	BkMatrix4x4_Inverse_test(void)
{
	struct BkMatrix4x4 m = BkMatrix4x4_Identity();

	m.m11 = BK_REAL(0.0);   m.m12 = BK_REAL(-1.0);   m.m13 = BK_REAL(0.0);   m.m14 = BK_REAL(3.0);
	m.m21 = BK_REAL(1.0);   m.m22 = BK_REAL(0.0);    m.m23 = BK_REAL(0.0);   m.m24 = BK_REAL(4.0);
	m.m31 = BK_REAL(0.0);   m.m32 = BK_REAL(0.0);    m.m33 = BK_REAL(1.0);   m.m34 = BK_REAL(0.0);
	m.m41 = BK_REAL(0.0);   m.m42 = BK_REAL(0.0);    m.m43 = BK_REAL(0.0);   m.m44 = BK_REAL(1.0);

	m = BkMatrix4x4_Inverse(&m);

	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)m.m11, (float)0.0);    TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)m.m12, (float)1.0);   TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)m.m13, (float)0.0);   TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)m.m14, (float)-4.0);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)m.m21, (float)-1.0);   TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)m.m22, (float)0.0);   TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)m.m23, (float)0.0);   TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)m.m24, (float)3.0);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)m.m31, (float)0.0);    TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)m.m32, (float)0.0);   TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)m.m33, (float)1.0);   TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)m.m34, (float)0.0);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)m.m41, (float)0.0);    TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)m.m42, (float)0.0);   TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)m.m43, (float)0.0);   TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)m.m44, (float)1.0);
}

void	BkMatrix4x4_FromAngleAxis_test(void)
{
	struct BkVector3 axis = BkVector3_FromXYZ(BK_REAL(1), BK_REAL(0), BK_REAL(0));
	axis = BkVector3_Normalize(&axis);

	struct BkAngleAxis aa;
	BkAngleAxis_SetAngle(&aa, BK_REAL(45));
	BkAngleAxis_SetAxis(&aa, &axis);

	struct BkMatrix4x4 m = BkMatrix4x4_FromBkAngleAxis(&aa);

	struct BkEulerAngles ea = BkEulerAngles_FromBkMatrix4x4(&m);

	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)45, (float)ea.x);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)0, (float)ea.y);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)0, (float)ea.z);
}

void	BkMatrix4x4_FromEulerAngles_test(void)
{
	struct BkEulerAngles ea = BkEulerAngles_FromXYZ(BK_REAL(0), BK_REAL(90), BK_REAL(0));

	struct BkMatrix4x4 m = BkMatrix4x4_FromBkEulerAngles(&ea);

	ea = BkEulerAngles_FromBkMatrix4x4(&m);

	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)0, (float)ea.x);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)90, (float)ea.y);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)0, (float)ea.z);
}

void	BkMatrix4x4_FromBkQuaternion_test(void)
{
	struct BkEulerAngles ea = BkEulerAngles_FromXYZ(BK_REAL(0), BK_REAL(90), BK_REAL(0));

	struct BkQuaternion q = BkQuaternion_FromEulerAngles(&ea);

	struct BkMatrix4x4 m = BkMatrix4x4_FromBkQuaternion(&q);

	ea = BkEulerAngles_FromBkMatrix4x4(&m);

	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)0, (float)ea.x);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)90, (float)ea.y);
	TEST_ASSERT_FLOAT_WITHIN(ERROR_LIMIT, (float)0, (float)ea.z);
}