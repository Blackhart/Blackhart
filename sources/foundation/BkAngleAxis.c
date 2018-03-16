// Blackhart.foundation headers.
#include "foundation/BkAngleAxis.h"
#include "foundation/BkVector3.h"

// ~~~~~ Def(PUBLIC) ~~~~~

struct BkAngleAxis	BkAngleAxis_FromAngleAxis(real const angle, struct BkVector3 const* axis)
{
	struct BkAngleAxis out;

	out.angle = angle;
	out.axis.x = axis->x;
	out.axis.y = axis->y;
	out.axis.z = axis->z;

	return out;
}

void	BkAngleAxis_SetAngle(struct BkAngleAxis* obj, real const angle)
{
	obj->angle = angle;
}

void	BkAngleAxis_SetAxis(struct BkAngleAxis* obj, struct BkVector3 const* axis)
{
	obj->axis.x = axis->x;
	obj->axis.y = axis->y;
	obj->axis.z = axis->z;
}