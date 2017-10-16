#ifndef __BK_VECTOR4_H__
#define __BK_VECTOR4_H__

#include <math.h>

#include "pil\BkAtomicDataType.h"

struct BkMatrix4x4;

struct BkVector4
{
    real    x;
    real    y;
    real    z;
    real    w;
};

// ~~~~~ Dcl(PUBLIC) ~~~~~

extern struct BkVector4	Addition_vec4_vec4(struct BkVector4 const*, struct BkVector4 const*);
extern struct BkVector4	Substract_vec4_vec4(struct BkVector4 const*, struct BkVector4 const*);
extern struct BkVector4	Multiply_vec4_real(struct BkVector4 const*, real);
extern struct BkVector4	Multiply_vec4_mat4(struct BkVector4 const*, struct BkMatrix4x4 const*);
extern struct BkVector4	Divide_vec4_real(struct BkVector4 const*, real);
extern real		Magnitude_vec4(struct BkVector4 const*);
extern void		Set_vec4(struct BkVector4*, real const x, real const y, real const z, real const w);
extern struct BkVector4	Copy_vec4(struct BkVector4 const*);
extern void		Assign_vec4(struct BkVector4*, struct BkVector4 const*);
extern real		Dot_vec4(struct BkVector4 const*, struct BkVector4 const*);
extern struct BkVector4	Cross_vec4(struct BkVector4 const*, struct BkVector4 const*);
extern struct BkVector4	Negate_vec4(struct BkVector4 const*);
extern real		Angle_vec4(struct BkVector4 const*, struct BkVector4 const*);
extern real		Distance_vec4(struct BkVector4 const*, struct BkVector4 const*);
extern struct BkVector4	Normalize_vec4(struct BkVector4 const*);
extern struct BkVector4	Lerp_vec4(struct BkVector4 const*, struct BkVector4 const*, real const t);
extern struct BkVector4	Max_vec4(struct BkVector4 const*, struct BkVector4 const*);
extern struct BkVector4	Min_vec4(struct BkVector4 const*, struct BkVector4 const*);

#endif