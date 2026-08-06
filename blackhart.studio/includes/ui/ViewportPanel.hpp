#ifndef __BK_STUDIO_VIEWPORT_PANEL_HPP__
#define __BK_STUDIO_VIEWPORT_PANEL_HPP__

namespace Studio {

struct ViewportRect {
  int x = 0;
  int y = 0;
  int width = 0;
  int height = 0;
};

struct ViewportPanelState {
  ViewportRect framebuffer = {};
  bool hovered = false;
};

/**
 * Draws the Scene host panel and fills @p out with its OpenGL framebuffer
 * rectangle (bottom-left origin) plus hover state for camera input.
 */
void ViewportPanel_Draw(float toolbar_h, float left_sidebar_w,
                        float right_sidebar_w, ViewportPanelState* out);

}  // namespace Studio

#endif
