#include "core/math/vector4.h"
#include "core/math/matrix4x4.h"

vec4    Lerp_vec4(vec4 const* const from, vec4 const* const to, real const t)
{
	vec4 sfromto = Substract_vec4_vec4(from, to);
	vec4 msfromtot = Multiply_vec4_real(&sfromto, t);
	return Addition_vec4_vec4(&msfromtot, from);
}

vec4    Addition_vec4_vec4(vec4 const* const a, vec4 const* const b)
{
	vec4 lOut;
	lOut.x = a->x + b->x;
	lOut.y = a->y + b->y;
	lOut.z = a->z + b->z;
	lOut.w = 1.0;
	return lOut;
}

vec4    Multiply_vec4_real(vec4 const* const a, real b)
{
	vec4 lOut;
	lOut.x = a->x * b;
	lOut.y = a->y * b;
	lOut.z = a->z * b;
	lOut.w = 1.0;
	return lOut;
}

vec4    Substract_vec4_vec4(vec4 const* const a, vec4 const* const b)
{
	vec4 lOut;
	lOut.x = a->x - b->x;
	lOut.y = a->y - b->y;
	lOut.z = a->z - b->z;
	lOut.w = 1.0;
	return lOut;
}

real    Distance_vec4(vec4 const* const a, vec4 const* const b)
{
	vec4 sab = Substract_vec4_vec4(a, b);
	return Magnitude_vec4(&sab);
}

real    Magnitude_vec4(vec4 const* const a)
{
	return sqrt(a->x * a->x + a->y * a->y + a->z * a->z);
}

vec4    Max_vec4(vec4 const* const a, vec4 const* const b)
{
	vec4 res;
	if (Magnitude_vec4(a) > Magnitude_vec4(b))
		Assign_vec4(&res, a);
	else
		Assign_vec4(&res, b);
	return res;
}

vec4    Min_vec4(vec4 const* const a, vec4 const* const b)
{
	vec4 res;
	if (Magnitude_vec4(a) < Magnitude_vec4(b))
		Assign_vec4(&res, a);
	else
		Assign_vec4(&res, b);
	return res;
}

void    Assign_vec4(vec4* const dst, vec4 const* const src)
{
	Set_vec4(dst, src->x, src->y, src->z, src->w);
}

vec4    Copy_vec4(vec4 const* const src)
{
	vec4 dst;
	Set_vec4(&dst, src->x, src->y, src->z, src->w);
	return dst;
}

void    Set_vec4(vec4* const dst, real const x, real const y, real const z, real const w)
{
    dst->x = x;
    dst->y = y;
    dst->z = z;
    dst->w = w;
}

real    Dot_vec4(vec4 const* const a, vec4 const* const b)
{
	return a->x * b->x + a->y * b->y + a->z * b->z;
}

real    Angle_vec4(vec4 const* const a, vec4 const* const b)
{
	vec4 na = Normalize_vec4(a);
	vec4 nb = Normalize_vec4(b);
	return acos(Dot_vec4(&na, &nb));
}

vec4    Normalize_vec4(vec4 const* const a)
{
	return Divide_vec4_real(a, Magnitude_vec4(a));
}

vec4    Divide_vec4_real(vec4 const* const a, real b)
{
	vec4 lOut;
	lOut.x = a->x / b;
	lOut.y = a->y / b;
	lOut.z = a->z / b;
	lOut.w = 1.0;
	return lOut;
}

vec4    Cross_vec4(vec4 const* const a, vec4 const* const b)
{
    vec4 lOut;
    lOut.x = a->y * b->z - a->z * b->y;
    lOut.y = a->z * b->x - a->x * b->z;
    lOut.z = a->x * b->y - a->y * b->x;
    lOut.w = 1.0;
    return lOut;
}

vec4    Multiply_vec4_mat4(vec4 const* const a, mat4 const* const b)
{
    vec4 res;
    res.x = a->x * b->m11 + a->y * b->m21 + a->z * b->m31 + a->w * b->m41;
    res.y = a->x * b->m12 + a->y * b->m22 + a->z * b->m32 + a->w * b->m42;
    res.z = a->x * b->m13 + a->y * b->m23 + a->z * b->m33 + a->w * b->m43;
    res.w = a->x * b->m14 + a->y * b->m24 + a->z * b->m34 + a->w * b->m44;
    return res;
}

vec4    Negate_vec4(vec4 const* const a)
{
    vec4 lOut;
    lOut.x = -a->x;
    lOut.y = -a->y;
    lOut.z = -a->z;
    lOut.w = 1.0;
    return lOut;
}