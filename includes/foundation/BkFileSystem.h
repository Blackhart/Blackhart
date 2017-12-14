#ifndef __BK_FILE_SYSTEM_H__
#define __BK_FILE_SYSTEM_H__

// Standard headers.
#include <stdio.h>

// Blackhart.foundation headers.
#include "foundation\__BkExport.h"
#include "foundation\BkAtomicDataType.h"
#include "foundation\BkError.h"


typedef FILE	BkFlux;

// ~~~~~ Dcl(PUBLIC) ~~~~~

/*! \brief Checks if a file exists.
 *
 * \param filename The file to check.
 * \return True if the file exists, false otherwise.
 */
extern BK_API bool	BkFileSystem_FluxExists(char const* filename);

/*! \brief Opens a flux.
 *
 * \param flux A pointer to the flux.
 * \param filename The file to open.
 * \param mode The file access mode.
 */
extern BK_API void	BkFileSystem_OpenFlux(BkFlux** flux, char const* filename, char const* mode);

/*! \brief Closes a flux.
 *
 * \param flux A pointer to the flux to close.
 */
extern BK_API void	BkFileSystem_CloseFlux(BkFlux** flux);

/*! \brief Writes a message into a flux.
 *
 * \param flux A pointer to the opened flux.
 * \param str The message to write.
 */
extern BK_API void	BkFileSystem_WriteToFlux(BkFlux* flux, char const* str);

/*! \brief Reads from a file.
 *
 * \param path The file to read.
 * \param buffer The buffer will contains the data [OUT]. Allocate and populate by the function.
 * \param buffer_size The size of the buffer. Populate by the function.
 */
extern BK_API void	BkFileSystem_ReadFromPath(char const* path, char** buffer, size_t* buffer_size);

/*! \brief Reads from a flux.
 *
 * \param flux The flux to read. The flux must be open!
 * \param buffer The buffer will contains the data [OUT]. Allocate and populate by the function.
 * \param buffer_size The size of the buffer. Populate by the function.
 */
extern BK_API void	BkFileSystem_ReadFromFlux(BkFlux* flux, char** buffer, size_t* buffer_size);

/*! \brief Combines two paths.
 *
 * \param dest The destination buffer. Must be allocate with the correct size!
 * \param str1 The first path.
 * \param str2 The second path.
 */
extern BK_API void	BkFileSystem_CombinePath(char* dest, char const* str1, char const* str2);

#endif