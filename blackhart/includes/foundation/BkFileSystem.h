#ifndef __BK_FILE_SYSTEM_H__
#define __BK_FILE_SYSTEM_H__

/**
 * @file BkFileSystem.h
 * @brief Defines file system operations and file I/O functions.
 *
 * This file provides functions for file operations including checking file
 * existence, opening/closing files, reading/writing file contents, and path
 * manipulation.
 */

// ~~~~~ Standard Headers ~~~~~

#include <stdio.h>

// ~~~~~ Blackhart Headers ~~~~~

#include "foundation/BkAtomicDataType.h"
#include "foundation/BkExport.h"

// ~~~~~ Type Definitions ~~~~~

/**
 * @typedef BkFlux
 * @brief Type alias for FILE stream.
 *
 * BkFlux is an alias for the standard FILE type, representing a file stream.
 */
typedef FILE BkFlux;

// ~~~~~ Dcl(PUBLIC) ~~~~~

/**
 * @brief Checks if a file exists at the specified path.
 *
 * Determines whether a file can be accessed at the given filename path.
 *
 * @param filename Path to the file to check.
 * @return true if the file exists and is accessible, false otherwise.
 */
extern BK_API bool BkFileSystem_FluxExists(char const* filename);

/**
 * @brief Opens a file stream (flux).
 *
 * Opens a file with the specified filename and access mode. The flux pointer
 * will be set to point to the opened file stream.
 *
 * @param flux Pointer to a pointer to BkFlux. Will be set to the opened file
 * stream.
 * @param filename Path to the file to open.
 * @param mode File access mode (e.g., "r" for read, "w" for write, "a" for
 * append).
 */
extern BK_API void BkFileSystem_OpenFlux(BkFlux** flux,
                                         char const* __restrict filename,
                                         char const* __restrict mode);

/**
 * @brief Closes a file stream (flux).
 *
 * Closes the specified file stream and frees associated resources.
 * The flux pointer will be set to NULL after closing.
 *
 * @param flux Pointer to a pointer to BkFlux. The pointer will be set to NULL
 * after closing.
 */
extern BK_API void BkFileSystem_CloseFlux(BkFlux** flux);

/**
 * @brief Writes a string message to a file stream.
 *
 * Writes the specified string to the opened file stream. The string is written
 * as-is without any additional formatting.
 *
 * @param flux Pointer to an opened file stream.
 * @param str The message string to write to the file.
 */
extern BK_API void BkFileSystem_WriteToFlux(BkFlux* flux, char const* str);

/**
 * @brief Reads the entire contents of a file from a path.
 *
 * Reads all data from the file at the specified path into a dynamically
 * allocated buffer. The buffer and its size are set by this function. The
 * caller is responsible for freeing the buffer when done.
 *
 * @param path Path to the file to read.
 * @param buffer Pointer to a char pointer. Will be set to point to the
 * allocated buffer containing the file contents [OUT].
 * @param buffer_size Pointer to a size_t. Will be set to the size of the
 * allocated buffer [OUT].
 */
extern BK_API void BkFileSystem_ReadFromPath(char const* path, char** buffer,
                                             size_t* buffer_size);

/**
 * @brief Reads the entire contents from an open file stream.
 *
 * Reads all remaining data from the opened file stream into a dynamically
 * allocated buffer. The buffer and its size are set by this function. The
 * caller is responsible for freeing the buffer when done.
 *
 * @param flux Pointer to an opened file stream. The flux must be open before
 * calling this function.
 * @param buffer Pointer to a char pointer. Will be set to point to the
 * allocated buffer containing the file contents [OUT].
 * @param buffer_size Pointer to a size_t. Will be set to the size of the
 * allocated buffer [OUT].
 */
extern BK_API void BkFileSystem_ReadFromFlux(BkFlux* flux, char** buffer,
                                             size_t* buffer_size);

/**
 * @brief Combines two path strings into a single path.
 *
 * Concatenates two path components, handling path separators appropriately
 * for the current platform. The result is written to the destination buffer.
 *
 * @param dst Buffer that will contain the combined path. Must be pre-allocated
 *            with sufficient space before calling this function.
 * @param str1 The first path component.
 * @param str2 The second path component to append.
 */
extern BK_API void BkFileSystem_CombinePath(char* __restrict dst,
                                            char const* __restrict str1,
                                            char const* __restrict str2);

#endif