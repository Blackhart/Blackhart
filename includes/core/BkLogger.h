#ifndef __BK_LOGGER_H__
#define __BK_LOGGER_H__

#include <stdarg.h>

// ~~~~~ Dcl(PUBLIC) ~~~~~

extern void	BkLog_arglist(char const* pFormat, ...);
extern void	BkLog_valist(char const* pFormat, va_list const ArgList);

#endif