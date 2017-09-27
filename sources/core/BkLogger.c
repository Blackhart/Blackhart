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

void	BkLog_arglist(char const* pFormat, ...)
{
	va_list		lArgList; // 4 bytes

	va_start(lArgList, pFormat);

	BkFileSystem_WriteToFlux_valist(__BkLogger_LogFile, pFormat, lArgList);

	va_end(lArgList);
}

void	BkLog_valist(char const* pFormat, va_list const ArgList)
{
	BkFileSystem_WriteToFlux_valist(__BkLogger_LogFile, pFormat, ArgList);
}