#ifndef __BK_STRING_H__
#define __BK_STRING_H__

/**
 * @file BkString.h
 * @brief Defines string formatting and manipulation functions.
 *
 * This file provides functions for creating formatted strings using printf-style
 * format specifiers.
 */

// ~~~~~ Standard Headers ~~~~~

#include <stdarg.h>

// ~~~~~ Blackhart Headers ~~~~~

#include "foundation/BkExport.h"
#include "foundation/BkAtomicDataType.h"

// ~~~~~ Dcl(PUBLIC) ~~~~~

/**
 * @brief Creates a formatted string using printf-style formatting.
 *
 * Formats a string using the specified format string and variable arguments,
 * similar to sprintf. The function allocates memory for the resulting string
 * internally.
 *
 * @param format The format string containing printf-style format specifiers
 *               (e.g., "%d", "%s", "%f").
 * @param ... Variable argument list matching the format specifiers in the format string.
 * @return Pointer to the newly created formatted string. The string is allocated
 *         internally and must be freed using BkString_Free() when no longer needed.
 *         Returns NULL if formatting fails.
 */
extern BK_API char const*	BkString_CreateFormatted(char const* format, ...);

/**
 * @brief Frees a string allocated by BkString_CreateFormatted.
 *
 * Releases the memory previously allocated by BkString_CreateFormatted.
 * This function should be called when the string is no longer needed to prevent
 * memory leaks.
 *
 * @param str Pointer to the string to free. Must be a string allocated by
 *            BkString_CreateFormatted. The pointer will be invalid after this call.
 */
extern BK_API void	BkString_Free(char const* str);

#endif