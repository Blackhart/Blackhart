#include "core\BkShader.h"
#include "pil\BkFileSystem.h"
#include "core\BkLogger.h"
#include "core\BkList.h"

#include <string.h>

// ~~~~~ Dcl(INTERNAL) ~~~~~

extern void	(*_BkCreateGraphicsAPIShader)(void** ppShader, BkShaderType const Type, BkStringBuf* pShaderContent);
extern void	(*_BkReleaseGraphicsAPIShader)(void** ppShader);
extern void	_BkGetShader(BkShader** ppShader, char const* pName);

static BkResult		__BkLoadShaderFromFlux(BkStringBuf* pContentBuf, char const* pPath);

static BkSimpleLinkedList*	__shaders = NULL;

// ~~~~~ Def(ALL) ~~~~~

BkResult	BkShader_Create(char const* pName, char const* pPath, BkShaderType const Type)
{
	BkStringBuf	lContentBuf; // 8 bytes
	BkShader*	lpShader = NULL; // 4 bytes

	BkSetStringBuf(&lContentBuf, NULL);

	if (BK_ERROR(__BkLoadShaderFromFlux(&lContentBuf, pPath)))
		return BkError(BK_ERROR_LOCATION "Failed to load shader from flux [ $%s$ ]");

	lpShader = malloc(sizeof(BkShader));
	if (BK_ISNULL(lpShader))
	{
		BkReleaseStringBuf(&lContentBuf);
		BkDie(BK_ERROR_LOCATION "Memory system failed to allocate memory block!");
	}
	lpShader->type = Type;

	_BkCreateGraphicsAPIShader(&lpShader->api, Type, &lContentBuf);

	BkReleaseStringBuf(&lContentBuf);

	BkSetStringBuf(&lpShader->name, pName);
	
	BkSimpleLinkedList_PushBack(&__shaders, lpShader);

	return BK_SUCCESS;
}

static BkResult	__BkLoadShaderFromFlux(BkStringBuf* pContentBuf, char const* pPath)
{
	assert(!BK_ISNULL(pContentBuf));
	assert(!BK_ISNULL(pPath));

	BkFlux*		lFlux = NULL; // 4 bytes

	if (BK_ERROR(BkOpenFlux(&lFlux, pPath, "r")))
		return BkError(BK_ERROR_LOCATION "Failed to open flux [ $%s$ ]", pPath);

	if (BK_ERROR(BkReadFromFlux(lFlux, &(pContentBuf->buf), &(pContentBuf->bufSize))))
	{
		BkCloseFlux(&lFlux);
		return BkError(BK_ERROR_LOCATION "Failed to read from flux [ $%s$ ]", pPath);
	}

	BkCloseFlux(&lFlux);

	return BK_SUCCESS;
}

void	BkShader_Release(char const* pName)
{
	BkShader* lpShader = NULL;
	_BkGetShader(&lpShader, pName); // 4 bytes
	if (BK_ISNULL(lpShader))
		return;

	BkReleaseStringBuf(&lpShader->name);
	_BkReleaseGraphicsAPIShader(&lpShader->api);
	BkSimpleLinkedList_RemoveElem(&__shaders, &lpShader);
	lpShader = NULL;
}

void	_BkGetShader(BkShader** ppShader, char const* pName)
{
	assert(!BK_ISNULL(ppShader));
	assert(!BK_ISNULL(pName));

	BkSimpleLinkedList*	lpCurrent = __shaders; // 4 bytes

	while (lpCurrent != NULL)
	{
		assert(!BK_ISNULL((BkShader*)lpCurrent->elem));
		assert(!BK_ISNULL(((BkShader*)lpCurrent->elem)->name.buf));

		if (strcmp(((BkShader*)lpCurrent->elem)->name.buf, pName) == 0)
		{
			*ppShader = lpCurrent->elem;
			return;
		}

		lpCurrent = lpCurrent->next;
	}

	*ppShader = NULL;
}