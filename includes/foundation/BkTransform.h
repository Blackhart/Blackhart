#ifndef __BK_TRANSFORM_H__
#define __BK_TRANSFORM_H__

// Blackhart.foundation headers.
#include "foundation\BkExport.h"
#include "foundation\BkMatrix4x4.h"
#include "foundation\BkPoint3.h"
#include "foundation\BkQuaternion.h"

// Forward declarations.
struct BkEulerAngles;
struct BkVector3;
struct BkAngleAxis;

// Type definitions.
struct BkTransform
{
	struct BkPoint3		position;
	struct BkQuaternion	rotation;
	struct BkMatrix4x4	local;
};

// ~~~~~ Dcl(PUBLIC) ~~~~~

extern BK_API void	BkTransform_Initialize(struct BkTransform* transform);
extern BK_API void	BkTransform_LookAt(struct BkTransform* transform, struct BkPoint3 const* from, struct BkPoint3 const* to, struct BkVector3 const* up);
extern BK_API void	BkTransform_Translate_BkVector3(struct BkTransform* transform, struct BkVector3 const* translation);
extern BK_API void	BkTransform_Rotate_BkQuaternion(struct BkTransform* transform, struct BkQuaternion const* rotation);
extern BK_API void	BkTransform_Rotate_EulerAngle(struct BkTransform* transform, struct BkEulerAngles const* euler);
extern BK_API void	BkTransform_Rotate_AngleAxis(struct BkTransform* transform, struct BkAngleAxis const* angle_axis);
extern BK_API void	BkTransform_RotateAround(struct BkTransform* transform, struct BkPoint3 const* point, struct BkAngleAxis const* angle_axis);

// ~~~~~ Dcl(INTERNAL) ~~~~~

extern void		_BkTransform_RecomputeLocal(struct BkTransform* transform);

#endif
