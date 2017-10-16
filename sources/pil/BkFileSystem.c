#include <stdlib.h>
#include <string.h>

#include "pil\BkFileSystem.h"

#include "core\BkLogger.h"

// ~~~~~ Def(ALL) ~~~~~

BkResult	BkFileSystem_OpenFlux(BkFlux** flux, char const* filename, char const* mode)
{
	if (BK_ISNULL(flux))
		return BkError(BK_ERROR_LOCATION "ppFlux == NULL");
	if (BK_ISNULL(filename))
		return BkError(BK_ERROR_LOCATION "pFilename == NULL");
	if (BK_ISNULL(mode))
		return BkError(BK_ERROR_LOCATION "pMode == NULL");

	*flux = fopen(filename, mode);
	if (BK_ISNULL(*flux))
		return BkError(BK_ERROR_LOCATION "File system has failed to open the flux [ $%s$ ]", filename);

	return BK_SUCCESS;
}

BkResult	BkFileSystem_CloseFlux(BkFlux** flux)
{
	if (BK_ISNULL(flux) || BK_ISNULL(*flux))
		return BkError(BK_ERROR_LOCATION "ppFlux == NULL");

	if (fclose(*flux) == EOF)
		return BkError(BK_ERROR_LOCATION "File system has failed to close the flux");

	*flux = NULL;

	return BK_SUCCESS;
}

void	BkFileSystem_WriteToFlux_arglist(BkFlux* flux, char const* format, ...)
{
	if (BK_ISNULL(flux) || BK_ISNULL(format))
		return;

	va_list		arglist;
	BkResult	result = BK_SUCCESS;

	va_start(arglist, format);

	if (vfprintf(flux, format, arglist) < 0 || ferror(flux) != 0)
	{
		clearerr(flux);
		BkWarning(BK_ERROR_LOCATION "File system has failed to write in the flux");
	}

	va_end(arglist);
}

void	BkFileSystem_WriteToFlux_valist(BkFlux* flux, char const* format, va_list const arglist)
{
	if (BK_ISNULL(flux) || BK_ISNULL(format))
		return;

	if (vfprintf(flux, format, arglist) < 0 || ferror(flux) != 0)
	{
		clearerr(flux);
		BkWarning(BK_ERROR_LOCATION "File system has failed to write in the flux");
	}
}

BkResult	BkFileSystem_ReadFromPath(char const* path, char** buffer, uint32* buffer_size)
{
	if (BK_ISNULL(path))
		return BkError(BK_ERROR_LOCATION "pPath == NULL");
	if (BK_ISNULL(buffer))
		return BkError(BK_ERROR_LOCATION "ppBuffer == NULL");
	if (BK_ISNULL(buffer_size))
		return BkError(BK_ERROR_LOCATION "pBufferSize == NULL");

	BkFlux*		flux = NULL; // 4 bytes

	if (BK_ERROR(BkFileSystem_OpenFlux(&flux, path, "r")))
		return BkError(BK_ERROR_LOCATION "Failed to open flux [ $%s$ ]", path);

	if (BK_ERROR(BkFileSystem_ReadFromFlux(flux, buffer, buffer_size)))
	{
		BkFileSystem_CloseFlux(&flux);
		return BkError(BK_ERROR_LOCATION "Failed to read from flux [ $%s$ ]", path);
	}

	BkFileSystem_CloseFlux(&flux);

	return BK_SUCCESS;
}

BkResult	BkFileSystem_ReadFromFlux(BkFlux* flux, char** buffer, uint32* buffer_size)
{
	if (BK_ISNULL(flux))
		return BkError(BK_ERROR_LOCATION "pFlux == NULL");
	if (BK_ISNULL(buffer))
		return BkError(BK_ERROR_LOCATION "ppBuffer == NULL");
	if (BK_ISNULL(buffer_size))
		return BkError(BK_ERROR_LOCATION "pBufferSize == NULL");

	if (fseek(flux, 0, SEEK_END) != 0 || ferror(flux) != 0)
	{
		clearerr(flux);
		return BkError(BK_ERROR_LOCATION "File system has failed to read from the flux");
	}
	
	*buffer_size = ftell(flux);
	if (*buffer_size < 0)
	{
		rewind(flux);
		return BkError(BK_ERROR_LOCATION "File system has failed to read from the flux");
	}
	
	rewind(flux);
	
	*buffer = malloc(((*buffer_size) + 1) * sizeof(char));
	if (*buffer == NULL)
	{
		*buffer_size = 0;
		BkDie(BK_ERROR_LOCATION "Memory system has failed to allocate memory");
	}

	*buffer_size = fread(*buffer, sizeof(char), *buffer_size, flux);
	if (ferror(flux) != 0)
	{
		clearerr(flux);
		free(*buffer);
		*buffer = NULL;
		*buffer_size = 0;
		return BkError(BK_ERROR_LOCATION "File system has failed to read from the flux");
	}

	(*buffer)[*buffer_size] = '\0';

	return BK_SUCCESS;
}

void	BkFileSystem_CombinePath(char* dest, char const* str1, char const* str2)
{
	if (str1 == NULL && str2 == NULL)
		dest[0] = '\0';
	else if (str1 == NULL || str1[0] == '\0')
		strcpy(dest, str2);
	else if (str2 == NULL || str2[0] == '\0')
		strcpy(dest, str1);
	else
	{
		uint8	separator_index = (uint8)strlen(str1); // 1 byte
		uint8	end_of_line_index = 0; // 1 byte

		strcpy(dest, str1);
		dest[separator_index] = '/';
		++separator_index;
		strcpy(dest + separator_index, str2);
		end_of_line_index = separator_index + (uint8)strlen(str2);
		dest[end_of_line_index] = '\0';
	}
}