#ifndef __BK_TRANSFORM_H__
#define __BK_TRANSFORM_H__

/**
 * @file BkTransform.h
 * @brief Defines the BkTransform structure and functions for representing and manipulating 3D transformations.
 *
 * This file provides the definition of the BkTransform struct, which represents a position, orientation,
 * and local transformation matrix in 3D space. It includes functions for initialization, manipulation,
 * and querying transform properties.
 */

// ~~~~~ Blackhart Headers ~~~~~

#include "foundation/BkExport.h"
#include "foundation/BkMatrix4x4.h"
#include "foundation/BkPoint3.h"
#include "foundation/BkQuaternion.h"

// ~~~~~ Forward declarations ~~~~~

struct BkEulerAngles;
struct BkVector3;
struct BkAngleAxis;

// ~~~~~ Type Definitions ~~~~~

/**
 * @struct BkTransform
 * @brief Structure representing a 3D transformation (position, orientation, and local matrix).
 *
 * The transform combines a position (BkPoint3), an orientation (BkQuaternion), and a local transformation
 * matrix (BkMatrix4x4). The dirty flag indicates whether the local matrix needs to be recalculated.
 */
struct BkTransform
{
	struct BkPoint3     position;      /**< The position of the transform in 3D space. */
	struct BkQuaternion orientation;   /**< The orientation of the transform as a quaternion. */
	struct BkMatrix4x4  local;         /**< The local transformation matrix. */
	bool                dirty;         /**< Flag indicating if the matrix needs recalculation. */
    uint8               __padding__[3]; /**< Padding for memory alignment. */
};

// ~~~~~ Dcl(PUBLIC) ~~~~~

/**
 * @brief Initializes a BkTransform object with default values.
 *
 * Sets the position to zero, orientation to identity quaternion, and marks the matrix as dirty.
 * Must be called before using the transform.
 *
 * @param obj Pointer to the BkTransform object to initialize.
 */
extern BK_API void	BkTransform_Initialize(struct BkTransform* obj);

/**
 * @brief Gets a pointer to the local transformation matrix.
 *
 * If the matrix is dirty, it should be recalculated before use.
 *
 * @param obj Pointer to the BkTransform object.
 * @return Pointer to the local transformation matrix.
 */
extern BK_API struct BkMatrix4x4*	BkTransform_Matrix(struct BkTransform* obj);

/**
 * @brief Computes and returns the inverse of the local transformation matrix.
 *
 * @param obj Pointer to the BkTransform object.
 * @return The inverse of the local transformation matrix.
 */
extern BK_API struct BkMatrix4x4	BkTransform_InvMatrix(struct BkTransform* obj);

/**
 * @brief Orients the transform to look at a target point from a source point.
 *
 * The transform's position is set to the 'from' point, and its orientation is calculated
 * to face the 'to' point using the specified up vector.
 *
 * @param obj Pointer to the BkTransform object to modify.
 * @param from Pointer to the source position.
 * @param to Pointer to the target position to look at.
 * @param up Pointer to the up vector (typically world up).
 */
extern BK_API void	BkTransform_LookAt(struct BkTransform* obj, struct BkPoint3 const* from, struct BkPoint3 const* to, struct BkVector3 const* up);

/**
 * @brief Translates the transform by a vector.
 *
 * Adds the translation vector to the current position.
 *
 * @param obj Pointer to the BkTransform object to modify.
 * @param translation Pointer to the translation vector.
 */
extern BK_API void	BkTransform_Translate_BkVector3(struct BkTransform* obj, struct BkVector3 const* translation);

/**
 * @brief Rotates the transform by a quaternion.
 *
 * Multiplies the current orientation by the given rotation quaternion.
 *
 * @param obj Pointer to the BkTransform object to modify.
 * @param rotation Pointer to the rotation quaternion.
 */
extern BK_API void	BkTransform_Rotate_BkQuaternion(struct BkTransform* obj, struct BkQuaternion const* rotation);

/**
 * @brief Rotates the transform by Euler angles.
 *
 * Converts the Euler angles to a quaternion and applies the rotation.
 *
 * @param obj Pointer to the BkTransform object to modify.
 * @param euler Pointer to the Euler angles (in degrees).
 */
extern BK_API void	BkTransform_Rotate_EulerAngle(struct BkTransform* obj, struct BkEulerAngles const* euler);

/**
 * @brief Rotates the transform by an angle-axis representation.
 *
 * Converts the angle-axis to a quaternion and applies the rotation.
 *
 * @param obj Pointer to the BkTransform object to modify.
 * @param angle_axis Pointer to the angle-axis rotation representation.
 */
extern BK_API void	BkTransform_Rotate_AngleAxis(struct BkTransform* obj, struct BkAngleAxis const* angle_axis);

/**
 * @brief Gets the forward direction vector of the transform.
 *
 * The forward vector is the direction the transform is facing (typically -Z axis in local space).
 *
 * @param obj Pointer to the BkTransform object.
 * @return The forward direction vector as a BkVector3.
 */
extern BK_API struct BkVector3	BkTransform_Forward(struct BkTransform* obj);

/**
 * @brief Gets the right direction vector of the transform.
 *
 * The right vector is perpendicular to both forward and up vectors (typically +X axis in local space).
 *
 * @param obj Pointer to the BkTransform object.
 * @return The right direction vector as a BkVector3.
 */
extern BK_API struct BkVector3	BkTransform_Right(struct BkTransform* obj);

/**
 * @brief Gets the up direction vector of the transform.
 *
 * The up vector points upward relative to the transform's orientation (typically +Y axis in local space).
 *
 * @param obj Pointer to the BkTransform object.
 * @return The up direction vector as a BkVector3.
 */
extern BK_API struct BkVector3	BkTransform_Up(struct BkTransform* obj);

/**
 * @brief Sets the position of the transform.
 *
 * @param obj Pointer to the BkTransform object to modify.
 * @param position Pointer to the new position.
 */
extern BK_API void	BkTransform_SetPosition(struct BkTransform* obj, struct BkPoint3 const* position);

/**
 * @brief Sets the orientation of the transform.
 *
 * @param obj Pointer to the BkTransform object to modify.
 * @param orientation Pointer to the new orientation quaternion.
 */
extern BK_API void	BkTransform_SetOrientation(struct BkTransform* obj, struct BkQuaternion const* orientation);

#endif
