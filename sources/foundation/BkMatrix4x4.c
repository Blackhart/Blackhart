// Standard headers.
#include <math.h>

// Blackhart.foundation headers.
#include "foundation\BkError.h"
#include "foundation\BkMatrix4x4.h"
#include "foundation\BkQuaternion.h"
#include "foundation\BkAngleAxis.h"
#include "foundation\BkEulerAngles.h"
#include "foundation\BkMath.h"

// ~~~~~ Def(PUBLIC) ~~~~~

struct BkMatrix4x4	BkMatrix4x4_Identity()
{
	return (struct BkMatrix4x4) {
		.m11 = BK_REAL(1.0),   .m12 = BK_REAL(0.0),   .m13 = BK_REAL(0.0),   .m14 = BK_REAL(0.0),
		.m21 = BK_REAL(0.0),   .m22 = BK_REAL(1.0),   .m23 = BK_REAL(0.0),   .m24 = BK_REAL(0.0),
		.m31 = BK_REAL(0.0),   .m32 = BK_REAL(0.0),   .m33 = BK_REAL(1.0),   .m34 = BK_REAL(0.0),
		.m41 = BK_REAL(0.0),   .m42 = BK_REAL(0.0),   .m43 = BK_REAL(0.0),   .m44 = BK_REAL(1.0)
	};
}

struct BkMatrix4x4	BkMatrix4x4_Mul_BkMatrix4x4(struct BkMatrix4x4 const* m1, struct BkMatrix4x4 const* m2)
{
	BK_ASSERT(BK_ISNULL(m1));
	BK_ASSERT(BK_ISNULL(m2));

	return (struct BkMatrix4x4) {
		.m11 = m1->m11 * m2->m11 + m1->m12 * m2->m21 + m1->m13 * m2->m31 + m1->m14 * m2->m41,
		.m12 = m1->m11 * m2->m12 + m1->m12 * m2->m22 + m1->m13 * m2->m32 + m1->m14 * m2->m42,
		.m13 = m1->m11 * m2->m13 + m1->m12 * m2->m23 + m1->m13 * m2->m33 + m1->m14 * m2->m43,
		.m14 = m1->m11 * m2->m14 + m1->m12 * m2->m24 + m1->m13 * m2->m34 + m1->m14 * m2->m44,
		.m21 = m1->m21 * m2->m11 + m1->m22 * m2->m21 + m1->m23 * m2->m31 + m1->m24 * m2->m41,
		.m22 = m1->m21 * m2->m12 + m1->m22 * m2->m22 + m1->m23 * m2->m32 + m1->m24 * m2->m42,
		.m23 = m1->m21 * m2->m13 + m1->m22 * m2->m23 + m1->m23 * m2->m33 + m1->m24 * m2->m43,
		.m24 = m1->m21 * m2->m14 + m1->m22 * m2->m24 + m1->m23 * m2->m34 + m1->m24 * m2->m44,
		.m31 = m1->m31 * m2->m11 + m1->m32 * m2->m21 + m1->m33 * m2->m31 + m1->m34 * m2->m41,
		.m32 = m1->m31 * m2->m12 + m1->m32 * m2->m22 + m1->m33 * m2->m32 + m1->m34 * m2->m42,
		.m33 = m1->m31 * m2->m13 + m1->m32 * m2->m23 + m1->m33 * m2->m33 + m1->m34 * m2->m43,
		.m34 = m1->m31 * m2->m14 + m1->m32 * m2->m24 + m1->m33 * m2->m34 + m1->m34 * m2->m44,
		.m41 = m1->m41 * m2->m11 + m1->m42 * m2->m21 + m1->m43 * m2->m31 + m1->m44 * m2->m41,
		.m42 = m1->m41 * m2->m12 + m1->m42 * m2->m22 + m1->m43 * m2->m32 + m1->m44 * m2->m42,
		.m43 = m1->m41 * m2->m13 + m1->m42 * m2->m23 + m1->m43 * m2->m33 + m1->m44 * m2->m43,
		.m44 = m1->m41 * m2->m14 + m1->m42 * m2->m24 + m1->m43 * m2->m34 + m1->m44 * m2->m44
	};
}

struct BkVector3	BkMatrix4x4_Mul_BkVector3(struct BkMatrix4x4 const* m, struct BkVector3 const* v)
{
	BK_ASSERT(BK_ISNULL(m));
	BK_ASSERT(BK_ISNULL(v));

	return (struct BkVector3) {
		.x = v->x * m->m11 + v->y * m->m12 + v->z * m->m13,
		.y = v->x * m->m21 + v->y * m->m22 + v->z * m->m23,
		.z = v->x * m->m31 + v->y * m->m32 + v->z * m->m33
	};
}

struct BkPoint3	BkMatrix4x4_Mul_BkPoint3(struct BkMatrix4x4 const* m, struct BkPoint3 const* p)
{
	BK_ASSERT(BK_ISNULL(m));
	BK_ASSERT(BK_ISNULL(p));

	return (struct BkPoint3) {
		.x = p->x * m->m11 + p->y * m->m12 + p->z * m->m13 + m->m14,
		.y = p->x * m->m21 + p->y * m->m22 + p->z * m->m23 + m->m24,
		.z = p->x * m->m31 + p->y * m->m32 + p->z * m->m33 + m->m34
	};
}

struct BkPoint3	BkMatrix4x4_Mul_BkPoint4(struct BkMatrix4x4 const* m, struct BkPoint3 const* p)
{
	BK_ASSERT(BK_ISNULL(m));
	BK_ASSERT(BK_ISNULL(p));

	real const w = p->x * m->m41 + p->y * m->m42 + p->z * m->m43 + m->m44;

	return (struct BkPoint3) {
		.x = (p->x * m->m11 + p->y * m->m12 + p->z * m->m13 + m->m14) / w,
		.y = (p->x * m->m21 + p->y * m->m22 + p->z * m->m23 + m->m24) / w,
		.z = (p->x * m->m31 + p->y * m->m32 + p->z * m->m33 + m->m34) / w
	};
}

struct BkMatrix4x4	BkMatrix4x4_Mul_real(struct BkMatrix4x4 const* m, real const r)
{
	BK_ASSERT(BK_ISNULL(m));

	return (struct BkMatrix4x4) {
		.m11 = m->m11 * r,   .m12 = m->m12 * r,   .m13 = m->m13 * r,   .m14 = m->m14 * r,
		.m21 = m->m21 * r,   .m22 = m->m22 * r,   .m23 = m->m23 * r,   .m24 = m->m24 * r,
		.m31 = m->m31 * r,   .m32 = m->m32 * r,   .m33 = m->m33 * r,   .m34 = m->m34 * r,
		.m41 = m->m41 * r,   .m42 = m->m42 * r,   .m43 = m->m43 * r,   .m44 = m->m44 * r
	};
}

struct BkMatrix4x4	BkMatrix4x4_FromBkQuaternion(struct BkQuaternion const* q)
{
	BK_ASSERT(BK_ISNULL(q));

	return (struct BkMatrix4x4)
	{
		.m11 = BK_REAL(1.0) - BK_REAL(2.0) * q->y * q->y - BK_REAL(2.0) * q->z * q->z,   .m12 = BK_REAL(2.0) * q->x * q->y - BK_REAL(2.0) * q->w * q->z,                  .m13 = BK_REAL(2.0) * q->x * q->z + BK_REAL(2.0) * q->w * q->y,                  .m14 = BK_REAL(0.0),
		.m21 = BK_REAL(2.0) * q->x * q->y + BK_REAL(2.0) * q->w * q->z,                  .m22 = BK_REAL(1.0) - BK_REAL(2.0) * q->x * q->x - BK_REAL(2.0) * q->z * q->z,   .m23 = BK_REAL(2.0) * q->y * q->z - BK_REAL(2.0) * q->w * q->x,                  .m24 = BK_REAL(0.0),
		.m31 = BK_REAL(2.0) * q->x * q->z - BK_REAL(2.0) * q->w * q->y,                  .m32 = BK_REAL(2.0) * q->y * q->z + BK_REAL(2.0) * q->w * q->x,                  .m33 = BK_REAL(1.0) - BK_REAL(2.0) * q->x * q->x - BK_REAL(2.0) * q->y * q->y,   .m34 = BK_REAL(0.0),
		.m41 = BK_REAL(0.0),                                                             .m42 = BK_REAL(0.0),                                                             .m43 = BK_REAL(0.0),                                                             .m44 = BK_REAL(1.0)
	};
}

struct BkMatrix4x4	BkMatrix4x4_FromBkAngleAxis(struct BkAngleAxis const* angle_axis)
{
	BK_ASSERT(BK_ISNULL(angle_axis));

	struct BkMatrix4x4 out;

	real const r = BkMath_RadFromDeg(angle_axis->angle);
	real const cr = BK_REAL(cos(r));
	real const omcr = BK_REAL(1.0) - cr;
	real const omcracr = omcr + cr;
	real const sr = BK_REAL(sin(r));
	real const vxmsr = angle_axis->axis.x * sr;
	real const vymsr = angle_axis->axis.y * sr;
	real const vzmsr = angle_axis->axis.z * sr;
	real const vxy = angle_axis->axis.x * angle_axis->axis.y;
	real const vxz = angle_axis->axis.x * angle_axis->axis.z;
	real const vyz = angle_axis->axis.y * angle_axis->axis.z;

	out.m11 = angle_axis->axis.x * angle_axis->axis.x * omcracr;   out.m12 = vxy * omcr - vzmsr;                                  out.m13 = vxz * omcr + vymsr;                                  out.m14 = BK_REAL(0.0);
	out.m21 = vxy * omcr + vzmsr;                                  out.m22 = angle_axis->axis.y * angle_axis->axis.y * omcracr;   out.m23 = vyz * omcr - vxmsr;                                  out.m24 = BK_REAL(0.0);
	out.m31 = vxz * omcr - vymsr;                                  out.m32 = vyz * omcr + vxmsr;                                  out.m33 = angle_axis->axis.z * angle_axis->axis.z * omcracr;   out.m34 = BK_REAL(0.0);
	out.m41 = BK_REAL(0.0);                                        out.m42 = BK_REAL(0.0);                                        out.m43 = BK_REAL(0.0);                                        out.m44 = BK_REAL(1.0);

	return out;
}

struct BkMatrix4x4	BkMatrix4x4_FromBkEulerAngles(struct BkEulerAngles const* euler)
{
	BK_ASSERT(BK_ISNULL(euler));

	struct BkMatrix4x4 out;

	real rad = BkMath_RadFromDeg(euler->x);
	real const cx = BK_REAL(cos(rad));
	real const sx = BK_REAL(sin(rad));
	rad = BkMath_RadFromDeg(euler->y);
	real const cy = BK_REAL(cos(rad));
	real const sy = BK_REAL(sin(rad));
	rad = BkMath_RadFromDeg(euler->z);
	real const cz = BK_REAL(cos(rad));
	real const sz = BK_REAL(sin(rad));

	out.m11 = cy * cz + sy * sx * sz;    out.m12 = -cy * sz + sy * sx * cz;   out.m13 = sy * cx;        out.m14 = BK_REAL(0.0);
	out.m21 = sz * cx;                   out.m22 = cz * cx;                   out.m23 = -sx;            out.m24 = BK_REAL(0.0);
	out.m31 = -sy * cz + cy * sx * sz;   out.m32 = sz * sy + cy * sx * cz;    out.m33 = cy * cx;        out.m34 = BK_REAL(0.0);
	out.m41 = BK_REAL(0.0);              out.m42 = BK_REAL(0.0);              out.m43 = BK_REAL(0.0);   out.m44 = BK_REAL(1.0);

	return out;
}

struct BkMatrix4x4	BkMatrix4x4_Copy(struct BkMatrix4x4 const* src)
{
	BK_ASSERT(BK_ISNULL(src));

	return (struct BkMatrix4x4) {
		.m11 = src->m11,   .m12 = src->m12,   .m13 = src->m13,   .m14 = src->m14,
		.m21 = src->m21,   .m22 = src->m22,   .m23 = src->m23,   .m24 = src->m24,
		.m31 = src->m31,   .m32 = src->m32,   .m33 = src->m33,   .m34 = src->m34,
		.m41 = src->m41,   .m42 = src->m42,   .m43 = src->m43,   .m44 = src->m44
	};
}

void	BkMatrix4x4_Assign(struct BkMatrix4x4* this, struct BkMatrix4x4 const* src)
{
	BK_ASSERT(BK_ISNULL(this));
	BK_ASSERT(BK_ISNULL(src));

	this->m11 = src->m11;   this->m12 = src->m12;   this->m13 = src->m13;   this->m14 = src->m14;
	this->m21 = src->m21;   this->m22 = src->m22;   this->m23 = src->m23;   this->m24 = src->m24;
	this->m31 = src->m31;   this->m32 = src->m32;   this->m33 = src->m33;   this->m34 = src->m34;
	this->m41 = src->m41;   this->m42 = src->m42;   this->m43 = src->m43;   this->m44 = src->m44;
}

struct BkMatrix4x4	BkMatrix4x4_Transpose(struct BkMatrix4x4 const* m)
{
	BK_ASSERT(BK_ISNULL(m));

	struct BkMatrix4x4 out;
	out.m11 = m->m11;   out.m12 = m->m21;   out.m13 = m->m31;   out.m14 = m->m41;
	out.m21 = m->m12;   out.m22 = m->m22;   out.m23 = m->m32;   out.m24 = m->m42;
	out.m31 = m->m13;   out.m32 = m->m23;   out.m33 = m->m33;   out.m34 = m->m43;
	out.m41 = m->m14;   out.m42 = m->m24;   out.m43 = m->m34;   out.m44 = m->m44;
	return out;
}

struct BkMatrix4x4	BkMatrix4x4_Scaling_Uniform(real const k)
{
	return (struct BkMatrix4x4) {
		.m11 = k,              .m12 = BK_REAL(0.0),   .m13 = BK_REAL(0.0),   .m14 = BK_REAL(0.0),
		.m21 = BK_REAL(0.0),   .m22 = k,              .m23 = BK_REAL(0.0),   .m24 = BK_REAL(0.0),
		.m31 = BK_REAL(0.0),   .m32 = BK_REAL(0.0),   .m33 = k,              .m34 = BK_REAL(0.0),
		.m41 = BK_REAL(0.0),   .m42 = BK_REAL(0.0),   .m43 = BK_REAL(0.0),   .m44 = BK_REAL(1.0)
	};
}

struct BkMatrix4x4	BkMatrix4x4_Scaling_Nonuniform(real const x, real const y, real const z)
{
	return (struct BkMatrix4x4) {
		.m11 = x,              .m12 = BK_REAL(0.0),   .m13 = BK_REAL(0.0),   .m14 = BK_REAL(0.0),
		.m21 = BK_REAL(0.0),   .m22 = y,              .m23 = BK_REAL(0.0),   .m24 = BK_REAL(0.0),
		.m31 = BK_REAL(0.0),   .m32 = BK_REAL(0.0),   .m33 = z,              .m34 = BK_REAL(0.0),
		.m41 = BK_REAL(0.0),   .m42 = BK_REAL(0.0),   .m43 = BK_REAL(0.0),   .m44 = BK_REAL(1.0)
	};
}

struct BkMatrix4x4	BkMatrix4x4_Scaling_axis(struct BkVector3 const* v, real const k)
{
	BK_ASSERT(BK_ISNULL(v));

	struct BkMatrix4x4 out;

	real const kmo = k - BK_REAL(1.0);
	real const vxy = v->x * v->y;
	real const vxz = v->x * v->z;
	real const vyz = v->y * v->z;
	real const kmomvxy = kmo * vxy;
	real const kmomvxz = kmo * vxz;
	real const kmomvyz = kmo * vyz;

	out.m11 = BK_REAL(1.0) + kmo * v->x * v->x;   out.m12 = kmomvxy;                            out.m13 = kmomvxz;                            out.m14 = BK_REAL(0.0);
	out.m21 = kmomvxy;                            out.m22 = BK_REAL(1.0) + kmo * v->y * v->y;   out.m23 = kmomvyz;                            out.m24 = BK_REAL(0.0);
	out.m31 = kmomvxz;                            out.m32 = kmomvyz;                            out.m33 = BK_REAL(1.0) + kmo * v->z * v->z;   out.m34 = BK_REAL(0.0);
	out.m41 = BK_REAL(0.0);                       out.m42 = BK_REAL(0.0);                       out.m43 = BK_REAL(0.0);                       out.m44 = BK_REAL(1.0);

	return out;
}

struct BkMatrix4x4	BkMatrix4x4_Translation_XYZ(real const x, real const y, real const z)
{
	return (struct BkMatrix4x4) {
		.m11 = BK_REAL(1.0),   .m12 = BK_REAL(0.0),   .m13 = BK_REAL(0.0),   .m14 = x,
		.m21 = BK_REAL(0.0),   .m22 = BK_REAL(1.0),   .m23 = BK_REAL(0.0),   .m24 = y,
		.m31 = BK_REAL(0.0),   .m32 = BK_REAL(0.0),   .m33 = BK_REAL(1.0),   .m34 = z,
		.m41 = BK_REAL(0.0),   .m42 = BK_REAL(0.0),   .m43 = BK_REAL(0.0),   .m44 = BK_REAL(1.0)
	};
}

struct BkMatrix4x4	BkMatrix4x4_Translation_BkVector3(struct BkVector3 const* v)
{
	return (struct BkMatrix4x4) {
		.m11 = BK_REAL(1.0), .m12 = BK_REAL(0.0), .m13 = BK_REAL(0.0), .m14 = v->x,
		.m21 = BK_REAL(0.0), .m22 = BK_REAL(1.0), .m23 = BK_REAL(0.0), .m24 = v->y,
		.m31 = BK_REAL(0.0), .m32 = BK_REAL(0.0), .m33 = BK_REAL(1.0), .m34 = v->z,
		.m41 = BK_REAL(0.0), .m42 = BK_REAL(0.0), .m43 = BK_REAL(0.0), .m44 = BK_REAL(1.0)
	};
}

struct BkMatrix4x4	BkMatrix4x4_Translation_BkPoint3(struct BkPoint3 const* p)
{
	return (struct BkMatrix4x4) {
		.m11 = BK_REAL(1.0), .m12 = BK_REAL(0.0), .m13 = BK_REAL(0.0), .m14 = p->x,
		.m21 = BK_REAL(0.0), .m22 = BK_REAL(1.0), .m23 = BK_REAL(0.0), .m24 = p->y,
		.m31 = BK_REAL(0.0), .m32 = BK_REAL(0.0), .m33 = BK_REAL(1.0), .m34 = p->z,
		.m41 = BK_REAL(0.0), .m42 = BK_REAL(0.0), .m43 = BK_REAL(0.0), .m44 = BK_REAL(1.0)
	};
}

real	BkMatrix4x4_Determinant(struct BkMatrix4x4 const* m)
{
	BK_ASSERT(BK_ISNULL(m));

	return m->m11 * (m->m22 * (m->m33 * m->m44 - m->m34 * m->m43) + m->m23 * (m->m34 * m->m42 - m->m32 * m->m44) + m->m24 * (m->m32 * m->m43 - m->m33 * m->m42)) -
	       m->m12 * (m->m21 * (m->m33 * m->m44 - m->m34 * m->m43) + m->m23 * (m->m34 * m->m41 - m->m31 * m->m44) + m->m24 * (m->m31 * m->m43 - m->m33 * m->m41)) +
	       m->m13 * (m->m21 * (m->m32 * m->m44 - m->m34 * m->m42) + m->m22 * (m->m34 * m->m41 - m->m31 * m->m44) + m->m24 * (m->m31 * m->m42 - m->m32 * m->m41)) -
	       m->m14 * (m->m21 * (m->m32 * m->m43 - m->m33 * m->m42) + m->m22 * (m->m33 * m->m41 - m->m31 * m->m43) + m->m23 * (m->m31 * m->m42 - m->m32 * m->m41));
}

struct BkMatrix4x4	BkMatrix4x4_Inverse(struct BkMatrix4x4 const* m)
{
	BK_ASSERT(BK_ISNULL(m));

	struct BkMatrix4x4 out;

	out.m11 = m->m22 * m->m33 * m->m44 -
		  m->m22 * m->m34 * m->m43 -
		  m->m32 * m->m23 * m->m44 +
		  m->m32 * m->m24 * m->m43 +
		  m->m42 * m->m23 * m->m34 -
		  m->m42 * m->m24 * m->m33;

	out.m21 = -m->m21 * m->m33 * m->m44 +
		  m->m21 * m->m34 * m->m43 +
		  m->m31 * m->m23 * m->m44 -
		  m->m31 * m->m24 * m->m43 -
		  m->m41 * m->m23 * m->m34 +
		  m->m41 * m->m24 * m->m33;

	out.m31 = m->m21 * m->m32 * m->m44 -
		  m->m21 * m->m34 * m->m42 -
		  m->m31 * m->m22 * m->m44 +
		  m->m31 * m->m24 * m->m42 +
		  m->m41 * m->m22 * m->m34 -
		  m->m41 * m->m24 * m->m32;

	out.m41 = -m->m21 * m->m32 * m->m43 +
		  m->m21 * m->m33 * m->m42 +
		  m->m31 * m->m22 * m->m43 -
		  m->m31 * m->m23 * m->m42 -
		  m->m41 * m->m22 * m->m33 +
		  m->m41 * m->m23 * m->m32;

	out.m12 = -m->m12 * m->m33 * m->m44 +
		  m->m12 * m->m34 * m->m43 +
		  m->m32 * m->m13 * m->m44 -
		  m->m32 * m->m14 * m->m43 -
		  m->m42 * m->m13 * m->m34 +
		  m->m42 * m->m14 * m->m33;

	out.m22 = m->m11 * m->m33 * m->m44 -
		  m->m11 * m->m34 * m->m43 -
		  m->m31 * m->m13 * m->m44 +
		  m->m31 * m->m14 * m->m43 +
		  m->m41 * m->m13 * m->m34 -
		  m->m41 * m->m14 * m->m33;

	out.m32 = -m->m11 * m->m32 * m->m44 +
		  m->m11 * m->m34 * m->m42 +
		  m->m31 * m->m12 * m->m44 -
		  m->m31 * m->m14 * m->m42 -
		  m->m41 * m->m12 * m->m34 +
		  m->m41 * m->m14 * m->m32;

	out.m42 = m->m11 * m->m32 * m->m43 -
		  m->m11 * m->m33 * m->m42 -
		  m->m31 * m->m12 * m->m43 +
		  m->m31 * m->m13 * m->m42 +
		  m->m41 * m->m12 * m->m33 -
		  m->m41 * m->m13 * m->m32;

	out.m13 = m->m12 * m->m23 * m->m44 -
		  m->m12 * m->m24 * m->m43 -
		  m->m22 * m->m13 * m->m44 +
		  m->m22 * m->m14 * m->m43 +
		  m->m42 * m->m13 * m->m24 -
		  m->m42 * m->m14 * m->m23;

	out.m23 = -m->m11 * m->m23 * m->m44 +
		  m->m11 * m->m24 * m->m43 +
		  m->m21 * m->m13 * m->m44 -
		  m->m21 * m->m14 * m->m43 -
		  m->m41 * m->m13 * m->m24 +
		  m->m41 * m->m14 * m->m23;

	out.m33 = m->m11 * m->m22 * m->m44 -
		  m->m11 * m->m24 * m->m42 -
		  m->m21 * m->m12 * m->m44 +
		  m->m21 * m->m14 * m->m42 +
		  m->m41 * m->m12 * m->m24 -
		  m->m41 * m->m14 * m->m22;

	out.m43 = -m->m11 * m->m22 * m->m43 +
		  m->m11 * m->m23 * m->m42 +
		  m->m21 * m->m12 * m->m43 -
		  m->m21 * m->m13 * m->m42 -
		  m->m41 * m->m12 * m->m23 +
		  m->m41 * m->m13 * m->m22;

	out.m14 = -m->m12 * m->m23 * m->m34 +
		  m->m12 * m->m24 * m->m33 +
		  m->m22 * m->m13 * m->m34 -
		  m->m22 * m->m14 * m->m33 -
		  m->m32 * m->m13 * m->m24 +
		  m->m32 * m->m14 * m->m23;

	out.m24 = m->m11 * m->m23 * m->m34 -
		  m->m11 * m->m24 * m->m33 -
		  m->m21 * m->m13 * m->m34 +
		  m->m21 * m->m14 * m->m33 +
		  m->m31 * m->m13 * m->m24 -
		  m->m31 * m->m14 * m->m23;

	out.m34 = -m->m11 * m->m22 * m->m34 +
		  m->m11 * m->m24 * m->m32 +
		  m->m21 * m->m12 * m->m34 -
		  m->m21 * m->m14 * m->m32 -
		  m->m31 * m->m12 * m->m24 +
		  m->m31 * m->m14 * m->m22;

	out.m44 = m->m11 * m->m22 * m->m33 -
		  m->m11 * m->m23 * m->m32 -
		  m->m21 * m->m12 * m->m33 +
		  m->m21 * m->m13 * m->m32 +
		  m->m31 * m->m12 * m->m23 -
		  m->m31 * m->m13 * m->m22;

	real det = m->m11 * out.m11 + m->m12 * out.m21 + m->m13 * out.m31 + m->m14 * out.m41;

	if (det == BK_REAL(0.0))
		return BkMatrix4x4_Identity();

	det = BK_REAL(1.0) / det;

	out.m11 *= det; out.m12 *= det; out.m13 *= det; out.m14 *= det;
	out.m21 *= det; out.m22 *= det; out.m23 *= det; out.m24 *= det;
	out.m31 *= det; out.m32 *= det; out.m33 *= det; out.m34 *= det;
	out.m41 *= det; out.m42 *= det; out.m43 *= det; out.m44 *= det;

	return out;
}