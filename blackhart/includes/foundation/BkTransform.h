#ifndef __BK_TRANSFORM_H__
#define __BK_TRANSFORM_H__

// blackhart headers.
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
	struct BkPoint3     position;
	struct BkQuaternion orientation;
	struct BkMatrix4x4  local;
	bool                dirty;
    uint8               __padding__[3];
};

// ~~~~~ Dcl(PUBLIC) ~~~~~

extern BK_API void	BkTransform_Initialize(struct BkTransform* obj);
extern BK_API struct BkMatrix4x4*	BkTransform_Matrix(struct BkTransform* obj);
extern BK_API struct BkMatrix4x4	BkTransform_InvMatrix(struct BkTransform* obj);
extern BK_API void	BkTransform_LookAt(struct BkTransform* obj, struct BkPoint3 const* from, struct BkPoint3 const* to, struct BkVector3 const* up);
extern BK_API void	BkTransform_Translate_BkVector3(struct BkTransform* obj, struct BkVector3 const* translation);
extern BK_API void	BkTransform_Rotate_BkQuaternion(struct BkTransform* obj, struct BkQuaternion const* rotation);
extern BK_API void	BkTransform_Rotate_EulerAngle(struct BkTransform* obj, struct BkEulerAngles const* euler);
extern BK_API void	BkTransform_Rotate_AngleAxis(struct BkTransform* obj, struct BkAngleAxis const* angle_axis);
extern BK_API struct BkVector3	BkTransform_Forward(struct BkTransform* obj);
extern BK_API struct BkVector3	BkTransform_Right(struct BkTransform* obj);
extern BK_API struct BkVector3	BkTransform_Up(struct BkTransform* obj);
extern BK_API void	BkTransform_SetPosition(struct BkTransform* obj, struct BkPoint3 const* position);
extern BK_API void	BkTransform_SetOrientation(struct BkTransform* obj, struct BkQuaternion const* orientation);

#endif
