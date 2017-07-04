#include <stdio.h>

#include "core\BkLogger.h"
#include "pil\BkFileSystem.h"
#include "core\BkError.h"

// ~~~~~ Dcl(INTERNAL) ~~~~~

extern BkResult	_BkInitializeLogger(void);
extern BkResult	_BkUninitializeLogger(void);

// ~~~~~ Def(INTERNAL) ~~~~~

static BkFlux*	__BkGlobalLogFile = NULL;

// ~~~~~ Def(ALL) ~~~~~

BkResult	_BkInitializeLogger(void)
{
	return BkOpenFlux(&__BkGlobalLogFile, "Log.txt", "w");
}

BkResult	_BkUninitializeLogger(void)
{
	return BkCloseFlux(&__BkGlobalLogFile);
}

void	BkLog_arglist(char const* pFormat, ...)
{
	va_list		lArgList; // 4 bytes

	va_start(lArgList, pFormat);

	BkWriteToFlux_valist(__BkGlobalLogFile, pFormat, lArgList);

	va_end(lArgList);
}

void	BkLog_valist(char const* pFormat, va_list const ArgList)
{
	BkWriteToFlux_valist(__BkGlobalLogFile, pFormat, ArgList);
}