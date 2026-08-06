#include "ui/ScenePanel.hpp"

#include <imgui.h>

#include <cstdio>

#include "../../blackhart/export/cpp/Blackhart.hpp"
#include "ui/CameraFrame.hpp"

namespace Studio {

namespace {

int g_selected_index = -1;

}  // namespace

void ScenePanel_Draw(BkScene* scene, BkOrbitalCamera* camera,
                     real camera_fov_deg, real camera_frame_margin) {
  size_t const count = (scene != nullptr) ? BkScene_GetCloudCount(scene) : 0;

  if (g_selected_index >= 0 && static_cast<size_t>(g_selected_index) >= count) {
    g_selected_index = (count > 0) ? 0 : -1;
  }

  ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.55f, 0.57f, 0.60f, 1.00f));
  ImGui::Text("HIERARCHY (%zu)", count);
  ImGui::PopStyleColor();
  ImGui::Separator();
  ImGui::Spacing();

  if (count == 0) {
    ImGui::TextDisabled("Scene is empty");
    return;
  }

  for (size_t i = 0; i < count; ++i) {
    BkPointCloud* cloud = BkScene_GetCloud(scene, i);
    if (cloud == nullptr) {
      continue;
    }

    char label[64];
    std::snprintf(label, sizeof(label), "PointCloud #%zu", i);

    bool const selected = (static_cast<int>(i) == g_selected_index);
    if (ImGui::Selectable(label, selected)) {
      g_selected_index = static_cast<int>(i);
      FrameCameraOn(cloud, camera, camera_fov_deg, camera_frame_margin);
    }

    ImGui::SameLine();
    ImGui::TextDisabled("%zu pts", BkPointCloud_GetCount(cloud));
  }
}

int ScenePanel_GetSelectedIndex(void) { return g_selected_index; }

BkPointCloud* ScenePanel_GetSelectedCloud(BkScene* scene) {
  if (scene == nullptr || g_selected_index < 0) {
    return nullptr;
  }

  size_t const count = BkScene_GetCloudCount(scene);
  if (static_cast<size_t>(g_selected_index) >= count) {
    return nullptr;
  }

  return BkScene_GetCloud(scene, static_cast<size_t>(g_selected_index));
}

void ScenePanel_SelectCloud(BkScene* scene, BkPointCloud* cloud) {
  if (scene == nullptr || cloud == nullptr) {
    g_selected_index = -1;
    return;
  }

  size_t const count = BkScene_GetCloudCount(scene);
  for (size_t i = 0; i < count; ++i) {
    if (BkScene_GetCloud(scene, i) == cloud) {
      g_selected_index = static_cast<int>(i);
      return;
    }
  }

  g_selected_index = -1;
}

}  // namespace Studio
