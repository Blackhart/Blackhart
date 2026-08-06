#ifndef __BK_STUDIO_PROPERTIES_PANEL_HPP__
#define __BK_STUDIO_PROPERTIES_PANEL_HPP__

struct BkPointCloud;

namespace Studio {

/**
 * Draws the right-hand Properties panel for @p cloud (NULL = empty state).
 * @return Whether world AABB wireframe draw is enabled.
 */
bool PropertiesPanel_Draw(BkPointCloud* cloud);

}  // namespace Studio

#endif
