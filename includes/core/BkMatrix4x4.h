#ifndef __BK_MATRIX4X4_h__
#define __BK_MATRIX4X4_h__

#include "pil\BkAtomicDataType.h"

struct BkVector4;

struct BkMatrix4x4
{
    real m11; real m12; real m13; real m14;
    real m21; real m22; real m23; real m24;
    real m31; real m32; real m33; real m34;
    real m41; real m42; real m43; real m44;
};

// ~~~~~ Dcl(PUBLIC) ~~~~~

extern struct BkMatrix4x4	Identity_mat4();
extern struct BkMatrix4x4	Multiply_mat4_mat4(struct BkMatrix4x4 const*, struct BkMatrix4x4 const*);
extern struct BkMatrix4x4	Multiply_mat4_real(struct BkMatrix4x4 const*, real const);
extern void			Set_mat4(struct BkMatrix4x4*, struct BkVector4 const*, struct BkVector4 const*, struct BkVector4 const*, struct BkVector4 const*);
extern struct BkMatrix4x4	Copy_mat4(struct BkMatrix4x4 const*);
extern void			Assign_mat4(struct BkMatrix4x4*, struct BkMatrix4x4 const*);
extern struct BkMatrix4x4	Transpose_mat4(struct BkMatrix4x4 const*);

#endif