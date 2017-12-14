#include <gtest\gtest.h>

#include "../export/cpp/Blackhart.hpp"

TEST(BkPoint3, BkPoint3_Zero)
{
	struct BkPoint3 p = BkPoint3_Zero();

	EXPECT_FLOAT_EQ(p.x, 0.0);
	EXPECT_FLOAT_EQ(p.y, 0.0);
	EXPECT_FLOAT_EQ(p.z, 0.0);
}

TEST(BkPoint3, BkPoint3_Set)
{
	struct BkPoint3 p = BkPoint3_Zero();

	BkPoint3_Set(&p, 1.0, 2.0, 4.0);

	EXPECT_FLOAT_EQ(p.x, 1.0);
	EXPECT_FLOAT_EQ(p.y, 2.0);
	EXPECT_FLOAT_EQ(p.z, 4.0);
}

TEST(BkPoint3, BkPoint3_Copy)
{
	struct BkPoint3 p = BkPoint3_Zero();

	BkPoint3_Set(&p, 1.0, 2.0, 4.0);

	struct BkPoint3 out = BkPoint3_Copy(&p);

	EXPECT_FLOAT_EQ(out.x, 1.0);
	EXPECT_FLOAT_EQ(out.y, 2.0);
	EXPECT_FLOAT_EQ(out.z, 4.0);
}

TEST(BkPoint3, BkPoint3_Assign)
{
	struct BkPoint3 p = BkPoint3_Zero();

	BkPoint3_Set(&p, 1.0, 2.0, 4.0);

	struct BkPoint3 out;

	BkPoint3_Assign(&out, &p);

	EXPECT_FLOAT_EQ(out.x, 1.0);
	EXPECT_FLOAT_EQ(out.y, 2.0);
	EXPECT_FLOAT_EQ(out.z, 4.0);
}

TEST(BkPoint3, BkPoint3_Add_BkVector3)
{
	struct BkPoint3 a = BkPoint3_Zero();
	struct BkVector3 b = BkVector3_Zero();

	BkPoint3_Set(&a, 1.0, 2.0, 3.0);
	BkVector3_Set(&b, 4.0, 5.0, 6.0);

	struct BkPoint3 out = BkPoint3_Add_BkVector3(&a, &b);

	EXPECT_FLOAT_EQ(out.x, 5.0);
	EXPECT_FLOAT_EQ(out.y, 7.0);
	EXPECT_FLOAT_EQ(out.z, 9.0);
}

TEST(BkPoint3, BkPoint3_Sub_BkVector3)
{
	struct BkPoint3 a = BkPoint3_Zero();
	struct BkVector3 b = BkVector3_Zero();

	BkPoint3_Set(&a, 1.0, 2.0, 3.0);
	BkVector3_Set(&b, 4.0, 5.0, 6.0);

	struct BkPoint3 out = BkPoint3_Sub_BkVector3(&a, &b);

	EXPECT_FLOAT_EQ(out.x, -3.0);
	EXPECT_FLOAT_EQ(out.y, -3.0);
	EXPECT_FLOAT_EQ(out.z, -3.0);
}

TEST(BkPoint3, BkPoint3_Sub_BkPoint3)
{
	struct BkPoint3 a = BkPoint3_Zero();
	struct BkPoint3 b = BkPoint3_Zero();

	a.x = 2.0; a.y = 4.0; a.z = 8.0;
	b.x = 1.0; b.y = 3.0; b.z = 5.0;

	struct BkVector3 v = BkPoint3_Sub_BkPoint3(&a, &b);

	EXPECT_FLOAT_EQ(v.x, 1.0);
	EXPECT_FLOAT_EQ(v.y, 1.0);
	EXPECT_FLOAT_EQ(v.z, 3.0);
}

TEST(BkPoint3, BkPoint3_Lerp)
{
	struct BkPoint3 a = BkPoint3_Zero();
	struct BkPoint3 b = BkPoint3_Zero();

	BkPoint3_Set(&b, 1.0, 2.0, 4.0);

	struct BkPoint3 out = BkPoint3_Lerp(&a, &b, 0.0);

	EXPECT_FLOAT_EQ(out.x, 0.0);
	EXPECT_FLOAT_EQ(out.y, 0.0);
	EXPECT_FLOAT_EQ(out.z, 0.0);

	out = BkPoint3_Lerp(&a, &b, 1.0);

	EXPECT_FLOAT_EQ(out.x, 1.0);
	EXPECT_FLOAT_EQ(out.y, 2.0);
	EXPECT_FLOAT_EQ(out.z, 4.0);

	out = BkPoint3_Lerp(&a, &b, 0.5);

	EXPECT_FLOAT_EQ(out.x, 0.5);
	EXPECT_FLOAT_EQ(out.y, 1.0);
	EXPECT_FLOAT_EQ(out.z, 2.0);

	out = BkPoint3_Lerp(&b, &a, 0.5);

	EXPECT_FLOAT_EQ(out.x, 0.5);
	EXPECT_FLOAT_EQ(out.y, 1.0);
	EXPECT_FLOAT_EQ(out.z, 2.0);

	out = BkPoint3_Lerp(&b, &b, 0.5);

	EXPECT_FLOAT_EQ(out.x, 1.0);
	EXPECT_FLOAT_EQ(out.y, 2.0);
	EXPECT_FLOAT_EQ(out.z, 4.0);
}

TEST(BkPoint3, BkPoint3_Distance)
{
	struct BkPoint3 a = BkPoint3_Zero();
	struct BkPoint3 b = BkPoint3_Zero();

	BkPoint3_Set(&a, 5.0, 0.0, 0.0);
	BkPoint3_Set(&b, -1.0, 8.0, 0.0);

	real d = BkPoint3_Distance(&a, &b);

	EXPECT_FLOAT_EQ(d, 10.0);
}