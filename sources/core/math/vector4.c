#include "../../../includes/core/math/vector4.h"

real    Magnitude(vec4 const* const a)
{
    return sqrt(a->x * a->x + a->y * a->y + a->z * a->z);
}

void    Set(vec4* const dst, real const x, real const y, real const z, real const w)
{
    dst->x = x;
    dst->y = y;
    dst->z = z;
    dst->w = w;
}

vec4    Copy(vec4 const* const src)
{
    vec4 dst;
    Set(&dst, src->x, src->y, src->z, src->w);
    return dst;
}

void    Assign(vec4* const dst, vec4 const* const src)
{
    Set(dst, src->x, src->y, src->z, src->w);
}

real    Dot(vec4 const* const a, vec4 const* const b)
{
   return a->x * b->x + a->y * b->y + a->z * b->z;
}

vec4    Cross(vec4 const* const a, vec4 const* const b)
{
    vec4 lOut;
    lOut.x = a->y * b->z - a->z * b->y;
    lOut.y = a->z * b->x - a->x * b->z;
    lOut.z = a->x * b->y - a->y * b->x;
    lOut.w = 1.0;
    return lOut;
}

vec4    Addition(vec4 const* const a, vec4 const* const b)
{
    vec4 lOut;
    lOut.x = a->x + b->x;
    lOut.y = a->y + b->y;
    lOut.z = a->z + b->z;
    lOut.w = 1.0;
    return lOut;
}

vec4    Substract(vec4 const* const a, vec4 const* const b)
{
    vec4 lOut;
    lOut.x = a->x - b->x;
    lOut.y = a->y - b->y;
    lOut.z = a->z - b->z;
    lOut.w = 1.0;
    return lOut;
}

vec4    Multiply(vec4 const* const a, real b)
{
    vec4 lOut;
    lOut.x = a->x * b;
    lOut.y = a->y * b;
    lOut.z = a->z * b;
    lOut.w = 1.0;
    return lOut;
}

vec4    Divide(vec4 const* const a, real b)
{
    vec4 lOut;
    lOut.x = a->x / b;
    lOut.y = a->y / b;
    lOut.z = a->z / b;
    lOut.w = 1.0;
    return lOut;
}

vec4    Negate(vec4 const* const a)
{
    vec4 lOut;
    lOut.x = -a->x;
    lOut.y = -a->y;
    lOut.z = -a->z;
    lOut.w = 1.0;
    return lOut;
}

real    Angle(vec4 const* const a, vec4 const* const b)
{
    vec4 na = Normalize(a);
    vec4 nb = Normalize(b);
    return acos(Dot(&na, &nb));
}

real    Distance(vec4 const* const a, vec4 const* const b)
{
    vec4 sab = Substract(a, b);
    return Magnitude(&sab);
}

vec4    Normalize(vec4 const* const a)
{
    return Divide(a, Magnitude(a));
}

vec4    Lerp(vec4 const* const from, vec4 const* const to, real const t)
{
    vec4 sfromto = Substract(from, to);
    vec4 msfromtot = Multiply(&sfromto, t);
    return Addition(&msfromtot, from);
}

vec4    Max(vec4 const* const a, vec4 const* const b)
{
    vec4 res;
    if (Magnitude(a) > Magnitude(b))
        Assign(&res, a);
    else
        Assign(&res, b);
    return res;
}

vec4    Min(vec4 const* const a, vec4 const* const b)
{
    vec4 res;
    if (Magnitude(a) < Magnitude(b))
        Assign(&res, a);
    else
        Assign(&res, b);
    return res;
}