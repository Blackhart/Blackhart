#include "ui/PropertiesPanel.hpp"

#include <imgui.h>

#include "../../blackhart/export/cpp/Blackhart.hpp"
#include "ui/StudioLayout.hpp"

namespace Studio {

namespace {

bool g_aabb_draw = true;

void DrawReadonlyFloat3(char const* label, float x, float y, float z) {
  float v[3] = {x, y, z};
  ImGui::BeginDisabled();
  ImGui::InputFloat3(label, v, "%.3f");
  ImGui::EndDisabled();
}

}  // namespace

bool PropertiesPanel_Draw(BkPointCloud* cloud) {
  ImGuiViewport const* viewport = ImGui::GetMainViewport();

  float const x =
      viewport->WorkPos.x + viewport->WorkSize.x - kRightSidebarWidth;
  ImGui::SetNextWindowPos(ImVec2(x, viewport->WorkPos.y + kToolbarHeight),
                          ImGuiCond_Always);
  ImGui::SetNextWindowSize(
      ImVec2(kRightSidebarWidth, viewport->WorkSize.y - kToolbarHeight),
      ImGuiCond_Always);

  ImGuiWindowFlags const flags =
      ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize |
      ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoBringToFrontOnFocus |
      ImGuiWindowFlags_NoSavedSettings;

  ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
  ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);

  if (!ImGui::Begin("Properties", nullptr, flags)) {
    ImGui::End();
    ImGui::PopStyleVar(2);
    return g_aabb_draw;
  }

  if (cloud == nullptr) {
    ImGui::TextDisabled("No selection");
    ImGui::End();
    ImGui::PopStyleVar(2);
    return g_aabb_draw;
  }

  struct BkTransform* transform = BkPointCloud_GetTransform(cloud);
  struct BkPoint3 const& pos = transform->position;
  struct BkEulerAngles const euler =
      BkEulerAngles_FromBkQuaternion(&transform->orientation);

  ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.55f, 0.57f, 0.60f, 1.00f));
  ImGui::TextUnformatted("TRANSFORM");
  ImGui::PopStyleColor();
  ImGui::Separator();
  ImGui::Spacing();
  DrawReadonlyFloat3("Position", static_cast<float>(pos.x),
                     static_cast<float>(pos.y), static_cast<float>(pos.z));
  DrawReadonlyFloat3("Rotation", static_cast<float>(euler.x),
                     static_cast<float>(euler.y), static_cast<float>(euler.z));

  ImGui::Spacing();
  ImGui::Spacing();
  ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.55f, 0.57f, 0.60f, 1.00f));
  ImGui::TextUnformatted("POINT CLOUD");
  ImGui::PopStyleColor();
  ImGui::Separator();
  ImGui::Spacing();
  ImGui::Text("Points: %zu", BkPointCloud_GetCount(cloud));
  ImGui::Text("Colors: %s", BkPointCloud_HasColors(cloud) ? "yes" : "no");

  ImGui::Spacing();
  ImGui::Spacing();
  ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.55f, 0.57f, 0.60f, 1.00f));
  ImGui::TextUnformatted("AABB");
  ImGui::PopStyleColor();
  ImGui::Separator();
  ImGui::Spacing();
  ImGui::Checkbox("Draw", &g_aabb_draw);

  struct BkAABB const world = BkPointCloud_GetWorldAABB(cloud);
  struct BkAABB const local = BkPointCloud_GetAABB(cloud);

  ImGui::Spacing();
  ImGui::TextUnformatted("World");
  ImGui::Text("  min  %.3f  %.3f  %.3f", static_cast<float>(world.min.x),
              static_cast<float>(world.min.y), static_cast<float>(world.min.z));
  ImGui::Text("  max  %.3f  %.3f  %.3f", static_cast<float>(world.max.x),
              static_cast<float>(world.max.y), static_cast<float>(world.max.z));

  ImGui::Spacing();
  ImGui::TextUnformatted("Local");
  ImGui::Text("  min  %.3f  %.3f  %.3f", static_cast<float>(local.min.x),
              static_cast<float>(local.min.y), static_cast<float>(local.min.z));
  ImGui::Text("  max  %.3f  %.3f  %.3f", static_cast<float>(local.max.x),
              static_cast<float>(local.max.y), static_cast<float>(local.max.z));

  ImGui::End();
  ImGui::PopStyleVar(2);
  return g_aabb_draw;
}

}  // namespace Studio
