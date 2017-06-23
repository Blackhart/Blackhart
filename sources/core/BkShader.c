#include "core\BkShader.h"
#include "pil\BkFileSystem.h"
#include "core\BkLogger.h"
#include "core\BkString.h"

// ~~~~~ Dcl(INTERNAL) ~~~~~

static BkResult	__BkLoadShaderFromFlux(BkStringBuf* pContentBuf, char const* pPath);

// ~~~~~ Def(INTERNAL) ~~~~~

static BkShader*	__shader = NULL;

// ~~~~~ Def(ALL) ~~~~~

BkResult	BkCreateShader(char const* pShaderName, char const* pPath)
{
	BkStringBuf	lContentBuf;

	BkCreateStringBuf(&lContentBuf);

	if (BK_FAILED(__BkLoadShaderFromFlux(&lContentBuf, pPath)))
		return BkError(BK_ERROR_LOCATION "Failed to load shader from flux [ $%s$ ]");

	__shader = malloc(sizeof(BkShader));
	if (__shader == NULL)
	{
		BkReleaseStringBuf(&lContentBuf);
		BkDie(BK_ERROR_LOCATION "Memory system failed to allocate memory");
	}

	return BK_SUCCESS;
}

static BkResult	__BkLoadShaderFromFlux(BkStringBuf* pContentBuf, char const* pPath)
{
	BkFlux*		lFlux = NULL; // 4 bytes

	if (BK_FAILED(BkOpenFlux(&lFlux, pPath, "r")))
		return BkError(BK_ERROR_LOCATION "Failed to open flux [ $%s$ ]", pPath);

	if (BK_FAILED(BkReadFromFlux(lFlux, &(pContentBuf->buf), &(pContentBuf->bufSize))))
	{
		BkCloseFlux(&lFlux);
		return BkError(BK_ERROR_LOCATION "Failed to read from flux [ $%s$ ]", pPath);
	}

	BkCloseFlux(&lFlux);

	return BK_SUCCESS;
}

void	BkReleaseShader(char const* pShaderName)
{
	if (__shader == NULL)
		return;
	free(__shader);
	__shader = NULL;
}