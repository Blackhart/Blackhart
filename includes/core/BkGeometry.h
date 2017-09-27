#ifndef __BK_GEOMETRY_H__
#define __BK_GEOMETRY_H__

#include "pil\BkAtomicDataType.h"

#include "core\BkList.h"
#include "core\BkVector4.h"

struct sGeometry
{
	real*	vertices;
	uint32*	indices;
	vec4*	color;
	BkBool	visible;
};

typedef struct sGeometry	BkGeometry;

#endif
