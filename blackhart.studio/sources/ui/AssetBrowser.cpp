#include "ui/AssetBrowser.hpp"

#include <imgui.h>

#include <cmath>
#include <cstdio>
#include <cstring>

#include "../../blackhart/export/cpp/Blackhart.hpp"
#include "ui/ScenePanel.hpp"
#include "ui/StudioLayout.hpp"

namespace Studio {

AssetBrowser::CatalogEntry const AssetBrowser::kCatalog[] = {
    {"Stanford Bunny", "bunny.ply"},
    {"Colored Fragment", "frag_colored.ply"},
};

int const AssetBrowser::kCatalogCount =
    static_cast<int>(sizeof(kCatalog) / sizeof(kCatalog[0]));

void AssetBrowser::Initialize(BkScene* scene, BkOrbitalCamera* camera,
                              real camera_fov_deg, real camera_frame_margin) {
  scene_ = scene;
  camera_ = camera;
  camera_fov_deg_ = camera_fov_deg;
  camera_frame_margin_ = camera_frame_margin;
  status_[0] = '\0';

  if (kCatalogCount > 0) {
    Select(0);
    LoadSelected();
  }
}

void AssetBrowser::Shutdown() {
  UnloadLoaded();
  ReleaseInspected();
  scene_ = nullptr;
  camera_ = nullptr;
}

void AssetBrowser::BuildAbsolutePath(char const* filename) {
  BkFileSystem_CombinePath(absolute_path_, BK_DEFAULT_ASSET_PATH, filename);
}

void AssetBrowser::ReleaseInspected() {
  if (inspected_ != nullptr) {
    BkPointCloud_Release(&inspected_);
  }
}

void AssetBrowser::UnloadLoaded() {
  if (loaded_ == nullptr || scene_ == nullptr) {
    loaded_index_ = -1;
    return;
  }

  BkScene_RemoveCloud(scene_, loaded_);
  BkPointCloud_Release(&loaded_);
  loaded_index_ = -1;
}

void AssetBrowser::FrameCameraOn(BkPointCloud* cloud) {
  if (cloud == nullptr || camera_ == nullptr) {
    return;
  }

  struct BkAABB const aabb = BkPointCloud_GetWorldAABB(cloud);
  struct BkPoint3 const target = BkAABB_Center(&aabb);
  struct BkVector3 const size = BkAABB_Size(&aabb);
  real const bounding_sphere_radius = BkVector3_Magnitude(&size) * BK_REAL(0.5);
  real const half_fov_rad = BkMath_RadFromDeg(camera_fov_deg_) * BK_REAL(0.5);
  real const radius = camera_frame_margin_ * bounding_sphere_radius /
                      BK_REAL(tan(half_fov_rad));

  BkOrbitalCamera_SetTarget(camera_, &target);
  BkOrbitalCamera_SetRadius(camera_, radius);
}

void AssetBrowser::Select(int index) {
  if (index < 0 || index >= kCatalogCount) {
    return;
  }

  if (index == selected_index_ &&
      (inspected_ != nullptr || index == loaded_index_)) {
    return;
  }

  selected_index_ = index;
  status_[0] = '\0';

  CatalogEntry const& entry = kCatalog[selected_index_];
  BuildAbsolutePath(entry.filename);

  // Already on screen: details come from loaded_, no second CPU copy.
  if (index == loaded_index_ && loaded_ != nullptr) {
    ReleaseInspected();
    return;
  }

  ReleaseInspected();
  inspected_ = BkPointCloud_CreateFromPlyFile(absolute_path_);
  if (inspected_ == nullptr) {
    std::snprintf(status_, sizeof(status_), "Failed to inspect %s",
                  entry.filename);
  }
}

void AssetBrowser::LoadSelected() {
  if (scene_ == nullptr || selected_index_ < 0) {
    return;
  }

  if (selected_index_ == loaded_index_ && loaded_ != nullptr) {
    std::snprintf(status_, sizeof(status_), "Already loaded");
    return;
  }

  if (inspected_ == nullptr) {
    Select(selected_index_);
  }
  if (inspected_ == nullptr) {
    std::snprintf(status_, sizeof(status_), "Nothing to load");
    return;
  }

  UnloadLoaded();

  loaded_ = inspected_;
  inspected_ = nullptr;
  BkScene_AddCloud(scene_, loaded_);
  loaded_index_ = selected_index_;
  FrameCameraOn(loaded_);

  std::snprintf(status_, sizeof(status_), "Loaded %s",
                kCatalog[loaded_index_].name);
}

void AssetBrowser::DrawContents() {
  ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.55f, 0.57f, 0.60f, 1.00f));
  ImGui::TextUnformatted("CATALOG");
  ImGui::PopStyleColor();
  ImGui::Separator();
  ImGui::Spacing();

  for (int i = 0; i < kCatalogCount; ++i) {
    bool const selected = (i == selected_index_);
    if (ImGui::Selectable(kCatalog[i].name, selected)) {
      Select(i);
    }
    if (i == loaded_index_) {
      ImGui::SameLine();
      ImGui::TextDisabled("loaded");
    }
  }

  ImGui::Spacing();
  ImGui::Spacing();
  ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.55f, 0.57f, 0.60f, 1.00f));
  ImGui::TextUnformatted("DETAILS");
  ImGui::PopStyleColor();
  ImGui::Separator();
  ImGui::Spacing();

  if (selected_index_ < 0) {
    ImGui::TextDisabled("No asset selected");
  } else {
    CatalogEntry const& entry = kCatalog[selected_index_];
    ImGui::Text("Name:  %s", entry.name);
    ImGui::TextWrapped("Path:  %s", absolute_path_);

    BkPointCloud* details = inspected_;
    if (details == nullptr && selected_index_ == loaded_index_) {
      details = loaded_;
    }

    if (details != nullptr) {
      ImGui::Text("Points: %zu", BkPointCloud_GetCount(details));
      ImGui::Text("Colors: %s", BkPointCloud_HasColors(details) ? "yes" : "no");

      struct BkAABB const aabb = BkPointCloud_GetAABB(details);
      ImGui::Spacing();
      ImGui::Text("Bounds");
      ImGui::Text("  min  %.3f  %.3f  %.3f", (float)aabb.min.x,
                  (float)aabb.min.y, (float)aabb.min.z);
      ImGui::Text("  max  %.3f  %.3f  %.3f", (float)aabb.max.x,
                  (float)aabb.max.y, (float)aabb.max.z);
    } else {
      ImGui::TextColored(ImVec4(1.0f, 0.45f, 0.40f, 1.0f), "Inspect failed");
    }
  }

  ImGui::Spacing();
  ImGui::Separator();
  ImGui::Spacing();

  bool const already_loaded =
      selected_index_ == loaded_index_ && loaded_ != nullptr;
  bool const can_load = inspected_ != nullptr && !already_loaded;
  if (!can_load) {
    ImGui::BeginDisabled();
  }
  if (ImGui::Button("Load", ImVec2(-1.0f, 0.0f))) {
    LoadSelected();
  }
  if (!can_load) {
    ImGui::EndDisabled();
  }

  if (status_[0] != '\0') {
    ImGui::Spacing();
    ImGui::TextWrapped("%s", status_);
  }
}

void AssetBrowser::Draw() {
  ImGuiViewport const* viewport = ImGui::GetMainViewport();

  ImGui::SetNextWindowPos(
      ImVec2(viewport->WorkPos.x, viewport->WorkPos.y + kToolbarHeight),
      ImGuiCond_Always);
  ImGui::SetNextWindowSize(
      ImVec2(kSidebarWidth, viewport->WorkSize.y - kToolbarHeight),
      ImGuiCond_Always);

  ImGuiWindowFlags const flags =
      ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize |
      ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoBringToFrontOnFocus |
      ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoTitleBar;

  ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
  ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);

  if (!ImGui::Begin("##StudioSidebar", nullptr, flags)) {
    ImGui::End();
    ImGui::PopStyleVar(2);
    return;
  }

  if (ImGui::BeginTabBar("##StudioSidebarTabs")) {
    if (ImGui::BeginTabItem("Assets")) {
      DrawContents();
      ImGui::EndTabItem();
    }
    if (ImGui::BeginTabItem("Scene")) {
      ScenePanel_Draw(scene_);
      ImGui::EndTabItem();
    }
    ImGui::EndTabBar();
  }

  ImGui::End();
  ImGui::PopStyleVar(2);
}

}  // namespace Studio
