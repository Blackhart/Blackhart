#ifndef __BK_GIZMO_H__
#define __BK_GIZMO_H__

/**
 * @file BkGizmo.h
 * @brief Internal orientation gizmo drawn in a viewport corner (Unity-style).
 *
 * Shows X (red), Y (green), Z (blue) axes that follow the camera orientation,
 * in a small overlay at the bottom-left of the framebuffer. Not a user-facing
 * scene object: applications toggle it through BkRender_SetGizmoVisible.
 *
 * Internal only — owned by the renderer. A valid OpenGL context is required
 * for Initialize/Uninitialize/Draw.
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
 * @brief Prepares the gizmo helper after the OpenGL context exists.
 *
 * Geometry is built lazily on the first Draw. Call from _BkRender_Initialize.
 */
extern void _BkGizmo_Initialize(void);

/**
 * @brief Releases OpenGL resources owned by the gizmo helper.
 *
 * Call from _BkRender_Uninitialize before destroying the OpenGL context.
 */
extern void _BkGizmo_Uninitialize(void);

/**
 * @brief Shows or hides the corner orientation gizmo.
 *
 * @param visible true to draw the gizmo, false to skip it.
 */
extern void _BkGizmo_SetVisible(bool visible);

/**
 * @brief Returns whether the corner gizmo will be drawn.
 */
extern bool _BkGizmo_IsVisible(void);

/**
 * @brief Draws the orientation gizmo in the bottom-left corner of the viewport.
 *
 * Saves/restores the GL viewport, clears depth in the overlay region, and
 * draws unit axes with a view that uses the camera rotation only (no world
 * translation). Call after the main scene so the widget sits on top.
 *
 * @param camera Active scene camera. Must not be NULL.
 * @param uni_mvp OpenGL uniform location of uni_mvp in the bound program.
 */
extern void _BkGizmo_Draw(BkCamera* camera, int uni_mvp);

#endif
