#ifndef __BK_MESH_SAMPLING_H__
#define __BK_MESH_SAMPLING_H__

/**
 * @file BkMeshSampling.h
 * @brief Defines functions for sampling points on triangular meshes.
 *
 * This file provides functions for generating sample points on triangular mesh surfaces,
 * which is useful for point-based rendering, collision detection, or mesh analysis.
 */

// ~~~~~ Blackhart Headers ~~~~~

#include "foundation/BkExport.h"
#include "foundation/BkAtomicDataType.h"

// ~~~~~ Forward declarations ~~~~~

struct BkPoint3;

// ~~~~~ Dcl(PUBLIC) ~~~~~

/**
 * @brief Samples a list of triangles to generate points on the mesh surface.
 *
 * Generates a specified number of sample points distributed across the triangles
 * in the mesh. The vertices array should contain the triangle vertices sorted
 * in a consistent order (e.g., all vertices of triangle 0, then all vertices of triangle 1, etc.).
 *
 * @param vertices Pointer to an array of BkPoint3 vertices representing the triangles.
 *                 The vertices must be sorted such that each triangle's three vertices
 *                 are consecutive in the array (e.g., [v0, v1, v2, v3, v4, v5, ...] for
 *                 triangles (v0,v1,v2) and (v3,v4,v5)).
 * @param number_of_geoms The number of triangles in the mesh.
 * @param number_of_points The total number of sample points to generate across all triangles.
 */
extern BK_API void	BkMeshSampling_Sample(struct BkPoint3 const* vertices, size_t const number_of_geoms, size_t const number_of_points);

#endif
