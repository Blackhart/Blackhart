#ifndef __BK_STUDIO_PROPERTIES_PANEL_HPP__
#define __BK_STUDIO_PROPERTIES_PANEL_HPP__

struct BkOrbitalCamera;
struct BkPointCloud;

namespace Studio {

/**
 * Draws the right-hand Properties panel for @p cloud (NULL = empty state).
 * When the transform changes, retargets @p camera to the world AABB center.
 * @return Whether world AABB wireframe draw is enabled.
 */
bool PropertiesPanel_Draw(BkPointCloud* cloud, BkOrbitalCamera* camera);

}  // namespace Studio

#endif
