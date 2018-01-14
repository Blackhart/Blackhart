#include <gtest\gtest.h>

#include "../export/cpp/Blackhart.hpp"

TEST(BkMatrix4x4, BkMatrix4x4_Identity)
{
	struct BkMatrix4x4 m = BkMatrix4x4_Identity();

	EXPECT_FLOAT_EQ(m.m11, 1.0); EXPECT_FLOAT_EQ(m.m12, 0.0); EXPECT_FLOAT_EQ(m.m13, 0.0); EXPECT_FLOAT_EQ(m.m14, 0.0);
	EXPECT_FLOAT_EQ(m.m21, 0.0); EXPECT_FLOAT_EQ(m.m22, 1.0); EXPECT_FLOAT_EQ(m.m23, 0.0); EXPECT_FLOAT_EQ(m.m24, 0.0);
	EXPECT_FLOAT_EQ(m.m31, 0.0); EXPECT_FLOAT_EQ(m.m32, 0.0); EXPECT_FLOAT_EQ(m.m33, 1.0); EXPECT_FLOAT_EQ(m.m34, 0.0);
	EXPECT_FLOAT_EQ(m.m41, 0.0); EXPECT_FLOAT_EQ(m.m42, 0.0); EXPECT_FLOAT_EQ(m.m43, 0.0); EXPECT_FLOAT_EQ(m.m44, 1.0);
}

TEST(BkMatrix4x4, BkMatrix4x4_Copy)
{
	struct BkMatrix4x4 m1 = BkMatrix4x4_Identity();

	m1.m11 = 1.0; m1.m12 = 2.0; m1.m13 = 3.0; m1.m14 = 4.0;
	m1.m21 = 5.0; m1.m22 = 6.0; m1.m23 = 7.0; m1.m24 = 8.0;
	m1.m31 = 9.0; m1.m32 = 10.0; m1.m33 = 11.0; m1.m34 = 12.0;
	m1.m41 = 13.0; m1.m42 = 14.0; m1.m43 = 15.0; m1.m44 = 16.0;

	struct BkMatrix4x4 m = BkMatrix4x4_Copy(&m1);

	EXPECT_FLOAT_EQ(m.m11, 1.0); EXPECT_FLOAT_EQ(m.m12, 2.0); EXPECT_FLOAT_EQ(m.m13, 3.0); EXPECT_FLOAT_EQ(m.m14, 4.0);
	EXPECT_FLOAT_EQ(m.m21, 5.0); EXPECT_FLOAT_EQ(m.m22, 6.0); EXPECT_FLOAT_EQ(m.m23, 7.0); EXPECT_FLOAT_EQ(m.m24, 8.0);
	EXPECT_FLOAT_EQ(m.m31, 9.0); EXPECT_FLOAT_EQ(m.m32, 10.0); EXPECT_FLOAT_EQ(m.m33, 11.0); EXPECT_FLOAT_EQ(m.m34, 12.0);
	EXPECT_FLOAT_EQ(m.m41, 13.0); EXPECT_FLOAT_EQ(m.m42, 14.0); EXPECT_FLOAT_EQ(m.m43, 15.0); EXPECT_FLOAT_EQ(m.m44, 16.0);
}

TEST(BkMatrix4x4, BkMatrix4x4_Assign)
{
	struct BkMatrix4x4 m1 = BkMatrix4x4_Identity();

	m1.m11 = 1.0; m1.m12 = 2.0; m1.m13 = 3.0; m1.m14 = 4.0;
	m1.m21 = 5.0; m1.m22 = 6.0; m1.m23 = 7.0; m1.m24 = 8.0;
	m1.m31 = 9.0; m1.m32 = 10.0; m1.m33 = 11.0; m1.m34 = 12.0;
	m1.m41 = 13.0; m1.m42 = 14.0; m1.m43 = 15.0; m1.m44 = 16.0;

	struct BkMatrix4x4 m = BkMatrix4x4_Identity();

	BkMatrix4x4_Assign(&m, &m1);

	EXPECT_FLOAT_EQ(m.m11, 1.0); EXPECT_FLOAT_EQ(m.m12, 2.0); EXPECT_FLOAT_EQ(m.m13, 3.0); EXPECT_FLOAT_EQ(m.m14, 4.0);
	EXPECT_FLOAT_EQ(m.m21, 5.0); EXPECT_FLOAT_EQ(m.m22, 6.0); EXPECT_FLOAT_EQ(m.m23, 7.0); EXPECT_FLOAT_EQ(m.m24, 8.0);
	EXPECT_FLOAT_EQ(m.m31, 9.0); EXPECT_FLOAT_EQ(m.m32, 10.0); EXPECT_FLOAT_EQ(m.m33, 11.0); EXPECT_FLOAT_EQ(m.m34, 12.0);
	EXPECT_FLOAT_EQ(m.m41, 13.0); EXPECT_FLOAT_EQ(m.m42, 14.0); EXPECT_FLOAT_EQ(m.m43, 15.0); EXPECT_FLOAT_EQ(m.m44, 16.0);
}

TEST(BkMatrix4x4, BkMatrix4x4_Transpose)
{
	struct BkMatrix4x4 m = BkMatrix4x4_Identity();

	m = BkMatrix4x4_Transpose(&m);

	EXPECT_FLOAT_EQ(m.m11, 1.0); EXPECT_FLOAT_EQ(m.m12, 0.0); EXPECT_FLOAT_EQ(m.m13, 0.0); EXPECT_FLOAT_EQ(m.m14, 0.0);
	EXPECT_FLOAT_EQ(m.m21, 0.0); EXPECT_FLOAT_EQ(m.m22, 1.0); EXPECT_FLOAT_EQ(m.m23, 0.0); EXPECT_FLOAT_EQ(m.m24, 0.0);
	EXPECT_FLOAT_EQ(m.m31, 0.0); EXPECT_FLOAT_EQ(m.m32, 0.0); EXPECT_FLOAT_EQ(m.m33, 1.0); EXPECT_FLOAT_EQ(m.m34, 0.0);
	EXPECT_FLOAT_EQ(m.m41, 0.0); EXPECT_FLOAT_EQ(m.m42, 0.0); EXPECT_FLOAT_EQ(m.m43, 0.0); EXPECT_FLOAT_EQ(m.m44, 1.0);

	m.m11 = 1.0; m.m12 = 2.0; m.m13 = 3.0; m.m14 = 4.0;
	m.m21 = 5.0; m.m22 = 6.0; m.m23 = 7.0; m.m24 = 8.0;
	m.m31 = 9.0; m.m32 = 10.0; m.m33 = 11.0; m.m34 = 12.0;
	m.m41 = 13.0; m.m42 = 14.0; m.m43 = 15.0; m.m44 = 16.0;

	m = BkMatrix4x4_Transpose(&m);

	EXPECT_FLOAT_EQ(m.m11, 1.0); EXPECT_FLOAT_EQ(m.m12, 5.0); EXPECT_FLOAT_EQ(m.m13, 9.0); EXPECT_FLOAT_EQ(m.m14, 13.0);
	EXPECT_FLOAT_EQ(m.m21, 2.0); EXPECT_FLOAT_EQ(m.m22, 6.0); EXPECT_FLOAT_EQ(m.m23, 10.0); EXPECT_FLOAT_EQ(m.m24, 14.0);
	EXPECT_FLOAT_EQ(m.m31, 3.0); EXPECT_FLOAT_EQ(m.m32, 7.0); EXPECT_FLOAT_EQ(m.m33, 11.0); EXPECT_FLOAT_EQ(m.m34, 15.0);
	EXPECT_FLOAT_EQ(m.m41, 4.0); EXPECT_FLOAT_EQ(m.m42, 8.0); EXPECT_FLOAT_EQ(m.m43, 12.0); EXPECT_FLOAT_EQ(m.m44, 16.0);
}

TEST(BkMatrix4x4, BkMatrix4x4_Mul_real)
{
	struct BkMatrix4x4 m = BkMatrix4x4_Identity();

	m.m11 = 1.0; m.m12 = 2.0; m.m13 = 3.0; m.m14 = 4.0;
	m.m21 = 5.0; m.m22 = 6.0; m.m23 = 7.0; m.m24 = 8.0;
	m.m31 = 9.0; m.m32 = 10.0; m.m33 = 11.0; m.m34 = 12.0;
	m.m41 = 13.0; m.m42 = 14.0; m.m43 = 15.0; m.m44 = 16.0;

	m = BkMatrix4x4_Mul_real(&m, 2.0);

	EXPECT_FLOAT_EQ(m.m11, 2.0); EXPECT_FLOAT_EQ(m.m12, 4.0); EXPECT_FLOAT_EQ(m.m13, 6.0); EXPECT_FLOAT_EQ(m.m14, 8.0);
	EXPECT_FLOAT_EQ(m.m21, 10.0); EXPECT_FLOAT_EQ(m.m22, 12.0); EXPECT_FLOAT_EQ(m.m23, 14.0); EXPECT_FLOAT_EQ(m.m24, 16.0);
	EXPECT_FLOAT_EQ(m.m31, 18.0); EXPECT_FLOAT_EQ(m.m32, 20.0); EXPECT_FLOAT_EQ(m.m33, 22.0); EXPECT_FLOAT_EQ(m.m34, 24.0);
	EXPECT_FLOAT_EQ(m.m41, 26.0); EXPECT_FLOAT_EQ(m.m42, 28.0); EXPECT_FLOAT_EQ(m.m43, 30.0); EXPECT_FLOAT_EQ(m.m44, 32.0);
}

TEST(BkMatrix4x4, BkMatrix4x4_Mul_BkMatrix4x4)
{
	struct BkMatrix4x4 m1 = BkMatrix4x4_Identity();
	struct BkMatrix4x4 m2 = BkMatrix4x4_Identity();

	m1.m11 = 1.0; m1.m12 = -5.0; m1.m13 = 3.0; m1.m14 = 0.0;
	m1.m21 = 0.0; m1.m22 = -2.0; m1.m23 = 6.0; m1.m24 = 0.0;
	m1.m31 = 7.0; m1.m32 = 2.0; m1.m33 = -4.0; m1.m34 = 0.0;
	m1.m41 = 0.0; m1.m42 = 0.0; m1.m43 = 0.0; m1.m44 = 1.0;

	m2.m11 = -8.0; m2.m12 = 6.0; m2.m13 = 1.0; m2.m14 = 0.0;
	m2.m21 = 7.0; m2.m22 = 0.0; m2.m23 = -3.0; m2.m24 = 0.0;
	m2.m31 = 2.0; m2.m32 = 4.0; m2.m33 = 5.0; m2.m34 = 0.0;
	m2.m41 = 0.0; m2.m42 = 0.0; m2.m43 = 0.0; m2.m44 = 1.0;

	struct BkMatrix4x4 m = BkMatrix4x4_Mul_BkMatrix4x4(&m1, &m2);

	EXPECT_FLOAT_EQ(m.m11, -37.0); EXPECT_FLOAT_EQ(m.m12, 18.0); EXPECT_FLOAT_EQ(m.m13, 31.0); EXPECT_FLOAT_EQ(m.m14, 0.0);
	EXPECT_FLOAT_EQ(m.m21, -2.0); EXPECT_FLOAT_EQ(m.m22, 24.0); EXPECT_FLOAT_EQ(m.m23, 36.0); EXPECT_FLOAT_EQ(m.m24, 0.0);
	EXPECT_FLOAT_EQ(m.m31, -50.0); EXPECT_FLOAT_EQ(m.m32, 26.0); EXPECT_FLOAT_EQ(m.m33, -19.0); EXPECT_FLOAT_EQ(m.m34, 0.0);
	EXPECT_FLOAT_EQ(m.m41, 0.0); EXPECT_FLOAT_EQ(m.m42, 0.0); EXPECT_FLOAT_EQ(m.m43, 0.0); EXPECT_FLOAT_EQ(m.m44, 1.0);
}

TEST(BkMatrix4x4, BkMatrix4x4_Mul_BkVector3)
{
	struct BkVector3 v = BkVector3_Zero();

	v.x = 1.0; v.y = 2.0; v.z = 4.0;

	struct BkMatrix4x4 m = BkMatrix4x4_Identity();

	m.m11 = 1.0; m.m12 = 2.0; m.m13 = 3.0; m.m14 = 4.0;
	m.m21 = 5.0; m.m22 = 6.0; m.m23 = 7.0; m.m24 = 8.0;
	m.m31 = 9.0; m.m32 = 10.0; m.m33 = 11.0; m.m34 = 12.0;
	m.m41 = 13.0; m.m42 = 14.0; m.m43 = 15.0; m.m44 = 16.0;

	v = BkMatrix4x4_Mul_BkVector3(&m, &v);

	EXPECT_FLOAT_EQ(v.x, 17.0); EXPECT_FLOAT_EQ(v.y, 45.0); EXPECT_FLOAT_EQ(v.z, 73.0);
}

TEST(BkMatrix4x4, BkMatrix4x4_Mul_BkPoint3)
{
	struct BkPoint3 p = BkPoint3_Zero();

	p.x = 1.0; p.y = 2.0; p.z = 4.0;

	struct BkMatrix4x4 m = BkMatrix4x4_Identity();

	m.m11 = 1.0; m.m12 = 2.0; m.m13 = 3.0; m.m14 = 4.0;
	m.m21 = 5.0; m.m22 = 6.0; m.m23 = 7.0; m.m24 = 8.0;
	m.m31 = 9.0; m.m32 = 10.0; m.m33 = 11.0; m.m34 = 12.0;
	m.m41 = 13.0; m.m42 = 14.0; m.m43 = 15.0; m.m44 = 16.0;

	p = BkMatrix4x4_Mul_BkPoint3(&m, &p);

	EXPECT_FLOAT_EQ(p.x, 21.0); EXPECT_FLOAT_EQ(p.y, 53.0); EXPECT_FLOAT_EQ(p.z, 85.0);
}

TEST(BkMatrix4x4, BkMatrix4x4_Mul_BkPoint4)
{
	struct BkPoint3 p = BkPoint3_Zero();

	p.x = 1.0; p.y = 2.0; p.z = 4.0;

	struct BkMatrix4x4 m = BkMatrix4x4_Identity();

	m.m11 = 1.0; m.m12 = 2.0; m.m13 = 3.0; m.m14 = 4.0;
	m.m21 = 5.0; m.m22 = 6.0; m.m23 = 7.0; m.m24 = 8.0;
	m.m31 = 9.0; m.m32 = 10.0; m.m33 = 11.0; m.m34 = 12.0;
	m.m41 = 2.0; m.m42 = 4.0; m.m43 = 8.0; m.m44 = 2.0;

	p = BkMatrix4x4_Mul_BkPoint4(&m, &p);

	EXPECT_FLOAT_EQ(p.x, 21.0 / 44.0); EXPECT_FLOAT_EQ(p.y, 53.0 / 44.0); EXPECT_FLOAT_EQ(p.z, 85.0 / 44.0);
}

TEST(BkMatrix4x4, BkMatrix4x4_Rotation_x)
{
	struct BkMatrix4x4 m = BkMatrix4x4_Identity();
	struct BkMatrix4x4 mr = BkMatrix4x4_Rotation_x(90.0);

	m = BkMatrix4x4_Mul_BkMatrix4x4(&m, &mr);

	real const r = 0.017453292519943295769236907684886127134428718885417254560 * 90.0;
	real const cr = cos(r);
	real const sr = sin(r);

	EXPECT_FLOAT_EQ(m.m11, 1.0); EXPECT_FLOAT_EQ(m.m12, 0.0); EXPECT_FLOAT_EQ(m.m13, 0.0); EXPECT_FLOAT_EQ(m.m14, 0.0);
	EXPECT_FLOAT_EQ(m.m21, 0.0); EXPECT_FLOAT_EQ(m.m22, cr); EXPECT_FLOAT_EQ(m.m23, -sr); EXPECT_FLOAT_EQ(m.m24, 0.0);
	EXPECT_FLOAT_EQ(m.m31, 0.0); EXPECT_FLOAT_EQ(m.m32, sr); EXPECT_FLOAT_EQ(m.m33, cr); EXPECT_FLOAT_EQ(m.m34, 0.0);
	EXPECT_FLOAT_EQ(m.m41, 0.0); EXPECT_FLOAT_EQ(m.m42, 0.0); EXPECT_FLOAT_EQ(m.m43, 0.0); EXPECT_FLOAT_EQ(m.m44, 1.0);
}

TEST(BkMatrix4x4, BkMatrix4x4_Rotation_y)
{
	struct BkMatrix4x4 m = BkMatrix4x4_Identity();
	struct BkMatrix4x4 mr = BkMatrix4x4_Rotation_y(90.0);

	m = BkMatrix4x4_Mul_BkMatrix4x4(&m, &mr);

	real const r = 0.017453292519943295769236907684886127134428718885417254560 * 90.0;
	real const cr = cos(r);
	real const sr = sin(r);

	EXPECT_FLOAT_EQ(m.m11, cr); EXPECT_FLOAT_EQ(m.m12, 0.0); EXPECT_FLOAT_EQ(m.m13, sr); EXPECT_FLOAT_EQ(m.m14, 0.0);
	EXPECT_FLOAT_EQ(m.m21, 0.0); EXPECT_FLOAT_EQ(m.m22, 1.0); EXPECT_FLOAT_EQ(m.m23, 0.0); EXPECT_FLOAT_EQ(m.m24, 0.0);
	EXPECT_FLOAT_EQ(m.m31, -sr); EXPECT_FLOAT_EQ(m.m32, 0.0); EXPECT_FLOAT_EQ(m.m33, cr); EXPECT_FLOAT_EQ(m.m34, 0.0);
	EXPECT_FLOAT_EQ(m.m41, 0.0); EXPECT_FLOAT_EQ(m.m42, 0.0); EXPECT_FLOAT_EQ(m.m43, 0.0); EXPECT_FLOAT_EQ(m.m44, 1.0);
}

TEST(BkMatrix4x4, BkMatrix4x4_Rotation_z)
{
	struct BkMatrix4x4 m = BkMatrix4x4_Identity();
	struct BkMatrix4x4 mr = BkMatrix4x4_Rotation_z(90.0);

	m = BkMatrix4x4_Mul_BkMatrix4x4(&m, &mr);

	real const r = 0.017453292519943295769236907684886127134428718885417254560 * 90.0;
	real const cr = cos(r);
	real const sr = sin(r);

	EXPECT_FLOAT_EQ(m.m11, cr); EXPECT_FLOAT_EQ(m.m12, -sr); EXPECT_FLOAT_EQ(m.m13, 0.0); EXPECT_FLOAT_EQ(m.m14, 0.0);
	EXPECT_FLOAT_EQ(m.m21, sr); EXPECT_FLOAT_EQ(m.m22, cr); EXPECT_FLOAT_EQ(m.m23, 0.0); EXPECT_FLOAT_EQ(m.m24, 0.0);
	EXPECT_FLOAT_EQ(m.m31, 0.0); EXPECT_FLOAT_EQ(m.m32, 0.0); EXPECT_FLOAT_EQ(m.m33, 1.0); EXPECT_FLOAT_EQ(m.m34, 0.0);
	EXPECT_FLOAT_EQ(m.m41, 0.0); EXPECT_FLOAT_EQ(m.m42, 0.0); EXPECT_FLOAT_EQ(m.m43, 0.0); EXPECT_FLOAT_EQ(m.m44, 1.0);
}

TEST(BkMatrix4x4, BkMatrix4x4_Scaling_Uniform)
{
	struct BkMatrix4x4 ms = BkMatrix4x4_Scaling_Uniform(2.0);

	EXPECT_FLOAT_EQ(ms.m11, 2.0); EXPECT_FLOAT_EQ(ms.m12, 0.0); EXPECT_FLOAT_EQ(ms.m13, 0.0); EXPECT_FLOAT_EQ(ms.m14, 0.0);
	EXPECT_FLOAT_EQ(ms.m21, 0.0); EXPECT_FLOAT_EQ(ms.m22, 2.0); EXPECT_FLOAT_EQ(ms.m23, 0.0); EXPECT_FLOAT_EQ(ms.m24, 0.0);
	EXPECT_FLOAT_EQ(ms.m31, 0.0); EXPECT_FLOAT_EQ(ms.m32, 0.0); EXPECT_FLOAT_EQ(ms.m33, 2.0); EXPECT_FLOAT_EQ(ms.m34, 0.0);
	EXPECT_FLOAT_EQ(ms.m41, 0.0); EXPECT_FLOAT_EQ(ms.m42, 0.0); EXPECT_FLOAT_EQ(ms.m43, 0.0); EXPECT_FLOAT_EQ(ms.m44, 1.0);
}

TEST(BkMatrix4x4, BkMatrix4x4_Scaling_Nonuniform)
{
	struct BkMatrix4x4 ms = BkMatrix4x4_Scaling_Nonuniform(2.0, 4.0, 6.0);

	EXPECT_FLOAT_EQ(ms.m11, 2.0); EXPECT_FLOAT_EQ(ms.m12, 0.0); EXPECT_FLOAT_EQ(ms.m13, 0.0); EXPECT_FLOAT_EQ(ms.m14, 0.0);
	EXPECT_FLOAT_EQ(ms.m21, 0.0); EXPECT_FLOAT_EQ(ms.m22, 4.0); EXPECT_FLOAT_EQ(ms.m23, 0.0); EXPECT_FLOAT_EQ(ms.m24, 0.0);
	EXPECT_FLOAT_EQ(ms.m31, 0.0); EXPECT_FLOAT_EQ(ms.m32, 0.0); EXPECT_FLOAT_EQ(ms.m33, 6.0); EXPECT_FLOAT_EQ(ms.m34, 0.0);
	EXPECT_FLOAT_EQ(ms.m41, 0.0); EXPECT_FLOAT_EQ(ms.m42, 0.0); EXPECT_FLOAT_EQ(ms.m43, 0.0); EXPECT_FLOAT_EQ(ms.m44, 1.0);
}

TEST(BkMatrix4x4, BkMatrix4x4_Translation)
{
	struct BkMatrix4x4 mt = BkMatrix4x4_Translation(2.0, 4.0, 8.0);

	EXPECT_FLOAT_EQ(mt.m11, 1.0); EXPECT_FLOAT_EQ(mt.m12, 0.0); EXPECT_FLOAT_EQ(mt.m13, 0.0); EXPECT_FLOAT_EQ(mt.m14, 2.0);
	EXPECT_FLOAT_EQ(mt.m21, 0.0); EXPECT_FLOAT_EQ(mt.m22, 1.0); EXPECT_FLOAT_EQ(mt.m23, 0.0); EXPECT_FLOAT_EQ(mt.m24, 4.0);
	EXPECT_FLOAT_EQ(mt.m31, 0.0); EXPECT_FLOAT_EQ(mt.m32, 0.0); EXPECT_FLOAT_EQ(mt.m33, 1.0); EXPECT_FLOAT_EQ(mt.m34, 8.0);
	EXPECT_FLOAT_EQ(mt.m41, 0.0); EXPECT_FLOAT_EQ(mt.m42, 0.0); EXPECT_FLOAT_EQ(mt.m43, 0.0); EXPECT_FLOAT_EQ(mt.m44, 1.0);
}

TEST(BkMatrix4x4, BkMatrix4x4_Determinant)
{
	struct BkMatrix4x4 m = BkMatrix4x4_Identity();

	m.m11 = 11.0; m.m12 = 12.0; m.m13 = 13.0; m.m14 = 14.0;
	m.m21 = 21.0; m.m22 = 22.0; m.m23 = 23.0; m.m24 = 24.0;
	m.m31 = 31.0; m.m32 = 32.0; m.m33 = 33.0; m.m34 = 34.0;
	m.m41 = 41.0; m.m42 = 42.0; m.m43 = 43.0; m.m44 = 44.0;

	real d = BkMatrix4x4_Determinant(&m);

	EXPECT_FLOAT_EQ(d, 0.0);

	m = BkMatrix4x4_Identity();

	m.m11 = 1.0; m.m12 = 0.0; m.m13 = 0.0; m.m14 = 0.0;
	m.m21 = 1.0; m.m22 = 1.0; m.m23 = 0.0; m.m24 = 0.0;
	m.m31 = 0.0; m.m32 = 0.0; m.m33 = 1.0; m.m34 = 0.0;
	m.m41 = 0.0; m.m42 = 0.0; m.m43 = 0.0; m.m44 = 1.0;

	d = BkMatrix4x4_Determinant(&m);

	EXPECT_FLOAT_EQ(d, 1.0);
}

TEST(BkMatrix4x4, BkMatrix4x4_Inverse)
{
	struct BkMatrix4x4 m = BkMatrix4x4_Identity();

	m.m11 = 0.0; m.m12 = -1.0; m.m13 = 0.0; m.m14 = 3.0;
	m.m21 = 1.0; m.m22 = 0.0; m.m23 = 0.0; m.m24 = 4.0;
	m.m31 = 0.0; m.m32 = 0.0; m.m33 = 1.0; m.m34 = 0.0;
	m.m41 = 0.0; m.m42 = 0.0; m.m43 = 0.0; m.m44 = 1.0;

	m = BkMatrix4x4_Inverse(&m);

	EXPECT_FLOAT_EQ(m.m11, 0.0); EXPECT_FLOAT_EQ(m.m12, 1.0); EXPECT_FLOAT_EQ(m.m13, 0.0); EXPECT_FLOAT_EQ(m.m14, -4.0);
	EXPECT_FLOAT_EQ(m.m21, -1.0); EXPECT_FLOAT_EQ(m.m22, 0.0); EXPECT_FLOAT_EQ(m.m23, 0.0); EXPECT_FLOAT_EQ(m.m24, 3.0);
	EXPECT_FLOAT_EQ(m.m31, 0.0); EXPECT_FLOAT_EQ(m.m32, 0.0); EXPECT_FLOAT_EQ(m.m33, 1.0); EXPECT_FLOAT_EQ(m.m34, 0.0);
	EXPECT_FLOAT_EQ(m.m41, 0.0); EXPECT_FLOAT_EQ(m.m42, 0.0); EXPECT_FLOAT_EQ(m.m43, 0.0); EXPECT_FLOAT_EQ(m.m44, 1.0);
}