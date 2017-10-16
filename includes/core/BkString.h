#ifndef __BK_STRING_H__
#define __BK_STRING_H__

#include "pil\BkAtomicDataType.h"
#include "pil\__BkExport.h"

struct BkStringBuf
{
	char*	buffer;
	uint32	size;
};

// ~~~~~ Dcl(PUBLIC) ~~~~~

extern BK_API void	BkStringBuf_Release(struct BkStringBuf* string);
extern BK_API void	BkStringBuf_Set(struct BkStringBuf* string, char const* str);
extern BK_API BkBool	BkStringBuf_Compare(struct BkStringBuf const* string1, struct BkStringBuf const* string2);

#endif