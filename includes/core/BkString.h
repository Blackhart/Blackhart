#ifndef __BK_STRING_H__
#define __BK_STRING_H__

#include "pil\BkAtomicDataType.h"
#include "BkError.h"

struct sStringBuf
{
	char*	buf; // 4 bytes
	uint32	bufSize; // 4 bytes
};

typedef struct sStringBuf	BkStringBuf;

// ~~~~~ Dcl(PUBLIC) ~~~~~

extern void		BkReleaseStringBuf(BkStringBuf* pString);
extern void		BkSetStringBuf(BkStringBuf* pString, char const* pStr);
extern BkBool	BkCompareStringBuf(BkStringBuf const* pString1, BkStringBuf const* pString2);

#endif