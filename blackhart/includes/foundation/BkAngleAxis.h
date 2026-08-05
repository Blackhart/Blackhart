#ifndef __BK_ANGLE_AXIS_H__
#define __BK_ANGLE_AXIS_H__

/**
 * @file BkAngleAxis.h
 * @brief Defines the BkAngleAxis structure and functions for representing and
 * manipulating 3D rotations using the angle-axis representation.
 *
 * This file provides the definition of the BkAngleAxis struct, which stores a
 * rotation as an angle (in degrees) and a normalized axis of rotation (as a 3D
 * vector). It also declares a set of functions for constructing and modifying
 * BkAngleAxis objects.
 */

// ~~~~~ Blackhart Headers ~~~~~

#include "foundation/BkAtomicDataType.h"
#include "foundation/BkExport.h"
#include "foundation/BkVector3.h"

// ~~~~~ Type Definitions ~~~~~

/**
 * @struct BkAngleAxis
 * @brief Structure representing a rotation in 3D space using the angle-axis
 * representation.
 *
 * The rotation is expressed as a rotation of `angle` degrees around the
 * specified `axis` (which must be normalized).
 */
struct BkAngleAxis {
  real angle; /**< Rotation angle in degrees. */
  struct BkVector3 axis; /**< Normalized axis of rotation. */
};

// ~~~~~ Dcl(PUBLIC) ~~~~~

/**
 * @brief Constructs a BkAngleAxis object with the specified angle and axis.
 *
 * @param angle The angle of rotation, in degrees.
 * @param axis Pointer to the normalized axis of rotation as a BkVector3.
 * @return The constructed BkAngleAxis object.
 *
 * @note The axis must be normalized before being passed to this function.
 */
extern BK_API struct BkAngleAxis BkAngleAxis_FromAngleAxis(
    real const angle, struct BkVector3 const* axis);

/**
 * @brief Sets the rotation angle in a BkAngleAxis object.
 *
 * @param obj Pointer to the BkAngleAxis to modify.
 * @param angle The new angle of rotation, in degrees.
 */
extern BK_API void BkAngleAxis_SetAngle(struct BkAngleAxis* obj,
                                        real const angle);

/**
 * @brief Sets the axis of rotation in a BkAngleAxis object.
 *
 * @param obj Pointer to the BkAngleAxis to modify.
 * @param axis Pointer to the new axis of rotation (must be normalized).
 *
 * @note The axis must be normalized before being passed to this function.
 */
extern BK_API void BkAngleAxis_SetAxis(struct BkAngleAxis* obj,
                                       struct BkVector3 const* axis);

#endif
