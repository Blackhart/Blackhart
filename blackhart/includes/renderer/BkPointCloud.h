#ifndef __BK_POINT_CLOUD_H__
#define __BK_POINT_CLOUD_H__

/**
 * @file BkPointCloud.h
 * @brief Defines the BkPointCloud structure and functions for point cloud
 * management in 3D rendering.
 *
 * This file provides the definition of the BkPointCloud struct, which
 * represents a point cloud with a list of points. It includes functions for
 * initializing, adding, and removing points from the point cloud.
 */

// ~~~~~ Blackhart Headers ~~~~~

#include "foundation/BkArray.h"
#include "foundation/BkExport.h"

// ~~~~~ Type Definitions ~~~~~

/**
 * @struct BkPointCloud
 * @brief Structure representing a point cloud in 3D rendering.
 *
 * The point cloud contains a list of points that can be rendered.
 */
struct BkPointCloud {
  struct BkArray* points; /**< List of points in the point cloud. */
};

// ~~~~~ Dcl(PUBLIC) ~~~~~

/**
 * @brief Creates a point cloud from a PLY file.
 *
 * Loads vertex positions from the given PLY file. Returns NULL if the path is
 * invalid, the file cannot be read, or the PLY content is not usable
 * (missing header / vertices). Does not abort the process on bad input.
 *
 * @param filename Path to the PLY file to load.
 * @return Pointer to the newly created point cloud, or NULL on failure.
 */
extern BK_API struct BkPointCloud* BkPointCloud_CreateFromPlyFile(
    char const* filename);

/**
 * @brief Releases a point cloud and frees its resources.
 *
 * Deletes the point cloud and frees the memory allocated for the point cloud
 * structure. The point cloud pointer is set to NULL after release.
 *
 * @param pointCloud Pointer to a pointer to the point cloud to release. The
 * pointer will be set to NULL.
 */
extern BK_API void BkPointCloud_Release(struct BkPointCloud** pointCloud);

#endif