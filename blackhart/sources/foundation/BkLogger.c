// blackhart headers.
#include "foundation\BkError.h"
#include "foundation\BkFileSystem.h"
#include "foundation\BkLogger.h"

// ~~~~~ Def(INTERNAL) ~~~~~

static BkFlux*	__BkLogFile = NULL;

void	_BkLogger_Initialize(void)
{
	BkFileSystem_OpenFlux(&__BkLogFile, "Log.txt", "w");
}

void	_BkLogger_Uninitialize(void)
{
	BkFileSystem_CloseFlux(&__BkLogFile);
}

// ~~~~~ Def(PUBLIC) ~~~~~

void	BkLog(char const* str)
{
	if (!BK_ISNULL(__BkLogFile))
		BkFileSystem_WriteToFlux(__BkLogFile, str);
}