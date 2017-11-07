#ifndef __BK_MATRIX4X4_H__
#define __BK_MATRIX4X4_H__

#include "pil\BkAtomicDataType.h"
#include "pil\__BkExport.h"

struct BkPoint;
struct BkVector4;

struct BkMatrix4x4
{
    real m11; real m12; real m13; real m14;
    real m21; real m22; real m23; real m24;
    real m31; real m32; real m33; real m34;
    real m41; real m42; real m43; real m44;
};

// ~~~~~ Dcl(PUBLIC) ~~~~~

extern BK_API struct BkMatrix4x4	BkMatrix4x4_Identity();
extern BK_API struct BkMatrix4x4	BkMatrix4x4_Mul_BkMatrix4x4(struct BkMatrix4x4 const* m1, struct BkMatrix4x4 const* m2);
extern BK_API struct BkMatrix4x4	BkMatrix4x4_Mul_real(struct BkMatrix4x4 const* m, real const r);
extern BK_API struct BkVector4		BkMatrix4x4_Mul_BkVector4(struct BkMatrix4x4 const* m, struct BkVector4 const* v);
extern BK_API struct BkPoint		BkMatrix4x4_Mul_BkPoint(struct BkMatrix4x4 const* m, struct BkPoint const* p);
extern BK_API struct BkMatrix4x4	BkMatrix4x4_Copy(struct BkMatrix4x4 const* src);
extern BK_API void			BkMatrix4x4_Assign(struct BkMatrix4x4* dst, struct BkMatrix4x4 const* src);
extern BK_API struct BkMatrix4x4	BkMatrix4x4_Transpose(struct BkMatrix4x4 const* m);
extern BK_API struct BkMatrix4x4	BkMatrix4x4_Rotate_x(real const deg);
extern BK_API struct BkMatrix4x4	BkMatrix4x4_Rotate_y(real const deg);
extern BK_API struct BkMatrix4x4	BkMatrix4x4_Rotate_z(real const deg);
extern BK_API struct BkMatrix4x4	BkMatrix4x4_Rotate_axis(struct BkVector4 const* v, real const deg);
extern BK_API struct BkMatrix4x4	BkMatrix4x4_Scale_Uniform(real const k);
extern BK_API struct BkMatrix4x4	BkMatrix4x4_Scale_Nonuniform(real const x, real const y, real const z);
extern BK_API struct BkMatrix4x4	BkMatrix4x4_Scale_axis(struct BkVector4 const* v, real const k);
extern BK_API struct BkMatrix4x4	BkMatrix4x4_Translate(real const x, real const y, real const z);
extern BK_API real			BkMatrix4x4_Determinant(struct BkMatrix4x4 const* m);
extern BK_API struct BkMatrix4x4	BkMatrix4x4_Inverse(struct BkMatrix4x4 const* m);

#endif