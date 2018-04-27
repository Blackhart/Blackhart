#ifndef __BK_CAMERA_H__
#define __BK_CAMERA_H__

// blackhart headers.
#include "foundation\BkExport.h"
#include "foundation\BkTransform.h"
#include "foundation\BkMatrix4x4.h"

// Struct definitions.
struct BkCamera
{
	struct BkTransform	transform;
	struct BkMatrix4x4	projection;
};

// ~~~~~ Dcl(PUBLIC) ~~~~~

extern BK_API void	BkCamera_Initialize(struct BkCamera* camera);
extern BK_API void	BkCamera_SetProjection(struct BkCamera* obj, struct BkMatrix4x4 const* projection);
extern BK_API struct BkMatrix4x4	BkCamera_ViewMatrix(struct BkCamera* obj);
extern BK_API struct BkTransform*	BkCamera_Transform(struct BkCamera* obj);
extern BK_API struct BkMatrix4x4*	BkCamera_Projection(struct BkCamera* obj);

#endif
