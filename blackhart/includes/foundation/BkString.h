#ifndef __BK_STRING_H__
#define __BK_STRING_H__

// Standard headers.
#include <stdarg.h>

// blackhart headers.
#include "foundation\BkExport.h"
#include "foundation\BkAtomicDataType.h"

// ~~~~~ Dcl(PUBLIC) ~~~~~

/*! \brief Writes formatted data to string.
 *
 * \param format The formatted string.
 * \param ... The list of arguments.
 * \return The string containing the full sentence.
 */
extern BK_API char const*	BkString_CreateFormatted(char const* format, ...);

#endif