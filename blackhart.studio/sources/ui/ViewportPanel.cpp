#include "ui/ViewportPanel.hpp"

#include <imgui.h>

namespace Studio {

void ViewportPanel_Draw(float const toolbar_h, float const left_sidebar_w,
                        float const right_sidebar_w, ViewportPanelState* out) {
  ImGuiViewport const* main = ImGui::GetMainViewport();
  ImGuiIO const& io = ImGui::GetIO();

  float const x = main->WorkPos.x + left_sidebar_w;
  float const y = main->WorkPos.y + toolbar_h;
  float const w = main->WorkSize.x - left_sidebar_w - right_sidebar_w;
  float const h = main->WorkSize.y - toolbar_h;

  if (out != nullptr) {
    out->framebuffer = {};
    out->hovered = false;
  }

  if (w < 1.0f || h < 1.0f) {
    return;
  }

  ImGui::SetNextWindowPos(ImVec2(x, y), ImGuiCond_Always);
  ImGui::SetNextWindowSize(ImVec2(w, h), ImGuiCond_Always);

  ImGuiWindowFlags const flags =
      ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize |
      ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse |
      ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse |
      ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus |
      ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoSavedSettings;

  ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
  ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
  ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

  if (!ImGui::Begin("##SceneViewport", nullptr, flags)) {
    ImGui::End();
    ImGui::PopStyleVar(3);
    return;
  }

  ImVec2 const content_pos = ImGui::GetCursorScreenPos();
  ImVec2 const content_size = ImGui::GetContentRegionAvail();

  ImGui::InvisibleButton("##scene_viewport_input", content_size);
  bool const hovered = ImGui::IsItemHovered();

  if (out != nullptr && content_size.x > 0.0f && content_size.y > 0.0f) {
    float const sx = io.DisplayFramebufferScale.x;
    float const sy = io.DisplayFramebufferScale.y;
    out->framebuffer.width = static_cast<int>(content_size.x * sx);
    out->framebuffer.height = static_cast<int>(content_size.y * sy);
    out->framebuffer.x = static_cast<int>(content_pos.x * sx);
    // OpenGL origin is bottom-left; ImGui is top-left.
    out->framebuffer.y = static_cast<int>(
        (io.DisplaySize.y - (content_pos.y + content_size.y)) * sy);
    out->hovered = hovered;
  }

  ImGui::End();
  ImGui::PopStyleVar(3);
}

}  // namespace Studio
