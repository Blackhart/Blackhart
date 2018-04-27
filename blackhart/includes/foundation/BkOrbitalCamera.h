#ifndef __BK_ORBITAL_CAMERA_HPP__
#define __BK_ORBITAL_CAMERA_HPP__

// blackhart headers.
#include "foundation\BkAtomicDataType.h"
#include "foundation\BkExport.h"
#include "foundation\BkCamera.h"
#include "foundation\BkPoint3.h"

// Struct definitions.
struct BkOrbitalCamera
{
	struct BkCamera	base;
	struct BkPoint3 target;
	real radius;
	real pitch_min_limit;
	real pitch_max_limit;
	real yaw;
	real pitch;
};

// ~~~~~ Dcl(PUBLIC) ~~~~~

extern BK_API void  BkOrbitalCamera_Initialize(struct BkOrbitalCamera* obj);
extern BK_API void  BkOrbitalCamera_Rotate(struct BkOrbitalCamera* obj, real const yaw, real const pitch);
extern BK_API void  BkOrbitalCamera_Zoom(struct BkOrbitalCamera* obj, real const radius);
extern BK_API void  BkOrbitalCamera_SetTarget(struct BkOrbitalCamera* obj, struct BkPoint3 const* target);
extern BK_API void  BkOrbitalCamera_SetRadius(struct BkOrbitalCamera* obj, real const radius);
extern BK_API void  BkOrbitalCamera_SetPitchBoundLimits(struct BkOrbitalCamera* obj, real const pitch_min_limit, real const pitch_max_limit);
extern BK_API void  BkOrbitalCamera_SetYaw(struct BkOrbitalCamera* obj, real const yaw);
extern BK_API void  BkOrbitalCamera_SetPitch(struct BkOrbitalCamera* obj, real const pitch);

#endif