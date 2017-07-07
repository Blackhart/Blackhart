#ifndef __BK_RENDERER_H__
#define __BK_RENDERER_H__

#include "pil\BkAtomicDataType.h"
#include "BkError.h"
#include "BkMaterial.h"
#include "BkBuffer.h"

// ~~~~~ Dcl(PUBLIC) ~~~~~

extern void	BkRender(BkBuffer const* pObject, BkMaterial const* pMaterial);

#endif