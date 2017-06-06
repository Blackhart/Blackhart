#ifndef __BK_MATRIX4X4_h__
#define __BK_MATRIX4X4_h__

#include "pil\BkAtomicDataType.h"

struct  sVector4;
struct  sMatrix4x4
{
    real m11; real m12; real m13; real m14;
    real m21; real m22; real m23; real m24;
    real m31; real m32; real m33; real m34;
    real m41; real m42; real m43; real m44;
};

typedef struct sMatrix4x4   Matrix4x4;
typedef struct sMatrix4x4   mat4;

// ~~~~~ Dcl(PUBLIC) ~~~~~

extern mat4    Identity_mat4();
extern mat4    Multiply_mat4_mat4(mat4 const* const, mat4 const* const);
extern mat4    Multiply_mat4_real(mat4 const* const, real const);
extern void    Set_mat4(mat4* const, struct sVector4 const* const, struct sVector4 const* const, struct sVector4 const* const, struct sVector4 const* const);
extern mat4    Copy_mat4(mat4 const* const);
extern void    Assign_mat4(mat4* const, mat4 const* const);
extern mat4    Transpose_mat4(mat4 const* const);

#endif