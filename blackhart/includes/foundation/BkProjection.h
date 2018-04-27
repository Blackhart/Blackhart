#ifndef __BK_PROJECTION_H__
#define __BK_PROJECTION_H__

// blackhart headers.
#include "foundation\BkAtomicDataType.h"
#include "foundation\BkExport.h"
#include "foundation\BkMatrix4x4.h"

// ~~~~~ Dcl(PUBLIC) ~~~~~

extern BK_API struct BkMatrix4x4	BkProjection_Perspective(real const fov, real const aspect_ratio, const real near, const real far);

#endif
