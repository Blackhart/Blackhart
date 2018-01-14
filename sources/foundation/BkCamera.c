// Blackhart.foundation headers.
#include "foundation\BkCamera.h"
#include "foundation\BkError.h"
#include "foundation\BkProjection.h"
#include "foundation\BkPoint3.h"
#include "foundation\BkVector3.h"

// ~~~~~ Def(PUBLIC) ~~~~~

void	BkCamera_Initialize(struct BkCamera* camera)
{
	BK_ERROR(BK_ISNULL(camera), "Camera pointer must not be NULL.");

	camera->transform.cam_to_world = BkMatrix4x4_Identity();
	camera->transform.world_to_cam = BkMatrix4x4_Identity();
	camera->projection = BkMatrix4x4_Identity();
}

void	BkCamera_LookAt(struct BkCamera* camera, struct BkPoint3 const* from, struct BkPoint3 const* to, struct BkVector3 const* up)
{
	BK_ERROR(BK_ISNULL(camera), "Camera pointer must not be NULL.");
	BK_ERROR(BK_ISNULL(from), "From location pointer must not be NULL.");
	BK_ERROR(BK_ISNULL(to), "To location pointer must not be NULL.");
	BK_ERROR(BK_ISNULL(up), "Up vector pointer must not be NULL.");

	struct BkVector3 f = BkPoint3_Sub_BkPoint3(from, to);
	f = BkVector3_Normalize(&f);

	struct BkVector3 r = BkVector3_Cross(up, &f);

	struct BkVector3 u = BkVector3_Cross(&f, &r);

	struct BkMatrix4x4* m = &(camera->transform.cam_to_world);

	m->m11 = r.x;            m->m12 = u.x;            m->m13 = f.x;            m->m14 = from->x;
	m->m21 = r.y;            m->m22 = u.y;            m->m23 = f.y;            m->m24 = from->y;
	m->m31 = r.z;            m->m32 = u.z;            m->m33 = f.z;            m->m34 = from->z;
	m->m41 = BK_REAL(0.0);   m->m42 = BK_REAL(0.0);   m->m43 = BK_REAL(0.0);   m->m44 = BK_REAL(1.0);
	
	camera->transform.world_to_cam = BkMatrix4x4_Inverse(m);
}

void	BkCamera_SetProjection(struct BkCamera* camera, struct BkMatrix4x4 const* projection)
{
	BkMatrix4x4_Assign(&(camera->projection), projection);
}
