// Standard headers.
#include <math.h>

// Blackhart.foundation headers.
#include "foundation\BkMath.h"
#include "foundation\BkError.h"
#include "foundation\BkEulerAngles.h"
#include "foundation\BkQuaternion.h"
#include "foundation\BkMatrix4x4.h"

// ~~~~~ Def(PUBLIC) ~~~~~

struct BkEulerAngles	BkEulerAngles_FromXYZ(real const x, real const y, real const z)
{
	struct BkEulerAngles out;

	out.x = x;
	out.y = y;
	out.z = z;

	return out;
}

struct BkEulerAngles	BkEulerAngles_FromBkQuaternion(struct BkQuaternion const* q)
{
	BK_ASSERT(BK_ISNULL(q));

	struct BkEulerAngles out;

	real const sp = BK_REAL(-2) * (q->y * q->z - q->w * q->x);

	if (BK_REAL(fabs((double)sp)) > BK_REAL(0.9999))
	{
		out.x = BkMath_RadToDeg(BK_PI_OVER_TWO * sp);
		out.y = BkMath_RadToDeg(BK_REAL(atan2((double)-q->x * q->z + q->w * q->y, 0.5 - q->y * q->y - q->z * q->z)));
		out.z = BK_REAL(0);
	}
	else
	{
		out.x = BkMath_RadToDeg(BK_REAL(asin((double)sp)));
		out.y = BkMath_RadToDeg(BK_REAL(atan2((double)q->x * q->z + q->w * q->y, 0.5 - q->x * q->x - q->y * q->y)));
		out.z = BkMath_RadToDeg(BK_REAL(atan2((double)q->x * q->y + q->w * q->z, 0.5 - q->x * q->x - q->z * q->z)));
	}

	return out;
}

struct BkEulerAngles	BkEulerAngles_FromBkMatrix4x4(struct BkMatrix4x4 const* m)
{
	BK_ASSERT(BK_ISNULL(m));

	struct BkEulerAngles out;

	real const sp = -m->m23;

	if (sp <= BK_REAL(-1))
		out.x = BkMath_RadToDeg(-BK_PI_OVER_TWO);
	else if (sp >= BK_REAL(1))
		out.x = BkMath_RadToDeg(BK_PI_OVER_TWO);
	else
		out.x = BkMath_RadToDeg(BK_REAL(asin(sp)));

	if (BK_REAL(fabs((double)sp)) > BK_REAL(0.9999))
	{
		out.y = BK_REAL(0);
		out.z = BkMath_RadToDeg(BK_REAL(atan2((double)-m->m31, (double)m->m11)));
	}
	else
	{
		out.y = BkMath_RadToDeg(BK_REAL(atan2((double)m->m13, (double)m->m33)));
		out.z = BkMath_RadToDeg(BK_REAL(atan2((double)m->m21, (double)m->m22)));
	}

	return out;
}

void	BkEulerAngles_Set(struct BkEulerAngles* this, real const x, real const y, real const z)
{
	BK_ASSERT(BK_ISNULL(this));

	this->x = x;
	this->y = y;
	this->z = z;
}