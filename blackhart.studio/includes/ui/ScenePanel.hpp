#ifndef __BK_STUDIO_SCENE_PANEL_HPP__
#define __BK_STUDIO_SCENE_PANEL_HPP__

struct BkScene;

namespace Studio {

/**
 * Draws the Scene hierarchy contents (for use inside a parent window / tab).
 * Selection is visual only for now.
 */
void ScenePanel_Draw(BkScene* scene);

}  // namespace Studio

#endif
