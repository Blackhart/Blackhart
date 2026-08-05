#ifndef __BK_ORBITAL_CAMERA_HPP__
#define __BK_ORBITAL_CAMERA_HPP__

/**
 * @file BkOrbitalCamera.h
 * @brief Defines the BkOrbitalCamera structure and functions for orbital camera
 * control.
 *
 * This file provides the definition of the BkOrbitalCamera struct, which
 * extends BkCamera to provide orbital camera controls. An orbital camera
 * rotates around a target point at a specified radius, with configurable yaw
 * and pitch angles.
 */

// ~~~~~ Blackhart Headers ~~~~~

#include "foundation/BkAtomicDataType.h"
#include "foundation/BkCamera.h"
#include "foundation/BkExport.h"
#include "foundation/BkPoint3.h"

// ~~~~~ Type Definitions ~~~~~

/**
 * @struct BkOrbitalCamera
 * @brief Structure representing an orbital camera that rotates around a target
 * point.
 *
 * The orbital camera extends BkCamera to provide orbital movement controls. The
 * camera rotates around a target point at a specified radius, with yaw
 * (horizontal rotation) and pitch (vertical rotation) angles. Pitch limits can
 * be set to prevent camera flipping.
 */
struct BkOrbitalCamera {
  struct BkCamera
      base; /**< Base camera structure (transform and projection). */
  struct BkPoint3
      target; /**< The target point around which the camera orbits. */
  real radius; /**< The distance from the target point. */
  real pitch_min_limit; /**< Minimum pitch angle limit (in degrees). */
  real pitch_max_limit; /**< Maximum pitch angle limit (in degrees). */
  real yaw; /**< Horizontal rotation angle around the target (in degrees). */
  real pitch; /**< Vertical rotation angle around the target (in degrees). */
};

// ~~~~~ Dcl(PUBLIC) ~~~~~

/**
 * @brief Initializes a BkOrbitalCamera object with default values.
 *
 * Initializes the base camera and sets default values for target, radius, and
 * angles. Must be called before using the orbital camera.
 *
 * @param obj Pointer to the BkOrbitalCamera object to initialize.
 */
extern BK_API void BkOrbitalCamera_Initialize(struct BkOrbitalCamera* obj);

/**
 * @brief Rotates the orbital camera by the specified yaw and pitch amounts.
 *
 * Adds the specified yaw and pitch angles to the current camera orientation.
 * The pitch will be clamped to the defined limits if they are set.
 *
 * @param obj Pointer to the BkOrbitalCamera object to modify.
 * @param yaw The horizontal rotation amount to add (in degrees).
 * @param pitch The vertical rotation amount to add (in degrees).
 */
extern BK_API void BkOrbitalCamera_Rotate(struct BkOrbitalCamera* obj,
                                          real const yaw, real const pitch);

/**
 * @brief Zooms the orbital camera in or out by adjusting the radius.
 *
 * Adds the specified amount to the current radius. Positive values zoom out,
 * negative values zoom in. The radius should remain positive.
 *
 * @param obj Pointer to the BkOrbitalCamera object to modify.
 * @param radius The amount to add to the current radius (positive = zoom out,
 * negative = zoom in).
 */
extern BK_API void BkOrbitalCamera_Zoom(struct BkOrbitalCamera* obj,
                                        real const radius);

/**
 * @brief Sets the target point around which the camera orbits.
 *
 * @param obj Pointer to the BkOrbitalCamera object to modify.
 * @param target Pointer to the target point in 3D space.
 */
extern BK_API void BkOrbitalCamera_SetTarget(struct BkOrbitalCamera* obj,
                                             struct BkPoint3 const* target);

/**
 * @brief Sets the radius (distance) from the target point.
 *
 * The radius determines how far the camera is from the target point.
 *
 * @param obj Pointer to the BkOrbitalCamera object to modify.
 * @param radius The new radius value (should be positive).
 */
extern BK_API void BkOrbitalCamera_SetRadius(struct BkOrbitalCamera* obj,
                                             real const radius);

/**
 * @brief Sets the pitch angle limits to prevent camera flipping.
 *
 * When the camera rotates, the pitch angle will be clamped between these
 * limits.
 *
 * @param obj Pointer to the BkOrbitalCamera object to modify.
 * @param pitch_min_limit The minimum pitch angle (in degrees, typically
 * negative).
 * @param pitch_max_limit The maximum pitch angle (in degrees, typically
 * positive).
 */
extern BK_API void BkOrbitalCamera_SetPitchBoundLimits(
    struct BkOrbitalCamera* obj, real const pitch_min_limit,
    real const pitch_max_limit);

/**
 * @brief Sets the yaw (horizontal rotation) angle.
 *
 * @param obj Pointer to the BkOrbitalCamera object to modify.
 * @param yaw The new yaw angle (in degrees).
 */
extern BK_API void BkOrbitalCamera_SetYaw(struct BkOrbitalCamera* obj,
                                          real const yaw);

/**
 * @brief Sets the pitch (vertical rotation) angle.
 *
 * The pitch will be clamped to the defined limits if they are set.
 *
 * @param obj Pointer to the BkOrbitalCamera object to modify.
 * @param pitch The new pitch angle (in degrees).
 */
extern BK_API void BkOrbitalCamera_SetPitch(struct BkOrbitalCamera* obj,
                                            real const pitch);

#endif