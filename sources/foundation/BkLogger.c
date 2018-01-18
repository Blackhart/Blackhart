// Blackhart.foundation headers.
#include "foundation\BkError.h"
#include "foundation\BkFileSystem.h"
#include "foundation\BkLogger.h"

// ~~~~~ Def(INTERNAL) ~~~~~

static BkFlux*	__BkLogger_LogFile = NULL;

void	_BkLogger_Initialize(void)
{
	BkFileSystem_OpenFlux(&__BkLogger_LogFile, "Log.txt", "w");
}

void	_BkLogger_Uninitialize(void)
{
	BkFileSystem_CloseFlux(&__BkLogger_LogFile);
}

// ~~~~~ Def(PUBLIC) ~~~~~

void	BkLog(char const* str)
{
	if (!BK_ISNULL(__BkLogger_LogFile))
		BkFileSystem_WriteToFlux(__BkLogger_LogFile, str);
}