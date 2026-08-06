#ifndef __BK_GRID_H__
#define __BK_GRID_H__

/**
 * @file BkGrid.h
 * @brief Ground grid under the scene (XZ plane, Y-up).
 *
 * Draws a flat reference grid on the ground so you can judge scale, align
 * objects, and keep a sense of space while navigating. Cell size controls how
 * large each square is in world units.
 *
 * This is a viewport helper, not a scene object: applications never create or
 * own it. They draw it when they want with BkRender_DrawGrid.
 *
 * Internal only — owned by the renderer.
 */

// ~~~~~ Blackhart Headers ~~~~~

#include "foundation/BkAtomicDataType.h"
#include "foundation/BkMatrix4x4.h"

// ~~~~~ Dcl(INTERNAL) ~~~~~

/**
 * @brief Prepares the ground grid after the OpenGL context exists.
 *
 * Call from _BkRender_Initialize.
 */
extern void _BkGrid_Initialize(void);

/**
 * @brief Releases resources owned by the ground grid.
 *
 * Call from _BkRender_Uninitialize before destroying the OpenGL context.
 */
extern void _BkGrid_Uninitialize(void);

/**
 * @brief Draws the ground grid with the given cell size.
 *
 * @param pv Projection × view matrix. Must not be NULL.
 * @param uni_mvp Uniform location of uni_mvp in the bound program.
 * @param cell_size Length of one grid square edge in world units.
 */
extern void _BkGrid_Draw(struct BkMatrix4x4 const* pv, int uni_mvp,
                         real cell_size);

#endif
