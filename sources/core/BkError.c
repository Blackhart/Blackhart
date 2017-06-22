#include "core\BkError.h"
#include "core\BkLogger.h"

// ~~~~~ Def(ALL) ~~~~~

void	BkDie(char const* pMsg, ...)
{
	va_list	lList; // 4 bytes

	va_start(lList, pMsg);

	BkLog_arglist("Fatal: ");
	BkLog_valist(pMsg, lList);
	BkLog_arglist("\n");

	va_end(lList);

	exit(BK_FAILURE);
}

BkResult	BkError(char const* pMsg, ...)
{
	va_list	lList; // 4 bytes

	va_start(lList, pMsg);

	BkLog_arglist("Error: ");
	BkLog_valist(pMsg, lList);
	BkLog_arglist("\n");

	va_end(lList);

	return BK_FAILURE;
}

void	BkWarning(char const* pMsg, ...)
{
	va_list	lList; // 4 bytes

	va_start(lList, pMsg);

	BkLog_arglist("Warning: ");
	BkLog_valist(pMsg, lList);
	BkLog_arglist("\n");

	va_end(lList);
}