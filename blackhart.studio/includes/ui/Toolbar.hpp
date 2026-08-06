#ifndef __BK_STUDIO_TOOLBAR_HPP__
#define __BK_STUDIO_TOOLBAR_HPP__

namespace Studio {

/** Viewport helper toggles owned by the toolbar (not by the renderer). */
struct ToolbarViewportHelpers {
  bool grid_visible = true;
  float grid_cell_size = 1.0f;
  bool orientation_gizmo_visible = true;
};

/** Accumulates frame timing; call once per frame before Draw. */
void Toolbar_Update();

/**
 * Draws the top toolbar (point size + helper toggles + FPS).
 * @return Toolbar height in pixels (for placing other panels below).
 */
float Toolbar_Draw();

/** Latest helper toggles after Toolbar_Draw. */
ToolbarViewportHelpers const& Toolbar_GetViewportHelpers();

}  // namespace Studio

#endif
