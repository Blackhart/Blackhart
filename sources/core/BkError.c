#include "core\BkError.h"
#include "core\BkLogger.h"

// ~~~~~ Dcl(INTERNAL) ~~~~~

static void __BkLogMsgError(char const* prefix, char const* msg, va_list const arglist);

// ~~~~~ Def(ALL) ~~~~~

void	BkDie(char const* msg, ...)
{
	va_list	arglist;

	va_start(arglist, msg);
	__BkLogMsgError("FATAL: ", msg, arglist);
	va_end(arglist);

	exit(BK_FAILURE);
}

BkResult	BkError(char const* msg, ...)
{
	va_list	arglist;

	va_start(arglist, msg);
	__BkLogMsgError("ERROR: ", msg, arglist);
	va_end(arglist);

	return BK_FAILURE;
}

void	BkWarning(char const* msg, ...)
{
	va_list	arglist;

	va_start(arglist, msg);
	__BkLogMsgError("WARNING: ", msg, arglist);
	va_end(arglist);
}

static void __BkLogMsgError(char const* prefix, char const* msg, va_list const arglist)
{
	BkLog_arglist(prefix);
	BkLog_valist(msg, arglist);
	BkLog_arglist("\n");
}