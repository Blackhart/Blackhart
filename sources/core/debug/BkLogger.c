#include <stdio.h>

#include "core\debug\BkLogger.h"
#include "pil\BkFileSystem.h"

// ~~~~~ Dcl(PROTECTED) ~~~~~

extern void	LgInitialize(void);
extern void	LgUninitialize(void);

// ~~~~~ Dcl(PRIVATE) ~~~~~

static BkFlux*	__BkGlobalLogFile = NULL;

// ~~~~~ Def(ALL) ~~~~~

void	LgInitialize(void)
{
	BkOpenFlux(&__BkGlobalLogFile, "Log.txt", "w");
}

void	LgUninitialize(void)
{
	BkCloseFlux(&__BkGlobalLogFile);
}

void	BkLog(char const* const pFormat, ...)
{
	va_list	lArgList; // 4 bytes

	va_start(lArgList, pFormat);

	BkWriteToFlux_valist(__BkGlobalLogFile, pFormat, lArgList);

	va_end(lArgList);
}