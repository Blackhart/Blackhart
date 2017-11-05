#include "core\BkPoint.h"
#include "core\BkVector4.h"

// ~~~~~ Dcl(INTERNAL) ~~~~~

static struct BkPoint	__BkPoint_Sub_BkPoint(struct BkPoint const* a, struct BkPoint const* b);
static struct BkPoint	__BkPoint_Mul_Real(struct BkPoint const* a, real b);
static struct BkPoint	__BkPoint_Add_BkPoint(struct BkPoint const* a, struct BkPoint const* b);

// ~~~~~ Def(ALL) ~~~~~

struct BkPoint	BkPoint_Zero(void)
{
	struct BkPoint out;
	out.x = 0.0;
	out.y = 0.0;
	out.z = 0.0;
	return out;
}

void	BkPoint_Set(struct BkPoint* dst, real const x, real const y, real const z)
{
	dst->x = x;
	dst->y = y;
	dst->z = z;
}

struct BkPoint	BkPoint_Copy(struct BkPoint const* src)
{
	struct BkPoint out;
	out.x = src->x;
	out.y = src->y;
	out.z = src->z;
	return out;
}

void	BkPoint_Assign(struct BkPoint* dst, struct BkPoint const* src)
{
	dst->x = src->x;
	dst->y = src->y;
	dst->z = src->z;
}

struct BkPoint	BkPoint_Add_BkVector4(struct BkPoint const* p, struct BkVector4 const* v)
{
	struct BkPoint out;
	out.x = p->x + v->x;
	out.y = p->y + v->y;
	out.z = p->z + v->z;
	return out;
}

struct BkPoint	BkPoint_Sub_BkVector4(struct BkPoint const* p, struct BkVector4 const* v)
{
	struct BkPoint out;
	out.x = p->x - v->x;
	out.y = p->y - v->y;
	out.z = p->z - v->z;
	return out;
}

real	BkPoint_Distance(struct BkPoint const* a, struct BkPoint const* b)
{
	struct BkVector4 out = BkVector4_From_Points(a, b);
	return BkVector4_Magnitude(&out);
}

struct BkPoint	BkPoint_Lerp(struct BkPoint const* from, struct BkPoint const* to, real const t)
{
	if (t <= 0.0)
		return BkPoint_Copy(from);
	else if (t >= 1.0)
		return BkPoint_Copy(to);
	else
	{
		struct BkPoint out = __BkPoint_Sub_BkPoint(to, from);
		out = __BkPoint_Mul_Real(&out, t);
		return __BkPoint_Add_BkPoint(from, &out);
	}
}

struct BkPoint	__BkPoint_Sub_BkPoint(struct BkPoint const* a, struct BkPoint const* b)
{
	struct BkPoint out;
	out.x = a->x - b->x;
	out.y = a->y - b->y;
	out.z = a->z - b->z;
	return out;
}

struct BkPoint	__BkPoint_Mul_Real(struct BkPoint const* a, real b)
{
	struct BkPoint out;
	out.x = a->x * b;
	out.y = a->y * b;
	out.z = a->z * b;
	return out;
}

struct BkPoint	__BkPoint_Add_BkPoint(struct BkPoint const* a, struct BkPoint const* b)
{
	struct BkPoint out;
	out.x = a->x + b->x;
	out.y = a->y + b->y;
	out.z = a->z + b->z;
	return out;
}