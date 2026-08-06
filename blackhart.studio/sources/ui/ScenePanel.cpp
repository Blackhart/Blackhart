#include "ui/ScenePanel.hpp"

#include <imgui.h>

#include <cstdio>

#include "../../blackhart/export/cpp/Blackhart.hpp"

namespace Studio {

namespace {

int g_selected_index = -1;

}  // namespace

void ScenePanel_Draw(BkScene* scene) {
  size_t const count = (scene != nullptr) ? BkScene_GetCloudCount(scene) : 0;

  if (g_selected_index >= 0 && static_cast<size_t>(g_selected_index) >= count) {
    g_selected_index = (count > 0) ? static_cast<int>(count) - 1 : -1;
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
    }

    ImGui::SameLine();
    ImGui::TextDisabled("%zu pts", BkPointCloud_GetCount(cloud));
  }
}

}  // namespace Studio
