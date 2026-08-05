#ifndef __BK_GPU_CACHE_H__
#define __BK_GPU_CACHE_H__

/**
 * @file BkGpuCache.h
 * @brief Remembers which point clouds are already on the GPU.
 *
 * The cache maps each CPU BkPointCloud to its BkGpuPointCloud. The first
 * time a cloud is needed for drawing, it is uploaded; later frames reuse
 * that GPU copy.
 *
 * When a cloud leaves the scene, MarkDirty tags its GPU entry. The actual
 * free happens later in FlushDirty (usually at the start of BkRender), so
 * it is safe to release the CPU cloud right after RemoveCloud.
 *
 * Internal only — created and owned by the renderer.
 */

// ~~~~~ Type Definitions ~~~~~

/**
 * @typedef BkPointCloud
 * @brief Opaque CPU point cloud handle (see BkPointCloud.h).
 */
typedef struct BkPointCloud BkPointCloud;

/**
 * @typedef BkGpuPointCloud
 * @brief Opaque GPU point cloud handle (see BkGpuPointCloud.h).
 */
typedef struct BkGpuPointCloud BkGpuPointCloud;

/**
 * @typedef BkGpuCache
 * @brief Opaque cache mapping CPU clouds to GPU resources.
 */
typedef struct BkGpuCache BkGpuCache;

// ~~~~~ Dcl(INTERNAL) ~~~~~

/**
 * @brief Creates an empty GPU cache.
 *
 * @return New cache handle, or NULL on allocation failure.
 */
extern BkGpuCache* _BkGpuCache_Create(void);

/**
 * @brief Destroys a GPU cache and all cached GPU resources.
 *
 * Sets @p cache to NULL.
 *
 * @param cache Pointer to the cache handle to destroy.
 */
extern void _BkGpuCache_Destroy(BkGpuCache** cache);

/**
 * @brief Returns the GPU resource for @p cloud, uploading if missing.
 *
 * Identity is by pointer: the same BkPointCloud* maps to one GPU entry.
 * If the entry was marked dirty (e.g. cloud re-added to the scene before
 * release), the dirty flag is cleared. Does not take ownership of @p cloud.
 *
 * @param cache GPU cache.
 * @param cloud CPU point cloud to resolve.
 * @return Cached or newly uploaded GPU handle, or NULL on failure.
 */
extern BkGpuPointCloud* _BkGpuCache_GetOrUpload(BkGpuCache* cache,
                                                BkPointCloud const* cloud);

/**
 * @brief Marks the GPU entry for @p cloud as dirty (deferred unload).
 *
 * No-op if @p cache is NULL, @p cloud is NULL, or the cloud is not cached.
 * Safe after the CPU cloud is released as long as FlushDirty does not
 * dereference the cloud pointer.
 *
 * @param cache GPU cache.
 * @param cloud CPU point cloud whose GPU entry should be unloaded later.
 */
extern void _BkGpuCache_MarkDirty(BkGpuCache* cache,
                                  BkPointCloud const* cloud);

/**
 * @brief Releases and removes all dirty GPU entries.
 *
 * Does not touch CPU point clouds (pointers may already be invalid).
 *
 * @param cache GPU cache.
 */
extern void _BkGpuCache_FlushDirty(BkGpuCache* cache);

/**
 * @brief Unloads the GPU resource for @p cloud immediately if present.
 *
 * No-op if @p cloud is not in the cache.
 *
 * @param cache GPU cache.
 * @param cloud CPU point cloud whose GPU entry should be removed.
 */
extern void _BkGpuCache_Remove(BkGpuCache* cache, BkPointCloud const* cloud);

/**
 * @brief Releases all cached GPU resources.
 *
 * The cache remains usable after this call.
 *
 * @param cache GPU cache to clear.
 */
extern void _BkGpuCache_Clear(BkGpuCache* cache);

#endif
