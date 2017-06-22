#include "core\BkShader.h"
#include "pil\BkFileSystem.h"
#include "core\BkLogger.h"

// ~~~~~ Def(ALL) ~~~~~

BkResult	BkCreateShader(BkShader** ppShader, char const* pPath)
{
	BkFlux*		lFlux = NULL; // 4 bytes
	uint32		lBufferSize = 0; // 4 bytes

	if (BK_FAILED(BkOpenFlux(&lFlux, pPath, "r")))
		return BkError(BK_ERROR_LOCATION "Failed to open flux [ $%s$ ]", pPath);

	*ppShader = malloc(sizeof(BkShader));
	if (*ppShader == NULL)
	{
		BkCloseFlux(&lFlux);
		BkDie(BK_ERROR_LOCATION "Memory system failed to allocate memory");
	}

	if (BK_FAILED(BkReadFromFlux(lFlux, &(*ppShader)->shader, &lBufferSize)))
	{
		BkError(BK_ERROR_LOCATION "Failed to read from flux [ $%s$ ]", pPath);
		goto cleanup;
	}

	BkCloseFlux(&lFlux);

	return BK_SUCCESS;

cleanup:
	free(*ppShader);
	*ppShader = NULL;
	BkCloseFlux(&lFlux);
	return BK_FAILURE;
}

void	BkReleaseShader(BkShader** ppShader)
{
	if (ppShader == NULL || *ppShader == NULL)
		return;
	free(*ppShader);
	*ppShader = NULL;
}