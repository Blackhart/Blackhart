#ifndef __BK_BUFFER_H__
#define __BK_BUFFER_H__

#include "pil\BkAtomicDataType.h"

#include "pil\__BkExport.h"

struct sBuffer
{
	void*	api;
};

typedef struct sBuffer	BkBuffer;

// ~~~~~ Dcl(PUBLIC) ~~~~~

extern BK_API BkBuffer*	BkBuffer_Create(uint32 const Size, void const* pData);
extern BK_API void		BkBuffer_Release(BkBuffer** ppBuffer);

#endif