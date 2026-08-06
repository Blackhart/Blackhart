#ifndef __BK_DEBUG_DRAW_H__
#define __BK_DEBUG_DRAW_H__

/**
 * @file BkDebugDraw.h
 * @brief Simple debug overlays: object axes and bounding boxes.
 *
 * Used to highlight a transform (RGB axes at an object's origin) or an AABB
 * (wireframe box) in the viewport. Nothing is remembered between calls — the
 * application passes what to draw each time.
 *
 * Applications use the public wrappers BkRender_DrawAxes and
 * BkRender_DrawAabb. Internal only — owned by the renderer.
 */

#include "foundation/BkAABB.h"
#include "foundation/BkAtomicDataType.h"
#include "foundation/BkMatrix4x4.h"
#include "foundation/BkTransform.h"

/**
 * @brief Prepares debug-draw resources after the OpenGL context exists.
 *
 * Call from _BkRender_Initialize.
 */
extern void _BkDebugDraw_Initialize(void);

/**
 * @brief Releases debug-draw resources.
 *
 * Call from _BkRender_Uninitialize before destroying the OpenGL context.
 */
extern void _BkDebugDraw_Uninitialize(void);

/**
 * @brief Draws RGB axes for a transform (X red, Y green, Z blue).
 *
 * @param pv Projection × view. Must not be NULL.
 * @param uni_mvp Uniform location of uni_mvp in the bound program.
 * @param transform Object transform. Must not be NULL.
 * @param length Axis length in local units.
 */
extern void _BkDebugDraw_Axes(struct BkMatrix4x4 const* pv, int uni_mvp,
                              struct BkTransform* transform, real length);

/**
 * @brief Draws a world-space AABB as a wireframe box.
 *
 * @param pv Projection × view. Must not be NULL.
 * @param uni_mvp Uniform location of uni_mvp in the bound program.
 * @param aabb World AABB. Must not be NULL.
 */
extern void _BkDebugDraw_Aabb(struct BkMatrix4x4 const* pv, int uni_mvp,
                              struct BkAABB const* aabb);

#endif
