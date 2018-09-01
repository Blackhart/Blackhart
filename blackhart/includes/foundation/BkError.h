#ifndef __BK_ERROR_H__
#define __BK_ERROR_H__

// Standard headers.
#include <assert.h>

// blackhart headers.
#include "foundation\BkExport.h"
#include "foundation\BkAtomicDataType.h"

#define BK_SUCCESS	EXIT_SUCCESS
#define BK_FAILURE	EXIT_FAILURE

#define BK_ISNULL(object)	(object == NULL)
#define BK_ISTRUE(boolean)	(boolean == true)

#define BK_ERROR(test, str)	if (test) { BkError_Fatal(#test, __FILE__, __LINE__, str); }

#define BK_ASSERT(test)	assert(!(test))
#define BK_COMPILER_ASSERT(test)    if(!(test)) { int 0_COMPILER_ASSERT_FAILED; }

// ~~~~~ Dcl(PUBLIC) ~~~~~

/*! \brief 
 */
extern BK_API void	BkError_PushContext(char* msg);

/*! \brief
 */
extern BK_API void	BkError_PopContext(void);

/*! \brief Logs a fatal error msg and exit the program.
 *
 * \param assert The test that has failed.
 * \param file The file where the error has occured.
 * \param line The line where the error has occured.
 * \param str Additionnal error msg.
 */
extern BK_API void	BkError_Fatal(char const* __restrict assert, char const* __restrict file, uint16 const line, char const* __restrict str);

// ~~~~~ Dcl(INTERNAL) ~~~~~

/*! \brief Initializes Blackhart error context
*/
extern void	_BkError_Initialize(void);

/*! \brief Uninitializes Blackhart error context
*/
extern void	_BkError_Uninitialize(void);

#endif