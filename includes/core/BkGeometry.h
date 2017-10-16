#ifndef __BK_GEOMETRY_H__
#define __BK_GEOMETRY_H__

#include "pil\BkAtomicDataType.h"

#include "core\BkList.h"
#include "core\BkVector4.h"

struct BkGeometry
{
	real*			vertices;
	uint32*			indices;
	struct BkVector4*	color;
	BkBool			visible;
};

#endif
