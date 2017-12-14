// Blackhart.foundation headers.
#include "foundation\__BkLogger.h"
#include "foundation\BkFileSystem.h"
#include "foundation\BkLogger.h"


// ~~~~~ Def(INTERNAL) ~~~~~

static BkFlux*	__BkLogger_LogFile = NULL;

// ~~~~~ Def(ALL) ~~~~~

void	_BkLogger_Initialize(void)
{
	BkFileSystem_OpenFlux(&__BkLogger_LogFile, "Log.txt", "w");
}

void	_BkLogger_Uninitialize(void)
{
	BkFileSystem_CloseFlux(&__BkLogger_LogFile);
}

void	BkLog(char const* str)
{
	if (!BK_ISNULL(__BkLogger_LogFile))
		BkFileSystem_WriteToFlux(__BkLogger_LogFile, str);
}