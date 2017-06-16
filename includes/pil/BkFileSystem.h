#ifndef __BK_FILE_SYSTEM_H__
#define __BK_FILE_SYSTEM_H__

#define WINDOWS

#include <stdio.h>
#include <stdarg.h>

#include "BkAtomicDataType.h"

typedef FILE	BkFlux;

// ~~~~~ Dcl(PUBLIC) ~~~~~

extern void	BkOpenFlux(BkFlux** ppFlux, char const* pFilename, char const* pMode);
extern int8	BkCloseFlux(BkFlux** ppFlux);
extern int8	BkWriteToFlux_arglist(BkFlux const* pFlux, char const* pFormat, ...);
extern int8	BkWriteToFlux_valist(BkFlux const* pFlux, char const* pFormat, va_list const ArgList);
extern int8	BkReadFromFlux(BkFlux const* pFlux, char** ppBuffer, uint32* pBufferSize);
extern void	BkCombinePath(char* pDest, char const* pStr1, char const* pStr2);

#endif