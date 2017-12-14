#ifndef __BK_VECTOR4_H__
#define __BK_VECTOR4_H__

// Blackhart.foundation headers.
#include "foundation\__BkExport.h"
#include "foundation\BkAtomicDataType.h"

struct BkPoint3;

struct BkVector3
{
    real    x;
    real    y;
    real    z;
};

// ~~~~~ Dcl(PUBLIC) ~~~~~

extern BK_API struct BkVector3	BkVector3_Zero(void);
extern BK_API struct BkVector3	BkVector3_Add_BkVector3(struct BkVector3 const* a, struct BkVector3 const* b);
extern BK_API struct BkVector3	BkVector3_Sub_BkVector3(struct BkVector3 const* a, struct BkVector3 const* b);
extern BK_API struct BkVector3	BkVector3_Mul_Real(struct BkVector3 const* a, real b);
extern BK_API struct BkVector3	BkVector3_Div_Real(struct BkVector3 const* a, real b);
extern BK_API real		BkVector3_Magnitude(struct BkVector3 const* a);
extern BK_API void		BkVector3_Set(struct BkVector3* dst, real const x, real const y, real const z);
extern BK_API struct BkVector3	BkVector3_Copy(struct BkVector3 const* src);
extern BK_API void		BkVector3_Assign(struct BkVector3* dst, struct BkVector3 const* src);
extern BK_API real		BkVector3_Dot(struct BkVector3 const* a, struct BkVector3 const* b);
extern BK_API real		BkVector3_AbsDot(struct BkVector3 const* a, struct BkVector3 const* b);
extern BK_API struct BkVector3	BkVector3_Cross(struct BkVector3 const* a, struct BkVector3 const* b);
extern BK_API struct BkVector3	BkVector3_Negate(struct BkVector3 const* a);
extern BK_API real		BkVector3_Angle(struct BkVector3 const* a, struct BkVector3 const* b);
extern BK_API struct BkVector3	BkVector3_Normalize(struct BkVector3 const* a);
extern BK_API struct BkVector3	BkVector3_Lerp(struct BkVector3 const* from, struct BkVector3 const* to, real const t);
extern BK_API struct BkVector3	BkVector3_Max(struct BkVector3 const* a, struct BkVector3 const* b);
extern BK_API struct BkVector3	BkVector3_Min(struct BkVector3 const* a, struct BkVector3 const* b);

#endif