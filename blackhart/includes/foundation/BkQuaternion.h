#ifndef __BK_QUATERNION_H__
#define __BK_QUATERNION_H__

/**
 * @file BkQuaternion.h
 * @brief Defines the BkQuaternion structure and functions for quaternion
 * operations.
 *
 * This file provides the definition of the BkQuaternion struct and
 * comprehensive quaternion operations including construction, multiplication,
 * normalization, conjugation, inversion, and conversions from other rotation
 * representations.
 */

// ~~~~~ Blackhart Headers ~~~~~

#include "foundation/BkAtomicDataType.h"
#include "foundation/BkError.h"
#include "foundation/BkExport.h"

// ~~~~~ Forward declarations ~~~~~

struct BkVector3;
struct BkMatrix4x4;
struct BkEulerAngles;
struct BkAngleAxis;

// ~~~~~ Type Definitions ~~~~~

/**
 * @struct BkQuaternion
 * @brief Structure representing a quaternion for 3D rotations.
 *
 * Quaternions are used to represent rotations in 3D space efficiently and avoid
 * gimbal lock. The quaternion has four components: w (scalar) and x, y, z
 * (vector part).
 */
struct BkQuaternion {
  real w; /**< The scalar (real) component of the quaternion. */
  real x; /**< The x-component of the vector part. */
  real y; /**< The y-component of the vector part. */
  real z; /**< The z-component of the vector part. */
};

// ~~~~~ Dcl(PUBLIC) ~~~~~

/**
 * @brief Returns an identity quaternion.
 *
 * The identity quaternion represents no rotation (w=1, x=0, y=0, z=0).
 *
 * @return The identity quaternion.
 */
extern BK_API struct BkQuaternion BkQuaternion_Identity(void);

/**
 * @brief Multiplies two quaternions.
 *
 * Performs quaternion multiplication: result = q1 * q2.
 *
 * Quaternion multiplication is not commutative: q1 * q2 ≠ q2 * q1.
 * Quaternion multiplication is associative: (q1 * q2) * q3 == q1 * (q2 * q3).
 *
 * @param q1 Pointer to the first quaternion.
 * @param q2 Pointer to the second quaternion.
 * @return The multiplied quaternion.
 */
extern BK_API struct BkQuaternion BkQuaternion_Mul_BkQuaternion(
    struct BkQuaternion const* q1, struct BkQuaternion const* q2);

/**
 * @brief Constructs a quaternion from an angle-axis representation.
 *
 * Converts a rotation represented as an angle (in degrees) around a normalized
 * axis into a quaternion.
 *
 * @param angle_axis Pointer to the angle-axis structure containing the
 * rotation.
 * @return A new quaternion representing the same rotation.
 */
extern BK_API struct BkQuaternion BkQuaternion_FromAngleAxis(
    struct BkAngleAxis const* angle_axis);

/**
 * @brief Constructs a quaternion from a 4x4 column-major rotation matrix.
 *
 * Extracts the rotation component from a 4x4 transformation matrix and converts
 * it to a quaternion representation.
 *
 * @param m Pointer to the 4x4 column-major matrix.
 * @return A new quaternion representing the rotation in the matrix.
 */
extern BK_API struct BkQuaternion BkQuaternion_FromBkMatrix4x4(
    struct BkMatrix4x4 const* m);

/**
 * @brief Constructs a quaternion from an Euler angles representation.
 *
 * Converts Euler angles (in degrees) to a quaternion. The rotation order
 * is typically ZYX (yaw-pitch-roll) or XYZ depending on the implementation.
 *
 * @param euler Pointer to the Euler angles structure.
 * @return A new quaternion representing the same rotation.
 */
extern BK_API struct BkQuaternion BkQuaternion_FromEulerAngles(
    struct BkEulerAngles const* euler);

/**
 * @brief Creates a copy of a quaternion.
 *
 * @param q Pointer to the quaternion to copy.
 * @return A new quaternion containing a copy of the source quaternion.
 */
extern BK_API struct BkQuaternion BkQuaternion_Copy(
    struct BkQuaternion const* q);

/**
 * @brief Sets the w, x, y, and z components of a quaternion.
 *
 * Modifies the quaternion in-place with new component values.
 *
 * @param obj Pointer to the quaternion to modify.
 * @param w The new w (scalar) component.
 * @param x The new x component.
 * @param y The new y component.
 * @param z The new z component.
 */
extern BK_API void BkQuaternion_Set(struct BkQuaternion* obj, real const w,
                                    real const x, real const y, real const z);

/**
 * @brief Normalizes a quaternion in-place.
 *
 * Modifies the quaternion to have unit length (magnitude = 1.0) while
 * preserving its rotation. If the quaternion has zero magnitude, the result is
 * undefined.
 *
 * @param obj Pointer to the quaternion to normalize.
 */
extern BK_API void BkQuaternion_Normalized(struct BkQuaternion* obj);

/**
 * @brief Normalizes a quaternion.
 *
 * Creates a new normalized quaternion (unit length) without modifying the
 * original. If the source quaternion has zero magnitude, the result is
 * undefined.
 *
 * @param q Pointer to the quaternion to normalize.
 * @return A new normalized quaternion with the same rotation as the input.
 */
extern BK_API struct BkQuaternion BkQuaternion_Normalize(
    struct BkQuaternion const* q);

/**
 * @brief Negates a quaternion in-place.
 *
 * Negates all components of the quaternion: q = -q.
 * This flips the rotation direction (negating both the angle and axis).
 *
 * @param obj Pointer to the quaternion to negate.
 */
extern BK_API void BkQuaternion_Negated(struct BkQuaternion* obj);

/**
 * @brief Negates a quaternion.
 *
 * Creates a new quaternion with all components negated without modifying the
 * original.
 *
 * @param q Pointer to the quaternion to negate.
 * @return A new negated quaternion.
 */
extern BK_API struct BkQuaternion BkQuaternion_Negate(
    struct BkQuaternion const* q);

/**
 * @brief Returns the magnitude (length) of a quaternion.
 *
 * The magnitude is computed as: magnitude = sqrt(w² + x² + y² + z²)
 *
 * @param q Pointer to the quaternion.
 * @return The magnitude of the quaternion.
 */
extern BK_API real BkQuaternion_Magnitude(struct BkQuaternion const* q);

/**
 * @brief Conjugates a quaternion in-place.
 *
 * Conjugating a quaternion flips the direction of rotation.
 * The conjugate of a quaternion (w, x, y, z) is (w, -x, -y, -z).
 *
 * As an example: Instead of rotating an object from left to right,
 * it rotates it from right to left.
 *
 * @param obj Pointer to the quaternion to conjugate.
 */
extern BK_API void BkQuaternion_Conjugated(struct BkQuaternion* obj);

/**
 * @brief Conjugates a quaternion.
 *
 * Creates a new conjugated quaternion without modifying the original.
 * The conjugate of a quaternion (w, x, y, z) is (w, -x, -y, -z).
 *
 * Conjugating a quaternion flips the direction of rotation.
 * As an example: Instead of rotating an object from left to right,
 * it rotates it from right to left.
 *
 * @param q Pointer to the quaternion to conjugate.
 * @return A new conjugated quaternion.
 */
extern BK_API struct BkQuaternion BkQuaternion_Conjugate(
    struct BkQuaternion const* q);

/**
 * @brief Inverts a quaternion in-place.
 *
 * The inverse of a quaternion is its conjugate divided by its magnitude
 * squared. For unit quaternions, the inverse equals the conjugate.
 *
 * @param obj Pointer to the quaternion to invert.
 */
extern BK_API void BkQuaternion_Inversed(struct BkQuaternion* obj);

/**
 * @brief Inverts a quaternion.
 *
 * Creates a new inverted quaternion without modifying the original.
 * The inverse of a quaternion is its conjugate divided by its magnitude
 * squared. For unit quaternions, the inverse equals the conjugate.
 *
 * @param q Pointer to the quaternion to invert.
 * @return A new inverted quaternion.
 */
extern BK_API struct BkQuaternion BkQuaternion_Inverse(
    struct BkQuaternion const* q);

/**
 * @brief Computes the difference between two quaternions.
 *
 * Computes the angular displacement that rotates from q1 to q2:
 * difference = q2 * inverse(q1)
 *
 * This represents the rotation needed to transform from q1's orientation to
 * q2's orientation.
 *
 * Quaternion difference is not commutative: diff(q1, q2) ≠ diff(q2, q1)
 *
 * @param q1 Pointer to the first quaternion (source orientation).
 * @param q2 Pointer to the second quaternion (target orientation).
 * @return A new quaternion representing the rotation from q1 to q2.
 */
extern BK_API struct BkQuaternion BkQuaternion_Difference(
    struct BkQuaternion const* q1, struct BkQuaternion const* q2);

/**
 * @brief Computes the dot product of two quaternions.
 *
 * The dot product is computed as: dot = q1.w * q2.w + q1.x * q2.x + q1.y * q2.y
 * + q1.z * q2.z
 *
 * The dot product can be used to measure the similarity between rotations.
 * A dot product of 1 means the rotations are identical, -1 means opposite.
 *
 * @param q1 Pointer to the first quaternion.
 * @param q2 Pointer to the second quaternion.
 * @return The dot product as a scalar real value.
 */
extern BK_API real BkQuaternion_Dot(struct BkQuaternion const* q1,
                                    struct BkQuaternion const* q2);

#endif
