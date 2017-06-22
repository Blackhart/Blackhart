#ifndef __BK_ERROR_H__
#define __BK_ERROR_H__

#include <assert.h>
#include <stdarg.h>
#include <stdlib.h>

#include "pil\BkAtomicDataType.h"

#define BK_SUCCESS	EXIT_SUCCESS
#define BK_FAILURE	EXIT_FAILURE

#define BK_FAILED(Error)		(Error != BK_SUCCESS)
#define BK_FAILED_ASSERT(Error)	(assert(!BK_FAILED(Error)))

typedef int8	BkResult;

// ~~~~~ Dcl(PUBLIC) ~~~~~

extern void		BkDie(char const* pMsg, ...);
extern BkResult	BkError(char const* pMsg, ...);
extern void		BkWarning(char const* pMsg, ...);

#endif