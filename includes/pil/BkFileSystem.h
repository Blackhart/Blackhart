#ifndef __BK_FILE_SYSTEM_H__
#define __BK_FILE_SYSTEM_H__

#include <stdio.h>
#include <stdarg.h>

#include "pil\BkAtomicDataType.h"
#include "pil\__BkExport.h"

#include "core\BkError.h"

typedef FILE	BkFlux;

// ~~~~~ Dcl(PUBLIC) ~~~~~

extern BK_API BkResult	BkFileSystem_OpenFlux(BkFlux** ppFlux, char const* pFilename, char const* pMode);
extern BK_API BkResult	BkFileSystem_CloseFlux(BkFlux** ppFlux);
extern BK_API void		BkFileSystem_WriteToFlux_arglist(BkFlux* pFlux, char const* pFormat, ...);
extern BK_API void		BkFileSystem_WriteToFlux_valist(BkFlux* pFlux, char const* pFormat, va_list const ArgList);
extern BK_API BkResult	BkFileSystem_ReadFromPath(char const* pPath, char** ppBuffer, uint32* pBufferSize);
extern BK_API BkResult	BkFileSystem_ReadFromFlux(BkFlux* pFlux, char** ppBuffer, uint32* pBufferSize);
extern BK_API void		BkFileSystem_CombinePath(char* pDest, char const* pStr1, char const* pStr2);

#endif