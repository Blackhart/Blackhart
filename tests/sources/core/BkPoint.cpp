#include <gtest\gtest.h>

#include "../export/cpp/Blackhart.hpp"

TEST(BkPoint, BkPoint_Zero)
{
	struct BkPoint p = BkPoint_Zero();

	EXPECT_FLOAT_EQ(p.x, 0.0);
	EXPECT_FLOAT_EQ(p.y, 0.0);
	EXPECT_FLOAT_EQ(p.z, 0.0);
}

TEST(BkPoint, BkPoint_Set)
{
	struct BkPoint p = BkPoint_Zero();

	BkPoint_Set(&p, 1.0, 2.0, 4.0);

	EXPECT_FLOAT_EQ(p.x, 1.0);
	EXPECT_FLOAT_EQ(p.y, 2.0);
	EXPECT_FLOAT_EQ(p.z, 4.0);
}

TEST(BkPoint, BkPoint_Copy)
{
	struct BkPoint p = BkPoint_Zero();

	BkPoint_Set(&p, 1.0, 2.0, 4.0);

	struct BkPoint out = BkPoint_Copy(&p);

	EXPECT_FLOAT_EQ(out.x, 1.0);
	EXPECT_FLOAT_EQ(out.y, 2.0);
	EXPECT_FLOAT_EQ(out.z, 4.0);
}

TEST(BkPoint, BkPoint_Assign)
{
	struct BkPoint p = BkPoint_Zero();

	BkPoint_Set(&p, 1.0, 2.0, 4.0);

	struct BkPoint out;

	BkPoint_Assign(&out, &p);

	EXPECT_FLOAT_EQ(out.x, 1.0);
	EXPECT_FLOAT_EQ(out.y, 2.0);
	EXPECT_FLOAT_EQ(out.z, 4.0);
}

TEST(BkPoint, BkPoint_Add_BkVector4)
{
	struct BkPoint a = BkPoint_Zero();
	struct BkVector4 b = BkVector4_Zero();

	BkPoint_Set(&a, 1.0, 2.0, 3.0);
	BkVector4_Set(&b, 4.0, 5.0, 6.0);

	struct BkPoint out = BkPoint_Add_BkVector4(&a, &b);

	EXPECT_FLOAT_EQ(out.x, 5.0);
	EXPECT_FLOAT_EQ(out.y, 7.0);
	EXPECT_FLOAT_EQ(out.z, 9.0);
}

TEST(BkPoint, BkPoint_Sub_BkVector4)
{
	struct BkPoint a = BkPoint_Zero();
	struct BkVector4 b = BkVector4_Zero();

	BkPoint_Set(&a, 1.0, 2.0, 3.0);
	BkVector4_Set(&b, 4.0, 5.0, 6.0);

	struct BkPoint out = BkPoint_Sub_BkVector4(&a, &b);

	EXPECT_FLOAT_EQ(out.x, -3.0);
	EXPECT_FLOAT_EQ(out.y, -3.0);
	EXPECT_FLOAT_EQ(out.z, -3.0);
}

TEST(BkPoint, BkPoint_Lerp)
{
	struct BkPoint a = BkPoint_Zero();
	struct BkPoint b = BkPoint_Zero();

	BkPoint_Set(&b, 1.0, 2.0, 4.0);

	struct BkPoint out = BkPoint_Lerp(&a, &b, 0.0);

	EXPECT_FLOAT_EQ(out.x, 0.0);
	EXPECT_FLOAT_EQ(out.y, 0.0);
	EXPECT_FLOAT_EQ(out.z, 0.0);

	out = BkPoint_Lerp(&a, &b, 1.0);

	EXPECT_FLOAT_EQ(out.x, 1.0);
	EXPECT_FLOAT_EQ(out.y, 2.0);
	EXPECT_FLOAT_EQ(out.z, 4.0);

	out = BkPoint_Lerp(&a, &b, 0.5);

	EXPECT_FLOAT_EQ(out.x, 0.5);
	EXPECT_FLOAT_EQ(out.y, 1.0);
	EXPECT_FLOAT_EQ(out.z, 2.0);

	out = BkPoint_Lerp(&b, &a, 0.5);

	EXPECT_FLOAT_EQ(out.x, 0.5);
	EXPECT_FLOAT_EQ(out.y, 1.0);
	EXPECT_FLOAT_EQ(out.z, 2.0);

	out = BkPoint_Lerp(&b, &b, 0.5);

	EXPECT_FLOAT_EQ(out.x, 1.0);
	EXPECT_FLOAT_EQ(out.y, 2.0);
	EXPECT_FLOAT_EQ(out.z, 4.0);
}

TEST(BkPoint, BkPoint_Distance)
{
	struct BkPoint a = BkPoint_Zero();
	struct BkPoint b = BkPoint_Zero();

	BkPoint_Set(&a, 5.0, 0.0, 0.0);
	BkPoint_Set(&b, -1.0, 8.0, 0.0);

	real d = BkPoint_Distance(&a, &b);

	EXPECT_FLOAT_EQ(d, 10.0);
}