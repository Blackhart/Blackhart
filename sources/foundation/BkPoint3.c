// Blackhart.foundation headers.
#include "foundation\BkPoint3.h"
#include "foundation\BkError.h"


// ~~~~~ Def(ALL) ~~~~~

struct BkPoint3	BkPoint3_Zero(void)
{
	struct BkPoint3 out;
	out.x = 0.0;
	out.y = 0.0;
	out.z = 0.0;
	return out;
}

void	BkPoint3_Set(struct BkPoint3* dst, real const x, real const y, real const z)
{
	BK_ASSERT(BK_ISNULL(dst));

	dst->x = x;
	dst->y = y;
	dst->z = z;
}

struct BkPoint3	BkPoint3_Copy(struct BkPoint3 const* src)
{
	BK_ASSERT(BK_ISNULL(src));

	struct BkPoint3 out;
	out.x = src->x;
	out.y = src->y;
	out.z = src->z;
	return out;
}

void	BkPoint3_Assign(struct BkPoint3* dst, struct BkPoint3 const* src)
{
	BK_ASSERT(BK_ISNULL(dst));
	BK_ASSERT(BK_ISNULL(src));

	dst->x = src->x;
	dst->y = src->y;
	dst->z = src->z;
}

struct BkPoint3	BkPoint3_Add_BkVector3(struct BkPoint3 const* p, struct BkVector3 const* v)
{
	BK_ASSERT(BK_ISNULL(p));
	BK_ASSERT(BK_ISNULL(v));

	struct BkPoint3 out;
	out.x = p->x + v->x;
	out.y = p->y + v->y;
	out.z = p->z + v->z;
	return out;
}

struct BkPoint3	BkPoint3_Sub_BkVector3(struct BkPoint3 const* p, struct BkVector3 const* v)
{
	BK_ASSERT(BK_ISNULL(p));
	BK_ASSERT(BK_ISNULL(v));

	struct BkPoint3 out;
	out.x = p->x - v->x;
	out.y = p->y - v->y;
	out.z = p->z - v->z;
	return out;
}

real	BkPoint3_Distance(struct BkPoint3 const* a, struct BkPoint3 const* b)
{
	BK_ASSERT(BK_ISNULL(a));
	BK_ASSERT(BK_ISNULL(b));

	struct BkVector3 out = BkPoint3_Sub_BkPoint3(a, b);
	return BkVector3_Magnitude(&out);
}

struct BkPoint3	BkPoint3_Lerp(struct BkPoint3 const* from, struct BkPoint3 const* to, real const t)
{
	BK_ASSERT(BK_ISNULL(from));
	BK_ASSERT(BK_ISNULL(to));

	if (t <= 0.0)
		return BkPoint3_Copy(from);
	else if (t >= 1.0)
		return BkPoint3_Copy(to);
	else
	{
		struct BkVector3 out = BkPoint3_Sub_BkPoint3(to, from);
		out = BkVector3_Mul_Real(&out, t);
		return BkPoint3_Add_BkVector3(from, &out);
	}
}

struct BkVector3	BkPoint3_Sub_BkPoint3(struct BkPoint3 const* a, struct BkPoint3 const* b)
{
	BK_ASSERT(BK_ISNULL(a));
	BK_ASSERT(BK_ISNULL(b));

	struct BkVector3 out;
	out.x = a->x - b->x;
	out.y = a->y - b->y;
	out.z = a->z - b->z;
	return out;
}
