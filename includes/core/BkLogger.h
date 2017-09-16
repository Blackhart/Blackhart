#ifndef __BK_LOGGER_H__
#define __BK_LOGGER_H__

#include <stdarg.h>

#include "pil\__BkExport.h"

// ~~~~~ Dcl(PUBLIC) ~~~~~

extern BK_API void	BkLog_arglist(char const* pFormat, ...);
extern BK_API void	BkLog_valist(char const* pFormat, va_list const ArgList);

#endif