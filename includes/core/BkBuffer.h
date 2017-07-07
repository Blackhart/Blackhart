#ifndef __BK_BUFFER_H__
#define __BK_BUFFER_H__

#include "pil\BkAtomicDataType.h"

struct sBuffer
{
	void*	api;
};

typedef struct sBuffer	BkBuffer;

// ~~~~~ Dcl(PUBLIC) ~~~~~

extern BkBuffer*	BkBuffer_Create(uint32 const Size, void const* pData);
extern void			BkBuffer_Release(BkBuffer** ppBuffer);

#endif