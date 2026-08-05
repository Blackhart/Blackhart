#ifndef __BK_AABB_H__
#define __BK_AABB_H__

/**
 * @file BkAABB.h
 * @brief Axis-aligned bounding box in 3D.
 *
 * An AABB is the smallest box aligned with the world axes that contains a set
 * of points. It is stored as two corners: min and max. Use it to frame a
 * camera, build spatial indexes later, or combine several bounds with Union.
 */

// ~~~~~ Blackhart Headers ~~~~~

#include "foundation/BkAtomicDataType.h"
#include "foundation/BkExport.h"
#include "foundation/BkPoint3.h"
#include "foundation/BkVector3.h"

// ~~~~~ Type Definitions ~~~~~

/**
 * @struct BkAABB
 * @brief Axis-aligned box defined by minimum and maximum corners.
 */
struct BkAABB {
  struct BkPoint3 min; /**< Corner with the smallest x, y, and z. */
  struct BkPoint3 max; /**< Corner with the largest x, y, and z. */
};

// ~~~~~ Dcl(PUBLIC) ~~~~~

/**
 * @brief Returns an AABB collapsed at the origin (min = max = 0).
 */
extern BK_API struct BkAABB BkAABB_Zero(void);

/**
 * @brief Builds an AABB from two opposite corners.
 *
 * Does not reorder the components: the caller must pass a true min and max.
 *
 * @param min Minimum corner.
 * @param max Maximum corner.
 */
extern BK_API struct BkAABB BkAABB_FromMinMax(struct BkPoint3 const* min,
                                              struct BkPoint3 const* max);

/**
 * @brief Computes the AABB of a contiguous array of points.
 *
 * If @p count is 0 or @p points is NULL, returns BkAABB_Zero().
 *
 * @param points Pointer to the first point.
 * @param count Number of points.
 */
extern BK_API struct BkAABB BkAABB_FromPoints(struct BkPoint3 const* points,
                                              size_t const count);

/**
 * @brief Returns the center of the box (midpoint of min and max).
 */
extern BK_API struct BkPoint3 BkAABB_Center(struct BkAABB const* aabb);

/**
 * @brief Returns the full size of the box (max - min) as a vector.
 */
extern BK_API struct BkVector3 BkAABB_Size(struct BkAABB const* aabb);

/**
 * @brief Returns the tightest AABB that contains both @p a and @p b.
 */
extern BK_API struct BkAABB BkAABB_Union(struct BkAABB const* a,
                                         struct BkAABB const* b);

#endif
