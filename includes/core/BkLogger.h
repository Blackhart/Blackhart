#ifndef __BK_LOGGER_H__
#define __BK_LOGGER_H__

#include <stdarg.h>

#include "pil\__BkExport.h"

// ~~~~~ Dcl(PUBLIC) ~~~~~

extern BK_API void	BkLog_arglist(char const* format, ...);
extern BK_API void	BkLog_valist(char const* format, va_list const arglist);

#endif