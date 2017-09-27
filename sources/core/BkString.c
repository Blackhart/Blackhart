#include <string.h>
#include <stdlib.h>

#include "core\BkString.h"
#include "core\BkError.h"

// ~~~~~ Def(ALL) ~~~~~

void	BkStringBuf_Set(BkStringBuf* pString, char const* pStr)
{
	pString->bufSize = pStr == NULL ? 0 : strlen(pStr);

	if (pString->bufSize > 0)
	{
		pString->buf = malloc((pString->bufSize + 1) * sizeof(char));
		if (pString->buf == NULL)
			BkDie(BK_ERROR_LOCATION "Memory system failed to allocate memory block");

		memcpy(pString->buf, pStr, pString->bufSize);

		pString->buf[pString->bufSize] = '\0';
	}
	else
		pString->buf = NULL;
}

void	BkStringBuf_Release(BkStringBuf* pString)
{
	if (pString->buf != NULL)
		free(pString->buf);
	pString->buf = NULL;
	pString->bufSize = 0;
}

BkBool	BkStringBuf_Compare(BkStringBuf const* pString1, BkStringBuf const* pString2)
{
	if (pString1->bufSize != pString2->bufSize)
		return FALSE;
	for (uint32 lIndex = 0; lIndex < pString1->bufSize; lIndex++)
	{
		if (pString1->buf[lIndex] != pString2->buf[lIndex])
			return FALSE;
	}
	return TRUE;
}