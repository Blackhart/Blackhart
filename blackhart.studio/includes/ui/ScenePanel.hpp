#ifndef __BK_STUDIO_SCENE_PANEL_HPP__
#define __BK_STUDIO_SCENE_PANEL_HPP__

struct BkPointCloud;
struct BkScene;

namespace Studio {

/**
 * Draws the Scene hierarchy contents (for use inside a parent window / tab).
 * Selection is visual only for now.
 */
void ScenePanel_Draw(BkScene* scene);

/** Selected hierarchy index, or -1 if none. */
int ScenePanel_GetSelectedIndex(void);

/** Selected cloud, or NULL if none / out of range. */
BkPointCloud* ScenePanel_GetSelectedCloud(BkScene* scene);

}  // namespace Studio

#endif
