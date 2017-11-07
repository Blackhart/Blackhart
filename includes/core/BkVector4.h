#ifndef __BK_VECTOR4_H__
#define __BK_VECTOR4_H__

#include "pil\BkAtomicDataType.h"
#include "pil\__BkExport.h"

struct BkPoint;

struct BkVector4
{
    real    x;
    real    y;
    real    z;
};

// ~~~~~ Dcl(PUBLIC) ~~~~~

extern BK_API struct BkVector4	BkVector4_Zero(void);
extern BK_API struct BkVector4	BkVector4_From_Points(struct BkPoint const* a, struct BkPoint const* b);
extern BK_API struct BkVector4	BkVector4_Add_BkVector4(struct BkVector4 const* a, struct BkVector4 const* b);
extern BK_API struct BkVector4	BkVector4_Sub_BkVector4(struct BkVector4 const* a, struct BkVector4 const* b);
extern BK_API struct BkVector4	BkVector4_Mul_Real(struct BkVector4 const* a, real b);
extern BK_API struct BkVector4	BkVector4_Div_Real(struct BkVector4 const* a, real b);
extern BK_API real		BkVector4_Magnitude(struct BkVector4 const* a);
extern BK_API void		BkVector4_Set(struct BkVector4* dst, real const x, real const y, real const z);
extern BK_API struct BkVector4	BkVector4_Copy(struct BkVector4 const* src);
extern BK_API void		BkVector4_Assign(struct BkVector4* dst, struct BkVector4 const* src);
extern BK_API real		BkVector4_Dot(struct BkVector4 const* a, struct BkVector4 const* b);
extern BK_API struct BkVector4	BkVector4_Cross(struct BkVector4 const* a, struct BkVector4 const* b);
extern BK_API struct BkVector4	BkVector4_Negate(struct BkVector4 const* a);
extern BK_API real		BkVector4_Angle(struct BkVector4 const* a, struct BkVector4 const* b);
extern BK_API struct BkVector4	BkVector4_Normalize(struct BkVector4 const* a);
extern BK_API struct BkVector4	BkVector4_Lerp(struct BkVector4 const* from, struct BkVector4 const* to, real const t);
extern BK_API struct BkVector4	BkVector4_Max(struct BkVector4 const* a, struct BkVector4 const* b);
extern BK_API struct BkVector4	BkVector4_Min(struct BkVector4 const* a, struct BkVector4 const* b);

#endif