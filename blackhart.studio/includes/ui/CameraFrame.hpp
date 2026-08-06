#ifndef __BK_STUDIO_CAMERA_FRAME_HPP__
#define __BK_STUDIO_CAMERA_FRAME_HPP__

extern "C" {
#include "foundation/BkAtomicDataType.h"
}

struct BkOrbitalCamera;
struct BkPointCloud;

namespace Studio {

/**
 * Points the orbital camera at @p cloud (target = world AABB center, radius
 * fitted to the bounds with @p frame_margin).
 */
void FrameCameraOn(BkPointCloud* cloud, BkOrbitalCamera* camera,
                   real camera_fov_deg, real frame_margin);

}  // namespace Studio

#endif
