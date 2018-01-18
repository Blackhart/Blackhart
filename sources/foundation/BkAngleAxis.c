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

void	BkAngleAxis_SetAngle(struct BkAngleAxis* this, real const angle)
{
	this->angle = angle;
}

void	BkAngleAxis_SetAxis(struct BkAngleAxis* this, struct BkVector3 const* axis)
{
	this->axis.x = axis->x;
	this->axis.y = axis->y;
	this->axis.z = axis->z;
}