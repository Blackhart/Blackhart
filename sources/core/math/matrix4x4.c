#include "core/math/matrix4x4.h"
#include "core/math/vector4.h"

mat4    Identity_mat4()
{
    return (mat4){ .m11 = 1.0, .m12 = 0.0, .m13 = 0.0, .m14 = 0.0,
                   .m21 = 0.0, .m22 = 1.0, .m23 = 0.0, .m24 = 0.0,
                   .m31 = 0.0, .m32 = 0.0, .m33 = 1.0, .m34 = 0.0,
                   .m41 = 0.0, .m42 = 0.0, .m43 = 0.0, .m44 = 1.0 };
}

mat4    Multiply_mat4_mat4(mat4 const* const a, mat4 const* const b)
{
    mat4 res;
    res.m11 = a->m11 * b->m11 + a->m12 * b->m21 + a->m13 * b->m31 + a->m14 * b->m41;
    res.m12 = a->m11 * b->m12 + a->m12 * b->m22 + a->m13 * b->m32 + a->m14 * b->m42;
    res.m13 = a->m11 * b->m13 + a->m12 * b->m23 + a->m13 * b->m33 + a->m14 * b->m43;
    res.m14 = a->m11 * b->m14 + a->m12 * b->m24 + a->m13 * b->m34 + a->m14 * b->m44;
    res.m21 = a->m21 * b->m11 + a->m22 * b->m21 + a->m23 * b->m31 + a->m24 * b->m41;
    res.m22 = a->m21 * b->m12 + a->m22 * b->m22 + a->m23 * b->m32 + a->m24 * b->m42;
    res.m23 = a->m21 * b->m13 + a->m22 * b->m23 + a->m23 * b->m33 + a->m24 * b->m43;
    res.m24 = a->m21 * b->m14 + a->m22 * b->m24 + a->m23 * b->m34 + a->m24 * b->m44;
    res.m31 = a->m31 * b->m11 + a->m32 * b->m21 + a->m33 * b->m31 + a->m34 * b->m41;
    res.m32 = a->m31 * b->m12 + a->m32 * b->m22 + a->m33 * b->m32 + a->m34 * b->m42;
    res.m33 = a->m31 * b->m13 + a->m32 * b->m23 + a->m33 * b->m33 + a->m34 * b->m43;
    res.m34 = a->m31 * b->m14 + a->m32 * b->m24 + a->m33 * b->m34 + a->m34 * b->m44;
    res.m41 = a->m41 * b->m11 + a->m42 * b->m21 + a->m43 * b->m31 + a->m44 * b->m41;
    res.m42 = a->m41 * b->m12 + a->m42 * b->m22 + a->m43 * b->m32 + a->m44 * b->m42;
    res.m43 = a->m41 * b->m13 + a->m42 * b->m23 + a->m43 * b->m33 + a->m44 * b->m43;
    res.m44 = a->m41 * b->m14 + a->m42 * b->m24 + a->m43 * b->m34 + a->m44 * b->m44;
    return res;
}

mat4    Multiply_mat4_real(mat4 const* const a, real const b)
{
    mat4 res;
    res.m11 = a->m11 * b; res.m12 = a->m12 * b; res.m13 = a->m13 * b; res.m14 = a->m14 * b;
    res.m21 = a->m21 * b; res.m22 = a->m22 * b; res.m23 = a->m23 * b; res.m24 = a->m24 * b;
    res.m31 = a->m31 * b; res.m32 = a->m32 * b; res.m33 = a->m33 * b; res.m34 = a->m34 * b;
    res.m41 = a->m41 * b; res.m42 = a->m42 * b; res.m43 = a->m43 * b; res.m44 = a->m44 * b;
    return res;
}

void    Set_mat4(mat4* const a, vec4 const* const row1, vec4 const* const row2, vec4 const* const row3, vec4 const* const row4)
{
    a->m11 = row1->x; a->m12 = row1->y; a->m13 = row1->z; a->m14 = row1->w;
    a->m21 = row2->x; a->m22 = row2->y; a->m23 = row2->z; a->m24 = row2->w;
    a->m31 = row3->x; a->m32 = row3->y; a->m33 = row3->z; a->m34 = row3->w;
    a->m41 = row4->x; a->m42 = row4->y; a->m43 = row4->z; a->m44 = row4->w;
}

mat4    Copy_mat4(mat4 const* const src)
{
    mat4 dst;
    dst.m11 = src->m11; dst.m12 = src->m12; dst.m13 = src->m13; dst.m14 = src->m14;
    dst.m21 = src->m21; dst.m22 = src->m22; dst.m23 = src->m23; dst.m24 = src->m24;
    dst.m31 = src->m31; dst.m32 = src->m32; dst.m33 = src->m33; dst.m34 = src->m34;
    dst.m41 = src->m41; dst.m42 = src->m42; dst.m43 = src->m43; dst.m44 = src->m44;
    return dst;
}

void    Assign_mat4(mat4* const dst, mat4 const* const src)
{
    dst->m11 = src->m11; dst->m12 = src->m12; dst->m13 = src->m13; dst->m14 = src->m14;
    dst->m21 = src->m21; dst->m22 = src->m22; dst->m23 = src->m23; dst->m24 = src->m24;
    dst->m31 = src->m31; dst->m32 = src->m32; dst->m33 = src->m33; dst->m34 = src->m34;
    dst->m41 = src->m41; dst->m42 = src->m42; dst->m43 = src->m43; dst->m44 = src->m44;
}

mat4    Transpose_mat4(mat4 const* const a)
{
    mat4 res;
    res.m11 = a->m11; res.m12 = a->m21; res.m13 = a->m31; res.m14 = a->m41;
    res.m21 = a->m12; res.m22 = a->m22; res.m23 = a->m32; res.m24 = a->m42;
    res.m31 = a->m13; res.m32 = a->m23; res.m33 = a->m33; res.m34 = a->m43;
    res.m41 = a->m14; res.m42 = a->m24; res.m43 = a->m34; res.m44 = a->m44;
    return res;
}