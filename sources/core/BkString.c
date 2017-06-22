#include "core\BkString.h"

#include <stdlib.h>

// ~~~~~ Def(ALL) ~~~~~

void	BkCreateStringBuf(BkStringBuf* pString)
{
	pString->buf = NULL;
	pString->bufSize = 0;
}

void	BkReleaseStringBuf(BkStringBuf* pString)
{
	if (pString->buf != NULL)
		free(pString->buf);
	pString->buf = NULL;
	pString->bufSize = 0;
}