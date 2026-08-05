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
 * Each cloud owns a BkTransform (position + orientation, identity by default).
 * Points stay in local space; the renderer applies the model matrix at draw
 * time. GetAABB returns local bounds; GetWorldAABB applies the transform.
 *
 * The renderer uploads the cloud to the GPU automatically through its cache.
 * When you are done, remove the cloud from the scene first, then release it.
 * That way the GPU copy can be marked dirty and freed on the next BkRender.
 */

// ~~~~~ Blackhart Headers ~~~~~

#include "foundation/BkAABB.h"
#include "foundation/BkAtomicDataType.h"
#include "foundation/BkExport.h"
#include "foundation/BkTransform.h"

// ~~~~~ Type Definitions ~~~~~

/**
 * @typedef BkPoint3
 * @brief 3D point type (see BkPoint3.h).
 */
typedef struct BkPoint3 BkPoint3;

/**
 * @typedef BkAABB
 * @brief Axis-aligned bounding box (see BkAABB.h).
 */
typedef struct BkAABB BkAABB;

/**
 * @typedef BkQuaternion
 * @brief Orientation quaternion (see BkQuaternion.h).
 */
typedef struct BkQuaternion BkQuaternion;

/**
 * @typedef BkPointCloud
 * @brief Opaque handle to a CPU point cloud (list of BkPoint3).
 */
typedef struct BkPointCloud BkPointCloud;

// ~~~~~ Dcl(PUBLIC) ~~~~~

/**
 * @brief Creates a point cloud from a PLY file.
 *
 * Loads vertex positions from the given PLY file and computes the local AABB.
 * The model transform is initialized to identity. Returns NULL if the path is
 * invalid, the file cannot be read, or the PLY content is not usable. Does not
 * abort the process on bad input.
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

/**
 * @brief Returns the local axis-aligned bounds of the cloud.
 *
 * Computed once when the cloud is created. Corners are in the cloud's local
 * space (no model transform applied).
 *
 * @param pointCloud Point cloud to query. Must not be NULL.
 */
extern BK_API BkAABB BkPointCloud_GetAABB(BkPointCloud const* pointCloud);

/**
 * @brief Returns the world-space AABB of the cloud.
 *
 * Transforms the eight corners of the local AABB by the model matrix, then
 * rebuilds an axis-aligned box. Non-const because the transform may rebuild
 * its cached matrix.
 *
 * @param pointCloud Point cloud to query. Must not be NULL.
 */
extern BK_API BkAABB BkPointCloud_GetWorldAABB(BkPointCloud* pointCloud);

/**
 * @brief Returns the cloud's model transform (position + orientation).
 *
 * Use BkTransform_* APIs for incremental Translate / Rotate. Must not be NULL.
 *
 * @param pointCloud Point cloud to query. Must not be NULL.
 */
extern BK_API struct BkTransform* BkPointCloud_GetTransform(
    BkPointCloud* pointCloud);

/**
 * @brief Sets the cloud's world position.
 *
 * @param pointCloud Point cloud to modify. Must not be NULL.
 * @param position New position. Must not be NULL.
 */
extern BK_API void BkPointCloud_SetPosition(BkPointCloud* pointCloud,
                                            BkPoint3 const* position);

/**
 * @brief Sets the cloud's world orientation.
 *
 * @param pointCloud Point cloud to modify. Must not be NULL.
 * @param orientation New orientation quaternion. Must not be NULL.
 */
extern BK_API void BkPointCloud_SetOrientation(BkPointCloud* pointCloud,
                                               BkQuaternion const* orientation);

#endif
