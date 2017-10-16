#ifndef __BK_FILE_SYSTEM_H__
#define __BK_FILE_SYSTEM_H__

#include <stdio.h>
#include <stdarg.h>

#include "pil\BkAtomicDataType.h"
#include "pil\__BkExport.h"

#include "core\BkError.h"

typedef FILE	BkFlux;

// ~~~~~ Dcl(PUBLIC) ~~~~~

extern BK_API BkResult	BkFileSystem_OpenFlux(BkFlux** flux, char const* filename, char const* mode);
extern BK_API BkResult	BkFileSystem_CloseFlux(BkFlux** flux);
extern BK_API void	BkFileSystem_WriteToFlux_arglist(BkFlux* flux, char const* format, ...);
extern BK_API void	BkFileSystem_WriteToFlux_valist(BkFlux* flux, char const* format, va_list const arglist);
extern BK_API BkResult	BkFileSystem_ReadFromPath(char const* path, char** buffer, uint32* buffer_size);
extern BK_API BkResult	BkFileSystem_ReadFromFlux(BkFlux* flux, char** buffer, uint32* buffer_size);
extern BK_API void	BkFileSystem_CombinePath(char* dest, char const* str1, char const* str2);

#endif