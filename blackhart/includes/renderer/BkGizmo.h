#ifndef __BK_GIZMO_H__
#define __BK_GIZMO_H__

/**
 * @file BkGizmo.h
 * @brief Corner orientation widget.
 *
 * Shows the world axes (X red, Y green, Z blue) in a small overlay at the
 * bottom-left of the viewport. The widget follows the camera's orientation
 * only — it does not move with the camera position — so you can always read
 * which way is up / forward while orbiting.
 *
 * This is a viewport helper, not a scene object: applications never create or
 * own it. They draw it when they want with BkRender_DrawOrientationGizmo.
 *
 * Internal only — owned by the renderer.
 */

// ~~~~~ Blackhart Headers ~~~~~

#include "foundation/BkAtomicDataType.h"

// ~~~~~ Type Definitions ~~~~~

/**
 * @typedef BkCamera
 * @brief Camera handle (see BkCamera.h).
 */
typedef struct BkCamera BkCamera;

// ~~~~~ Dcl(INTERNAL) ~~~~~

/**
 * @brief Prepares the orientation gizmo after the OpenGL context exists.
 *
 * Call from _BkRender_Initialize.
 */
extern void _BkGizmo_Initialize(void);

/**
 * @brief Releases resources owned by the orientation gizmo.
 *
 * Call from _BkRender_Uninitialize before destroying the OpenGL context.
 */
extern void _BkGizmo_Uninitialize(void);

/**
 * @brief Draws the corner orientation gizmo for the given camera.
 *
 * @param camera Active scene camera. Must not be NULL.
 * @param uni_mvp Uniform location of uni_mvp in the bound program.
 */
extern void _BkGizmo_Draw(BkCamera* camera, int uni_mvp);

#endif
