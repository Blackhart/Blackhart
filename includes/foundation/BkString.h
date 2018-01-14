#ifndef __BK_STRING_H__
#define __BK_STRING_H__

// Standard headers.
#include <stdarg.h>

// Blackhart.foundation headers.
#include "foundation\__BkExport.h"
#include "foundation\BkAtomicDataType.h"

// ~~~~~ Dcl(PUBLIC) ~~~~~

/*! \brief Writes formatted data to string.
 *
 * \param format The formatted string.
 * \param ... The list of arguments.
 * \return The string containing the full sentence.
 */
extern BK_API char const*	BkString_CreateFormatted(char const* format, ...);

/*! \brief Compares two strings.
 *
 * \param str1 The first string.
 * \param str2 The second string.
 * \return True if the strings are the same, false otherwise.
 */
extern BK_API bool	BkString_Compare(char const* string1, char const* string2);

#endif