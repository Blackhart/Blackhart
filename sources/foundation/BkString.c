// Standard headers.
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

// Blackhart.foundation headers.
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

bool	BkString_Compare(char const* str1, char const* str2)
{
	BK_ASSERT(BK_ISNULL(str1));
	BK_ASSERT(BK_ISNULL(str2));

	size_t const str1_len = strlen(str1);
	size_t const str2_len = strlen(str2);

	if (str1_len != str2_len)
		return false;

	for (size_t i = 0; i < str1_len; i++)
	{
		if (str1[i] != str2[i])
			return false;
	}

	return true;
}