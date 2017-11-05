#ifndef __BK_POINT_H_
#define __BK_POINT_H_

#include "pil\BkAtomicDataType.h"
#include "pil\__BkExport.h"

struct BkVector4;

struct BkPoint
{
	real	x;
	real	y;
	real	z;
};

// ~~~~~ Dcl(PUBLIC) ~~~~~

extern BK_API struct BkPoint	BkPoint_Zero(void);
extern BK_API void		BkPoint_Set(struct BkPoint* dst, real const x, real const y, real const z);
extern BK_API struct BkPoint	BkPoint_Copy(struct BkPoint const* src);
extern BK_API void		BkPoint_Assign(struct BkPoint* dst, struct BkPoint const* src);
extern BK_API struct BkPoint	BkPoint_Add_BkVector4(struct BkPoint const* a, struct BkVector4 const* b);
extern BK_API struct BkPoint	BkPoint_Sub_BkVector4(struct BkPoint const* a, struct BkVector4 const* b);
extern BK_API real		BkPoint_Distance(struct BkPoint const* a, struct BkPoint const* b);
extern BK_API struct BkPoint	BkPoint_Lerp(struct BkPoint const* from, struct BkPoint const* to, real const t);

#endif
