// blackhart headers.
#include "foundation\BkCamera.h"
#include "foundation\BkProjection.h"

// ~~~~~ Def(PUBLIC) ~~~~~

void	BkCamera_Initialize(struct BkCamera* camera)
{
	BK_ASSERT(BK_ISNULL(camera));

	BkTransform_Initialize(BkCamera_Transform(camera));
	camera->projection = BkMatrix4x4_Identity();
}

void	BkCamera_SetProjection(struct BkCamera* obj, struct BkMatrix4x4 const* projection)
{
	BK_ASSERT(BK_ISNULL(obj));
	BK_ASSERT(BK_ISNULL(projection));

	obj->projection = *projection;
}

struct BkMatrix4x4	BkCamera_ViewMatrix(struct BkCamera* obj)
{
	BK_ASSERT(BK_ISNULL(obj));

	return BkTransform_InvMatrix(BkCamera_Transform(obj));
}

struct BkTransform*	BkCamera_Transform(struct BkCamera* obj)
{
	BK_ASSERT(BK_ISNULL(obj));

	return &obj->transform;
}

struct BkMatrix4x4*	BkCamera_Projection(struct BkCamera* obj)
{
	BK_ASSERT(BK_ISNULL(obj));

	return &obj->projection;
}