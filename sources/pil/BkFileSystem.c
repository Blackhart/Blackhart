#include "pil\BkFileSystem.h"

#include <string.h>

// ~~~~~ Def(ALL) ~~~~~

void	BkOpenFlux(BkFlux const** const ppFlux, char const* const pFilename, char const* const pMode)
{
	*ppFlux = fopen(pFilename, pMode);
}

void	BkCloseFlux(BkFlux const* const* const ppFlux)
{
	fclose(*ppFlux);
}

void	BkWriteToFlux_arglist(BkFlux const* const pFlux, char const* const pFormat, ...)
{
	va_list	lArgList;

	va_start(lArgList, pFormat);

	vfprintf(pFlux, pFormat, lArgList);

	va_end(lArgList);
}

void	BkWriteToFlux_valist(BkFlux const* const pFlux, char const* const pFormat, va_list const ArgList)
{
	vfprintf(pFlux, pFormat, ArgList);
}

void	BkCombinePath(char* const pDest, char const* const pStr1, char const* const pStr2)
{
	if (pStr1 == NULL && pStr2 == NULL)
		pDest[0] = '\0';
	else if (pStr1 == NULL || pStr1[0] == '\0')
		strcpy(pDest, pStr2);
	else if (pStr2 == NULL || pStr2[0] == '\0')
		strcpy(pDest, pStr1);
	else
	{
		uint8	lSeparatorIndex = strlen(pStr1);
		uint8	lEOLIndex = 0;

		strcpy(pDest, pStr1);
		pDest[lSeparatorIndex] = '\\';
		++lSeparatorIndex;
		strcpy(pDest + lSeparatorIndex, pStr2);
		lEOLIndex = lSeparatorIndex + strlen(pStr2);
		pDest[lEOLIndex] = '\0';
	}
}