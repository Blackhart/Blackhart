// Standard headers.
#include <math.h>

// Blackhart.foundation headers.
#include "foundation\BkMatrix4x4.h"
#include "foundation\BkQuaternion.h"
#include "foundation\BkEulerAngles.h"
#include "foundation\BkAngleAxis.h"
#include "foundation\BkMath.h"

// ~~~~~ Def(PUBLIC) ~~~~~

struct BkQuaternion	BkQuaternion_Identity(void)
{
	struct BkQuaternion ret;
	ret.w = BK_REAL(1);
	ret.x = BK_REAL(0);
	ret.y = BK_REAL(0);
	ret.z = BK_REAL(0);
	return ret;
}

struct BkQuaternion	BkQuaternion_Mul_BkQuaternion(struct BkQuaternion const* q1, struct BkQuaternion const* q2)
{
	BK_ASSERT(BK_ISNULL(q1));
	BK_ASSERT(BK_ISNULL(q2));

	return (struct BkQuaternion)
	{
		.w = q1->w * q2->w - q1->x * q2->x - q1->y * q2->y - q1->z * q2->z,
		.x = q1->w * q2->x + q1->x * q2->w + q1->y * q2->z - q1->z * q2->y,
		.y = q1->w * q2->y + q1->y * q2->w + q1->z * q2->x - q1->x * q2->z,
		.z = q1->w * q2->z + q1->z * q2->w + q1->x * q2->y - q1->y * q2->x
	};
}

struct BkQuaternion	BkQuaternion_FromAngleAxis(struct BkAngleAxis const* angle_axis)
{
	BK_ASSERT(BK_ISNULL(angle_axis));

	real const rao2 = BkMath_RadFromDeg(angle_axis->angle * BK_REAL(0.5));
	real const srao2 = BK_REAL(sin(rao2));

	return (struct BkQuaternion)
	{
		.w = BK_REAL(cos(rao2)),
		.x = angle_axis->axis.x * srao2,
		.y = angle_axis->axis.y * srao2,
		.z = angle_axis->axis.z * srao2
	};
}

struct BkQuaternion	BkQuaternion_FromBkMatrix4x4(struct BkMatrix4x4 const* m)
{
	BK_ASSERT(BK_ISNULL(m));

	real const fourWSquaredMinus1 = m->m11 + m->m22 + m->m33;
	real const fourXSquaredMinus1 = m->m11 - m->m22 - m->m33;
	real const fourYSquaredMinus1 = m->m22 - m->m11 - m->m33;
	real const fourZSquaredMinus1 = m->m33 - m->m11 - m->m22;

	uint8 biggestIndex = 0;
	real fourBiggestSquaredMinus1 = fourWSquaredMinus1;

	if (fourXSquaredMinus1 > fourBiggestSquaredMinus1)
	{
		fourBiggestSquaredMinus1 = fourXSquaredMinus1;
		biggestIndex = 1;
	}
	if (fourYSquaredMinus1 > fourBiggestSquaredMinus1)
	{
		fourBiggestSquaredMinus1 = fourYSquaredMinus1;
		biggestIndex = 2;
	}
	if (fourZSquaredMinus1 > fourBiggestSquaredMinus1)
	{
		fourBiggestSquaredMinus1 = fourZSquaredMinus1;
		biggestIndex = 3;
	}

	real const biggestVal = BK_REAL(sqrt(fourBiggestSquaredMinus1 + BK_REAL(1.0)) * BK_REAL(0.5));
	real const mult = BK_REAL(0.25) / biggestVal;

	struct BkQuaternion q;

	switch (biggestIndex)
	{
	case 0:
		q.w = biggestVal;
		q.x = (m->m32 - m->m23) * mult;
		q.y = (m->m13 - m->m31) * mult;
		q.z = (m->m21 - m->m12) * mult;
		break;
	case 1:
		q.x = biggestVal;
		q.w = (m->m32 - m->m23) * mult;
		q.y = (m->m21 + m->m12) * mult;
		q.z = (m->m13 + m->m31) * mult;
		break;
	case 2:
		q.y = biggestVal;
		q.w = (m->m13 - m->m31) * mult;
		q.x = (m->m21 + m->m12) * mult;
		q.z = (m->m32 + m->m23) * mult;
		break;
	case 3:
		q.z = biggestVal;
		q.w = (m->m21 - m->m12) * mult;
		q.x = (m->m13 + m->m31) * mult;
		q.y = (m->m32 + m->m23) * mult;
		break;
	}

	return q;
}

struct BkQuaternion	BkQuaternion_FromEulerAngles(struct BkEulerAngles const* euler)
{
	BK_ASSERT(BK_ISNULL(euler));

	real const rad = BkMath_RadFromDeg(BK_REAL(0.5));

	real const y_rad = euler->y * rad;
	real const hw = BK_REAL(cos(y_rad));
	real const hy = BK_REAL(sin(y_rad));

	real const x_rad = euler->x * rad;
	real const pw = BK_REAL(cos(x_rad));
	real const px = BK_REAL(sin(x_rad));

	real const z_rad = euler->z * rad;
	real const bw = BK_REAL(cos(z_rad));
	real const bz = BK_REAL(sin(z_rad));

	return (struct BkQuaternion)
	{
		.w = hw * pw * bw + hy * px * bz,
		.x = hw * px * bw + hy * pw * bz,
		.y = hy * pw * bw - hw * px * bz,
		.z = hw * pw * bz - hy * px * bw
	};
}

struct BkQuaternion	BkQuaternion_Copy(struct BkQuaternion const* q)
{
	BK_ASSERT(BK_ISNULL(q));

	struct BkQuaternion ret;
	ret.w = q->w;
	ret.x = q->x;
	ret.y = q->y;
	ret.z = q->z;
	return ret;
}

void	BkQuaternion_Set(struct BkQuaternion* this, real const w, real const x, real const y, real const z)
{
	this->w = w;
	this->x = x;
	this->y = y;
	this->z = z;
}

void	BkQuaternion_Normalized(struct BkQuaternion* this)
{
	BK_ASSERT(BK_ISNULL(this));

	real const m = BK_REAL(sqrt(this->w * this->w + this->x * this->x + this->y * this->y + this->z * this->z));
	if (m > BK_REAL(1))
	{
		this->w /= m;
		this->x /= m;
		this->y /= m;
		this->z /= m;
	}
}

struct BkQuaternion	BkQuaternion_Normalize(struct BkQuaternion const* q)
{
	BK_ASSERT(BK_ISNULL(q));

	real const m = BK_REAL(sqrt(q->w * q->w + q->x * q->x + q->y * q->y + q->z * q->z));

	struct BkQuaternion out;

	if (m > BK_REAL(1))
	{
		out.w = q->w / m;
		out.x = q->x / m;
		out.y = q->y / m;
		out.z = q->z / m;
	}

	return out;
}

void	BkQuaternion_Negated(struct BkQuaternion* this)
{
	BK_ASSERT(BK_ISNULL(this));

	this->w = -this->w;
	this->x = -this->x;
	this->y = -this->y;
	this->z = -this->z;
}

struct BkQuaternion	BkQuaternion_Negate(struct BkQuaternion const* q)
{
	BK_ASSERT(BK_ISNULL(q));

	struct BkQuaternion ret;
	ret.w = -q->w;
	ret.x = -q->x;
	ret.y = -q->y;
	ret.z = -q->z;
	return ret;
}

real	BkQuaternion_Magnitude(struct BkQuaternion const* q)
{
	BK_ASSERT(BK_ISNULL(q));

	return BK_REAL(sqrt(q->w * q->w + q->x * q->x + q->y * q->y + q->z * q->z));
}

void	BkQuaternion_Conjugated(struct BkQuaternion* this)
{
	BK_ASSERT(BK_ISNULL(this));

	this->w = this->w;
	this->x = -this->x;
	this->y = -this->y;
	this->z = -this->z;
}

struct BkQuaternion	BkQuaternion_Conjugate(struct BkQuaternion const* q)
{
	BK_ASSERT(BK_ISNULL(q));

	struct BkQuaternion ret;
	ret.w = q->w;
	ret.x = -q->x;
	ret.y = -q->y;
	ret.z = -q->z;
	return ret;
}

void	BkQuaternion_Inversed(struct BkQuaternion* this)
{
	BK_ASSERT(BK_ISNULL(this));

	real const magn = BkQuaternion_Magnitude(this);

	BkQuaternion_Conjugated(this);

	this->w /= magn;
	this->x /= magn;
	this->y /= magn;
	this->z /= magn;
}

struct BkQuaternion	BkQuaternion_Inverse(struct BkQuaternion const* q)
{
	BK_ASSERT(BK_ISNULL(q));

	struct BkQuaternion ret = BkQuaternion_Conjugate(q);
	real const magn = BkQuaternion_Magnitude(q);

	ret.w /= magn;
	ret.x /= magn;
	ret.y /= magn;
	ret.z /= magn;

	return ret;
}

struct BkQuaternion	BkQuaternion_Difference(struct BkQuaternion const* q1, struct BkQuaternion const* q2)
{
	BK_ASSERT(BK_ISNULL(q1));
	BK_ASSERT(BK_ISNULL(q2));

	struct BkQuaternion inv = BkQuaternion_Inverse(q1);
	return BkQuaternion_Mul_BkQuaternion(q2, &inv);
}

real	BkQuaternion_Dot(struct BkQuaternion const* q1, struct BkQuaternion const* q2)
{
	BK_ASSERT(BK_ISNULL(q1));
	BK_ASSERT(BK_ISNULL(q2));

	return q1->w * q2->w + q1->x * q2->x + q1->y * q2->y + q1->z * q2->z;
}