#ifndef __BK_FILE_SYSTEM_H__
#define __BK_FILE_SYSTEM_H__

#define WINDOWS

#include <stdio.h>
#include <stdarg.h>

#include "BkAtomicDataType.h"

typedef FILE	BkFlux;

// ~~~~~ Dcl(PUBLIC) ~~~~~

extern void	BkOpenFlux(BkFlux const** const ppFlux, char const* const pFilename, char const* const pMode);
extern void	BkCloseFlux(BkFlux const* const* const ppFlux);
extern void	BkWriteToFlux_arglist(BkFlux const* const pFlux, char const* const pFormat, ...);
extern void	BkWriteToFlux_valist(BkFlux const* const pFlux, char const* const pFormat, va_list const ArgList);
extern void	BkCombinePath(char* const pDest, char const* const pStr1, char const* const pStr2);

#endif