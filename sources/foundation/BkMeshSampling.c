// Standard headers.
#include <stdlib.h>
#include <math.h>

// Blackhart.foundation headers.
#include "foundation\BkMeshSampling.h"
#include "foundation\BkPoint3.h"
#include "foundation\BkError.h"
#include "foundation\BkMath.h"

// ~~~~~ Dcl(PRIVATE) ~~~~~

/*! \brief Computes the scale factor of all geometries.
 *
 * \param scale_factors The array of scale factors to fill. [OUT]
 * \param total_scale_factors The total amount of scale factor. [OUT]
 * \param vertices The array of triangle's vertices.
 * \param number_of_geoms The number of geometries.
 */
static void	__BkMeshSampling_ComputeScaleFactors(real* __restrict scale_factors, real* __restrict total_scale_factors, struct BkPoint3 const* vertices, size_t const number_of_geoms);

/*! \brief Computes the barycentric step per geometries according to their scale factors and the total of points needed.
 *
 * \param barycentric_steps The numbers of points per triangles. [OUT]
 * \param scale_factors The array of scale factors.
 * \param total_scale_factors The total amount of scale factors.
 * \param number_of_geoms The number of geometries.
 * \param total_of_points The number of points to sample.
 */
static void	__BkMeshSampling_ComputeBarycentricSteps(real* __restrict barycentric_steps, real const* scale_factors, real const total_scale_factors, size_t const number_of_geoms, size_t const total_of_points);

// ~~~~~ Def(PUBLIC) ~~~~~

void	BkMeshSampling_Sample(struct BkPoint3 const* vertices, size_t const number_of_geoms, size_t const number_of_points)
{
	real* tmp = malloc(number_of_geoms * sizeof(real));
	BK_ERROR(BK_ISNULL(tmp), "Memory system failed to allocate memory block!");

	real const total_scale_factors = 0;

	// Computes both scale factor of each geometries and total amount of overall scale factors.
	__BkMeshSampling_ComputeScaleFactors(tmp, &total_scale_factors, vertices, number_of_geoms);

	// Computes the kernel size according to the number of points and the scale factor of each triangles.
	__BkMeshSampling_ComputeBarycentricSteps(tmp, tmp, total_scale_factors, number_of_geoms, number_of_points);
}

// ~~~~~ Def(PRIVATE) ~~~~~

void	__BkMeshSampling_ComputeScaleFactors(real* __restrict scale_factors, real* __restrict total_scale_factors, struct BkPoint3 const* vertices, size_t const number_of_geoms)
{
	BK_ASSERT(BK_ISNULL(scale_factors));
	BK_ASSERT(BK_ISNULL(total_scale_factors));
	BK_ASSERT(BK_ISNULL(vertices));

	// Total scale factors will be summed in a temporary variable in order to avoid cache misses.
	real total_scale_factors_tmp = 0;

	for (size_t i = 0, offset = 0; i < number_of_geoms; i++, offset += 3)
	{
		struct BkPoint3 const* A = &vertices[offset];
		struct BkPoint3 const* B = &vertices[offset + 1];
		struct BkPoint3 const* C = &vertices[offset + 2];

		struct BkVector3 const AB = BkPoint3_Sub_BkPoint3(B, A);
		struct BkVector3 const AC = BkPoint3_Sub_BkPoint3(C, A);

		struct BkVector3 const D = BkVector3_Cross(&AB, &AC);

		scale_factors[i] = D.x + D.y + D.z;

		total_scale_factors_tmp += scale_factors[i];
	}

	*total_scale_factors = total_scale_factors_tmp;
}

void	__BkMeshSampling_ComputeBarycentricSteps(real* __restrict barycentric_steps, real const* scale_factors, real const total_scale_factors, size_t const number_of_geoms, size_t const total_of_points)
{
	BK_ASSERT(BK_ISNULL(barycentric_steps));
	BK_ASSERT(BK_ISNULL(scale_factors));

	for (size_t i = 0; i < number_of_geoms; i++)
	{
		size_t const number_of_points_per_geoms = (scale_factors[i] / total_scale_factors) * total_of_points;
		size_t const kernel_size_per_geoms = sqrt((double)number_of_points_per_geoms * 3);
		barycentric_steps[i] = BK_REAL(1.0) / (kernel_size_per_geoms + 1);
	}
}
