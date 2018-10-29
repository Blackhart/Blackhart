// Standard headers.
#include <stdlib.h>
#include <string.h>

// blackhart headers.
#include "foundation\BkError.h"
#include "foundation\BkLogger.h"
#include "foundation\BkQueue.h"
#include "foundation\BkString.h"

// ~~~~~ Def(INTERNAL) ~~~~~

static struct BkQueue	__Bk_Error_Context;

void	_BkError_Initialize(void)
{
	BkQueue_Initialize(&__Bk_Error_Context);
}

void	_BkError_Uninitialize(void)
{
	BkQueue_Clear(&__Bk_Error_Context);
}

// ~~~~~ Def(PUBLIC) ~~~~~

void	BkError_PushContext(char* msg)
{
	BkQueue_Push(&__Bk_Error_Context, msg);
}

void	BkError_PopContext(void)
{
	BkQueue_Pop(&__Bk_Error_Context);
}

void	BkError_Fatal(char const* __restrict assert, char const* __restrict file, uint16 const line, char const* __restrict str)
{
	BK_ASSERT(BK_ISNULL(assert));
	BK_ASSERT(BK_ISNULL(file));
	BK_ASSERT(BK_ISNULL(str));

	while (!BkQueue_Empty(&__Bk_Error_Context))
	{
		BkLog((char*)(BkQueue_Front(&__Bk_Error_Context)));
		BkLog("\n");
		BkError_PopContext();
	}

	BkLog(BkString_CreateFormatted("Unexpected Error: %s\n\t", assert));

	if (strcmp(str, "") != 0)
		BkLog(str);

	BkLog(BkString_CreateFormatted("\n\tIn %s:%d", file, line));

	exit(BK_FAILURE);
}