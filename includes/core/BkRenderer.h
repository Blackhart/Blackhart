#ifndef __BK_RENDERER_H__
#define __BK_RENDERER_H__

#include "pil\BkAtomicDataType.h"
#include "BkError.h"
#include "BkMaterial.h"
#include "BkBuffer.h"

#include "pil\__BkExport.h"

// ~~~~~ Dcl(PUBLIC) ~~~~~

extern BK_API void	BkRender(BkBuffer const* pObject, BkMaterial const* pMaterial);

#endif