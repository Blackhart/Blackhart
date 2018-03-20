// Standard library headers.
#include <math.h>

// Blackhart.foundation headers.
#include "foundation\BkTransform.h"
#include "foundation\BkAngleAxis.h"
#include "foundation\BkMath.h"
#include "foundation\BkError.h"

// ~~~~~ Def(PUBLIC) ~~~~~

void	BkTransform_Initialize(struct BkTransform* transform)
{
	BK_ASSERT(BK_ISNULL(transform));

	transform->local = BkMatrix4x4_Identity();
	transform->position = BkPoint3_Zero();
	transform->rotation = BkQuaternion_Identity();
}

void	BkTransform_LookAt(struct BkTransform* transform, struct BkPoint3 const* from, struct BkPoint3 const* to, struct BkVector3 const* up)
{
	BK_ASSERT(BK_ISNULL(transform));
	BK_ASSERT(BK_ISNULL(from));
	BK_ASSERT(BK_ISNULL(to));
	BK_ASSERT(BK_ISNULL(up));

	struct BkVector3 f = BkPoint3_Sub_BkPoint3(from, to);
	f = BkVector3_Normalize(&f);

	struct BkVector3 r = BkVector3_Cross(up, &f);

	struct BkVector3 u = BkVector3_Cross(&f, &r);

	struct BkMatrix4x4* m = &(transform->local);

	m->m11 = r.x;            m->m12 = u.x;            m->m13 = f.x;            m->m14 = from->x;
	m->m21 = r.y;            m->m22 = u.y;            m->m23 = f.y;            m->m24 = from->y;
	m->m31 = r.z;            m->m32 = u.z;            m->m33 = f.z;            m->m34 = from->z;
	m->m41 = BK_REAL(0.0);   m->m42 = BK_REAL(0.0);   m->m43 = BK_REAL(0.0);   m->m44 = BK_REAL(1.0);
}

void	BkTransform_Translate_BkVector3(struct BkTransform* transform, struct BkVector3 const* translation)
{
	BK_ASSERT(BK_ISNULL(transform));
	BK_ASSERT(BK_ISNULL(translation));

	transform->position = BkPoint3_Add_BkVector3(&(transform->position), translation);

	_BkTransform_RecomputeLocal(transform);
}

void	BkTransform_Rotate_BkQuaternion(struct BkTransform* transform, struct BkQuaternion const* rotation)
{
	BK_ASSERT(BK_ISNULL(transform));
	BK_ASSERT(BK_ISNULL(rotation));

	transform->rotation = BkQuaternion_Mul_BkQuaternion(&(transform->rotation), rotation);

	_BkTransform_RecomputeLocal(transform);
}

void	BkTransform_Rotate_EulerAngle(struct BkTransform* transform, struct BkEulerAngles const* euler)
{
	BK_ASSERT(BK_ISNULL(transform));
	BK_ASSERT(BK_ISNULL(euler));

	struct BkQuaternion const q = BkQuaternion_FromEulerAngles(euler);
	transform->rotation = BkQuaternion_Mul_BkQuaternion(&(transform->rotation), &q);

	_BkTransform_RecomputeLocal(transform);
}

void	BkTransform_Rotate_AngleAxis(struct BkTransform* transform, struct BkAngleAxis const* angle_axis)
{
	BK_ASSERT(BK_ISNULL(transform));
	BK_ASSERT(BK_ISNULL(angle_axis));

	struct BkQuaternion const q = BkQuaternion_FromAngleAxis(angle_axis);
	transform->rotation = BkQuaternion_Mul_BkQuaternion(&(transform->rotation), &q);

	_BkTransform_RecomputeLocal(transform);
}

void	BkTransform_RotateAround(struct BkTransform* transform, struct BkPoint3 const* center, struct BkEulerAngles const* euler)
{
	BK_ASSERT(BK_ISNULL(transform));
	BK_ASSERT(BK_ISNULL(center));
	BK_ASSERT(BK_ISNULL(euler));

	struct BkMatrix4x4 local = BkMatrix4x4_Identity();

	struct BkMatrix4x4 const center_matrix = BkMatrix4x4_Translation_BkPoint3(center);
	struct BkMatrix4x4 const inv_center_matrix = BkMatrix4x4_Inverse(&center_matrix);

	struct BkQuaternion const q = BkQuaternion_FromEulerAngles(euler);
	struct BkMatrix4x4 const rotation = BkMatrix4x4_FromBkQuaternion(&q);

	local = BkMatrix4x4_Mul_BkMatrix4x4(&inv_center_matrix, &(transform->local));
	local = BkMatrix4x4_Mul_BkMatrix4x4(&rotation, &local);
	local = BkMatrix4x4_Mul_BkMatrix4x4(&center_matrix, &local);

	transform->position = BkPoint3_FromXYZ(local.m14 / local.m44, local.m24 / local.m44, local.m34 / local.m44);
	transform->rotation = BkQuaternion_FromBkMatrix4x4(&local);
	transform->local = local;
}

// ~~~~~ Def(INTERNAL) ~~~~~

void	_BkTransform_RecomputeLocal(struct BkTransform* transform)
{
	BK_ASSERT(BK_ISNULL(transform));

	struct BkMatrix4x4 mt = BkMatrix4x4_Translation_BkPoint3(&(transform->position));
	struct BkMatrix4x4 mr = BkMatrix4x4_FromBkQuaternion(&(transform->rotation));

	transform->local = BkMatrix4x4_Mul_BkMatrix4x4(&mt, &mr);
}