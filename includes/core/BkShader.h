#ifndef __BK_SHADER_H__
#define __BK_SHADER_H__

#include <stdlib.h>

#include "pil\BkAtomicDataType.h"
#include "BkError.h"
#include "pil\BkOpenGL.h"

// ~~~~~ Dcl(PUBLIC) ~~~~~

extern BkResult	BkCreateShader(BkShader** ppShader, char const* pPath);
extern void		BkReleaseShader(BkShader** ppShader);

#endif