#ifndef __BK_EULER_ANGLES_H__
#define __BK_EULER_ANGLES_H__

/**
 * @file BkEulerAngles.h
 * @brief Defines the BkEulerAngles structure and functions for Euler angle
 * rotations.
 *
 * This file provides the definition of the BkEulerAngles struct which
 * represents rotations as three separate angles around the x, y, and z axes,
 * and functions to construct them from various rotation representations.
 */

// ~~~~~ Blackhart Headers ~~~~~

#include "foundation/BkAtomicDataType.h"
#include "foundation/BkExport.h"

// ~~~~~ Forward declarations ~~~~~
struct BkQuaternion;
struct BkMatrix4x4;

// ~~~~~ Type Definitions ~~~~~

/**
 * @struct BkEulerAngles
 * @brief Structure representing a rotation using Euler angles.
 *
 * Euler angles represent a rotation as three separate angles around the x, y,
 * and z axes. All angles are stored in degrees.
 */
struct BkEulerAngles {
  real x; /**< Rotation angle around the x-axis (in degrees). */
  real y; /**< Rotation angle around the y-axis (in degrees). */
  real z; /**< Rotation angle around the z-axis (in degrees). */
};

// ~~~~~ Dcl(PUBLIC) ~~~~~

/**
 * @brief Constructs a BkEulerAngles object with specified x, y, and z
 * components.
 *
 * Creates an Euler angles representation from individual rotation angles around
 * each axis.
 *
 * @param x The rotation angle around the x-axis (in degrees).
 * @param y The rotation angle around the y-axis (in degrees).
 * @param z The rotation angle around the z-axis (in degrees).
 * @return A new BkEulerAngles object with the specified angles.
 */
extern BK_API struct BkEulerAngles BkEulerAngles_FromXYZ(real const x,
                                                         real const y,
                                                         real const z);

/**
 * @brief Constructs a BkEulerAngles object from a BkQuaternion.
 *
 * Extracts Euler angles from a quaternion representation. The conversion may
 * suffer from gimbal lock in certain orientations.
 *
 * @param q Pointer to the quaternion to convert.
 * @return A new BkEulerAngles object representing the same rotation.
 */
extern BK_API struct BkEulerAngles BkEulerAngles_FromBkQuaternion(
    struct BkQuaternion const* q);

/**
 * @brief Constructs a BkEulerAngles object from a BkMatrix4x4.
 *
 * Extracts Euler angles from a 4x4 rotation matrix. The conversion may
 * suffer from gimbal lock in certain orientations.
 *
 * @param m Pointer to the 4x4 matrix to convert.
 * @return A new BkEulerAngles object representing the same rotation.
 */
extern BK_API struct BkEulerAngles BkEulerAngles_FromBkMatrix4x4(
    struct BkMatrix4x4 const* m);

/**
 * @brief Sets the x, y, and z components of a BkEulerAngles object.
 *
 * Modifies the Euler angles in-place with new angle values.
 *
 * @param obj Pointer to the BkEulerAngles object to modify.
 * @param x The new rotation angle around the x-axis (in degrees).
 * @param y The new rotation angle around the y-axis (in degrees).
 * @param z The new rotation angle around the z-axis (in degrees).
 */
extern BK_API void BkEulerAngles_Set(struct BkEulerAngles* obj, real const x,
                                     real const y, real const z);

#endif
