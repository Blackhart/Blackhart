#include <math.h>

#include "core\BkMath.h"

// ~~~~~ Def(ALL) ~~~~~

struct BkVector4	BkVector4_Zero(void)
{
	struct BkVector4 out;
	out.x = 0.0;
	out.y = 0.0;
	out.z = 0.0;
	return out;
}

struct BkVector4	BkVector4_From_Points(struct BkPoint const* a, struct BkPoint const* b)
{
	struct BkVector4 out;
	out.x = b->x - a->x;
	out.y = b->y - a->y;
	out.z = b->z - a->z;
	return out;
}

struct BkVector4	BkVector4_Lerp(struct BkVector4 const* from, struct BkVector4 const* to, real const t)
{
	if (t <= 0.0)
		return BkVector4_Copy(from);
	else if (t >= 1.0)
		return BkVector4_Copy(to);
	else
	{
		struct BkVector4 out = BkVector4_Sub_BkVector4(to, from);
		out = BkVector4_Mul_Real(&out, t);
		return BkVector4_Add_BkVector4(from, &out);
	}
}

struct BkVector4	BkVector4_Add_BkVector4(struct BkVector4 const* a, struct BkVector4 const* b)
{
	struct BkVector4 out;
	out.x = a->x + b->x;
	out.y = a->y + b->y;
	out.z = a->z + b->z;
	return out;
}

struct BkVector4	BkVector4_Mul_Real(struct BkVector4 const* a, real b)
{
	struct BkVector4 out;
	out.x = a->x * b;
	out.y = a->y * b;
	out.z = a->z * b;
	return out;
}

struct BkVector4	BkVector4_Sub_BkVector4(struct BkVector4 const* a, struct BkVector4 const* b)
{
	struct BkVector4 out;
	out.x = a->x - b->x;
	out.y = a->y - b->y;
	out.z = a->z - b->z;
	return out;
}

real	BkVector4_Magnitude(struct BkVector4 const* a)
{
	return (real)sqrt(a->x * a->x + a->y * a->y + a->z * a->z);
}

struct BkVector4	BkVector4_Max(struct BkVector4 const* a, struct BkVector4 const* b)
{
	struct BkVector4 out;
	if (BkVector4_Magnitude(a) > BkVector4_Magnitude(b))
		BkVector4_Assign(&out, a);
	else
		BkVector4_Assign(&out, b);
	return out;
}

struct BkVector4	BkVector4_Min(struct BkVector4 const* a, struct BkVector4 const* b)
{
	struct BkVector4 out;
	if (BkVector4_Magnitude(a) < BkVector4_Magnitude(b))
		BkVector4_Assign(&out, a);
	else
		BkVector4_Assign(&out, b);
	return out;
}

void	BkVector4_Assign(struct BkVector4* dst, struct BkVector4 const* src)
{
	BkVector4_Set(dst, src->x, src->y, src->z);
}

struct BkVector4	BkVector4_Copy(struct BkVector4 const* src)
{
	struct BkVector4 out;
	BkVector4_Set(&out, src->x, src->y, src->z);
	return out;
}

void	BkVector4_Set(struct BkVector4* dst, real const x, real const y, real const z)
{
	dst->x = x;
	dst->y = y;
	dst->z = z;
}

real	BkVector4_Dot(struct BkVector4 const* a, struct BkVector4 const* b)
{
	return a->x * b->x + a->y * b->y + a->z * b->z;
}

real	BkVector4_Angle(struct BkVector4 const* a, struct BkVector4 const* b)
{
	struct BkVector4 na = BkVector4_Normalize(a);
	struct BkVector4 nb = BkVector4_Normalize(b);
	return (real)acos(BkVector4_Dot(&na, &nb)) * RAD_TO_DEG;
}

struct BkVector4	BkVector4_Normalize(struct BkVector4 const* a)
{
	return BkVector4_Div_Real(a, BkVector4_Magnitude(a));
}

struct BkVector4	BkVector4_Div_Real(struct BkVector4 const* a, real b)
{
	struct BkVector4 out;
	out.x = a->x / b;
	out.y = a->y / b;
	out.z = a->z / b;
	return out;
}

struct BkVector4	BkVector4_Cross(struct BkVector4 const* a, struct BkVector4 const* b)
{
	struct BkVector4 out;
	out.x = a->y * b->z - a->z * b->y;
	out.y = a->z * b->x - a->x * b->z;
	out.z = a->x * b->y - a->y * b->x;
	return out;
}

struct BkVector4	BkVector4_Negate(struct BkVector4 const* a)
{
	struct BkVector4 out;
	out.x = -a->x;
	out.y = -a->y;
	out.z = -a->z;
	return out;
}