#include <stdio.h>

#include "core\debug\BkLogger.h"
#include "pil\BkFileSystem.h"

// ~~~~~ Dcl(PROTECTED) ~~~~~

extern void	FsInitialize(void);
extern void	FsUninitialize(void);

// ~~~~~ Dcl(PRIVATE) ~~~~~

static BkFlux*	__BkGlobalLogFile = NULL;

// ~~~~~ Def(ALL) ~~~~~

void	FsInitialize(void)
{
	BkOpenFlux(&__BkGlobalLogFile, "Global.txt", "w");
}

void	FsUninitialize(void)
{
	BkCloseFlux(&__BkGlobalLogFile);
}

void	BkLog(char const* const pFormat, ...)
{
	va_list	lArgList;

	va_start(lArgList, pFormat);

	BkWriteToFlux_valist(__BkGlobalLogFile, pFormat, lArgList);

	va_end(lArgList);
}