#ifndef __BK_POINT_H_
#define __BK_POINT_H_

// Blackhart.foundation headers.
#include "foundation\__BkExport.h"
#include "foundation\BkAtomicDataType.h"
#include "foundation\BkVector3.h"


struct BkPoint3
{
	real	x;
	real	y;
	real	z;
};

// ~~~~~ Dcl(PUBLIC) ~~~~~

extern BK_API struct BkPoint3	BkPoint3_Zero(void);
extern BK_API void		BkPoint3_Set(struct BkPoint3* dst, real const x, real const y, real const z);
extern BK_API struct BkPoint3	BkPoint3_Copy(struct BkPoint3 const* src);
extern BK_API void		BkPoint3_Assign(struct BkPoint3* dst, struct BkPoint3 const* src);
extern BK_API struct BkPoint3	BkPoint3_Add_BkVector3(struct BkPoint3 const* a, struct BkVector3 const* b);
extern BK_API struct BkPoint3	BkPoint3_Sub_BkVector3(struct BkPoint3 const* a, struct BkVector3 const* b);
extern BK_API struct BkVector3	BkPoint3_Sub_BkPoint3(struct BkPoint3 const* a, struct BkPoint3 const* b);
extern BK_API real		BkPoint3_Distance(struct BkPoint3 const* a, struct BkPoint3 const* b);
extern BK_API struct BkPoint3	BkPoint3_Lerp(struct BkPoint3 const* from, struct BkPoint3 const* to, real const t);

#endif
