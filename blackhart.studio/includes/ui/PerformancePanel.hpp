#ifndef __BK_STUDIO_PERFORMANCE_PANEL_HPP__
#define __BK_STUDIO_PERFORMANCE_PANEL_HPP__

namespace Studio {

/** Accumulates frame timing; call once per frame before Draw. */
void PerformancePanel_Update();

/** Draws the FPS / frame-time ImGui window. */
void PerformancePanel_Draw();

}  // namespace Studio

#endif
