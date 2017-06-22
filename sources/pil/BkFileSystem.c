#include "pil\BkFileSystem.h"
#include "core\BkLogger.h"

#include <stdlib.h>
#include <string.h>

// ~~~~~ Def(ALL) ~~~~~

BkResult	BkOpenFlux(BkFlux** ppFlux, char const* pFilename, char const* pMode)
{
	*ppFlux = fopen(pFilename, pMode);
	if (*ppFlux == NULL)
		return BkError(BK_ERROR_LOCATION "File system has failed to open the flux [ $%s$ ]", pFilename);
	return BK_SUCCESS;
}

BkResult	BkCloseFlux(BkFlux** ppFlux)
{
	if (ppFlux == NULL || *ppFlux == NULL)
		return FALSE;

	if (fclose(*ppFlux) == EOF)
		return BkError(BK_ERROR_LOCATION "File system has failed to close the flux");

	*ppFlux = NULL;

	return BK_SUCCESS;
}

void	BkWriteToFlux_arglist(BkFlux* pFlux, char const* pFormat, ...)
{
	va_list		lArgList; // 4 bytes
	BkResult	lResult = BK_SUCCESS; // 1 byte

	va_start(lArgList, pFormat);

	if (vfprintf(pFlux, pFormat, lArgList) < 0 || ferror(pFlux) != 0)
	{
		clearerr(pFlux);
		BkWarning(BK_ERROR_LOCATION "File system has failed to write in the flux");
	}

	va_end(lArgList);
}

void	BkWriteToFlux_valist(BkFlux* pFlux, char const* pFormat, va_list const ArgList)
{
	if (vfprintf(pFlux, pFormat, ArgList) < 0 || ferror(pFlux) != 0)
	{
		clearerr(pFlux);
		BkWarning(BK_ERROR_LOCATION "File system has failed to write in the flux");
	}
}

BkResult	BkReadFromFlux(BkFlux* pFlux, char** ppBuffer, uint32* pBufferSize)
{
	if (fseek(pFlux, 0, SEEK_END) != 0 || ferror(pFlux) != 0)
	{
		clearerr(pFlux);
		return BkError(BK_ERROR_LOCATION "File system has failed to read from the flux");
	}
	
	*pBufferSize = ftell(pFlux);
	if (*pBufferSize < 0)
	{
		rewind(pFlux);
		return BkError(BK_ERROR_LOCATION "File system has failed to read from the flux");
	}
	
	rewind(pFlux);
	
	*ppBuffer = malloc(((*pBufferSize) + 1) * sizeof(char));
	if (*ppBuffer == NULL)
	{
		*pBufferSize = 0;
		BkDie(BK_ERROR_LOCATION "Memory system has failed to allocate memory");
	}

	*pBufferSize = fread(*ppBuffer, sizeof(char), *pBufferSize, pFlux);
	if (ferror(pFlux) != 0)
	{
		clearerr(pFlux);
		free(*ppBuffer);
		*ppBuffer = NULL;
		*pBufferSize = 0;
		return BkError(BK_ERROR_LOCATION "File system has failed to read from the flux");
	}

	(*ppBuffer)[*pBufferSize] = '\0';

	return BK_SUCCESS;
}

void	BkCombinePath(char* pDest, char const* pStr1, char const* pStr2)
{
	if (pStr1 == NULL && pStr2 == NULL)
		pDest[0] = '\0';
	else if (pStr1 == NULL || pStr1[0] == '\0')
		strcpy(pDest, pStr2);
	else if (pStr2 == NULL || pStr2[0] == '\0')
		strcpy(pDest, pStr1);
	else
	{
		uint8	lSeparatorIndex = (uint8)strlen(pStr1); // 1 byte
		uint8	lEOLIndex = 0; // 1 byte

		strcpy(pDest, pStr1);
		pDest[lSeparatorIndex] = '/';
		++lSeparatorIndex;
		strcpy(pDest + lSeparatorIndex, pStr2);
		lEOLIndex = lSeparatorIndex + (uint8)strlen(pStr2);
		pDest[lEOLIndex] = '\0';
	}
}