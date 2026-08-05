#ifndef __BK_MATH_H__
#define __BK_MATH_H__

/**
 * @file BkMath.h
 * @brief Defines mathematical utility functions and constants.
 *
 * This file provides mathematical utility functions including angle
 * conversions, trigonometric conversions, barycentric coordinates, and value
 * clamping operations.
 */

// ~~~~~ Blackhart Headers ~~~~~

#include "foundation/BkAtomicDataType.h"
#include "foundation/BkExport.h"

// ~~~~~ Forward declarations ~~~~~

struct BkPoint3;

// ~~~~~ Type Definitions ~~~~~

/** @brief Mathematical constant pi (π). */
static real const BK_PI =
    BK_REAL(3.141592653589793238462643383279502884197169399375105820974);

/** @brief Mathematical constant pi divided by two (π/2). */
static real const BK_PI_OVER_TWO =
    BK_REAL(1.570796326794896619231321691639751442098584699687552910487);

/** @brief Conversion factor from degrees to radians. */
static real const BK_DEG_TO_RAD =
    BK_REAL(0.017453292519943295769236907684886127134428718885417254560);

/** @brief Conversion factor from radians to degrees. */
static real const BK_RAD_TO_DEG =
    BK_REAL(57.29577951308232087679815481410517033240547246656432154916);

// ~~~~~ Dcl(PUBLIC) ~~~~~

/**
 * @brief Converts a degree value to a radian value.
 *
 * Multiplies the degree value by the conversion factor to obtain the equivalent
 * in radians.
 *
 * @param deg The angle value in degrees.
 * @return The equivalent angle value in radians.
 */
extern BK_API real BkMath_RadFromDeg(real const deg);

/**
 * @brief Converts a radian value to a degree value.
 *
 * Multiplies the radian value by the conversion factor to obtain the equivalent
 * in degrees.
 *
 * @param rad The angle value in radians.
 * @return The equivalent angle value in degrees.
 */
extern BK_API real BkMath_DegFromRad(real const rad);

/**
 * @brief Computes the cosine value from a sine value.
 *
 * Uses the Pythagorean identity: cos²(θ) + sin²(θ) = 1
 * Therefore: cos(θ) = √(1 - sin²(θ))
 *
 * @param sin The sine value.
 * @return The corresponding cosine value.
 *
 * @note The result is always non-negative (cosine of the positive acute angle).
 */
extern BK_API real BkMath_CosFromSin(real const sin);

/**
 * @brief Computes the sine value from a cosine value.
 *
 * Uses the Pythagorean identity: cos²(θ) + sin²(θ) = 1
 * Therefore: sin(θ) = √(1 - cos²(θ))
 *
 * @param cos The cosine value.
 * @return The corresponding sine value.
 *
 * @note The result is always non-negative (sine of the positive acute angle).
 */
extern BK_API real BkMath_SinFromCos(real const cos);

/**
 * @brief Computes the tangent value from sine and cosine values.
 *
 * Uses the identity: tan(θ) = sin(θ) / cos(θ)
 *
 * @param sin The sine value.
 * @param cos The cosine value.
 * @return The tangent value (sin/cos), or 0 if cos is zero to avoid division by
 * zero.
 */
extern BK_API real BkMath_TanFromSinCos(real const sin, real const cos);

/**
 * @brief Computes a point in a triangular mesh using barycentric coordinates.
 *
 * Barycentric coordinates represent a point within a triangle as a weighted
 * combination of the triangle's vertices. The sum of u and v should not
 * exceed 1.0, with the third coordinate being w = 1 - (u + v).
 *
 * @param u The first barycentric coordinate.
 * @param v The second barycentric coordinate.
 * @return A BkPoint3 representing the point in the triangle.
 *
 * @note The sum of u and v must not exceed 1.0.
 */
extern BK_API struct BkPoint3 BkMath_TriangularBarycentricCoordinate(
    real const u, real const v);

/**
 * @brief Clamps a value to the range [min, max].
 *
 * Returns the value clamped to the specified range:
 * - If value < min, returns min
 * - If value > max, returns max
 * - Otherwise, returns value
 *
 * @param value The value to clamp.
 * @param min The minimum value of the range.
 * @param max The maximum value of the range.
 * @return The clamped value within [min, max].
 */
extern BK_API real BkMath_Clamp(real const value, real const min,
                                real const max);

/**
 * @brief Clamps a value to a minimum bound.
 *
 * Returns the maximum of the value and the minimum:
 * - If value < min, returns min
 * - Otherwise, returns value
 *
 * @param value The value to clamp.
 * @param min The minimum bound.
 * @return The clamped value (at least min).
 */
extern BK_API real BkMath_Min(real const value, real const min);

/**
 * @brief Clamps a value to a maximum bound.
 *
 * Returns the minimum of the value and the maximum:
 * - If value > max, returns max
 * - Otherwise, returns value
 *
 * @param value The value to clamp.
 * @param max The maximum bound.
 * @return The clamped value (at most max).
 */
extern BK_API real BkMath_Max(real const value, real const max);

#endif