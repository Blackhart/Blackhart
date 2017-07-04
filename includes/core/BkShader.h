#ifndef __BK_SHADER_H__
#define __BK_SHADER_H__

#include <stdlib.h>

#include "pil\BkAtomicDataType.h"
#include "BkError.h"
#include "BkString.h"

enum eShaderType
{
	_BK_VERTEX_SHADER_,
	_BK_PIXEL_SHADER_
};

typedef enum eShaderType	BkShaderType;

struct sShader
{
	BkStringBuf	name; // 8 bytes
	void*		api; // 4 bytes
};

typedef struct sShader	BkShader;

// ~~~~~ Dcl(PUBLIC) ~~~~~

extern BkResult	BkCreateShader(char const* pName, char const* pPath, BkShaderType const Type);
extern void		BkReleaseShader(char const* pName);

#endif