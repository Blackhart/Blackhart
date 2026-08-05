#ifndef __BK_POINT_CLOUD_H__
#define __BK_POINT_CLOUD_H__

/**
 * @file BkPointCloud.h
 * @brief Point cloud data living on the CPU.
 *
 * A BkPointCloud is a list of 3D positions (BkPoint3). There is no OpenGL
 * here: you load points (usually from a PLY file), read them with getters if
 * needed, and add the cloud to a BkScene so the renderer can draw it.
 *
 * The renderer uploads the cloud to the GPU automatically through its cache.
 * When you are done, remove the cloud from the scene first, then release it.
 * That way the GPU copy can be marked dirty and freed on the next BkRender.
 */

// ~~~~~ Blackhart Headers ~~~~~

#include "foundation/BkAtomicDataType.h"
#include "foundation/BkExport.h"

// ~~~~~ Type Definitions ~~~~~

/**
 * @typedef BkPoint3
 * @brief 3D point type (see BkPoint3.h).
 */
typedef struct BkPoint3 BkPoint3;

/**
 * @typedef BkPointCloud
 * @brief Opaque handle to a CPU point cloud (list of BkPoint3).
 */
typedef struct BkPointCloud BkPointCloud;

// ~~~~~ Dcl(PUBLIC) ~~~~~

/**
 * @brief Creates a point cloud from a PLY file.
 *
 * Loads vertex positions from the given PLY file. Returns NULL if the path is
 * invalid, the file cannot be read, or the PLY content is not usable
 * (missing header / vertices). Does not abort the process on bad input.
 *
 * @param filename Path to the PLY file to load.
 * @return New point cloud handle, or NULL on failure.
 */
extern BK_API BkPointCloud* BkPointCloud_CreateFromPlyFile(
    char const* filename);

/**
 * @brief Releases a point cloud and frees its CPU resources.
 *
 * Call BkScene_RemoveCloud first so the GPU entry is marked dirty; the
 * renderer frees GPU resources on the next BkRender. Sets @p pointCloud to
 * NULL.
 *
 * @param pointCloud Pointer to the point cloud handle to release.
 */
extern BK_API void BkPointCloud_Release(BkPointCloud** pointCloud);

/**
 * @brief Returns the number of points in the cloud.
 *
 * @param pointCloud Point cloud to query. Must not be NULL.
 * @return Point count (0 if empty).
 */
extern BK_API size_t BkPointCloud_GetCount(BkPointCloud const* pointCloud);

/**
 * @brief Returns a read-only pointer to the contiguous point array.
 *
 * @param pointCloud Point cloud to query. Must not be NULL.
 * @return Pointer to BkPoint3[count], or NULL if there is no data.
 */
extern BK_API BkPoint3 const* BkPointCloud_GetPoints(
    BkPointCloud const* pointCloud);

#endif
