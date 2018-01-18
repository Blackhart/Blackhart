// Standard headers.
#include <math.h>

// Blackhart.foundation headers.
#include "foundation\BkMath.h"

// ~~~~~ Def(PUBLIC) ~~~~~

real	BkMath_DegToRad(real const deg)
{
	return deg * BK_DEG_TO_RAD;
}

real	BkMath_RadToDeg(real const rad)
{
	return rad * BK_RAD_TO_DEG;
}

real	BkMath_CosFromSin(real const sin)
{
	return BK_REAL(sqrt(1.0 - sin * sin));
}

real	BkMath_SinFromCos(real const cos)
{
	return BK_REAL(sqrt(1.0 - cos * cos));
}

real	BkMath_TanFromSinCos(real const sin, real const cos)
{
	if (cos == BK_REAL(0))
		return BK_REAL(0);
	else
		return sin / cos;
}