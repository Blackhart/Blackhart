#include "core\BkShader.h"
#include "pil\BkFileSystem.h"
#include "core\BkLogger.h"

// ~~~~~ Def(ALL) ~~~~~

BkResult	BkCreateShader(BkShader** ppShader, char const* pPath)
{
	BkFlux*		lFlux = NULL; // 4 bytes
	uint32		lBufferSize = 0; // 4 bytes
	BkResult	lResult; // 1 byte

	lResult = BkOpenFlux(&lFlux, pPath, "r");
	if (lResult != BK_SUCCESS)
		return lResult;

	*ppShader = malloc(sizeof(BkShader));
	if (*ppShader == NULL)
	{
		BkCloseFlux(&lFlux);
		BkDie("BkCreateShader: Memory system failed to allocate memory");
	}

	lResult = BkReadFromFlux(lFlux, &(*ppShader)->shader, &lBufferSize);
	if (lResult != BK_SUCCESS)
	{
		free(*ppShader);
		*ppShader = NULL;
		return lResult;
	}

	lResult = BkCloseFlux(&lFlux);
	if (lResult != BK_SUCCESS)
	{
		free(*ppShader);
		*ppShader = NULL;
		return lResult;
	}

	return BK_SUCCESS;
}

void	BkReleaseShader(BkShader** ppShader)
{
	if (ppShader == NULL || *ppShader == NULL)
		return;
	free(*ppShader);
	*ppShader = NULL;
}