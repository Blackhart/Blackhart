#include "ui/PropertiesPanel.hpp"

#include <imgui.h>

#include "../../blackhart/export/cpp/Blackhart.hpp"
#include "ui/CameraFrame.hpp"
#include "ui/StudioLayout.hpp"

namespace Studio {

namespace {

bool g_aabb_draw = true;

BkPointCloud* g_bound_cloud = nullptr;
float g_position[3] = {0.0f, 0.0f, 0.0f};
float g_orientation[3] = {0.0f, 0.0f, 0.0f};

void SyncTransformBuffers(BkPointCloud* cloud) {
  struct BkTransform* transform = BkPointCloud_GetTransform(cloud);
  struct BkPoint3 const& pos = transform->position;
  struct BkEulerAngles const euler =
      BkEulerAngles_FromBkQuaternion(&transform->orientation);

  g_position[0] = static_cast<float>(pos.x);
  g_position[1] = static_cast<float>(pos.y);
  g_position[2] = static_cast<float>(pos.z);
  g_orientation[0] = static_cast<float>(euler.x);
  g_orientation[1] = static_cast<float>(euler.y);
  g_orientation[2] = static_cast<float>(euler.z);
  g_bound_cloud = cloud;
}

bool DrawEditableXyz(char const* label, char const* id, float values[3],
                     float speed, char const* format) {
  ImGui::AlignTextToFramePadding();
  ImGui::TextUnformatted(label);
  ImGui::SameLine(96.0f);
  ImGui::SetNextItemWidth(-1.0f);
  return ImGui::DragFloat3(id, values, speed, 0.0f, 0.0f, format);
}

}  // namespace

bool PropertiesPanel_Draw(BkPointCloud* cloud, BkOrbitalCamera* camera) {
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
    g_bound_cloud = nullptr;
    ImGui::TextDisabled("No selection");
    ImGui::End();
    ImGui::PopStyleVar(2);
    return g_aabb_draw;
  }

  if (cloud != g_bound_cloud) {
    SyncTransformBuffers(cloud);
  }

  ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.55f, 0.57f, 0.60f, 1.00f));
  ImGui::TextUnformatted("TRANSFORM");
  ImGui::PopStyleColor();
  ImGui::Separator();
  ImGui::Spacing();

  if (DrawEditableXyz("Position:", "##prop_position", g_position, 0.01f,
                      "%.3f")) {
    struct BkPoint3 const position = {
        BK_REAL(g_position[0]), BK_REAL(g_position[1]), BK_REAL(g_position[2])};
    BkPointCloud_SetPosition(cloud, &position);
    TrackCameraOn(cloud, camera);
  }

  ImGui::Spacing();
  if (DrawEditableXyz("Orientation:", "##prop_orientation", g_orientation, 0.5f,
                      "%.1f")) {
    struct BkEulerAngles const euler = BkEulerAngles_FromXYZ(
        BK_REAL(g_orientation[0]), BK_REAL(g_orientation[1]),
        BK_REAL(g_orientation[2]));
    struct BkQuaternion const orientation =
        BkQuaternion_FromEulerAngles(&euler);
    BkPointCloud_SetOrientation(cloud, &orientation);
    TrackCameraOn(cloud, camera);
  }

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

  struct BkAABB const world = BkPointCloud_GetAABB(cloud);

  ImGui::Spacing();
  ImGui::Text("min  %.3f  %.3f  %.3f", static_cast<float>(world.min.x),
              static_cast<float>(world.min.y), static_cast<float>(world.min.z));
  ImGui::Text("max  %.3f  %.3f  %.3f", static_cast<float>(world.max.x),
              static_cast<float>(world.max.y), static_cast<float>(world.max.z));

  ImGui::End();
  ImGui::PopStyleVar(2);
  return g_aabb_draw;
}

}  // namespace Studio
