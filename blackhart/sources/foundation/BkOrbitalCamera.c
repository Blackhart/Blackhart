// Standard library headers.
#include <math.h>

// blackhart headers.
#include "foundation\BkOrbitalCamera.h"
#include "foundation\BkAtomicDataType.h"
#include "foundation\BkMath.h"

// ~~~~~ Dcl(INTERNAL) ~~~~~

static void	_BkOrbitalCamera_RecomputeTransform(struct BkOrbitalCamera* obj);

static real const _MIN_ZOOM = BK_REAL(0.01);

// ~~~~~ Def(PUBLIC) ~~~~~

void	BkOrbitalCamera_Initialize(struct BkOrbitalCamera* obj)
{
	BK_ASSERT(BK_ISNULL(obj));

	BkCamera_Initialize(&(obj->base));

	obj->target = BkPoint3_Zero();
	obj->radius = BK_REAL(1);
	obj->yaw = BK_REAL(0);
	obj->pitch = BK_REAL(0);
	obj->pitch_min_limit = BK_REAL(-89);
	obj->pitch_max_limit = BK_REAL(89);
	obj->radius = BK_REAL(1);

	_BkOrbitalCamera_RecomputeTransform(obj);
}

void	BkOrbitalCamera_Rotate(struct BkOrbitalCamera* obj, real const yaw, real const pitch)
{
	BK_ASSERT(BK_ISNULL(obj));

    real const yt = obj->yaw + yaw;
    if (yt > BK_REAL(180))
        obj->yaw = BK_REAL(-180) + (yt - BK_REAL(180));
    else if (yt < BK_REAL(-180))
        obj->yaw = BK_REAL(180) - (yt + BK_REAL(180));
    else
        obj->yaw = yt;

	obj->pitch = BkMath_Clamp(obj->pitch + pitch, obj->pitch_min_limit, obj->pitch_max_limit);

	_BkOrbitalCamera_RecomputeTransform(obj);
}

void  BkOrbitalCamera_Zoom(struct BkOrbitalCamera* obj, real const radius)
{
    BK_ASSERT(BK_ISNULL(obj));

    obj->radius = BkMath_Max(obj->radius + radius, BK_REAL(_MIN_ZOOM));

    _BkOrbitalCamera_RecomputeTransform(obj);
}

void	BkOrbitalCamera_SetTarget(struct BkOrbitalCamera* obj, struct BkPoint3 const* target)
{
	BK_ASSERT(BK_ISNULL(obj));
	BK_ASSERT(BK_ISNULL(target));

	obj->target = *target;

	_BkOrbitalCamera_RecomputeTransform(obj);
}

void	BkOrbitalCamera_SetRadius(struct BkOrbitalCamera* obj, real const radius)
{
	BK_ASSERT(BK_ISNULL(obj));

	obj->radius = BkMath_Max(radius, BK_REAL(_MIN_ZOOM));

	_BkOrbitalCamera_RecomputeTransform(obj);
}

void	BkOrbitalCamera_SetPitchBoundLimits(struct BkOrbitalCamera* obj, real const pitch_min_limit, real const pitch_max_limit)
{
	BK_ASSERT(BK_ISNULL(obj));

	obj->pitch_min_limit = pitch_min_limit;
	obj->pitch_max_limit = pitch_max_limit;
	
	BkOrbitalCamera_SetPitch(obj, obj->pitch);

	_BkOrbitalCamera_RecomputeTransform(obj);
}

void	BkOrbitalCamera_SetYaw(struct BkOrbitalCamera* obj, real const yaw)
{
	BK_ASSERT(BK_ISNULL(obj));

    real const yt = obj->yaw + yaw;
    if (yt > BK_REAL(180))
        obj->yaw = BK_REAL(-180) + (yt - BK_REAL(180));
    else if (yt < BK_REAL(-180))
        obj->yaw = BK_REAL(180) - (yt + BK_REAL(180));
    else
        obj->yaw = yt;

	_BkOrbitalCamera_RecomputeTransform(obj);
}

void	BkOrbitalCamera_SetPitch(struct BkOrbitalCamera* obj, real const pitch)
{
	BK_ASSERT(BK_ISNULL(obj));

	obj->pitch = BkMath_Clamp(pitch, obj->pitch_min_limit, obj->pitch_max_limit);

	_BkOrbitalCamera_RecomputeTransform(obj);
}

// ~~~~~ Def(INTERNAL) ~~~~~

void	_BkOrbitalCamera_RecomputeTransform(struct BkOrbitalCamera* obj)
{
	BK_ASSERT(BK_ISNULL(obj));

	struct BkPoint3 const position = BkPoint3_RotateAround(&(obj->target), obj->radius, obj->yaw, obj->pitch);

	struct BkVector3 const up = BkVector3_FromXYZ(BK_REAL(0), BK_REAL(1), BK_REAL(0));

	BkTransform_LookAt(&(obj->base.transform), &position, &(obj->target), &up);
}