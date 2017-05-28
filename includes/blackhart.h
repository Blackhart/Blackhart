#ifndef __BK_BLACKHART_H__
#define __BK_BLACKHART_H__

#include "pil/pil.h"
#include "core/core.h"

typedef struct sGraphicsInfo	BkGraphicsInfo;

// ~~~~~ Dcl(PUBLIC) ~~~~~

extern void	BkInitialize(BkGraphicsInfo const* const pGraphicsInfo);
extern void	BkUninitialize(void);
extern void	BkGetSupportedExtensions(uint32* const pExtensionCount, char*** pppExtensions);
extern void	BkGetSupportedExtensionCount(uint32* const pExtensionCount);

#endif