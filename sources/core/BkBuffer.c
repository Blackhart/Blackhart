#include "core\BkBuffer.h"
#include "core\BkError.h"

#include "pil\__BkGraphicsAPI.h"

// ~~~~~ Def(ALL) ~~~~~

BkBuffer*	BkBuffer_Create(uint32 const Size, void const* pData)
{
	BkBuffer*	lpBuffer = malloc(sizeof(BkBuffer));
	if (BK_ISNULL(lpBuffer))
		BkDie(BK_ERROR_LOCATION "Memory system failed to allocate memory block");

	_BkGraphicsAPI_CreateBuffer(&(lpBuffer->api), Size, pData);

	return lpBuffer;
}

void	BkBuffer_Release(BkBuffer** ppBuffer)
{
	if (BK_ISNULL(ppBuffer))
		return (void)BkError(BK_ERROR_LOCATION "ppBuffer is null");
	if (BK_ISNULL(*ppBuffer))
		return (void)BkWarning(BK_ERROR_LOCATION "*ppBuffer is null");

	_BkGraphicsAPI_ReleaseBuffer(&(*ppBuffer)->api);

	free(*ppBuffer);
	*ppBuffer = NULL;
}