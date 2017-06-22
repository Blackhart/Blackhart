#ifndef __BK_STRING_H__
#define __BK_STRING_H__

#include "pil\BkAtomicDataType.h"

struct sStringBuf
{
	char*	buf; // 4 bytes
	uint32	bufSize; // 4 bytes
};

typedef struct sStringBuf	BkStringBuf;

// ~~~~~ Dcl(PUBLIC) ~~~~~

extern void	BkCreateStringBuf(BkStringBuf* pString);
extern void	BkReleaseStringBuf(BkStringBuf* pString);

#endif