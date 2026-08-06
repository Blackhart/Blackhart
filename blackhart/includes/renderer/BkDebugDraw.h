#ifndef __BK_DEBUG_DRAW_H__
#define __BK_DEBUG_DRAW_H__

/**
 * @file BkDebugDraw.h
 * @brief Internal line-draw helpers (object axes, AABB wireframe).
 *
 * Immediate-mode style overlays: the caller supplies matrices / geometry each
 * draw. No selection state is stored. Owned by the renderer.
 */

#include "foundation/BkAABB.h"
#include "foundation/BkAtomicDataType.h"
#include "foundation/BkMatrix4x4.h"
#include "foundation/BkTransform.h"

/**
 * @brief Prepares debug-draw GPU resources. Call from _BkRender_Initialize.
 */
extern void _BkDebugDraw_Initialize(void);

/**
 * @brief Releases debug-draw GPU resources. Call from _BkRender_Uninitialize.
 */
extern void _BkDebugDraw_Uninitialize(void);

/**
 * @brief Draws RGB object axes for @p transform with the given axis length.
 *
 * @param pv Projection × view. Must not be NULL.
 * @param uni_mvp Uniform location of uni_mvp in the bound program.
 * @param transform Object transform. Must not be NULL.
 * @param length Axis length in local units (clamped to a small minimum).
 */
extern void _BkDebugDraw_Axes(struct BkMatrix4x4 const* pv, int uni_mvp,
                              struct BkTransform* transform, real length);

/**
 * @brief Draws a world-space AABB as 12 line edges.
 *
 * @param pv Projection × view. Must not be NULL.
 * @param uni_mvp Uniform location of uni_mvp in the bound program.
 * @param aabb World AABB. Must not be NULL.
 */
extern void _BkDebugDraw_Aabb(struct BkMatrix4x4 const* pv, int uni_mvp,
                              struct BkAABB const* aabb);

#endif
