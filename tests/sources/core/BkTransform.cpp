#include <gtest\gtest.h>

#include "../export/cpp/Blackhart.hpp"

TEST(BkTransform, BkTransform_Forward)
{
	struct BkMatrix4x4 m = BkMatrix4x4_Identity();

	m.m11 = 1.0; m.m12 = 2.0; m.m13 = 3.0; m.m14 = 4.0;
	m.m21 = 5.0; m.m22 = 6.0; m.m23 = 7.0; m.m24 = 8.0;
	m.m31 = 9.0; m.m32 = 10.0; m.m33 = 11.0; m.m34 = 12.0;
	m.m41 = 13.0; m.m42 = 14.0; m.m43 = 15.0; m.m44 = 16.0;

	struct BkVector3 f = BkTransform_Forward(&m);

	EXPECT_FLOAT_EQ(f.x, 3.0);
	EXPECT_FLOAT_EQ(f.y, 7.0);
	EXPECT_FLOAT_EQ(f.z, 11.0);
}

TEST(BkTransform, BkTransform_Right)
{
	struct BkMatrix4x4 m = BkMatrix4x4_Identity();

	m.m11 = 1.0; m.m12 = 2.0; m.m13 = 3.0; m.m14 = 4.0;
	m.m21 = 5.0; m.m22 = 6.0; m.m23 = 7.0; m.m24 = 8.0;
	m.m31 = 9.0; m.m32 = 10.0; m.m33 = 11.0; m.m34 = 12.0;
	m.m41 = 13.0; m.m42 = 14.0; m.m43 = 15.0; m.m44 = 16.0;

	struct BkVector3 r = BkTransform_Right(&m);

	EXPECT_FLOAT_EQ(r.x, 1.0);
	EXPECT_FLOAT_EQ(r.y, 5.0);
	EXPECT_FLOAT_EQ(r.z, 9.0);
}

TEST(BkTransform, BkTransform_Up)
{
	struct BkMatrix4x4 m = BkMatrix4x4_Identity();

	m.m11 = 1.0; m.m12 = 2.0; m.m13 = 3.0; m.m14 = 4.0;
	m.m21 = 5.0; m.m22 = 6.0; m.m23 = 7.0; m.m24 = 8.0;
	m.m31 = 9.0; m.m32 = 10.0; m.m33 = 11.0; m.m34 = 12.0;
	m.m41 = 13.0; m.m42 = 14.0; m.m43 = 15.0; m.m44 = 16.0;

	struct BkVector3 u = BkTransform_Up(&m);

	EXPECT_FLOAT_EQ(u.x, 2.0);
	EXPECT_FLOAT_EQ(u.y, 6.0);
	EXPECT_FLOAT_EQ(u.z, 10.0);
}

TEST(BkTransform, BkTransform_Position)
{
	struct BkMatrix4x4 m = BkMatrix4x4_Identity();

	m.m11 = 1.0; m.m12 = 2.0; m.m13 = 3.0; m.m14 = 4.0;
	m.m21 = 5.0; m.m22 = 6.0; m.m23 = 7.0; m.m24 = 8.0;
	m.m31 = 9.0; m.m32 = 10.0; m.m33 = 11.0; m.m34 = 12.0;
	m.m41 = 13.0; m.m42 = 14.0; m.m43 = 15.0; m.m44 = 16.0;

	struct BkPoint3 p = BkTransform_Position(&m);

	EXPECT_FLOAT_EQ(p.x, 4.0);
	EXPECT_FLOAT_EQ(p.y, 8.0);
	EXPECT_FLOAT_EQ(p.z, 12.0);
}