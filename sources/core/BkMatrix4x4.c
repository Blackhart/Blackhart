#include <math.h>

#include "core\BkMath.h"

struct BkMatrix4x4	BkMatrix4x4_Identity()
{
	return (struct BkMatrix4x4) {
		.m11 = 1.0, .m12 = 0.0, .m13 = 0.0, .m14 = 0.0,
		.m21 = 0.0, .m22 = 1.0, .m23 = 0.0, .m24 = 0.0,
		.m31 = 0.0, .m32 = 0.0, .m33 = 1.0, .m34 = 0.0,
		.m41 = 0.0, .m42 = 0.0, .m43 = 0.0, .m44 = 1.0
	};
}

struct BkMatrix4x4	BkMatrix4x4_Mul_BkMatrix4x4(struct BkMatrix4x4 const* m1, struct BkMatrix4x4 const* m2)
{
	struct BkMatrix4x4 out;
	out.m11 = m1->m11 * m2->m11 + m1->m12 * m2->m21 + m1->m13 * m2->m31 + m1->m14 * m2->m41;
	out.m12 = m1->m11 * m2->m12 + m1->m12 * m2->m22 + m1->m13 * m2->m32 + m1->m14 * m2->m42;
	out.m13 = m1->m11 * m2->m13 + m1->m12 * m2->m23 + m1->m13 * m2->m33 + m1->m14 * m2->m43;
	out.m14 = m1->m11 * m2->m14 + m1->m12 * m2->m24 + m1->m13 * m2->m34 + m1->m14 * m2->m44;
	out.m21 = m1->m21 * m2->m11 + m1->m22 * m2->m21 + m1->m23 * m2->m31 + m1->m24 * m2->m41;
	out.m22 = m1->m21 * m2->m12 + m1->m22 * m2->m22 + m1->m23 * m2->m32 + m1->m24 * m2->m42;
	out.m23 = m1->m21 * m2->m13 + m1->m22 * m2->m23 + m1->m23 * m2->m33 + m1->m24 * m2->m43;
	out.m24 = m1->m21 * m2->m14 + m1->m22 * m2->m24 + m1->m23 * m2->m34 + m1->m24 * m2->m44;
	out.m31 = m1->m31 * m2->m11 + m1->m32 * m2->m21 + m1->m33 * m2->m31 + m1->m34 * m2->m41;
	out.m32 = m1->m31 * m2->m12 + m1->m32 * m2->m22 + m1->m33 * m2->m32 + m1->m34 * m2->m42;
	out.m33 = m1->m31 * m2->m13 + m1->m32 * m2->m23 + m1->m33 * m2->m33 + m1->m34 * m2->m43;
	out.m34 = m1->m31 * m2->m14 + m1->m32 * m2->m24 + m1->m33 * m2->m34 + m1->m34 * m2->m44;
	out.m41 = m1->m41 * m2->m11 + m1->m42 * m2->m21 + m1->m43 * m2->m31 + m1->m44 * m2->m41;
	out.m42 = m1->m41 * m2->m12 + m1->m42 * m2->m22 + m1->m43 * m2->m32 + m1->m44 * m2->m42;
	out.m43 = m1->m41 * m2->m13 + m1->m42 * m2->m23 + m1->m43 * m2->m33 + m1->m44 * m2->m43;
	out.m44 = m1->m41 * m2->m14 + m1->m42 * m2->m24 + m1->m43 * m2->m34 + m1->m44 * m2->m44;
	return out;
}

struct BkVector4	BkMatrix4x4_Mul_BkVector4(struct BkMatrix4x4 const* m, struct BkVector4 const* v)
{
	struct BkVector4 out;
	out.x = v->x * m->m11 + v->y * m->m12 + v->z * m->m13;
	out.y = v->x * m->m21 + v->y * m->m22 + v->z * m->m23;
	out.z = v->x * m->m31 + v->y * m->m32 + v->z * m->m33;
	return out;
}

struct BkPoint	BkMatrix4x4_Mul_BkPoint(struct BkMatrix4x4 const* m, struct BkPoint const* p)
{
	struct BkPoint out;
	out.x = p->x * m->m11 + p->y * m->m12 + p->z * m->m13 + 1.0 * m->m14;
	out.y = p->x * m->m21 + p->y * m->m22 + p->z * m->m23 + 1.0 * m->m24;
	out.z = p->x * m->m31 + p->y * m->m32 + p->z * m->m33 + 1.0 * m->m34;
	return out;
}

struct BkMatrix4x4	BkMatrix4x4_Mul_real(struct BkMatrix4x4 const* m, real const r)
{
	struct BkMatrix4x4 out;
	out.m11 = m->m11 * r; out.m12 = m->m12 * r; out.m13 = m->m13 * r; out.m14 = m->m14 * r;
	out.m21 = m->m21 * r; out.m22 = m->m22 * r; out.m23 = m->m23 * r; out.m24 = m->m24 * r;
	out.m31 = m->m31 * r; out.m32 = m->m32 * r; out.m33 = m->m33 * r; out.m34 = m->m34 * r;
	out.m41 = m->m41 * r; out.m42 = m->m42 * r; out.m43 = m->m43 * r; out.m44 = m->m44 * r;
	return out;
}

struct BkMatrix4x4	BkMatrix4x4_Copy(struct BkMatrix4x4 const* src)
{
	struct BkMatrix4x4 out;
	out.m11 = src->m11; out.m12 = src->m12; out.m13 = src->m13; out.m14 = src->m14;
	out.m21 = src->m21; out.m22 = src->m22; out.m23 = src->m23; out.m24 = src->m24;
	out.m31 = src->m31; out.m32 = src->m32; out.m33 = src->m33; out.m34 = src->m34;
	out.m41 = src->m41; out.m42 = src->m42; out.m43 = src->m43; out.m44 = src->m44;
	return out;
}

void	BkMatrix4x4_Assign(struct BkMatrix4x4* dst, struct BkMatrix4x4 const* src)
{
	dst->m11 = src->m11; dst->m12 = src->m12; dst->m13 = src->m13; dst->m14 = src->m14;
	dst->m21 = src->m21; dst->m22 = src->m22; dst->m23 = src->m23; dst->m24 = src->m24;
	dst->m31 = src->m31; dst->m32 = src->m32; dst->m33 = src->m33; dst->m34 = src->m34;
	dst->m41 = src->m41; dst->m42 = src->m42; dst->m43 = src->m43; dst->m44 = src->m44;
}

struct BkMatrix4x4	BkMatrix4x4_Transpose(struct BkMatrix4x4 const* m)
{
	struct BkMatrix4x4 out;
	out.m11 = m->m11; out.m12 = m->m21; out.m13 = m->m31; out.m14 = m->m41;
	out.m21 = m->m12; out.m22 = m->m22; out.m23 = m->m32; out.m24 = m->m42;
	out.m31 = m->m13; out.m32 = m->m23; out.m33 = m->m33; out.m34 = m->m43;
	out.m41 = m->m14; out.m42 = m->m24; out.m43 = m->m34; out.m44 = m->m44;
	return out;
}

struct BkMatrix4x4	BkMatrix4x4_Rotate_x(real const deg)
{
	struct BkMatrix4x4 out;

	real const r = DEG_TO_RAD * deg;
	real const cr = cos(r);
	real const sr = sin(r);

	out.m11 = 1.0; out.m12 = 0.0; out.m13 = 0.0; out.m14 = 0.0;
	out.m21 = 0.0; out.m22 = cr;  out.m23 = -sr; out.m24 = 0.0;
	out.m31 = 0.0; out.m32 = sr;  out.m33 = cr;  out.m34 = 0.0;
	out.m41 = 0.0; out.m42 = 0.0; out.m43 = 0.0; out.m44 = 1.0;

	return out;
}

struct BkMatrix4x4	BkMatrix4x4_Rotate_y(real const deg)
{
	struct BkMatrix4x4 out;

	real const r = DEG_TO_RAD * deg;
	real const cr = cos(r);
	real const sr = sin(r);

	out.m11 = cr;  out.m12 = 0.0; out.m13 = sr;  out.m14 = 0.0;
	out.m21 = 0.0; out.m22 = 1.0; out.m23 = 0.0; out.m24 = 0.0;
	out.m31 = -sr; out.m32 = 0.0; out.m33 = cr;  out.m34 = 0.0;
	out.m41 = 0.0; out.m42 = 0.0; out.m43 = 0.0; out.m44 = 1.0;

	return out;
}

struct BkMatrix4x4	BkMatrix4x4_Rotate_z(real const deg)
{
	struct BkMatrix4x4 out;

	real const r = DEG_TO_RAD * deg;
	real const cr = cos(r);
	real const sr = sin(r);

	out.m11 = cr;  out.m12 = -sr; out.m13 = 0.0; out.m14 = 0.0;
	out.m21 = sr;  out.m22 = cr;  out.m23 = 0.0; out.m24 = 0.0;
	out.m31 = 0.0; out.m32 = 0.0; out.m33 = 1.0; out.m34 = 0.0;
	out.m41 = 0.0; out.m42 = 0.0; out.m43 = 0.0; out.m44 = 1.0;

	return out;
}

struct BkMatrix4x4	BkMatrix4x4_Rotate_axis(struct BkVector4 const* v, real const deg)
{
	struct BkMatrix4x4 out;

	real const r = DEG_TO_RAD * deg;
	real const cr = cos(r);
	real const omcr = 1.0 - cr;
	real const omcracr = omcr + cr;
	real const sr = sin(r);
	real const vxmsr = v->x * sr;
	real const vymsr = v->y * sr;
	real const vzmsr = v->z * sr;
	real const vxy = v->x * v->y;
	real const vxz = v->x * v->z;
	real const vyz = v->y * v->z;

	out.m11 = v->x * v->x * omcracr; out.m12 = vxy * omcr - vzmsr;    out.m13 = vxz * omcr + vymsr;    out.m14 = 0.0;
	out.m21 = vxy * omcr + vzmsr;    out.m22 = v->y * v->y * omcracr; out.m23 = vyz * omcr - vxmsr;    out.m24 = 0.0;
	out.m31 = vxz * omcr - vymsr;    out.m32 = vyz * omcr + vxmsr;    out.m33 = v->z * v->z * omcracr; out.m34 = 0.0;
	out.m41 = 0.0;                   out.m42 = 0.0;                   out.m43 = 0.0;                   out.m44 = 1.0;

	return out;
}

struct BkMatrix4x4	BkMatrix4x4_Scale_Uniform(real const k)
{
	return (struct BkMatrix4x4) {
		.m11 = k, .m12 = 0.0, .m13 = 0.0, .m14 = 0.0,
		.m21 = 0.0, .m22 = k, .m23 = 0.0, .m24 = 0.0,
		.m31 = 0.0, .m32 = 0.0, .m33 = k, .m34 = 0.0,
		.m41 = 0.0, .m42 = 0.0, .m43 = 0.0, .m44 = 1.0
	};
}

struct BkMatrix4x4	BkMatrix4x4_Scale_Nonuniform(real const x, real const y, real const z)
{
	return (struct BkMatrix4x4) {
		.m11 = x, .m12 = 0.0, .m13 = 0.0, .m14 = 0.0,
		.m21 = 0.0, .m22 = y, .m23 = 0.0, .m24 = 0.0,
		.m31 = 0.0, .m32 = 0.0, .m33 = z, .m34 = 0.0,
		.m41 = 0.0, .m42 = 0.0, .m43 = 0.0, .m44 = 1.0
	};
}

struct BkMatrix4x4	BkMatrix4x4_Scale_axis(struct BkVector4 const* v, real const k)
{
	struct BkMatrix4x4 out;

	real const kmo = k - 1.0;
	real const opkmo = 1.0 + kmo;
	real const vxy = v->x * v->y;
	real const vxz = v->x * v->z;
	real const vyz = v->y * v->z;
	real const kmomvxy = kmo * vxy;
	real const kmomvxz = kmo * vxz;
	real const kmomvyz = kmo * vyz;

	out.m11 = opkmo * v->x * v->x; out.m12 = kmomvxy;             out.m13 = kmomvxz;             out.m14 = 0.0;
	out.m21 = kmomvxy;             out.m22 = opkmo * v->y * v->y; out.m23 = kmomvyz;             out.m24 = 0.0;
	out.m31 = kmomvxz;             out.m32 = kmomvyz;             out.m33 = opkmo * v->z * v->z; out.m34 = 0.0;
	out.m41 = 0.0;                 out.m42 = 0.0;                 out.m43 = 0.0;                 out.m44 = 1.0;

	return out;
}

struct BkMatrix4x4	BkMatrix4x4_Translate(real const x, real const y, real const z)
{
	return (struct BkMatrix4x4) {
		.m11 = 1.0, .m12 = 0.0, .m13 = 0.0, .m14 = x,
		.m21 = 0.0, .m22 = 1.0, .m23 = 0.0, .m24 = y,
		.m31 = 0.0, .m32 = 0.0, .m33 = 1.0, .m34 = z,
		.m41 = 0.0, .m42 = 0.0, .m43 = 0.0, .m44 = 1.0
	};
}

real	BkMatrix4x4_Determinant(struct BkMatrix4x4 const* m)
{
	return m->m11 * (m->m22 * (m->m33 * m->m44 - m->m34 * m->m43) + m->m23 * (m->m34 * m->m42 - m->m32 * m->m44) + m->m24 * (m->m32 * m->m43 - m->m33 * m->m42)) -
	       m->m12 * (m->m21 * (m->m33 * m->m44 - m->m34 * m->m43) + m->m23 * (m->m34 * m->m41 - m->m31 * m->m44) + m->m24 * (m->m31 * m->m43 - m->m33 * m->m41)) +
	       m->m13 * (m->m21 * (m->m32 * m->m44 - m->m34 * m->m42) + m->m22 * (m->m34 * m->m41 - m->m31 * m->m44) + m->m24 * (m->m31 * m->m42 - m->m32 * m->m41)) -
	       m->m14 * (m->m21 * (m->m32 * m->m43 - m->m33 * m->m42) + m->m22 * (m->m33 * m->m41 - m->m31 * m->m43) + m->m23 * (m->m31 * m->m42 - m->m32 * m->m41));
}

struct BkMatrix4x4	BkMatrix4x4_Inverse(struct BkMatrix4x4 const* m)
{
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

	if (det == 0.0)
		return BkMatrix4x4_Identity();

	det = 1.0 / det;

	out.m11 *= det; out.m12 *= det; out.m13 *= det; out.m14 *= det;
	out.m21 *= det; out.m22 *= det; out.m23 *= det; out.m24 *= det;
	out.m31 *= det; out.m32 *= det; out.m33 *= det; out.m34 *= det;
	out.m41 *= det; out.m42 *= det; out.m43 *= det; out.m44 *= det;

	return out;
}