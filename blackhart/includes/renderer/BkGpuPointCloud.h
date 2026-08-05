#ifndef __BK_GPU_POINT_CLOUD_H__
#define __BK_GPU_POINT_CLOUD_H__

/**
 * @file BkGpuPointCloud.h
 * @brief Point cloud data living on the GPU.
 *
 * This is the drawable version of a BkPointCloud. Upload copies the CPU
 * positions into a VBO, sets up a VAO (attribute 0 = xyz), and Render draws
 * them as GL_POINTS. Upload does not take ownership of the CPU cloud.
 *
 * Applications never create these directly. BkGpuCache creates them on
 * first use, reuses them across frames, and releases them when they are
 * marked dirty and flushed.
 */

// ~~~~~ Type Definitions ~~~~~

/**
 * @typedef BkPointCloud
 * @brief Opaque CPU point cloud handle (see BkPointCloud.h).
 */
typedef struct BkPointCloud BkPointCloud;

/**
 * @typedef BkGpuPointCloud
 * @brief Opaque GPU point cloud handle (VAO, VBO, draw count).
 */
typedef struct BkGpuPointCloud BkGpuPointCloud;

// ~~~~~ Dcl(INTERNAL) ~~~~~

/**
 * @brief Uploads a CPU point cloud to the GPU.
 *
 * Creates a VBO (via BkBuffer) and a VAO with attribute 0 = position xyz.
 * Requires a valid OpenGL context. Does not take ownership of @p cloud.
 *
 * @param cloud Source CPU point cloud (must contain BkPoint3 elements).
 * @return New GPU handle, or NULL on failure.
 */
extern BkGpuPointCloud* _BkGpuPointCloud_Upload(BkPointCloud const* cloud);

/**
 * @brief Releases GPU resources for a point cloud.
 *
 * Deletes the VAO and VBO, then frees the handle. Sets @p gpu to NULL.
 *
 * @param gpu Pointer to the GPU handle to release.
 */
extern void _BkGpuPointCloud_Release(BkGpuPointCloud** gpu);

/**
 * @brief Draws the GPU point cloud.
 *
 * Binds the VAO and issues glDrawArrays(GL_POINTS, ...).
 * Shader program and uniforms must already be set by the caller.
 *
 * @param gpu GPU point cloud to draw.
 */
extern void _BkGpuPointCloud_Render(BkGpuPointCloud const* gpu);

#endif
