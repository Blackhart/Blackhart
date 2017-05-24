#ifndef __BK_BLACKHART_H__
#define __BK_BLACKHART_H__

#include "pil/pil.h"
#include "core/core.h"

// ~~~~~ Dcl(PUBLIC) ~~~~~

extern void	BkInitialize(char const* const* pExtensions, uint8 const pExtensionCount);
extern void	BkUninitialize();

#endif