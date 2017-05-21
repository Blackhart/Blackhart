#ifndef __BK_VECTOR4_H__
#define __BK_VECTOR4_H__

#include <math.h>

#include "../../pil/pil.h"

struct  sVector4
{
    real    x;
    real    y;
    real    z;
    real    w;
};

typedef struct sVector4     Vector4;
typedef struct sVector4     vec4;

vec4    Addition(vec4 const* const, vec4 const* const);
vec4    Substract(vec4 const* const, vec4 const* const);
vec4    Multiply(vec4 const* const, real);
vec4    Divide(vec4 const* const, real);
real    Magnitude(vec4 const* const);
void    Set(vec4* const, real const x, real const y, real const z, real const w);
vec4    Copy(vec4 const* const);
void    Assign(vec4* const, vec4 const* const);
real    Dot(vec4 const* const, vec4 const* const);
vec4    Cross(vec4 const* const, vec4 const* const);
vec4    Negate(vec4 const* const);
real    Angle(vec4 const* const, vec4 const* const);
real    Distance(vec4 const* const, vec4 const* const);
vec4    Normalize(vec4 const* const);
vec4    Lerp(vec4 const* const, vec4 const* const, real const t);
vec4    Max(vec4 const* const, vec4 const* const);
vec4    Min(vec4 const* const, vec4 const* const);

#endif