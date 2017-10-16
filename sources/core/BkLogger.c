#include "pil\BkFileSystem.h"

#include "core\BkLogger.h"
#include "core\__BkLogger.h"

// ~~~~~ Def(INTERNAL) ~~~~~

static BkFlux*	__BkLogger_LogFile = NULL;

// ~~~~~ Def(ALL) ~~~~~

BkResult	_BkLogger_Initialize(void)
{
	return BkFileSystem_OpenFlux(&__BkLogger_LogFile, "Log.txt", "w");
}

BkResult	_BkLogger_Uninitialize(void)
{
	return BkFileSystem_CloseFlux(&__BkLogger_LogFile);
}

void	BkLog_arglist(char const* format, ...)
{
	va_list arglist;

	va_start(arglist, format);

	BkFileSystem_WriteToFlux_valist(__BkLogger_LogFile, format, arglist);

	va_end(arglist);
}

void	BkLog_valist(char const* format, va_list const arglist)
{
	BkFileSystem_WriteToFlux_valist(__BkLogger_LogFile, format, arglist);
}