#ifndef __BK_PROJECTION_H__
#define __BK_PROJECTION_H__

/**
 * @file BkProjection.h
 * @brief Defines functions for creating projection matrices.
 *
 * This file provides functions for creating various types of projection
 * matrices, such as perspective projections for 3D rendering.
 */

// ~~~~~ Blackhart Headers ~~~~~

#include "foundation/BkAtomicDataType.h"
#include "foundation/BkExport.h"
#include "foundation/BkMatrix4x4.h"

// ~~~~~ Dcl(PUBLIC) ~~~~~

/**
 * @brief Creates a perspective projection matrix.
 *
 * The perspective projection matrix transforms 3D coordinates in view space
 * into normalized device coordinates (NDC) with perspective correction. Objects
 * closer to the camera appear larger, creating a realistic 3D perspective
 * effect.
 *
 * @param fov The field of view angle in degrees (typically 45-90 degrees).
 *            A smaller value creates a narrower view (zoom in), a larger value
 *            creates a wider view (zoom out).
 * @param aspect_ratio The aspect ratio of the viewport (width / height).
 *                     This should match the window's aspect ratio to avoid
 * distortion.
 * @param near The distance to the near clipping plane. Objects closer than this
 *             distance are not rendered. Must be positive and less than 'far'.
 * @param far The distance to the far clipping plane. Objects farther than this
 *            distance are not rendered. Must be greater than 'near'.
 * @return A BkMatrix4x4 containing the perspective projection matrix.
 *
 * @note The near and far planes define the depth range that will be visible.
 *       It's recommended to keep the ratio between far and near as small as
 *       possible to maintain depth buffer precision.
 */
extern BK_API struct BkMatrix4x4 BkProjection_Perspective(
    real const fov, real const aspect_ratio, const real near, const real far);

#endif
