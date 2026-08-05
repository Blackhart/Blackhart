#ifndef __BK_LOGGER_H__
#define __BK_LOGGER_H__

/**
 * @file BkLogger.h
 * @brief Defines logging functions for the Blackhart library.
 *
 * This file provides functions for logging messages to a log file.
 * The logger must be initialized before use.
 */

// ~~~~~ Blackhart Headers ~~~~~

#include "foundation/BkExport.h"

// ~~~~~ Dcl(PUBLIC) ~~~~~

/**
 * @brief Logs a message to the log file.
 *
 * Writes the specified message string to the log file. The log file location
 * and format are determined by the logger implementation.
 *
 * @param str The message string to log.
 */
extern BK_API void BkLog(char const* str);

// ~~~~~ Dcl(INTERNAL) ~~~~~

/**
 * @brief Initializes the logger system.
 *
 * Sets up the logging infrastructure, including opening the log file.
 * This function should be called during library initialization.
 */
extern void _BkLogger_Initialize(void);

/**
 * @brief Uninitializes the logger system.
 *
 * Cleans up the logging infrastructure, including closing the log file.
 * This function should be called during library cleanup.
 */
extern void _BkLogger_Uninitialize(void);

#endif