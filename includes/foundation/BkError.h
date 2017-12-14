#ifndef __BK_ERROR_H__
#define __BK_ERROR_H__

// Standard headers.
#include <assert.h>
#include <stdlib.h>

// Blackhart.foundation headers.
#include "foundation\__BkExport.h"
#include "foundation\BkAtomicDataType.h"
#include "foundation\BkString.h"


#define BK_SUCCESS	EXIT_SUCCESS
#define BK_FAILURE	EXIT_FAILURE

#define BK_ISNULL(object)	(object == NULL)
#define BK_ISTRUE(boolean)	(boolean == true)

#define BK_ERROR(test, str)	if (test) { BkError_Fatal(#test, __FILE__, __LINE__, str); }

#define BK_ASSERT(test)	assert(!(test))

// ~~~~~ Dcl(PUBLIC) ~~~~~

/*! \brief 
 */
extern void	BkError_PushContext(char* msg);

/*! \brief
 */
extern void	BkError_PopContext(void);

/*! \brief Logs a fatal error msg and exit the program.
 *
 * \param assert The test that has failed.
 * \param file The file where the error has occured.
 * \param line The line where the error has occured.
 * \param str Additionnal error msg.
 */
extern void	BkError_Fatal(char const* assert, char const* file, uint16 const line, char const* str);

#endif