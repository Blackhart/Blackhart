// Standard headers.
#include <math.h>

// blackhart headers.
#include "foundation\BkError.h"
#include "foundation\BkVector3.h"
#include "foundation\BkMath.h"

// ~~~~~ Def(PUBLIC) ~~~~~

struct BkVector3	BkVector3_Zero(void)
{
	return (struct BkVector3) {
		.x = BK_REAL(0.0),
		.y = BK_REAL(0.0),
		.z = BK_REAL(0.0)
	};
}

struct BkVector3	BkVector3_FromXYZ(real const x, real const y, real const z)
{
	return (struct BkVector3) {
		.x = x,
		.y = y,
		.z = z
	};
}

struct BkVector3	BkVector3_Lerp(struct BkVector3 const* from, struct BkVector3 const* to, real const t)
{
	BK_ASSERT(BK_ISNULL(from));
	BK_ASSERT(BK_ISNULL(to));

	if (t <= 0.0)
		return BkVector3_Copy(from);
	else if (t >= 1.0)
		return BkVector3_Copy(to);
	else
	{
		struct BkVector3 out = BkVector3_Sub_BkVector3(to, from);
		out = BkVector3_Mul_Real(&out, t);
		return BkVector3_Add_BkVector3(from, &out);
	}
}

struct BkVector3	BkVector3_Add_BkVector3(struct BkVector3 const* a, struct BkVector3 const* b)
{
	BK_ASSERT(BK_ISNULL(a));
	BK_ASSERT(BK_ISNULL(b));

	struct BkVector3 out;
	out.x = a->x + b->x;
	out.y = a->y + b->y;
	out.z = a->z + b->z;
	return out;
}

struct BkVector3	BkVector3_Mul_Real(struct BkVector3 const* a, real b)
{
	BK_ASSERT(BK_ISNULL(a));

	struct BkVector3 out;
	out.x = a->x * b;
	out.y = a->y * b;
	out.z = a->z * b;
	return out;
}

struct BkVector3	BkVector3_Sub_BkVector3(struct BkVector3 const* a, struct BkVector3 const* b)
{
	BK_ASSERT(BK_ISNULL(a));
	BK_ASSERT(BK_ISNULL(b));

	struct BkVector3 out;
	out.x = a->x - b->x;
	out.y = a->y - b->y;
	out.z = a->z - b->z;
	return out;
}

real	BkVector3_Magnitude(struct BkVector3 const* a)
{
	BK_ASSERT(BK_ISNULL(a));

	return (real)sqrt(a->x * a->x + a->y * a->y + a->z * a->z);
}

struct BkVector3	BkVector3_Max(struct BkVector3 const* a, struct BkVector3 const* b)
{
	BK_ASSERT(BK_ISNULL(a));
	BK_ASSERT(BK_ISNULL(b));

	struct BkVector3 out;
	if (BkVector3_Magnitude(a) > BkVector3_Magnitude(b))
		BkVector3_Assign(&out, a);
	else
		BkVector3_Assign(&out, b);
	return out;
}

struct BkVector3	BkVector3_Min(struct BkVector3 const* a, struct BkVector3 const* b)
{
	BK_ASSERT(BK_ISNULL(a));
	BK_ASSERT(BK_ISNULL(b));

	struct BkVector3 out;
	if (BkVector3_Magnitude(a) < BkVector3_Magnitude(b))
		BkVector3_Assign(&out, a);
	else
		BkVector3_Assign(&out, b);
	return out;
}

void	BkVector3_Assign(struct BkVector3* __restrict obj, struct BkVector3 const* __restrict src)
{
	BK_ASSERT(BK_ISNULL(obj));
	BK_ASSERT(BK_ISNULL(src));

	BkVector3_Set(obj, src->x, src->y, src->z);
}

struct BkVector3	BkVector3_Copy(struct BkVector3 const* src)
{
	BK_ASSERT(BK_ISNULL(src));

	struct BkVector3 out;
	BkVector3_Set(&out, src->x, src->y, src->z);
	return out;
}

void	BkVector3_Set(struct BkVector3* obj, real const x, real const y, real const z)
{
	BK_ASSERT(BK_ISNULL(obj));

	obj->x = x;
	obj->y = y;
	obj->z = z;
}

real	BkVector3_Dot(struct BkVector3 const* a, struct BkVector3 const* b)
{
	BK_ASSERT(BK_ISNULL(a));
	BK_ASSERT(BK_ISNULL(b));

	return a->x * b->x + a->y * b->y + a->z * b->z;
}

real	BkVector3_AbsDot(struct BkVector3 const* a, struct BkVector3 const* b)
{
	BK_ASSERT(BK_ISNULL(a));
	BK_ASSERT(BK_ISNULL(b));

	return BK_REAL(fabs(a->x * b->x + a->y * b->y + a->z * b->z));
}

real	BkVector3_Angle(struct BkVector3 const* a, struct BkVector3 const* b)
{
	BK_ASSERT(BK_ISNULL(a));
	BK_ASSERT(BK_ISNULL(b));

	struct BkVector3 na = BkVector3_Normalize(a);
	struct BkVector3 nb = BkVector3_Normalize(b);
	return BkMath_DegFromRad(BK_REAL(acos(BkVector3_Dot(&na, &nb))));
}

void	BkVector3_Normalized(struct BkVector3* obj)
{
	BK_ASSERT(BK_ISNULL(obj));

	*obj = BkVector3_Div_Real(obj, BkVector3_Magnitude(obj));
}

struct BkVector3	BkVector3_Normalize(struct BkVector3 const* a)
{
	BK_ASSERT(BK_ISNULL(a));

	return BkVector3_Div_Real(a, BkVector3_Magnitude(a));
}

struct BkVector3	BkVector3_Div_Real(struct BkVector3 const* a, real b)
{
	BK_ASSERT(BK_ISNULL(a));

	struct BkVector3 out;
	out.x = a->x / b;
	out.y = a->y / b;
	out.z = a->z / b;
	return out;
}

struct BkVector3	BkVector3_Cross(struct BkVector3 const* a, struct BkVector3 const* b)
{
	BK_ASSERT(BK_ISNULL(a));
	BK_ASSERT(BK_ISNULL(b));

	struct BkVector3 out;
	out.x = a->y * b->z - a->z * b->y;
	out.y = a->z * b->x - a->x * b->z;
	out.z = a->x * b->y - a->y * b->x;
	return out;
}

void	BkVector3_Negated(struct BkVector3* obj)
{
	BK_ASSERT(BK_ISNULL(obj));

	obj->x = -obj->x;
	obj->y = -obj->y;
	obj->z = -obj->z;
}

struct BkVector3	BkVector3_Negate(struct BkVector3 const* a)
{
	BK_ASSERT(BK_ISNULL(a));

	struct BkVector3 out;
	out.x = -a->x;
	out.y = -a->y;
	out.z = -a->z;
	return out;
}