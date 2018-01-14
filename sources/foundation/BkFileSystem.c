#define __STDC_WANT_LIB_EXT1__ 1

// Standard headers.
#include <stdlib.h>
#include <string.h>

// Blackhart.foundation headers.
#include "foundation\BkError.h"
#include "foundation\BkFileSystem.h"
#include "foundation\BkLogger.h"
#include "foundation\BkString.h"

// ~~~~~ Def(PUBLIC) ~~~~~

bool	BkFileSystem_FluxExists(char const* filename)
{
	BK_ASSERT(BK_ISNULL(filename));

	FILE* tmp = NULL;
	tmp = fopen(filename, "r");

	if (BK_ISNULL(tmp))
		return false;
	else
	{
		fclose(tmp);
		return true;
	}
}

void	BkFileSystem_OpenFlux(BkFlux** flux, char const* filename, char const* mode)
{
	BK_ASSERT(BK_ISNULL(flux));
	BK_ASSERT(BK_ISNULL(filename));
	BK_ASSERT(BK_ISNULL(mode));

#ifdef __STDC_LIB_EXT1__
	set_constraint_handler_s(abort_handler_s);
	fopen_s(flux, filename, mode);
#else
	*flux = fopen(filename, mode);
	BK_ERROR(BK_ISNULL(*flux), BkString_CreateFormatted("File system has failed to open the flux: %s", filename));
#endif
}

void	BkFileSystem_CloseFlux(BkFlux** flux)
{
	BK_ASSERT(BK_ISNULL(flux) || BK_ISNULL(*flux));

	BK_ERROR(fclose(*flux), "File system has failed to close the flux");

	*flux = NULL;
}

void	BkFileSystem_WriteToFlux(BkFlux* flux, char const* str)
{
	BK_ASSERT(BK_ISNULL(flux));

	BK_ERROR(fprintf(flux, str) < 0 || ferror(flux) != 0, "File system has failed to write in the flux");
}

void	BkFileSystem_ReadFromPath(char const* path, char** buffer, size_t* buffer_size)
{
	BK_ASSERT(BK_ISNULL(path));
	BK_ASSERT(BK_ISNULL(buffer));
	BK_ASSERT(BK_ISNULL(buffer_size));

	BkFlux*	flux = NULL;

	BkFileSystem_OpenFlux(&flux, path, "r");

	BkFileSystem_ReadFromFlux(flux, buffer, buffer_size);

	BkFileSystem_CloseFlux(&flux);
}

void	BkFileSystem_ReadFromFlux(BkFlux* flux, char** buffer, size_t* buffer_size)
{
	BK_ASSERT(BK_ISNULL(flux));
	BK_ASSERT(BK_ISNULL(buffer));
	BK_ASSERT(BK_ISNULL(buffer_size));

	BK_ERROR(fseek(flux, 0, SEEK_END) != 0 || ferror(flux) != 0, "File system has failed to read from the flux");
	
	*buffer_size = ftell(flux);
	BK_ERROR(*buffer_size < 0, "File system has failed to read from the flux");
	
	rewind(flux);
	
	*buffer = malloc(((*buffer_size) + 1) * sizeof(char));
	BK_ERROR(BK_ISNULL(*buffer), "Memory system has failed to allocate memory block");

	*buffer_size = fread(*buffer, sizeof(char), *buffer_size, flux);
	BK_ERROR(ferror(flux) != 0, "File system has failed to read from the flux");

	(*buffer)[*buffer_size] = '\0';
}

void	BkFileSystem_CombinePath(char* dst, char const* str1, char const* str2)
{
	size_t str1_s = 0;
	size_t str2_s = 0;

	if (str1 != NULL)
		str1_s = strlen(str1);

	if (str2 != NULL)
		str2_s = strlen(str2);

	size_t dst_s = str1_s + str2_s + 1;

#ifdef __STDC_LIB_EXT1__
	set_constraint_handler_s(abort_handler_s);
	if (str1_s > 0 && str2_s == 0)
		strcpy_s(dst, str1_s, str1);
	else if (str2_s > 0 && str1_s == 0)
		strcpy_s(dst, str2_s, str2);
	else if (str1_s > 0 && str2_s > 0)
	{
		dst_s += 1;
		strcpy_s(dst, str1_s, str1);
		dst[str1_s] = '/';
		strcpy_s(dst + str1_s + 1, str2_s, str2);
	}
#else
	if (str1_s > 0 && str2_s == 0)
		strcpy(dst, str1);
	else if (str2_s > 0 && str1_s == 0)
		strcpy(dst, str2);
	else if (str1_s > 0 && str2_s > 0)
	{
		dst_s += 1;
		strcpy(dst, str1);
		dst[str1_s] = '/';
		strcpy(dst + str1_s + 1, str2);
	}
#endif

	dst[dst_s - 1] = '\0';
}