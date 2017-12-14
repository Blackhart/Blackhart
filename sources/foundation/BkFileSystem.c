#define __STDC_WANT_LIB_EXT1__ 1

// Standard headers.
#include <stdlib.h>
#include <string.h>

// Blackhart.foundation headers.
#include "foundation\BkFileSystem.h"
#include "foundation\BkLogger.h"
#include "foundation\BkString.h"


// ~~~~~ Def(ALL) ~~~~~

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
	BK_ERROR(BK_ISNULL(*buffer), "Memory system has failed to allocate memory");

	*buffer_size = fread(*buffer, sizeof(char), *buffer_size, flux);
	BK_ERROR(ferror(flux) != 0, "File system has failed to read from the flux");

	(*buffer)[*buffer_size] = '\0';
}

void	BkFileSystem_CombinePath(char* dest, char const* str1, char const* str2)
{
#ifdef __STDC_LIB_EXT1__
	set_constraint_handler_s(abort_handler_s);
	if (str1 == NULL && str2 == NULL)
		dest[0] = '\0';
	else if (str1 == NULL || str1[0] == '\0')
		strcpy_s(dest, RSIZE_MAX, str2);
	else if (str2 == NULL || str2[0] == '\0')
		strcpy_s(dest, RSIZE_MAX, str1);
	else
	{
		uint8	separator_index = (uint8)strlen(str1);
		uint8	end_of_line_index = 0;

		strcpy_s(dest, RSIZE_MAX, str1);
		dest[separator_index] = '/';
		++separator_index;
		strcpy_s(dest + separator_index, RSIZE_MAX, str2);
		end_of_line_index = separator_index + (uint8)strlen(str2);
		dest[end_of_line_index] = '\0';
	}
#else
	if (str1 == NULL && str2 == NULL)
		dest[0] = '\0';
	else if (str1 == NULL || str1[0] == '\0')
		strcpy(dest, str2);
	else if (str2 == NULL || str2[0] == '\0')
		strcpy(dest, str1);
	else
	{
		uint8	separator_index = (uint8)strlen(str1);
		uint8	end_of_line_index = 0;

		strcpy(dest, str1);
		dest[separator_index] = '/';
		++separator_index;
		strcpy(dest + separator_index, str2);
		end_of_line_index = separator_index + (uint8)strlen(str2);
		dest[end_of_line_index] = '\0';
	}
#endif
}