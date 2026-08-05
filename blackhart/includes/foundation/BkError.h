#ifndef __BK_ERROR_H__
#define __BK_ERROR_H__

/**
 * @file BkError.h
 * @brief Error handling for the Blackhart library.
 *
 * Two recoverable/fatal paths share the same structured log format
 * (what / why / where / how / result):
 * - BK_ERROR  : log and return
 * - BK_FATAL  : log and exit
 *
 * BK_ASSERT remains for programmer invariants (debug abort).
 */

// ~~~~~ Standard Headers ~~~~~

#include <assert.h>
#include <stdlib.h>

// ~~~~~ Blackhart Headers ~~~~~

#include "foundation/BkAtomicDataType.h"
#include "foundation/BkExport.h"

// ~~~~~ Macros Definitions ~~~~~

/** @def BK_SUCCESS
 *  @brief Success exit code constant.
 */
#define BK_SUCCESS EXIT_SUCCESS

/** @def BK_FAILURE
 *  @brief Failure exit code constant.
 */
#define BK_FAILURE EXIT_FAILURE

/** @def BK_ISNULL(object)
 *  @brief Checks if a pointer is NULL.
 *  @param object The pointer to check.
 */
#define BK_ISNULL(object) (object == NULL)

/** @def BK_ISTRUE(boolean)
 *  @brief Checks if a boolean is true.
 *  @param boolean The boolean to check.
 */
#define BK_ISTRUE(boolean) (boolean == true)

/**
 * @def BK_ASSERT(test)
 * @brief Aborts in debug if the failure condition is true.
 * @param test The condition that must be false.
 */
#define BK_ASSERT(test) assert(!(test))

/**
 * @def BK_COMPILER_ASSERT(test)
 * @brief Compile-time assertion. Fails to compile if the failure condition is
 * true.
 * @param test The failure condition (same convention as BK_ASSERT).
 */
#define BK_COMPILER_ASSERT(test) _Static_assert(!(test), #test)

/**
 * @def BK_FATAL(test, info)
 * @brief If test is true, logs a structured error and exits the process.
 * @param test Failure condition.
 * @param info struct BkErrorInfo (or compound literal).
 */
#define BK_FATAL(test, info)                             \
  do {                                                   \
    if (test) {                                          \
      struct BkErrorInfo const _bk_err_info_ = (info);   \
      BkError_Fatal(&_bk_err_info_, __FILE__, __LINE__); \
    }                                                    \
  } while (0)

/**
 * @def BK_ERROR(test, info, ret)
 * @brief If test is true, logs a structured error and returns ret.
 * @param test Failure condition.
 * @param info struct BkErrorInfo (or compound literal).
 * @param ret Value returned to the caller.
 */
#define BK_ERROR(test, info, ret)                      \
  do {                                                 \
    if (test) {                                        \
      struct BkErrorInfo const _bk_err_info_ = (info); \
      BkError_Log(&_bk_err_info_, __FILE__, __LINE__); \
      return (ret);                                    \
    }                                                  \
  } while (0)

/**
 * @def BK_ERROR_VOID(test, info)
 * @brief If test is true, logs a structured error and returns from a void
 * function.
 */
#define BK_ERROR_VOID(test, info)                      \
  do {                                                 \
    if (test) {                                        \
      struct BkErrorInfo const _bk_err_info_ = (info); \
      BkError_Log(&_bk_err_info_, __FILE__, __LINE__); \
      return;                                          \
    }                                                  \
  } while (0)

// ~~~~~ Type Definitions ~~~~~

/**
 * @struct BkErrorInfo
 * @brief Structured error description for logging.
 *
 * Optional fields may be NULL and will be omitted or defaulted in the log.
 */
struct BkErrorInfo {
  char const* what; /**< What failed (required). */
  char const* why; /**< Why it failed (required). */
  char const* where; /**< Resource path / name (optional). */
  char const* how; /**< How to resolve (optional). */
  char const* result; /**< Consequence for the caller (optional). */
};

// ~~~~~ Dcl(PUBLIC) ~~~~~

/**
 * @brief Logs a structured error (does not abort).
 *
 * @param info Error description.
 * @param file Source file (__FILE__).
 * @param line Source line (__LINE__).
 */
extern BK_API void BkError_Log(struct BkErrorInfo const* info, char const* file,
                               int line);

/**
 * @brief Logs a structured error and terminates the process.
 *
 * @param info Error description.
 * @param file Source file (__FILE__).
 * @param line Source line (__LINE__).
 */
extern BK_API void BkError_Fatal(struct BkErrorInfo const* info,
                                 char const* file, int line);

// ~~~~~ Dcl(INTERNAL) ~~~~~

/**
 * @brief Initializes the Blackhart error handling system.
 */
extern void _BkError_Initialize(void);

/**
 * @brief Uninitializes the Blackhart error handling system.
 */
extern void _BkError_Uninitialize(void);

#endif
