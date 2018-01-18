#ifndef __BK_LOGGER_H__
#define __BK_LOGGER_H__

// Blackhart.foundation headers.
#include "foundation\BkExport.h"

// ~~~~~ Dcl(PUBLIC) ~~~~~

/*! \brief Logs a message to the log file.
 *
 * \param str The message to log.
 */
extern BK_API void	BkLog(char const* str);

// ~~~~~ Dcl(INTERNAL) ~~~~~

/*! \brief Initializes the logger.
*/
extern void	_BkLogger_Initialize(void);

/*! \brief Uninitializes the logger.
*/
extern void	_BkLogger_Uninitialize(void);

#endif