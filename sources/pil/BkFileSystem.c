#include "pil\BkFileSystem.h"
#include "core\debug\BkLogger.h"

#include <string.h>

// ~~~~~ Def(ALL) ~~~~~

void	BkOpenFlux(BkFlux** ppFlux, char const* pFilename, char const* pMode)
{
	*ppFlux = fopen(pFilename, pMode);
}

int8	BkCloseFlux(BkFlux** ppFlux)
{
	if (ppFlux == NULL || *ppFlux == NULL)
		return;

	if (fclose(*ppFlux) == EOF)
	{
#ifdef _DEBUG
		BkLog("BkCloseFlux() : fclose has failed!\n");
#endif
		return -1;
	}

	*ppFlux = NULL;

	return 0;
}

int8	BkWriteToFlux_arglist(BkFlux const* pFlux, char const* pFormat, ...)
{
	va_list	lArgList; // 4 bytes

	va_start(lArgList, pFormat);

	if (vfprintf(pFlux, pFormat, lArgList) < 0 || ferror(pFlux) != 0)
	{
#ifdef _DEBUG
		BkLog("BkWriteToFlux_arglist() : vfprintf has failed!\n");
#endif
		clearerr(pFlux);
		va_end(lArgList);
		return -1;
	}

	va_end(lArgList);

	return 0;
}

int8	BkWriteToFlux_valist(BkFlux const* pFlux, char const* pFormat, va_list const ArgList)
{
	if (vfprintf(pFlux, pFormat, ArgList) < 0 || ferror(pFlux) != 0)
	{
#ifdef _DEBUG
		BkLog("BkWriteToFlux_valist() : vfprintf has failed!\n");
#endif
		clearerr(pFlux);
		return -1;
	}
	
	return 0;
}

int8	BkReadFromFlux(BkFlux const* pFlux, char** ppBuffer, uint32* pBufferSize)
{
	if (fseek(pFlux, 0, SEEK_END) != 0 || ferror(pFlux) != 0)
	{
#ifdef _DEBUG
		BkLog("BkReadFromFlux() : fseek has failed!\n");
#endif
		clearerr(pFlux);
		return -1;
	}
	
	*pBufferSize = ftell(pFlux);
	if (*pBufferSize < 0)
	{
#ifdef _DEBUG
		BkLog("BkReadFromFlux() : ftell has failed!\n");
#endif
		rewind(pFlux);
		return -1;
	}
	
	rewind(pFlux);
	
	*ppBuffer = malloc(((*pBufferSize) + 1) * sizeof(char));
	if (*ppBuffer == NULL)
	{
#ifdef _DEBUG
		BkLog("BkReadFromFlux() : Failed to allocate buffer!\n");
#endif
		*pBufferSize = 0;
		return -1;
	}

	*pBufferSize = fread(*ppBuffer, sizeof(char), *pBufferSize, pFlux);
	if (ferror(pFlux) != 0)
	{
#ifdef _DEBUG
		BkLog("BkReadFromFlux() : Failed to read the flux!\n");
#endif
		clearerr(pFlux);
		free(*ppBuffer);
		*ppBuffer = NULL;
		*pBufferSize = 0;
		return -1;
	}

	(*ppBuffer)[*pBufferSize] = '\0';

	return 0;
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
		uint8	lSeparatorIndex = strlen(pStr1); // 1 byte
		uint8	lEOLIndex = 0; // 1 byte

		strcpy(pDest, pStr1);
		pDest[lSeparatorIndex] = '/';
		++lSeparatorIndex;
		strcpy(pDest + lSeparatorIndex, pStr2);
		lEOLIndex = lSeparatorIndex + strlen(pStr2);
		pDest[lEOLIndex] = '\0';
	}
}