#ifndef __BK_MESH_SAMPLING_H__
#define __BK_MESH_SAMPLING_H__

// blackhart headers.
#include "foundation\BkExport.h"
#include "foundation\BkAtomicDataType.h"

// Forward declarations.
struct BkPoint3;

// ~~~~~ Dcl(PUBLIC) ~~~~~

/*! \brief Samples a list of triangles.
 *
 * \param vertices The vertices of each triangles. Must be sorted.
 * \param number_of_geoms The number of triangles.
 * \param number_of_points The number of points to sample.
 */
extern BK_API void	BkMeshSampling_Sample(struct BkPoint3 const* vertices, size_t const number_of_geoms, size_t const number_of_points);

#endif
