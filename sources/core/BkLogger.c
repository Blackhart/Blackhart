#include <stdio.h>

#include "core\BkLogger.h"
#include "pil\BkFileSystem.h"
#include "core\BkError.h"

// ~~~~~ Dcl(PROTECTED) ~~~~~

extern BkResult	LgInitialize(void);
extern BkResult	LgUninitialize(void);

// ~~~~~ Dcl(PRIVATE) ~~~~~

static BkFlux*	__BkGlobalLogFile = NULL;

// ~~~~~ Def(ALL) ~~~~~

BkResult	LgInitialize(void)
{
	return BkOpenFlux(&__BkGlobalLogFile, "Log.txt", "w");
}

BkResult	LgUninitialize(void)
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