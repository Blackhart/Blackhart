// Blackhart.foundation headers.
#include "foundation\BkPoint3.h"
#include "foundation\BkError.h"

// ~~~~~ Def(PUBLIC) ~~~~~

struct BkPoint3	BkPoint3_Zero(void)
{
	return (struct BkPoint3) 
	{
		.x = BK_REAL(0.0),
		.y = BK_REAL(0.0),
		.z = BK_REAL(0.0)
	};
}

struct BkPoint3	BkPoint3_FromXYZ(real const x, real const y, real const z)
{
	return (struct BkPoint3) 
	{
		.x = x,
		.y = y,
		.z = z
	};
}

void	BkPoint3_Set(struct BkPoint3* obj, real const x, real const y, real const z)
{
	BK_ASSERT(BK_ISNULL(obj));

	obj->x = x;
	obj->y = y;
	obj->z = z;
}

struct BkPoint3	BkPoint3_Copy(struct BkPoint3 const* src)
{
	BK_ASSERT(BK_ISNULL(src));

	return (struct BkPoint3) 
	{
		.x = src->x,
		.y = src->y,
		.z = src->z
	};
}

void	BkPoint3_Assign(struct BkPoint3* obj, struct BkPoint3 const* src)
{
	BK_ASSERT(BK_ISNULL(obj));
	BK_ASSERT(BK_ISNULL(src));

	obj->x = src->x;
	obj->y = src->y;
	obj->z = src->z;
}

struct BkPoint3	BkPoint3_Add_BkVector3(struct BkPoint3 const* p, struct BkVector3 const* v)
{
	BK_ASSERT(BK_ISNULL(p));
	BK_ASSERT(BK_ISNULL(v));

	return (struct BkPoint3) 
	{
		.x = p->x + v->x,
		.y = p->y + v->y,
		.z = p->z + v->z
	};
}

struct BkPoint3	BkPoint3_Sub_BkVector3(struct BkPoint3 const* p, struct BkVector3 const* v)
{
	BK_ASSERT(BK_ISNULL(p));
	BK_ASSERT(BK_ISNULL(v));

	return (struct BkPoint3)
	{
		.x = p->x - v->x,
		.y = p->y - v->y,
		.z = p->z - v->z
	};
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

	return (struct BkVector3)
	{
		.x = a->x - b->x,
		.y = a->y - b->y,
		.z = a->z - b->z
	};
}
