#ifndef __BK_CAMERA_H__
#define __BK_CAMERA_H__

// Blackhart.foundation headers.
#include "foundation\__BkExport.h"
#include "foundation\BkAtomicDataType.h"
#include "foundation\BkMatrix4x4.h"

// Forward declarations.
struct BkPoint3;
struct BkVector3;

// Struct definitions.
struct BkCamera_Transform
{
	struct BkMatrix4x4	cam_to_world;
	struct BkMatrix4x4	world_to_cam;
};

struct BkCamera
{
	struct BkCamera_Transform	transform;
	struct BkMatrix4x4		projection;
};

// ~~~~~ Dcl(PUBLIC) ~~~~~

extern BK_API void	BkCamera_Initialize(struct BkCamera* camera);
extern BK_API void	BkCamera_LookAt(struct BkCamera* camera, struct BkPoint3 const* from, struct BkPoint3 const* to, struct BkVector3 const* up);
extern BK_API void	BkCamera_SetProjection(struct BkCamera* camera, struct BkMatrix4x4 const* projection);

#endif
