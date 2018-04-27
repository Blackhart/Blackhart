// Standard headers.
#include <math.h>

// blackhart headers.
#include "foundation\BkProjection.h"
#include "foundation\BkMath.h"

// ~~~~~ Def(PUBLIC) ~~~~~

struct BkMatrix4x4	BkProjection_Perspective(real const fovx, real const aspect_ratio, const real near, const real far)
{
	real const scale = BK_REAL(tan((double)BkMath_RadFromDeg(fovx * BK_REAL(0.5)))) * near;
	real const right = scale * aspect_ratio;
	real const left = -scale * aspect_ratio;
	real const top = scale;
	real const bottom = -scale;

	struct BkMatrix4x4 m;

	m.m11 = (BK_REAL(2.0) * near) / (right - left);   m.m12 = BK_REAL(0.0);                             m.m13 = (right + left) / (right - left);   m.m14 = BK_REAL(0.0);
	m.m21 = BK_REAL(0.0);                             m.m22 = (BK_REAL(2.0) * near) / (top - bottom);   m.m23 = (top + bottom) / (top - bottom);   m.m24 = BK_REAL(0.0);
	m.m31 = BK_REAL(0.0);                             m.m32 = BK_REAL(0.0);                             m.m33 = -(far + near) / (far - near);      m.m34 = -(BK_REAL(2.0) * far * near) / (far - near);
	m.m41 = BK_REAL(0.0);                             m.m42 = BK_REAL(0.0);                             m.m43 = BK_REAL(-1.0);                     m.m44 = BK_REAL(0.0);

	return m;
}