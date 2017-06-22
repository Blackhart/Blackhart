#include "core\BkError.h"
#include "core\BkLogger.h"

// ~~~~~ Dcl(PRIVATE) ~~~~~

static void BkLogMsgError(char const* pPrefix, char const* pMsg, va_list const ArgList);

// ~~~~~ Def(ALL) ~~~~~

void	BkDie(char const* pMsg, ...)
{
	va_list	lList; // 4 bytes

	va_start(lList, pMsg);
	BkLogMsgError("Fatal: ", pMsg, lList);
	va_end(lList);

	exit(BK_FAILURE);
}

BkResult	BkError(char const* pMsg, ...)
{
	va_list	lList; // 4 bytes

	va_start(lList, pMsg);
	BkLogMsgError("Error: ", pMsg, lList);
	va_end(lList);

	return BK_FAILURE;
}

void	BkWarning(char const* pMsg, ...)
{
	va_list	lList; // 4 bytes

	va_start(lList, pMsg);
	BkLogMsgError("Warning: ", pMsg, lList);
	va_end(lList);
}

static void BkLogMsgError(char const* pPrefix, char const* pMsg, va_list const ArgList)
{
	BkLog_arglist(pPrefix);
	BkLog_valist(pMsg, ArgList);
	BkLog_arglist("\n");
}