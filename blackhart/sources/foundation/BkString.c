// Standard headers.
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

// blackhart headers.
#include "foundation\BkString.h"
#include "foundation\BkError.h"

// ~~~~~ Def(PUBLIC) ~~~~~

char const*	BkString_CreateFormatted(char const* format, ...)
{
	BK_ASSERT(BK_ISNULL(format));

	va_list arglist;

	va_start(arglist, format);

	char* str = NULL;

	size_t const size = vsnprintf(NULL, 0, format, arglist) + 1;
	
	str = malloc(size * sizeof(char));
	BK_ERROR(BK_ISNULL(str), "Memory system failed to allocate memory block");
	
	vsnprintf(str, size, format, arglist);

	va_end(arglist);

	return str;
}