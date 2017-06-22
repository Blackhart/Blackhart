#ifndef __BK_FILE_SYSTEM_H__
#define __BK_FILE_SYSTEM_H__

#define WINDOWS

#include <stdio.h>
#include <stdarg.h>

#include "BkAtomicDataType.h"
#include "core\BkError.h"

typedef FILE	BkFlux;

// ~~~~~ Dcl(PUBLIC) ~~~~~

extern BkResult	BkOpenFlux(BkFlux** ppFlux, char const* pFilename, char const* pMode);
extern BkResult	BkCloseFlux(BkFlux** ppFlux);
extern void		BkWriteToFlux_arglist(BkFlux* pFlux, char const* pFormat, ...);
extern void		BkWriteToFlux_valist(BkFlux* pFlux, char const* pFormat, va_list const ArgList);
extern BkResult	BkReadFromFlux(BkFlux* pFlux, char** ppBuffer, uint32* pBufferSize);
extern void		BkCombinePath(char* pDest, char const* pStr1, char const* pStr2);

#endif