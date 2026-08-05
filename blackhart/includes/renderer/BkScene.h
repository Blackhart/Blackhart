#ifndef __BK_SCENE_H__
#define __BK_SCENE_H__

/**
 * @file BkScene.h
 * @brief Scene container for point cloud rendering.
 *
 * A scene holds the list of point clouds to draw.
 */

// ~~~~~ Blackhart Headers ~~~~~

#include "foundation/BkExport.h"
#include "foundation/BkList.h"

// ~~~~~ Forward declarations ~~~~~

struct BkPointCloud;

// ~~~~~ Type Definitions ~~~~~

/**
 * @struct BkScene
 * @brief Scene containing point clouds to render.
 */
struct BkScene {
  struct BkList* clouds; /**< List of BkPointCloud pointers. */
};

// ~~~~~ Dcl(PUBLIC) ~~~~~

/**
 * @brief Initializes an empty scene.
 *
 * @return A scene with an empty cloud list.
 */
extern BK_API struct BkScene BkScene_Initialize(void);

/**
 * @brief Releases scene list resources.
 *
 * Does not release the point clouds themselves; the caller owns them.
 *
 * @param obj Scene to uninitialize.
 */
extern BK_API void BkScene_Uninitialize(struct BkScene* obj);

/**
 * @brief Adds a point cloud to the scene.
 *
 * @param scene Target scene.
 * @param cloud Point cloud to add (not owned by the scene).
 */
extern BK_API void BkScene_AddCloud(struct BkScene* scene,
                                    struct BkPointCloud* cloud);

/**
 * @brief Removes a point cloud from the scene.
 *
 * @param scene Target scene.
 * @param cloud Point cloud to remove.
 */
extern BK_API void BkScene_RemoveCloud(struct BkScene* scene,
                                       struct BkPointCloud* cloud);

#endif
