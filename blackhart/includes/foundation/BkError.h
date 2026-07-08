#ifndef __BK_ERROR_H__
#define __BK_ERROR_H__

/**
 * @file BkError.h
 * @brief Defines error handling macros and functions for the Blackhart library.
 *
 * This file provides error handling utilities including macros for assertions,
 * error checking, and functions for fatal error reporting and error context management.
 */

// ~~~~~ Standard Headers ~~~~~

#include <assert.h>

// ~~~~~ Blackhart Headers ~~~~~

#include "foundation/BkExport.h"
#include "foundation/BkAtomicDataType.h"

// ~~~~~ Macros Definitions ~~~~~

/** @def BK_SUCCESS
 *  @brief Success exit code constant.
 */
#define BK_SUCCESS	EXIT_SUCCESS

/** @def BK_FAILURE
 *  @brief Failure exit code constant.
 */
#define BK_FAILURE	EXIT_FAILURE

/** @def BK_ISNULL(object)
 *  @brief Checks if a pointer is NULL.
 *  @param object The pointer to check.
 */
#define BK_ISNULL(object)	(object == NULL)

/** @def BK_ISTRUE(boolean)
 *  @brief Checks if a boolean is true.
 *  @param boolean The boolean to check.
 */
#define BK_ISTRUE(boolean)	(boolean == true)

/** @def BK_ERROR(test, str)
 *  @brief Logs a fatal error and exits if the test condition is true.
 *  @param test The condition to test.
 *  @param str Additional error message string.
 */
#define BK_ERROR(test, str)	if (test) { BkError_Fatal(#test, __FILE__, __LINE__, str); }

/** @def BK_ASSERT(test)
 *  @brief Asserts that the test condition is false. If true, the program aborts.
 *  @param test The condition to assert.
 */
#define BK_ASSERT(test)	assert(!(test))

/** @def BK_COMPILER_ASSERT(test)
 *  @brief Compile-time assertion. Causes a compilation error if the test fails.
 *  @param test The condition to test at compile time.
 */
#define BK_COMPILER_ASSERT(test)    if(!(test)) { int 0_COMPILER_ASSERT_FAILED; }

// ~~~~~ Dcl(PUBLIC) ~~~~~

/**
 * @brief Pushes an error context message onto the error context stack.
 *
 * Error contexts allow tracking the call stack when errors occur. Each call to
 * BkError_PushContext adds a context message, which should be matched with a
 * corresponding call to BkError_PopContext.
 *
 * @param msg The error context message to push.
 */
extern BK_API void	BkError_PushContext(char* msg);

/**
 * @brief Pops the most recent error context message from the error context stack.
 *
 * This function should be called to remove an error context that was previously
 * added with BkError_PushContext. It should be called in pairs with PushContext
 * to maintain a proper call stack trace.
 */
extern BK_API void	BkError_PopContext(void);

/**
 * @brief Logs a fatal error message and exits the program.
 *
 * This function is called when a fatal error is detected. It logs the error
 * information including the assertion that failed, the file and line where it
 * occurred, and an additional error message. The program then exits.
 *
 * @param assert The test condition string that failed.
 * @param file The source file name where the error occurred.
 * @param line The line number where the error occurred.
 * @param str Additional error message providing context about the error.
 */
extern BK_API void	BkError_Fatal(char const* __restrict assert, char const* __restrict file, uint16 const line, char const* __restrict str);

// ~~~~~ Dcl(INTERNAL) ~~~~~

/**
 * @brief Initializes the Blackhart error handling context.
 *
 * This function should be called during library initialization to set up
 * the error handling system.
 */
extern void	_BkError_Initialize(void);

/**
 * @brief Uninitializes the Blackhart error handling context.
 *
 * This function should be called during library cleanup to tear down
 * the error handling system.
 */
extern void	_BkError_Uninitialize(void);

#endif