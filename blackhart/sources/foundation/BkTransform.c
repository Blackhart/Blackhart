// Standard library headers.
#include <math.h>

// blackhart headers.
#include "foundation\BkTransform.h"
#include "foundation\BkAngleAxis.h"
#include "foundation\BkMath.h"
#include "foundation\BkError.h"

// ~~~~~ Def(PUBLIC) ~~~~~

void	BkTransform_Initialize(struct BkTransform* obj)
{
	BK_ASSERT(BK_ISNULL(obj));

	obj->position = BkPoint3_Zero();
	obj->orientation = BkQuaternion_Identity();
	obj->dirty = true;
}

struct BkMatrix4x4*	BkTransform_Matrix(struct BkTransform* obj)
{
	BK_ASSERT(BK_ISNULL(obj));

	if (obj->dirty)
	{
		struct BkMatrix4x4 const mt = BkMatrix4x4_Translation_BkPoint3(&(obj->position));
		struct BkMatrix4x4 const mr = BkMatrix4x4_FromBkQuaternion(&(obj->orientation));

		obj->local = BkMatrix4x4_Mul_BkMatrix4x4(&mt, &mr);

		obj->dirty = false;
	}

	return &obj->local;
}

struct BkMatrix4x4	BkTransform_InvMatrix(struct BkTransform* obj)
{
	BK_ASSERT(BK_ISNULL(obj));

	return BkMatrix4x4_Inverse(BkTransform_Matrix(obj));
}

void	BkTransform_LookAt(struct BkTransform* obj, struct BkPoint3 const* from, struct BkPoint3 const* to, struct BkVector3 const* up)
{
	BK_ASSERT(BK_ISNULL(obj));
	BK_ASSERT(BK_ISNULL(from));
	BK_ASSERT(BK_ISNULL(to));
	BK_ASSERT(BK_ISNULL(up));

	obj->position = *from;

	struct BkVector3 f = BkPoint3_Sub_BkPoint3(from, to);
	f = BkVector3_Normalize(&f);

	struct BkVector3 r = BkVector3_Cross(up, &f);
    r = BkVector3_Normalize(&r);

	struct BkVector3 u = BkVector3_Cross(&f, &r);
    u = BkVector3_Normalize(&u);

	struct BkMatrix4x4 m;

	m.m11 = r.x;            m.m12 = u.x;            m.m13 = f.x;            m.m14 = from->x;
	m.m21 = r.y;            m.m22 = u.y;            m.m23 = f.y;            m.m24 = from->y;
	m.m31 = r.z;            m.m32 = u.z;            m.m33 = f.z;            m.m34 = from->z;
	m.m41 = BK_REAL(0.0);   m.m42 = BK_REAL(0.0);   m.m43 = BK_REAL(0.0);   m.m44 = BK_REAL(1.0);

	obj->orientation = BkQuaternion_FromBkMatrix4x4(&m);

	obj->dirty = true;
}

void	BkTransform_Translate_BkVector3(struct BkTransform* obj, struct BkVector3 const* translation)
{
	BK_ASSERT(BK_ISNULL(obj));
	BK_ASSERT(BK_ISNULL(translation));

	obj->position = BkPoint3_Add_BkVector3(&(obj->position), translation);

	obj->dirty = true;
}

void	BkTransform_Rotate_BkQuaternion(struct BkTransform* obj, struct BkQuaternion const* rotation)
{
	BK_ASSERT(BK_ISNULL(obj));
	BK_ASSERT(BK_ISNULL(rotation));

	obj->orientation = BkQuaternion_Mul_BkQuaternion(&(obj->orientation), rotation);

	obj->dirty = true;
}

void	BkTransform_Rotate_EulerAngle(struct BkTransform* obj, struct BkEulerAngles const* euler)
{
	BK_ASSERT(BK_ISNULL(obj));
	BK_ASSERT(BK_ISNULL(euler));

	struct BkQuaternion const q = BkQuaternion_FromEulerAngles(euler);
	obj->orientation = BkQuaternion_Mul_BkQuaternion(&(obj->orientation), &q);

	obj->dirty = true;
}

void	BkTransform_Rotate_AngleAxis(struct BkTransform* obj, struct BkAngleAxis const* angle_axis)
{
	BK_ASSERT(BK_ISNULL(obj));
	BK_ASSERT(BK_ISNULL(angle_axis));

	struct BkQuaternion const q = BkQuaternion_FromAngleAxis(angle_axis);
	obj->orientation = BkQuaternion_Mul_BkQuaternion(&(obj->orientation), &q);

	obj->dirty = true;
}

struct BkVector3	BkTransform_Forward(struct BkTransform* obj)
{
	BK_ASSERT(BK_ISNULL(obj));

	struct BkMatrix4x4 const* local = BkTransform_Matrix(obj);
	return BkVector3_FromXYZ(local->m13, local->m23, local->m33);
}

struct BkVector3	BkTransform_Right(struct BkTransform* obj)
{
	BK_ASSERT(BK_ISNULL(obj));

	struct BkMatrix4x4 const* local = BkTransform_Matrix(obj);
	return BkVector3_FromXYZ(local->m11, local->m21, local->m31);
}

struct BkVector3	BkTransform_Up(struct BkTransform* obj)
{
	BK_ASSERT(BK_ISNULL(obj));

	struct BkMatrix4x4 const* local = BkTransform_Matrix(obj);
	return BkVector3_FromXYZ(local->m12, local->m22, local->m32);
}

void	BkTransform_SetPosition(struct BkTransform* obj, struct BkPoint3 const* position)
{
	BK_ASSERT(BK_ISNULL(obj));
	BK_ASSERT(BK_ISNULL(position));

	obj->position = *position;

	obj->dirty = true;
}

void	BkTransform_SetOrientation(struct BkTransform* obj, struct BkQuaternion const* orientation)
{
	BK_ASSERT(BK_ISNULL(obj));
	BK_ASSERT(BK_ISNULL(orientation));

	obj->orientation = *orientation;

	obj->dirty = true;
}