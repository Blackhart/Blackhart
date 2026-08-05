// Standard headers.
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

// blackhart headers.
#include "foundation/BkString.h"
#include "foundation/BkError.h"

// ~~~~~ Def(PUBLIC) ~~~~~

char const*	BkString_CreateFormatted(char const* format, ...)
{
	BK_ASSERT(BK_ISNULL(format));

	va_list arglist;
	va_list arglist_copy;

	va_start(arglist, format);

	char* str = NULL;

	/* First pass: compute required size. */
	size_t const size = (size_t)vsnprintf(NULL, 0, format, arglist) + 1;

	/* We must copy or reinitialize the va_list before using it again. */
	va_end(arglist);
	va_start(arglist, format);
	va_copy(arglist_copy, arglist);
	
	str = malloc(size * sizeof(char));
	BK_FATAL(BK_ISNULL(str), ((struct BkErrorInfo){
		.what = "Fatal error",
		.why = "Memory system failed to allocate memory block",
		.result = "Process aborted",
	}));
	
	/* Second pass: actually format into the allocated buffer. */
	vsnprintf(str, size, format, arglist_copy);

	va_end(arglist_copy);
	va_end(arglist);

	return str;
}

void	BkString_Free(char const* str)
{
	BK_ASSERT(BK_ISNULL(str));

	free((void*)str);
}

bool	BkString_Compare(char const* str1, char const* str2)
{
	BK_ASSERT(BK_ISNULL(str1));
	BK_ASSERT(BK_ISNULL(str2));

	return strcmp(str1, str2) == 0;
}