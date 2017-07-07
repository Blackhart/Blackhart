#include "core\BkShader.h"
#include "pil\BkFileSystem.h"
#include "core\BkLogger.h"
#include "core\BkList.h"

#include <string.h>

// ~~~~~ Dcl(INTERNAL) ~~~~~

extern void	(*_BkGraphicsAPI_CreateShader)(void** ppShader, BkShaderType const Type, char const* pShaderContent);
extern void	(*_BkGraphicsAPI_ReleaseShader)(void** ppShader);

static BkResult	__BkShader_LoadFromFlux(BkStringBuf* pContentBuf, char const* pPath);

// ~~~~~ Def(ALL) ~~~~~

BkShader*	BkShader_Create(char const* pPath, BkShaderType const Type)
{
	BkStringBuf	lContentBuf; // 8 bytes
	BkShader*	lpShader = NULL; // 4 bytes

	BkStringBuf_Set(&lContentBuf, NULL);

	if (BK_ERROR(__BkShader_LoadFromFlux(&lContentBuf, pPath)))
	{
		BkError(BK_ERROR_LOCATION "Failed to load shader from flux [ $%s$ ]");
		return NULL;
	}

	lpShader = malloc(sizeof(BkShader));
	if (BK_ISNULL(lpShader))
	{
		BkStringBuf_Release(&lContentBuf);
		BkDie(BK_ERROR_LOCATION "Memory system failed to allocate memory block!");
	}
	lpShader->type = Type;

	_BkGraphicsAPI_CreateShader(&lpShader->api, Type, lContentBuf.buf);

	BkStringBuf_Release(&lContentBuf);
	
	return lpShader;
}

static BkResult	__BkShader_LoadFromFlux(BkStringBuf* pContentBuf, char const* pPath)
{
	assert(!BK_ISNULL(pContentBuf));
	assert(!BK_ISNULL(pPath));

	BkFlux*		lFlux = NULL; // 4 bytes

	if (BK_ERROR(BkFileSystem_OpenFlux(&lFlux, pPath, "r")))
		return BkError(BK_ERROR_LOCATION "Failed to open flux [ $%s$ ]", pPath);

	if (BK_ERROR(BkFileSystem_ReadFromFlux(lFlux, &(pContentBuf->buf), &(pContentBuf->bufSize))))
	{
		BkFileSystem_CloseFlux(&lFlux);
		return BkError(BK_ERROR_LOCATION "Failed to read from flux [ $%s$ ]", pPath);
	}

	BkFileSystem_CloseFlux(&lFlux);

	return BK_SUCCESS;
}

void	BkShader_Release(BkShader** ppShader)
{
	if (BK_ISNULL(ppShader))
		return (void)BkError(BK_ERROR_LOCATION "ppShader is null");
	if (BK_ISNULL(*ppShader))
		return (void)BkWarning(BK_ERROR_LOCATION "*ppShader is null");

	_BkGraphicsAPI_ReleaseShader(&(*ppShader)->api);

	free(*ppShader);
	(*ppShader) = NULL;
}