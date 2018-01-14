#ifndef __BK_TRANSFORM_H__
#define __BK_TRANSFORM_H__

// Blackhart.foundation headers.
#include "foundation\__BkExport.h"
#include "foundation\BkVector3.h"
#include "foundation\BkPoint3.h"

// Forward declarations.
struct BkMatrix4x4;

// ~~~~~ Dcl(PUBLIC) ~~~~~

extern BK_API struct BkVector3	BkTransform_Forward(struct BkMatrix4x4 const* m);
extern BK_API struct BkVector3	BkTransform_Right(struct BkMatrix4x4 const* m);
extern BK_API struct BkVector3	BkTransform_Up(struct BkMatrix4x4 const* m);
extern BK_API struct BkPoint3	BkTransform_Position(struct BkMatrix4x4 const* m);

#endif
