#ifndef __BK_STUDIO_SCENE_PANEL_HPP__
#define __BK_STUDIO_SCENE_PANEL_HPP__

extern "C" {
#include "foundation/BkAtomicDataType.h"
}

struct BkOrbitalCamera;
struct BkPointCloud;
struct BkScene;

namespace Studio {

/**
 * Draws the Scene hierarchy contents (for use inside a parent window / tab).
 * Selecting an entry frames the orbital camera on that cloud.
 */
void ScenePanel_Draw(BkScene* scene, BkOrbitalCamera* camera,
                     real camera_fov_deg, real camera_frame_margin);

/** Selected hierarchy index, or -1 if none. */
int ScenePanel_GetSelectedIndex(void);

/** Selected cloud, or NULL if none / out of range. */
BkPointCloud* ScenePanel_GetSelectedCloud(BkScene* scene);

/**
 * Selects @p cloud in the hierarchy (by pointer). Clears selection if @p cloud
 * is NULL or not in the scene.
 */
void ScenePanel_SelectCloud(BkScene* scene, BkPointCloud* cloud);

}  // namespace Studio

#endif
