#include "pil\fs\file.h"

#include <stdio.h>
#include <string.h>

// ~~~~~ Def(ALL) ~~~~~

char*	combine_path(char const* const p1, char const* const p2)
{
	char*	lCombinePath = NULL;
	uint8	lLength = strlen(p1) + strlen(p2) + 2;

	lCombinePath = malloc(lLength * sizeof(char));
	if (lCombinePath == NULL)
		return NULL;

	strcpy(lCombinePath, p1);
	strcat(lCombinePath, "\\");
	strcat(lCombinePath, p2);
	strcat(lCombinePath, "\0");

	return lCombinePath;
}