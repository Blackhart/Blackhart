#ifndef __BK_SHADER_H__
#define __BK_SHADER_H__

#include <stdlib.h>

#include "pil\BkAtomicDataType.h"

struct sShader
{
	char*	shader;
};

typedef struct sShader	BkShader;

// ~~~~~ Dcl(PUBLIC) ~~~~~

extern int8	BkCreateShader(BkShader** ppShader, char const* pPath);
extern void	BkReleaseShader(BkShader** ppShader);

#endif