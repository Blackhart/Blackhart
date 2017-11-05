#include <gtest\gtest.h>

#include "../export/cpp/Blackhart.hpp"

TEST(BkVector4, BkVector4_Zero)
{
	struct BkVector4 vec4 = BkVector4_Zero();

	EXPECT_FLOAT_EQ(vec4.x, 0.0);
	EXPECT_FLOAT_EQ(vec4.y, 0.0);
	EXPECT_FLOAT_EQ(vec4.z, 0.0);
}

TEST(BkVector4, BkVector4_Set)
{
	struct BkVector4 vec4 = BkVector4_Zero();

	BkVector4_Set(&vec4, 1.0, 2.0, 4.0);

	EXPECT_FLOAT_EQ(vec4.x, 1.0);
	EXPECT_FLOAT_EQ(vec4.y, 2.0);
	EXPECT_FLOAT_EQ(vec4.z, 4.0);
}

TEST(BkVector4, BkVector4_Copy)
{
	struct BkVector4 vec4 = BkVector4_Zero();

	BkVector4_Set(&vec4, 1.0, 2.0, 4.0);

	struct BkVector4 out = BkVector4_Copy(&vec4);

	EXPECT_FLOAT_EQ(out.x, 1.0);
	EXPECT_FLOAT_EQ(out.y, 2.0);
	EXPECT_FLOAT_EQ(out.z, 4.0);
}

TEST(BkVector4, BkVector4_Assign)
{
	struct BkVector4 vec4 = BkVector4_Zero();

	BkVector4_Set(&vec4, 1.0, 2.0, 4.0);

	struct BkVector4 out;

	BkVector4_Assign(&out, &vec4);

	EXPECT_FLOAT_EQ(out.x, 1.0);
	EXPECT_FLOAT_EQ(out.y, 2.0);
	EXPECT_FLOAT_EQ(out.z, 4.0);
}

TEST(BkVector4, BkVector4_Negate)
{
	struct BkVector4 vec4 = BkVector4_Zero();

	BkVector4_Set(&vec4, 2.0, 4.0, 8.0);

	vec4 = BkVector4_Negate(&vec4);

	EXPECT_FLOAT_EQ(vec4.x, -2.0);
	EXPECT_FLOAT_EQ(vec4.y, -4.0);
	EXPECT_FLOAT_EQ(vec4.z, -8.0);
}

TEST(BkVector4, BkVector4_Mul_Real)
{
	struct BkVector4 vec4 = BkVector4_Zero();

	BkVector4_Set(&vec4, 1.0, 2.0, 3.0);

	vec4 = BkVector4_Mul_Real(&vec4, 2.0);

	EXPECT_FLOAT_EQ(vec4.x, 1.0 * 2.0);
	EXPECT_FLOAT_EQ(vec4.y, 2.0 * 2.0);
	EXPECT_FLOAT_EQ(vec4.z, 3.0 * 2.0);

	BkVector4_Set(&vec4, -5.4, 0.0, 3.0);

	vec4 = BkVector4_Mul_Real(&vec4, -3.0);

	EXPECT_FLOAT_EQ(vec4.x, -5.4 * -3.0);
	EXPECT_FLOAT_EQ(vec4.y, 0.0 * -3.0);
	EXPECT_FLOAT_EQ(vec4.z, 3.0 * -3.0);
}

TEST(BkVector4, BkVector4_Div_Real)
{
	struct BkVector4 vec4 = BkVector4_Zero();

	BkVector4_Set(&vec4, 4.7, -6.0, 8.0);

	vec4 = BkVector4_Div_Real(&vec4, 2.0);

	EXPECT_FLOAT_EQ(vec4.x, 4.7 / 2.0);
	EXPECT_FLOAT_EQ(vec4.y, -6.0 / 2.0);
	EXPECT_FLOAT_EQ(vec4.z, 8.0 / 2.0);
}

TEST(BkVector4, BkVector4_Add_BkVector4)
{
	struct BkVector4 a = BkVector4_Zero();
	struct BkVector4 b = BkVector4_Zero();
	
	BkVector4_Set(&a, 1.0, 2.0, 3.0);
	BkVector4_Set(&b, 4.0, 5.0, 6.0);

	struct BkVector4 out = BkVector4_Add_BkVector4(&a, &b);

	EXPECT_FLOAT_EQ(out.x, 5.0);
	EXPECT_FLOAT_EQ(out.y, 7.0);
	EXPECT_FLOAT_EQ(out.z, 9.0);
}

TEST(BkVector4, BkVector4_Sub_BkVector4)
{
	struct BkVector4 a = BkVector4_Zero();
	struct BkVector4 b = BkVector4_Zero();

	BkVector4_Set(&a, 1.0, 2.0, 3.0);
	BkVector4_Set(&b, 4.0, 5.0, 6.0);

	struct BkVector4 out = BkVector4_Sub_BkVector4(&a, &b);

	EXPECT_FLOAT_EQ(out.x, -3.0);
	EXPECT_FLOAT_EQ(out.y, -3.0);
	EXPECT_FLOAT_EQ(out.z, -3.0);
}

TEST(BkVector4, BkVector4_Magnitude)
{
	struct BkVector4 vec4 = BkVector4_Zero();

	BkVector4_Set(&vec4, 5.0, -4.0, 7.0);

	real out = BkVector4_Magnitude(&vec4);

	EXPECT_FLOAT_EQ(out, sqrt(90.0));
}

TEST(BkVector4, BkVector4_Normalize)
{
	struct BkVector4 vec4 = BkVector4_Zero();

	BkVector4_Set(&vec4, 12.0, -5.0, 8.0);

	struct BkVector4 out = BkVector4_Normalize(&vec4);

	EXPECT_FLOAT_EQ(out.x, 12.0 / sqrt(233));
	EXPECT_FLOAT_EQ(out.y, -5.0 / sqrt(233));
	EXPECT_FLOAT_EQ(out.z, 8.0 / sqrt(233));

	EXPECT_FLOAT_EQ(BkVector4_Magnitude(&out), 1.0);
}

TEST(BkVector4, BkVector4_Dot)
{
	struct BkVector4 a = BkVector4_Zero();
	struct BkVector4 b = BkVector4_Zero();

	BkVector4_Set(&a, 3.0, -2.0, 7.0);
	BkVector4_Set(&b, 0.0, 4.0, -1.0);

	real out = BkVector4_Dot(&a, &b);

	EXPECT_FLOAT_EQ(out, -15.0);
}

TEST(BkVector4, BkVector4_Cross)
{
	struct BkVector4 a = BkVector4_Zero();
	struct BkVector4 b = BkVector4_Zero();

	BkVector4_Set(&a, 1.0, 3.0, 4.0);
	BkVector4_Set(&b, 2.0, -5.0, 8.0);

	struct BkVector4 out = BkVector4_Cross(&a, &b);

	EXPECT_FLOAT_EQ(out.x, 44.0);
	EXPECT_FLOAT_EQ(out.y, 0.0);
	EXPECT_FLOAT_EQ(out.z, -11.0);
}

TEST(BkVector4, BkVector4_Angle)
{
	struct BkVector4 a = BkVector4_Zero();
	struct BkVector4 b = BkVector4_Zero();

	a.x = 1.0;
	b.y = 1.0;

	real out = BkVector4_Angle(&a, &b);

	EXPECT_FLOAT_EQ(out, 90.0);
}

TEST(BkVector4, BkVector4_Lerp)
{
	struct BkVector4 a = BkVector4_Zero();
	struct BkVector4 b = BkVector4_Zero();

	BkVector4_Set(&b, 1.0, 2.0, 4.0);

	struct BkVector4 out = BkVector4_Lerp(&a, &b, 0.0);

	EXPECT_FLOAT_EQ(out.x, 0.0);
	EXPECT_FLOAT_EQ(out.y, 0.0);
	EXPECT_FLOAT_EQ(out.z, 0.0);

	out = BkVector4_Lerp(&a, &b, 1.0);

	EXPECT_FLOAT_EQ(out.x, 1.0);
	EXPECT_FLOAT_EQ(out.y, 2.0);
	EXPECT_FLOAT_EQ(out.z, 4.0);

	out = BkVector4_Lerp(&a, &b, 0.5);

	EXPECT_FLOAT_EQ(out.x, 0.5);
	EXPECT_FLOAT_EQ(out.y, 1.0);
	EXPECT_FLOAT_EQ(out.z, 2.0);

	out = BkVector4_Lerp(&b, &a, 0.5);

	EXPECT_FLOAT_EQ(out.x, 0.5);
	EXPECT_FLOAT_EQ(out.y, 1.0);
	EXPECT_FLOAT_EQ(out.z, 2.0);

	out = BkVector4_Lerp(&b, &b, 0.5);

	EXPECT_FLOAT_EQ(out.x, 1.0);
	EXPECT_FLOAT_EQ(out.y, 2.0);
	EXPECT_FLOAT_EQ(out.z, 4.0);
}

TEST(BkVector4, BkVector4_Max)
{
	struct BkVector4 a = BkVector4_Zero();
	struct BkVector4 b = BkVector4_Zero();

	BkVector4_Set(&b, 1.0, 2.0, 4.0);

	struct BkVector4 out = BkVector4_Max(&a, &b);

	EXPECT_FLOAT_EQ(out.x, 1.0);
	EXPECT_FLOAT_EQ(out.y, 2.0);
	EXPECT_FLOAT_EQ(out.z, 4.0);
}

TEST(BkVector4, BkVector4_Min)
{
	struct BkVector4 a = BkVector4_Zero();
	struct BkVector4 b = BkVector4_Zero();

	BkVector4_Set(&b, 1.0, 2.0, 4.0);

	struct BkVector4 out = BkVector4_Min(&a, &b);

	EXPECT_FLOAT_EQ(out.x, 0.0);
	EXPECT_FLOAT_EQ(out.y, 0.0);
	EXPECT_FLOAT_EQ(out.z, 0.0);
}