#ifndef __BK_CAMERA_H__
#define __BK_CAMERA_H__

/**
 * @file BkCamera.h
 * @brief Defines the BkCamera structure and functions for camera management in
 * 3D scenes.
 *
 * This file provides the definition of the BkCamera struct, which represents a
 * camera with a transform (position and orientation) and a projection matrix.
 * It includes functions for initialization, projection management, and view
 * matrix computation.
 */

// ~~~~~ Blackhart Headers ~~~~~

#include "foundation/BkExport.h"
#include "foundation/BkMatrix4x4.h"
#include "foundation/BkTransform.h"

// ~~~~~ Type Definitions ~~~~~

/**
 * @struct BkCamera
 * @brief Structure representing a camera in 3D space.
 *
 * The camera contains a transform (position and orientation) and a projection
 * matrix. The transform defines where the camera is positioned and which
 * direction it's facing, while the projection matrix defines how the 3D scene
 * is projected onto the 2D viewport.
 */
struct BkCamera {
  struct BkTransform transform; /**< The camera's position and orientation. */
  struct BkMatrix4x4 projection; /**< The projection matrix defining the
                                    camera's field of view. */
};

// ~~~~~ Dcl(PUBLIC) ~~~~~

/**
 * @brief Initializes a BkCamera object with default values.
 *
 * Initializes the camera's transform and sets the projection matrix to
 * identity. Must be called before using the camera.
 *
 * @param camera Pointer to the BkCamera object to initialize.
 */
extern BK_API void BkCamera_Initialize(struct BkCamera* camera);

/**
 * @brief Sets the projection matrix of the camera.
 *
 * The projection matrix defines how the 3D scene is transformed into 2D screen
 * space. Common projections include perspective and orthographic.
 *
 * @param obj Pointer to the BkCamera object to modify.
 * @param projection Pointer to the projection matrix to use.
 */
extern BK_API void BkCamera_SetProjection(struct BkCamera* obj,
                                          struct BkMatrix4x4 const* projection);

/**
 * @brief Computes and returns the view matrix of the camera.
 *
 * The view matrix transforms world coordinates into camera/view space
 * coordinates. It is computed from the camera's transform (position and
 * orientation).
 *
 * @param obj Pointer to the BkCamera object.
 * @return The view matrix as a BkMatrix4x4.
 */
extern BK_API struct BkMatrix4x4 BkCamera_ViewMatrix(struct BkCamera* obj);

/**
 * @brief Gets a pointer to the camera's transform.
 *
 * The transform can be used to modify the camera's position and orientation.
 *
 * @param obj Pointer to the BkCamera object.
 * @return Pointer to the camera's transform.
 */
extern BK_API struct BkTransform* BkCamera_Transform(struct BkCamera* obj);

/**
 * @brief Gets a pointer to the camera's projection matrix.
 *
 * The projection matrix can be modified to change the camera's field of view,
 * aspect ratio, near/far clipping planes, etc.
 *
 * @param obj Pointer to the BkCamera object.
 * @return Pointer to the camera's projection matrix.
 */
extern BK_API struct BkMatrix4x4* BkCamera_Projection(struct BkCamera* obj);

#endif
