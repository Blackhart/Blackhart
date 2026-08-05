#ifndef __BK_SCENE_H__
#define __BK_SCENE_H__

/**
 * @file BkScene.h
 * @brief List of point clouds to draw.
 *
 * A scene is the collection of BkPointCloud pointers you want on screen.
 * You create clouds yourself, add them to the scene, and pass the scene to
 * BkRender each frame. The scene does not own the clouds — releasing the
 * scene only clears the list.
 *
 * Removing a cloud from the scene also marks its GPU cache entry as dirty.
 * After RemoveCloud you can safely release the CPU cloud; FlushDirty in
 * BkRender will free the GPU resources on the next frame.
 */

// ~~~~~ Blackhart Headers ~~~~~

#include "foundation/BkAtomicDataType.h"
#include "foundation/BkExport.h"

// ~~~~~ Type Definitions ~~~~~

/**
 * @typedef BkPointCloud
 * @brief Opaque CPU point cloud handle (see BkPointCloud.h).
 */
typedef struct BkPointCloud BkPointCloud;

/**
 * @typedef BkScene
 * @brief Opaque scene handle containing point clouds to render.
 */
typedef struct BkScene BkScene;

// ~~~~~ Dcl(PUBLIC) ~~~~~

/**
 * @brief Creates an empty scene.
 *
 * @return New scene handle, or NULL on allocation failure.
 */
extern BK_API BkScene* BkScene_Create(void);

/**
 * @brief Releases scene list resources.
 *
 * Does not release the point clouds themselves; the caller owns them.
 * Sets @p scene to NULL.
 *
 * @param scene Pointer to the scene handle to release.
 */
extern BK_API void BkScene_Release(BkScene** scene);

/**
 * @brief Adds a point cloud to the scene.
 *
 * @param scene Target scene.
 * @param cloud Point cloud to add (not owned by the scene).
 */
extern BK_API void BkScene_AddCloud(BkScene* scene, BkPointCloud* cloud);

/**
 * @brief Removes a point cloud from the scene.
 *
 * Also marks the matching GPU cache entry as dirty (deferred unload on the
 * next BkRender). Typical teardown:
 *   BkScene_RemoveCloud(scene, cloud);
 *   BkPointCloud_Release(&cloud);
 *
 * @param scene Target scene.
 * @param cloud Point cloud to remove.
 */
extern BK_API void BkScene_RemoveCloud(BkScene* scene, BkPointCloud* cloud);

/**
 * @brief Returns the number of point clouds in the scene.
 *
 * @param scene Scene to query. Must not be NULL.
 * @return Cloud count.
 */
extern BK_API size_t BkScene_GetCloudCount(BkScene const* scene);

/**
 * @brief Returns the point cloud at @p index.
 *
 * @param scene Scene to query. Must not be NULL.
 * @param index Zero-based cloud index.
 * @return Point cloud handle, or NULL if @p index is out of range.
 */
extern BK_API BkPointCloud* BkScene_GetCloud(BkScene const* scene,
                                             size_t const index);

#endif
