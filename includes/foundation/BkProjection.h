#ifndef __BK_PROJECTION_H__
#define __BK_PROJECTION_H__

// Blackhart.foundation headers.
#include "__BkExport.h"
#include "BkAtomicDataType.h"
#include "BkMatrix4x4.h"

// ~~~~~ Dcl(PUBLIC) ~~~~~

extern BK_API struct BkMatrix4x4	BkProjection_Perspective(real const fov, real const aspect_ratio, const real near, const real far);

#endif
