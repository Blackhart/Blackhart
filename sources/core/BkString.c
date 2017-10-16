#include <string.h>
#include <stdlib.h>

#include "core\BkString.h"
#include "core\BkError.h"

// ~~~~~ Def(ALL) ~~~~~

void	BkStringBuf_Set(struct BkStringBuf* string, char const* str)
{
	string->size = str == NULL ? 0 : strlen(str);

	if (string->size > 0)
	{
		string->buffer = malloc((string->size + 1) * sizeof(char));
		if (string->buffer == NULL)
			BkDie(BK_ERROR_LOCATION "Memory system failed to allocate memory block");

		memcpy(string->buffer, str, string->size);

		string->buffer[string->size] = '\0';
	}
	else
		string->buffer = NULL;
}

void	BkStringBuf_Release(struct BkStringBuf* string)
{
	if (string->buffer != NULL)
		free(string->buffer);
	string->buffer = NULL;
	string->size = 0;
}

BkBool	BkStringBuf_Compare(struct BkStringBuf const* string1, struct BkStringBuf const* string2)
{
	if (string1->size != string2->size)
		return FALSE;
	for (uint32 lIndex = 0; lIndex < string1->size; lIndex++)
	{
		if (string1->buffer[lIndex] != string2->buffer[lIndex])
			return FALSE;
	}
	return TRUE;
}