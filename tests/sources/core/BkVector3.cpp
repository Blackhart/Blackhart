#include <gtest\gtest.h>

#include "../export/cpp/Blackhart.hpp"

TEST(BkVector3, BkVector3_Zero)
{
	struct BkVector3 vec4 = BkVector3_Zero();

	EXPECT_FLOAT_EQ(vec4.x, 0.0);
	EXPECT_FLOAT_EQ(vec4.y, 0.0);
	EXPECT_FLOAT_EQ(vec4.z, 0.0);
}

TEST(BkVector3, BkVector3_Set)
{
	struct BkVector3 vec4 = BkVector3_Zero();

	BkVector3_Set(&vec4, 1.0, 2.0, 4.0);

	EXPECT_FLOAT_EQ(vec4.x, 1.0);
	EXPECT_FLOAT_EQ(vec4.y, 2.0);
	EXPECT_FLOAT_EQ(vec4.z, 4.0);
}

TEST(BkVector3, BkVector3_Copy)
{
	struct BkVector3 vec4 = BkVector3_Zero();

	BkVector3_Set(&vec4, 1.0, 2.0, 4.0);

	struct BkVector3 out = BkVector3_Copy(&vec4);

	EXPECT_FLOAT_EQ(out.x, 1.0);
	EXPECT_FLOAT_EQ(out.y, 2.0);
	EXPECT_FLOAT_EQ(out.z, 4.0);
}

TEST(BkVector3, BkVector3_Assign)
{
	struct BkVector3 vec4 = BkVector3_Zero();

	BkVector3_Set(&vec4, 1.0, 2.0, 4.0);

	struct BkVector3 out;

	BkVector3_Assign(&out, &vec4);

	EXPECT_FLOAT_EQ(out.x, 1.0);
	EXPECT_FLOAT_EQ(out.y, 2.0);
	EXPECT_FLOAT_EQ(out.z, 4.0);
}

TEST(BkVector3, BkVector3_Negate)
{
	struct BkVector3 vec4 = BkVector3_Zero();

	BkVector3_Set(&vec4, 2.0, 4.0, 8.0);

	vec4 = BkVector3_Negate(&vec4);

	EXPECT_FLOAT_EQ(vec4.x, -2.0);
	EXPECT_FLOAT_EQ(vec4.y, -4.0);
	EXPECT_FLOAT_EQ(vec4.z, -8.0);
}

TEST(BkVector3, BkVector3_Mul_Real)
{
	struct BkVector3 vec4 = BkVector3_Zero();

	BkVector3_Set(&vec4, 1.0, 2.0, 3.0);

	vec4 = BkVector3_Mul_Real(&vec4, 2.0);

	EXPECT_FLOAT_EQ(vec4.x, 1.0 * 2.0);
	EXPECT_FLOAT_EQ(vec4.y, 2.0 * 2.0);
	EXPECT_FLOAT_EQ(vec4.z, 3.0 * 2.0);

	BkVector3_Set(&vec4, -5.4, 0.0, 3.0);

	vec4 = BkVector3_Mul_Real(&vec4, -3.0);

	EXPECT_FLOAT_EQ(vec4.x, -5.4 * -3.0);
	EXPECT_FLOAT_EQ(vec4.y, 0.0 * -3.0);
	EXPECT_FLOAT_EQ(vec4.z, 3.0 * -3.0);
}

TEST(BkVector3, BkVector3_Div_Real)
{
	struct BkVector3 vec4 = BkVector3_Zero();

	BkVector3_Set(&vec4, 4.7, -6.0, 8.0);

	vec4 = BkVector3_Div_Real(&vec4, 2.0);

	EXPECT_FLOAT_EQ(vec4.x, 4.7 / 2.0);
	EXPECT_FLOAT_EQ(vec4.y, -6.0 / 2.0);
	EXPECT_FLOAT_EQ(vec4.z, 8.0 / 2.0);
}

TEST(BkVector3, BkVector3_Add_BkVector3)
{
	struct BkVector3 a = BkVector3_Zero();
	struct BkVector3 b = BkVector3_Zero();
	
	BkVector3_Set(&a, 1.0, 2.0, 3.0);
	BkVector3_Set(&b, 4.0, 5.0, 6.0);

	struct BkVector3 out = BkVector3_Add_BkVector3(&a, &b);

	EXPECT_FLOAT_EQ(out.x, 5.0);
	EXPECT_FLOAT_EQ(out.y, 7.0);
	EXPECT_FLOAT_EQ(out.z, 9.0);
}

TEST(BkVector3, BkVector3_Sub_BkVector3)
{
	struct BkVector3 a = BkVector3_Zero();
	struct BkVector3 b = BkVector3_Zero();

	BkVector3_Set(&a, 1.0, 2.0, 3.0);
	BkVector3_Set(&b, 4.0, 5.0, 6.0);

	struct BkVector3 out = BkVector3_Sub_BkVector3(&a, &b);

	EXPECT_FLOAT_EQ(out.x, -3.0);
	EXPECT_FLOAT_EQ(out.y, -3.0);
	EXPECT_FLOAT_EQ(out.z, -3.0);
}

TEST(BkVector3, BkVector3_Magnitude)
{
	struct BkVector3 vec4 = BkVector3_Zero();

	BkVector3_Set(&vec4, 5.0, -4.0, 7.0);

	real out = BkVector3_Magnitude(&vec4);

	EXPECT_FLOAT_EQ(out, sqrt(90.0));
}

TEST(BkVector3, BkVector3_Normalize)
{
	struct BkVector3 vec4 = BkVector3_Zero();

	BkVector3_Set(&vec4, 12.0, -5.0, 8.0);

	struct BkVector3 out = BkVector3_Normalize(&vec4);

	EXPECT_FLOAT_EQ(out.x, 12.0 / sqrt(233));
	EXPECT_FLOAT_EQ(out.y, -5.0 / sqrt(233));
	EXPECT_FLOAT_EQ(out.z, 8.0 / sqrt(233));

	EXPECT_FLOAT_EQ(BkVector3_Magnitude(&out), 1.0);
}

TEST(BkVector3, BkVector3_Dot)
{
	struct BkVector3 a = BkVector3_Zero();
	struct BkVector3 b = BkVector3_Zero();

	BkVector3_Set(&a, 3.0, -2.0, 7.0);
	BkVector3_Set(&b, 0.0, 4.0, -1.0);

	real out = BkVector3_Dot(&a, &b);

	EXPECT_FLOAT_EQ(out, -15.0);
}

TEST(BkVector3, BkVector3_AbsDot)
{
	struct BkVector3 a = BkVector3_Zero();
	struct BkVector3 b = BkVector3_Zero();

	BkVector3_Set(&a, 3.0, -2.0, 7.0);
	BkVector3_Set(&b, 0.0, 4.0, -1.0);

	real out = BkVector3_AbsDot(&a, &b);

	EXPECT_FLOAT_EQ(out, 15.0);
}

TEST(BkVector3, BkVector3_Cross)
{
	struct BkVector3 a = BkVector3_Zero();
	struct BkVector3 b = BkVector3_Zero();

	BkVector3_Set(&a, 1.0, 3.0, 4.0);
	BkVector3_Set(&b, 2.0, -5.0, 8.0);

	struct BkVector3 out = BkVector3_Cross(&a, &b);

	EXPECT_FLOAT_EQ(out.x, 44.0);
	EXPECT_FLOAT_EQ(out.y, 0.0);
	EXPECT_FLOAT_EQ(out.z, -11.0);
}

TEST(BkVector3, BkVector3_Angle)
{
	struct BkVector3 a = BkVector3_Zero();
	struct BkVector3 b = BkVector3_Zero();

	a.x = 1.0;
	b.y = 1.0;

	real out = BkVector3_Angle(&a, &b);

	EXPECT_FLOAT_EQ(out, 90.0);
}

TEST(BkVector3, BkVector3_Lerp)
{
	struct BkVector3 a = BkVector3_Zero();
	struct BkVector3 b = BkVector3_Zero();

	BkVector3_Set(&b, 1.0, 2.0, 4.0);

	struct BkVector3 out = BkVector3_Lerp(&a, &b, 0.0);

	EXPECT_FLOAT_EQ(out.x, 0.0);
	EXPECT_FLOAT_EQ(out.y, 0.0);
	EXPECT_FLOAT_EQ(out.z, 0.0);

	out = BkVector3_Lerp(&a, &b, 1.0);

	EXPECT_FLOAT_EQ(out.x, 1.0);
	EXPECT_FLOAT_EQ(out.y, 2.0);
	EXPECT_FLOAT_EQ(out.z, 4.0);

	out = BkVector3_Lerp(&a, &b, 0.5);

	EXPECT_FLOAT_EQ(out.x, 0.5);
	EXPECT_FLOAT_EQ(out.y, 1.0);
	EXPECT_FLOAT_EQ(out.z, 2.0);

	out = BkVector3_Lerp(&b, &a, 0.5);

	EXPECT_FLOAT_EQ(out.x, 0.5);
	EXPECT_FLOAT_EQ(out.y, 1.0);
	EXPECT_FLOAT_EQ(out.z, 2.0);

	out = BkVector3_Lerp(&b, &b, 0.5);

	EXPECT_FLOAT_EQ(out.x, 1.0);
	EXPECT_FLOAT_EQ(out.y, 2.0);
	EXPECT_FLOAT_EQ(out.z, 4.0);
}

TEST(BkVector3, BkVector3_Max)
{
	struct BkVector3 a = BkVector3_Zero();
	struct BkVector3 b = BkVector3_Zero();

	BkVector3_Set(&b, 1.0, 2.0, 4.0);

	struct BkVector3 out = BkVector3_Max(&a, &b);

	EXPECT_FLOAT_EQ(out.x, 1.0);
	EXPECT_FLOAT_EQ(out.y, 2.0);
	EXPECT_FLOAT_EQ(out.z, 4.0);
}

TEST(BkVector3, BkVector3_Min)
{
	struct BkVector3 a = BkVector3_Zero();
	struct BkVector3 b = BkVector3_Zero();

	BkVector3_Set(&b, 1.0, 2.0, 4.0);

	struct BkVector3 out = BkVector3_Min(&a, &b);

	EXPECT_FLOAT_EQ(out.x, 0.0);
	EXPECT_FLOAT_EQ(out.y, 0.0);
	EXPECT_FLOAT_EQ(out.z, 0.0);
}