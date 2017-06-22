#ifndef __BK_VECTOR4_H__
#define __BK_VECTOR4_H__

#include <math.h>

#include "pil\BkAtomicDataType.h"

struct  sMatrix4x4;
struct  sVector4
{
    real    x;
    real    y;
    real    z;
    real    w;
};

typedef struct sVector4     Vector4;
typedef struct sVector4     vec4;

// ~~~~~ Dcl(PUBLIC) ~~~~~

extern vec4    Addition_vec4_vec4(vec4 const* const, vec4 const* const);
extern vec4    Substract_vec4_vec4(vec4 const* const, vec4 const* const);
extern vec4    Multiply_vec4_real(vec4 const* const, real);
extern vec4    Multiply_vec4_mat4(vec4 const* const, struct sMatrix4x4 const* const);
extern vec4    Divide_vec4_real(vec4 const* const, real);
extern real    Magnitude_vec4(vec4 const* const);
extern void    Set_vec4(vec4* const, real const x, real const y, real const z, real const w);
extern vec4    Copy_vec4(vec4 const* const);
extern void    Assign_vec4(vec4* const, vec4 const* const);
extern real    Dot_vec4(vec4 const* const, vec4 const* const);
extern vec4    Cross_vec4(vec4 const* const, vec4 const* const);
extern vec4    Negate_vec4(vec4 const* const);
extern real    Angle_vec4(vec4 const* const, vec4 const* const);
extern real    Distance_vec4(vec4 const* const, vec4 const* const);
extern vec4    Normalize_vec4(vec4 const* const);
extern vec4    Lerp_vec4(vec4 const* const, vec4 const* const, real const t);
extern vec4    Max_vec4(vec4 const* const, vec4 const* const);
extern vec4    Min_vec4(vec4 const* const, vec4 const* const);

#endif