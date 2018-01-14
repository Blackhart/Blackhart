#include <gtest\gtest.h>

#include "../export/cpp/Blackhart.hpp"

TEST(BkCamera, BkCamera_Initialize)
{
	struct BkCamera cam;

	BkCamera_Initialize(&cam);

	EXPECT_FLOAT_EQ(cam.transform.cam_to_world.m11, 1.0); EXPECT_FLOAT_EQ(cam.transform.cam_to_world.m12, 0.0); EXPECT_FLOAT_EQ(cam.transform.cam_to_world.m13, 0.0); EXPECT_FLOAT_EQ(cam.transform.cam_to_world.m14, 0.0);
	EXPECT_FLOAT_EQ(cam.transform.cam_to_world.m21, 0.0); EXPECT_FLOAT_EQ(cam.transform.cam_to_world.m22, 1.0); EXPECT_FLOAT_EQ(cam.transform.cam_to_world.m23, 0.0); EXPECT_FLOAT_EQ(cam.transform.cam_to_world.m24, 0.0);
	EXPECT_FLOAT_EQ(cam.transform.cam_to_world.m31, 0.0); EXPECT_FLOAT_EQ(cam.transform.cam_to_world.m32, 0.0); EXPECT_FLOAT_EQ(cam.transform.cam_to_world.m33, 1.0); EXPECT_FLOAT_EQ(cam.transform.cam_to_world.m34, 0.0);
	EXPECT_FLOAT_EQ(cam.transform.cam_to_world.m41, 0.0); EXPECT_FLOAT_EQ(cam.transform.cam_to_world.m42, 0.0); EXPECT_FLOAT_EQ(cam.transform.cam_to_world.m43, 0.0); EXPECT_FLOAT_EQ(cam.transform.cam_to_world.m44, 1.0);


	EXPECT_FLOAT_EQ(cam.transform.world_to_cam.m11, 1.0); EXPECT_FLOAT_EQ(cam.transform.world_to_cam.m12, 0.0); EXPECT_FLOAT_EQ(cam.transform.world_to_cam.m13, 0.0); EXPECT_FLOAT_EQ(cam.transform.world_to_cam.m14, 0.0);
	EXPECT_FLOAT_EQ(cam.transform.world_to_cam.m21, 0.0); EXPECT_FLOAT_EQ(cam.transform.world_to_cam.m22, 1.0); EXPECT_FLOAT_EQ(cam.transform.world_to_cam.m23, 0.0); EXPECT_FLOAT_EQ(cam.transform.world_to_cam.m24, 0.0);
	EXPECT_FLOAT_EQ(cam.transform.world_to_cam.m31, 0.0); EXPECT_FLOAT_EQ(cam.transform.world_to_cam.m32, 0.0); EXPECT_FLOAT_EQ(cam.transform.world_to_cam.m33, 1.0); EXPECT_FLOAT_EQ(cam.transform.world_to_cam.m34, 0.0);
	EXPECT_FLOAT_EQ(cam.transform.world_to_cam.m41, 0.0); EXPECT_FLOAT_EQ(cam.transform.world_to_cam.m42, 0.0); EXPECT_FLOAT_EQ(cam.transform.world_to_cam.m43, 0.0); EXPECT_FLOAT_EQ(cam.transform.world_to_cam.m44, 1.0);
}

TEST(BkCamera, BkCamera_LookAt)
{
	struct BkCamera cam;

	BkCamera_Initialize(&cam);

	struct BkPoint3 from = BkPoint3_Zero();
	struct BkPoint3 to = BkPoint3_Zero();
	struct BkVector3 up = BkVector3_Zero();

	from.x = -2.0;
	from.z = 2.0;

	to.x = 0.0;
	to.z = 2.0;

	up.y = 1.0;

	BkCamera_LookAt(&cam, &from, &to, &up);

	EXPECT_FLOAT_EQ(cam.transform.cam_to_world.m11, 0.0); EXPECT_FLOAT_EQ(cam.transform.cam_to_world.m12, 0.0); EXPECT_FLOAT_EQ(cam.transform.cam_to_world.m13, -1.0); EXPECT_FLOAT_EQ(cam.transform.cam_to_world.m14, -2.0);
	EXPECT_FLOAT_EQ(cam.transform.cam_to_world.m21, 0.0); EXPECT_FLOAT_EQ(cam.transform.cam_to_world.m22, 1.0); EXPECT_FLOAT_EQ(cam.transform.cam_to_world.m23, 0.0); EXPECT_FLOAT_EQ(cam.transform.cam_to_world.m24, 0.0);
	EXPECT_FLOAT_EQ(cam.transform.cam_to_world.m31, 1.0); EXPECT_FLOAT_EQ(cam.transform.cam_to_world.m32, 0.0); EXPECT_FLOAT_EQ(cam.transform.cam_to_world.m33, 0.0); EXPECT_FLOAT_EQ(cam.transform.cam_to_world.m34, 2.0);
	EXPECT_FLOAT_EQ(cam.transform.cam_to_world.m41, 0.0); EXPECT_FLOAT_EQ(cam.transform.cam_to_world.m42, 0.0); EXPECT_FLOAT_EQ(cam.transform.cam_to_world.m43, 0.0); EXPECT_FLOAT_EQ(cam.transform.cam_to_world.m44, 1.0);

	EXPECT_FLOAT_EQ(cam.transform.world_to_cam.m11, 0.0); EXPECT_FLOAT_EQ(cam.transform.world_to_cam.m12, 0.0); EXPECT_FLOAT_EQ(cam.transform.world_to_cam.m13, 1.0); EXPECT_FLOAT_EQ(cam.transform.world_to_cam.m14, -2.0);
	EXPECT_FLOAT_EQ(cam.transform.world_to_cam.m21, 0.0); EXPECT_FLOAT_EQ(cam.transform.world_to_cam.m22, 1.0); EXPECT_FLOAT_EQ(cam.transform.world_to_cam.m23, 0.0); EXPECT_FLOAT_EQ(cam.transform.world_to_cam.m24, 0.0);
	EXPECT_FLOAT_EQ(cam.transform.world_to_cam.m31, -1.0); EXPECT_FLOAT_EQ(cam.transform.world_to_cam.m32, 0.0); EXPECT_FLOAT_EQ(cam.transform.world_to_cam.m33, 0.0); EXPECT_FLOAT_EQ(cam.transform.world_to_cam.m34, -2.0);
	EXPECT_FLOAT_EQ(cam.transform.world_to_cam.m41, 0.0); EXPECT_FLOAT_EQ(cam.transform.world_to_cam.m42, 0.0); EXPECT_FLOAT_EQ(cam.transform.world_to_cam.m43, 0.0); EXPECT_FLOAT_EQ(cam.transform.world_to_cam.m44, 1.0);
}