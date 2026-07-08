#ifndef __BK_VECTOR3_H__
#define __BK_VECTOR3_H__

/**
 * @file BkVector3.h
 * @brief Defines the BkVector3 structure and functions for 3D vector operations.
 *
 * This file provides the definition of the BkVector3 struct and comprehensive vector operations
 * including arithmetic operations, normalization, dot/cross products, and interpolation.
 */

// ~~~~~ Blackhart Headers ~~~~~

#include "foundation/BkExport.h"
#include "foundation/BkAtomicDataType.h"

// ~~~~~ Forward declarations ~~~~~

struct BkPoint3;

// ~~~~~ Type Definitions ~~~~~

/**
 * @struct BkVector3
 * @brief Structure representing a 3D vector in Cartesian coordinates.
 *
 * A vector represents a direction and magnitude in 3D space. It has three components:
 * x, y, and z along the respective axes.
 */
struct BkVector3
{
    real    x;  /**< The x-component of the vector. */
    real    y;  /**< The y-component of the vector. */
    real    z;  /**< The z-component of the vector. */
};

// ~~~~~ Dcl(PUBLIC) ~~~~~

/**
 * @brief Constructs a BkVector3 object with all components set to zero.
 *
 * Creates a zero vector with x=0, y=0, z=0.
 *
 * @return A new BkVector3 object with all components set to zero.
 */
extern BK_API struct BkVector3	BkVector3_Zero(void);

/**
 * @brief Constructs a BkVector3 object with specified x, y, and z components.
 *
 * @param x The cartesian coordinate along the x-axis.
 * @param y The cartesian coordinate along the y-axis.
 * @param z The cartesian coordinate along the z-axis.
 * @return A new BkVector3 object with the specified components.
 */
extern BK_API struct BkVector3	BkVector3_FromXYZ(real const x, real const y, real const z);

/**
 * @brief Adds two BkVector3 vectors together.
 *
 * Performs component-wise addition: result = a + b.
 *
 * @param a Pointer to the first BkVector3.
 * @param b Pointer to the second BkVector3.
 * @return A new BkVector3 containing the sum of the two vectors.
 */
extern BK_API struct BkVector3	BkVector3_Add_BkVector3(struct BkVector3 const* a, struct BkVector3 const* b);

/**
 * @brief Subtracts one BkVector3 from another.
 *
 * Performs component-wise subtraction: result = a - b.
 *
 * @param a Pointer to the first BkVector3 (minuend).
 * @param b Pointer to the second BkVector3 (subtrahend).
 * @return A new BkVector3 containing the difference of the two vectors.
 */
extern BK_API struct BkVector3	BkVector3_Sub_BkVector3(struct BkVector3 const* a, struct BkVector3 const* b);

/**
 * @brief Multiplies a BkVector3 by a scalar real number.
 *
 * Performs scalar multiplication: result = a * b.
 * Each component of the vector is multiplied by the scalar.
 *
 * @param a Pointer to the BkVector3.
 * @param b The scalar real number to multiply by.
 * @return A new BkVector3 with each component multiplied by the scalar.
 */
extern BK_API struct BkVector3	BkVector3_Mul_Real(struct BkVector3 const* a, real b);

/**
 * @brief Divides a BkVector3 by a scalar real number.
 *
 * Performs scalar division: result = a / b.
 * Each component of the vector is divided by the scalar.
 *
 * @param a Pointer to the BkVector3.
 * @param b The scalar real number to divide by (must not be zero).
 * @return A new BkVector3 with each component divided by the scalar.
 */
extern BK_API struct BkVector3	BkVector3_Div_Real(struct BkVector3 const* a, real b);

/**
 * @brief Computes the magnitude (length) of a BkVector3.
 *
 * The magnitude is equal to the Euclidean length of the vector:
 * magnitude = sqrt(x² + y² + z²)
 *
 * @param a Pointer to the BkVector3.
 * @return The magnitude (length) of the vector.
 */
extern BK_API real	BkVector3_Magnitude(struct BkVector3 const* a);

/**
 * @brief Sets the x, y, and z components of a BkVector3.
 *
 * Modifies the vector in-place with new component values.
 *
 * @param obj Pointer to the BkVector3 object to modify.
 * @param x The new x-component.
 * @param y The new y-component.
 * @param z The new z-component.
 */
extern BK_API void	BkVector3_Set(struct BkVector3* obj, real const x, real const y, real const z);

/**
 * @brief Creates a copy of a BkVector3.
 *
 * @param src Pointer to the source BkVector3 to copy.
 * @return A new BkVector3 containing a copy of the source vector.
 */
extern BK_API struct BkVector3	BkVector3_Copy(struct BkVector3 const* src);

/**
 * @brief Copies one BkVector3 into another existing vector.
 *
 * Assigns the values from the source vector to the destination vector.
 * The destination vector must already be allocated.
 *
 * @param obj Pointer to the destination vector (must be allocated).
 * @param src Pointer to the source vector to copy from.
 */
extern BK_API void	BkVector3_Assign(struct BkVector3* __restrict obj, struct BkVector3 const* __restrict src);

/**
 * @brief Computes the dot product of two BkVector3 vectors.
 *
 * The dot product is a scalar value equal to:
 * dot = a.x * b.x + a.y * b.y + a.z * b.z
 *
 * The dot product can be used to determine the angle between two vectors
 * and whether they are perpendicular (dot product = 0).
 *
 * @param a Pointer to the first BkVector3.
 * @param b Pointer to the second BkVector3.
 * @return The dot product as a scalar real value.
 */
extern BK_API real	BkVector3_Dot(struct BkVector3 const* a, struct BkVector3 const* b);

/**
 * @brief Computes the absolute dot product of two BkVector3 vectors.
 *
 * Returns the absolute value of the dot product. Useful when only the magnitude
 * of the relationship between vectors is needed, not the direction.
 *
 * @param a Pointer to the first BkVector3.
 * @param b Pointer to the second BkVector3.
 * @return The absolute value of the dot product.
 */
extern BK_API real	BkVector3_AbsDot(struct BkVector3 const* a, struct BkVector3 const* b);

/**
 * @brief Computes the cross product of two BkVector3 vectors.
 *
 * The cross product returns a vector that is perpendicular to both input vectors.
 * The magnitude of the cross product equals the area of the parallelogram formed
 * by the two vectors.
 *
 * @param a Pointer to the first BkVector3.
 * @param b Pointer to the second BkVector3.
 * @return A new BkVector3 containing the cross product of a and b.
 */
extern BK_API struct BkVector3	BkVector3_Cross(struct BkVector3 const* a, struct BkVector3 const* b);

/**
 * @brief Negates all components of a BkVector3 in-place.
 *
 * Modifies the vector by negating each component: v = -v
 *
 * @param obj Pointer to the BkVector3 to negate.
 */
extern BK_API void	BkVector3_Negated(struct BkVector3* obj);

/**
 * @brief Negates all components of a BkVector3.
 *
 * Creates a new vector with negated components without modifying the original.
 *
 * @param a Pointer to the BkVector3 to negate.
 * @return A new BkVector3 with all components negated.
 */
extern BK_API struct BkVector3	BkVector3_Negate(struct BkVector3 const* a);

/**
 * @brief Computes the angle between two BkVector3 vectors in degrees.
 *
 * The angle is computed using the dot product and magnitudes of the vectors.
 *
 * @param a Pointer to the first BkVector3.
 * @param b Pointer to the second BkVector3.
 * @return The angle between the vectors in degrees (0 to 180).
 */
extern BK_API real	BkVector3_Angle(struct BkVector3 const* a, struct BkVector3 const* b);

/**
 * @brief Normalizes a BkVector3 in-place.
 *
 * Modifies the vector to have unit length (magnitude = 1.0) while preserving direction.
 * If the vector has zero magnitude, the result is undefined.
 *
 * @param obj Pointer to the BkVector3 to normalize.
 */
extern BK_API void	BkVector3_Normalized(struct BkVector3* obj);

/**
 * @brief Normalizes a BkVector3.
 *
 * Creates a new normalized vector (unit length) without modifying the original.
 * If the source vector has zero magnitude, the result is undefined.
 *
 * @param a Pointer to the BkVector3 to normalize.
 * @return A new BkVector3 with unit length and the same direction as the input.
 */
extern BK_API struct BkVector3	BkVector3_Normalize(struct BkVector3 const* a);

/**
 * @brief Performs linear interpolation between two BkVector3 vectors.
 *
 * Computes the interpolated vector: result = from + t * (to - from)
 * When t=0, returns 'from'. When t=1, returns 'to'. Values outside [0,1] extrapolate.
 *
 * @param from Pointer to the first BkVector3 (t=0).
 * @param to Pointer to the second BkVector3 (t=1).
 * @param t The interpolation parameter (typically between 0.0 and 1.0).
 * @return A new BkVector3 containing the interpolated vector.
 */
extern BK_API struct BkVector3	BkVector3_Lerp(struct BkVector3 const* from, struct BkVector3 const* to, real const t);

/**
 * @brief Returns the vector with the larger magnitude.
 *
 * Compares the magnitudes of two vectors and returns the one with the greater length.
 *
 * @param a Pointer to the first BkVector3.
 * @param b Pointer to the second BkVector3.
 * @return A copy of the vector with the larger magnitude.
 */
extern BK_API struct BkVector3	BkVector3_Max(struct BkVector3 const* a, struct BkVector3 const* b);

/**
 * @brief Returns the vector with the smaller magnitude.
 *
 * Compares the magnitudes of two vectors and returns the one with the lesser length.
 *
 * @param a Pointer to the first BkVector3.
 * @param b Pointer to the second BkVector3.
 * @return A copy of the vector with the smaller magnitude.
 */
extern BK_API struct BkVector3	BkVector3_Min(struct BkVector3 const* a, struct BkVector3 const* b);

#endif