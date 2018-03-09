#ifndef __BK_MATH_H__
#define __BK_MATH_H__

// Blackhart.foundation headers.
#include "foundation\BkExport.h"
#include "foundation\BkAtomicDataType.h"

// Forward declarations.
struct BkPoint3;

static real const BK_PI = BK_REAL(3.141592653589793238462643383279502884197169399375105820974);
static real const BK_PI_OVER_TWO = BK_REAL(1.570796326794896619231321691639751442098584699687552910487);
static real const BK_DEG_TO_RAD = BK_REAL(0.017453292519943295769236907684886127134428718885417254560);
static real const BK_RAD_TO_DEG = BK_REAL(57.29577951308232087679815481410517033240547246656432154916);

// ~~~~~ Dcl(PUBLIC) ~~~~~

/*! \brief Converts a degree value to a radian value.
 *
 * \param deg Degree value.
 */
extern BK_API real	BkMath_RadFromDeg(real const deg);

/*! \brief Converts a radian value to a degree value.
 *
 * \param rad Radian value.
 */
extern BK_API real	BkMath_DegFromRad(real const rad);

/*! \brief Converts a sinus value to the corresponding cosinus value.
 *
 * \param sin Sinus value.
 */
extern BK_API real	BkMath_CosFromSin(real const sin);

/*! \brief Converts a cosinus value to the corresponding sinus value.
 *
 * \param cos Cosinus value.
 */
extern BK_API real	BkMath_SinFromCos(real const cos);

/*! \brief Converts a sinus value and a cosinus value to the corresponding tangente value.
 *
 * \param sin Sinus value.
 * \param cos Cosinus value.
 */
extern BK_API real	BkMath_TanFromSinCos(real const sin, real const cos);

/*! \brief Computes a point into a triangular mesh using barycentric coordinate system.
 *
 * The sum of u and v must not be superior to 1.
 *
 * \param u The barycentric coordinate u.
 * \param v The barycentric coordinate v.
 * \return The new point.
 */
extern BK_API struct BkPoint3	BkMath_TriangularBarycentricCoordinate(real const u, real const v);

#endif