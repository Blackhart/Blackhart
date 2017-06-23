#ifndef __BK_SHADER_H__
#define __BK_SHADER_H__

#include <stdlib.h>

#include "pil\BkAtomicDataType.h"
#include "BkError.h"
#include "pil\BkOpenGL.h"

struct sShader
{
	BkOpenGLShader	openGLShader;
};

typedef struct sShader	BkShader;

// ~~~~~ Dcl(PUBLIC) ~~~~~

extern BkResult	BkCreateShader(char const* pShaderName, char const* pPath);
extern void		BkReleaseShader(char const* pShaderName);

#endif