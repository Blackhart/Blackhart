#include "ui/CameraFrame.hpp"

#include <cmath>

#include "../../blackhart/export/cpp/Blackhart.hpp"

namespace Studio {

void FrameCameraOn(BkPointCloud* cloud, BkOrbitalCamera* camera,
                   real camera_fov_deg, real frame_margin) {
  if (cloud == nullptr || camera == nullptr) {
    return;
  }

  struct BkAABB const aabb = BkPointCloud_GetAABB(cloud);
  struct BkPoint3 const target = BkAABB_Center(&aabb);
  struct BkVector3 const size = BkAABB_Size(&aabb);
  real const bounding_sphere_radius = BkVector3_Magnitude(&size) * BK_REAL(0.5);
  real const half_fov_rad = BkMath_RadFromDeg(camera_fov_deg) * BK_REAL(0.5);
  real const radius =
      frame_margin * bounding_sphere_radius / BK_REAL(tan(half_fov_rad));

  BkOrbitalCamera_SetTarget(camera, &target);
  BkOrbitalCamera_SetRadius(camera, radius);
}

void TrackCameraOn(BkPointCloud* cloud, BkOrbitalCamera* camera) {
  if (cloud == nullptr || camera == nullptr) {
    return;
  }

  struct BkAABB const aabb = BkPointCloud_GetAABB(cloud);
  struct BkPoint3 const target = BkAABB_Center(&aabb);
  BkOrbitalCamera_SetTarget(camera, &target);
}

}  // namespace Studio
