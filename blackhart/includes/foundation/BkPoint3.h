#ifndef __BK_POINT3_H__
#define __BK_POINT3_H__

/**
 * @file BkPoint3.h
 * @brief Defines the BkPoint3 structure and functions for 3D point operations.
 *
 * This file provides the definition of the BkPoint3 struct and functions for
 * working with 3D points in Cartesian space, including translation, distance
 * calculation, and interpolation.
 */

// ~~~~~ Blackhart Headers ~~~~~

#include "foundation/BkAtomicDataType.h"
#include "foundation/BkExport.h"
#include "foundation/BkVector3.h"

// ~~~~~ Type Definitions ~~~~~

/**
 * @struct BkPoint3
 * @brief Structure representing a 3D point in Cartesian coordinates.
 *
 * A point represents a position in 3D space. It has three components: x, y, and
 * z along the respective axes. Unlike vectors, points are affected by
 * translations.
 */
struct BkPoint3 {
  real x; /**< The x-coordinate of the point. */
  real y; /**< The y-coordinate of the point. */
  real z; /**< The z-coordinate of the point. */
};

// ~~~~~ Dcl(PUBLIC) ~~~~~

/**
 * @brief Constructs a BkPoint3 object with all components set to zero.
 *
 * Creates a point at the origin (0, 0, 0).
 *
 * @return A new BkPoint3 object at the origin.
 */
extern BK_API struct BkPoint3 BkPoint3_Zero(void);

/**
 * @brief Constructs a BkPoint3 object with specified x, y, and z components.
 *
 * @param x The cartesian coordinate along the x-axis.
 * @param y The cartesian coordinate along the y-axis.
 * @param z The cartesian coordinate along the z-axis.
 * @return A new BkPoint3 object with the specified coordinates.
 */
extern BK_API struct BkPoint3 BkPoint3_FromXYZ(real const x, real const y,
                                               real const z);

/**
 * @brief Sets the x, y, and z components of a BkPoint3.
 *
 * Modifies the point in-place with new coordinate values.
 *
 * @param obj Pointer to the BkPoint3 object to modify.
 * @param x The new x-coordinate.
 * @param y The new y-coordinate.
 * @param z The new z-coordinate.
 */
extern BK_API void BkPoint3_Set(struct BkPoint3* obj, real const x,
                                real const y, real const z);

/**
 * @brief Creates a copy of a BkPoint3 object.
 *
 * @param src Pointer to the source BkPoint3 object to copy.
 * @return A new BkPoint3 object containing a copy of the source point.
 */
extern BK_API struct BkPoint3 BkPoint3_Copy(struct BkPoint3 const* src);

/**
 * @brief Copies one BkPoint3 object into another existing point.
 *
 * Assigns the values from the source point to the destination point.
 * The destination point must already be allocated.
 *
 * @param obj Pointer to the destination point (must be allocated).
 * @param src Pointer to the source point to copy from.
 */
extern BK_API void BkPoint3_Assign(struct BkPoint3* __restrict obj,
                                   struct BkPoint3 const* __restrict src);

/**
 * @brief Translates a BkPoint3 by adding a BkVector3.
 *
 * Performs point translation: result = point + vector.
 * The vector is added component-wise to move the point in 3D space.
 *
 * @param a Pointer to the BkPoint3 to translate.
 * @param b Pointer to the BkVector3 representing the translation.
 * @return A new BkPoint3 containing the translated point.
 */
extern BK_API struct BkPoint3 BkPoint3_Add_BkVector3(struct BkPoint3 const* a,
                                                     struct BkVector3 const* b);

/**
 * @brief Translates a BkPoint3 by subtracting a BkVector3.
 *
 * Performs point translation: result = point - vector.
 * The vector is subtracted component-wise to move the point in 3D space.
 *
 * @param a Pointer to the BkPoint3 to translate.
 * @param b Pointer to the BkVector3 representing the translation.
 * @return A new BkPoint3 containing the translated point.
 */
extern BK_API struct BkPoint3 BkPoint3_Sub_BkVector3(struct BkPoint3 const* a,
                                                     struct BkVector3 const* b);

/**
 * @brief Computes the vector from one point to another.
 *
 * Calculates the difference vector: result = a - b.
 * This returns a vector that represents the displacement from point b to point
 * a.
 *
 * @param a Pointer to the first BkPoint3 (destination).
 * @param b Pointer to the second BkPoint3 (origin).
 * @return A BkVector3 representing the vector from b to a.
 */
extern BK_API struct BkVector3 BkPoint3_Sub_BkPoint3(struct BkPoint3 const* a,
                                                     struct BkPoint3 const* b);

/**
 * @brief Computes the Euclidean distance between two points.
 *
 * Calculates the straight-line distance: distance = sqrt((a.x-b.x)² +
 * (a.y-b.y)² + (a.z-b.z)²)
 *
 * @param a Pointer to the first point.
 * @param b Pointer to the second point.
 * @return The distance between the two points as a scalar real value.
 */
extern BK_API real BkPoint3_Distance(struct BkPoint3 const* a,
                                     struct BkPoint3 const* b);

/**
 * @brief Performs linear interpolation between two points.
 *
 * Computes the interpolated point: result = from + t * (to - from)
 * When t=0, returns 'from'. When t=1, returns 'to'. Values outside [0,1]
 * extrapolate.
 *
 * @param from Pointer to the first point (t=0).
 * @param to Pointer to the second point (t=1).
 * @param t The interpolation parameter (typically between 0.0 and 1.0).
 * @return A new BkPoint3 containing the interpolated position.
 */
extern BK_API struct BkPoint3 BkPoint3_Lerp(struct BkPoint3 const* from,
                                            struct BkPoint3 const* to,
                                            real const t);

/**
 * @brief Computes a point rotated around a center point by yaw and pitch
 * angles.
 *
 * Calculates the position of a point that is located at a specified radius from
 * the center and rotated by the given yaw (horizontal) and pitch (vertical)
 * angles.
 *
 * @param center Pointer to the center point of rotation.
 * @param radius The distance from the center to the point.
 * @param yaw The horizontal rotation angle around the center (in degrees).
 * @param pitch The vertical rotation angle around the center (in degrees).
 * @return A new BkPoint3 containing the rotated point position.
 */
extern BK_API struct BkPoint3 BkPoint3_RotateAround(
    struct BkPoint3 const* center, real const radius, real const yaw,
    real const pitch);

#endif
