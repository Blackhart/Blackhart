#include "core\graphics\BkShader.h"
#include "pil\BkFileSystem.h"
#include "core\debug\BkLogger.h"

// ~~~~~ Def(ALL) ~~~~~

int8	BkCreateShader(BkShader** ppShader, char const* pPath)
{
	BkFlux*		lFlux = NULL; // 4 bytes
	uint32		lBufferSize = 0;

	BkOpenFlux(&lFlux, pPath, "r");
	if (lFlux == NULL)
	{
#ifdef _DEBUG
		BkLog("BkCreateShader() : BkOpenFlux has failed!\n");
#endif
		return -1;
	}

	*ppShader = malloc(sizeof(BkShader));
	if (*ppShader == NULL)
	{
#ifdef _DEBUG
		BkLog("BkCreateShader() : failed to allocate BkShader!\n");
#endif
		BkCloseFlux(&lFlux);
		return -1;
	}

	if (BkReadFromFlux(lFlux, &(*ppShader)->shader, &lBufferSize) != 0)
	{
#ifdef _DEBUG
		BkLog("BkCreateShader() : BkReadFromFile has failed!\n");
#endif
		free(*ppShader);
		*ppShader = NULL;
		return -1;
	}

	if (BkCloseFlux(&lFlux) != 0)
	{
#ifdef _DEBUG
		BkLog("BkCreateShader() : BkCloseFlux has failed!\n");
#endif
		free(*ppShader);
		*ppShader = NULL;
		return -1;
	}

	return 0;
}

void	BkReleaseShader(BkShader** ppShader)
{
	if (ppShader == NULL || *ppShader == NULL)
		return;
	free(*ppShader);
	*ppShader = NULL;
}