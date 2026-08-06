#ifndef __BK_STUDIO_TOOLBAR_HPP__
#define __BK_STUDIO_TOOLBAR_HPP__

namespace Studio {

/** Accumulates frame timing; call once per frame before Draw. */
void Toolbar_Update();

/**
 * Draws the top toolbar (point size + FPS).
 * @return Toolbar height in pixels (for placing other panels below).
 */
float Toolbar_Draw();

}  // namespace Studio

#endif
