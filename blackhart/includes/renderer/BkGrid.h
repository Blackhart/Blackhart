#ifndef __BK_GRID_H__
#define __BK_GRID_H__

/**
 * @file BkGrid.h
 * @brief Internal ground-grid helper drawn by the renderer.
 *
 * The grid is a viewport helper, not a user-facing scene object: applications
 * never create or own it. They only toggle it through BkRender_SetGridVisible
 * and BkRender_SetGridCellSize (thin wrappers around the functions below).
 *
 * Geometry is an XZ plane at y = 0 (Y-up, matching BkOrbitalCamera). Lines
 * span a fixed world extent; spacing equals the cell size. The GPU mesh is
 * rebuilt lazily when the cell size changes. Draw uses GL_LINES and expects
 * the default renderer shader (position + color attributes, uni_mvp).
 *
 * Internal only — owned by the renderer. A valid OpenGL context is required
 * for Initialize/Uninitialize/Draw.
 */

// ~~~~~ Blackhart Headers ~~~~~

#include "foundation/BkAtomicDataType.h"
#include "foundation/BkMatrix4x4.h"

// ~~~~~ Dcl(INTERNAL) ~~~~~

/**
 * @brief Prepares the grid helper after the OpenGL context exists.
 *
 * Does not upload geometry yet; the mesh is built on the first Draw (or after
 * a cell-size change). Call from _BkRender_Initialize.
 */
extern void _BkGrid_Initialize(void);

/**
 * @brief Releases OpenGL resources owned by the grid helper.
 *
 * Deletes the VAO/VBO if present. Call from _BkRender_Uninitialize before
 * destroying the OpenGL context.
 */
extern void _BkGrid_Uninitialize(void);

/**
 * @brief Shows or hides the grid on subsequent draws.
 *
 * @param visible true to draw the grid, false to skip it.
 */
extern void _BkGrid_SetVisible(bool visible);

/**
 * @brief Returns whether the grid will be drawn.
 *
 * @return true if visible, false otherwise.
 */
extern bool _BkGrid_IsVisible(void);

/**
 * @brief Sets the length of one grid square edge in world units.
 *
 * Values below 0.01 are clamped. Changing the size marks the mesh dirty so
 * the next Draw rebuilds the lines.
 *
 * @param cell_size Desired cell size (default is 1).
 */
extern void _BkGrid_SetCellSize(real cell_size);

/**
 * @brief Returns the current grid cell size in world units.
 *
 * @return Cell edge length (at least 0.01).
 */
extern real _BkGrid_GetCellSize(void);

/**
 * @brief Draws the ground grid if it is visible.
 *
 * Rebuilds the mesh when dirty. Uses the currently bound shader program;
 * uploads @p pv as the model-view-projection (identity model) and draws
 * GL_LINES. Must not be called without a prior _BkGrid_Initialize and an
 * active OpenGL context.
 *
 * @param pv Projection × view matrix. Must not be NULL.
 * @param uni_mvp OpenGL uniform location of uni_mvp in the bound program.
 */
extern void _BkGrid_Draw(struct BkMatrix4x4 const* pv, int uni_mvp);

#endif
