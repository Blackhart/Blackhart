#include "ui/AssetBrowser.hpp"

#include <imgui.h>

#include <cstdio>
#include <cstring>

#include "../../blackhart/export/cpp/Blackhart.hpp"
#include "ui/CameraFrame.hpp"
#include "ui/ScenePanel.hpp"
#include "ui/StudioLayout.hpp"

namespace Studio {

AssetBrowser::CatalogEntry const AssetBrowser::kCatalog[] = {
    {"Stanford Bunny", "bunny.ply"},
    {"Stanford Dragon", "dragon.ply"},
    {"Stanford Happy Buddha", "happy.ply"},
    {"Stanford Armadillo", "armadillo.ply"},
    {"Stanford Drill", "drill.ply"},
    {"Colored Eagle", "eagle_large.ply"},
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
  UnloadAll();
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

AssetBrowser::LoadedEntry* AssetBrowser::FindLoaded(int catalog_index) {
  for (LoadedEntry& entry : loaded_) {
    if (entry.catalog_index == catalog_index) {
      return &entry;
    }
  }
  return nullptr;
}

AssetBrowser::LoadedEntry const* AssetBrowser::FindLoaded(
    int catalog_index) const {
  for (LoadedEntry const& entry : loaded_) {
    if (entry.catalog_index == catalog_index) {
      return &entry;
    }
  }
  return nullptr;
}

bool AssetBrowser::IsCatalogLoaded(int catalog_index) const {
  return FindLoaded(catalog_index) != nullptr;
}

void AssetBrowser::UnloadAll() {
  if (scene_ == nullptr) {
    loaded_.clear();
    return;
  }

  for (LoadedEntry& entry : loaded_) {
    if (entry.cloud != nullptr) {
      BkScene_RemoveCloud(scene_, entry.cloud);
      BkPointCloud_Release(&entry.cloud);
    }
  }
  loaded_.clear();
}

void AssetBrowser::UnloadSelected() {
  if (scene_ == nullptr || selected_index_ < 0) {
    return;
  }

  LoadedEntry* entry = FindLoaded(selected_index_);
  if (entry == nullptr) {
    std::snprintf(status_, sizeof(status_), "Not loaded");
    return;
  }

  char const* name = kCatalog[selected_index_].name;
  BkPointCloud* const removed = entry->cloud;
  BkPointCloud* const prev_selected = ScenePanel_GetSelectedCloud(scene_);
  bool const was_scene_selected = (prev_selected == removed);

  BkScene_RemoveCloud(scene_, removed);
  BkPointCloud_Release(&entry->cloud);

  for (auto it = loaded_.begin(); it != loaded_.end(); ++it) {
    if (it->catalog_index == selected_index_) {
      loaded_.erase(it);
      break;
    }
  }

  if (was_scene_selected) {
    BkPointCloud* const first = BkScene_GetCloud(scene_, 0);
    ScenePanel_SelectCloud(scene_, first);
    if (first != nullptr) {
      FrameCameraOn(first, camera_, camera_fov_deg_, camera_frame_margin_);
    }
  } else {
    ScenePanel_SelectCloud(scene_, prev_selected);
  }

  // Details / Load need an inspect copy again (the scene instance was released).
  ReleaseInspected();
  BuildAbsolutePath(kCatalog[selected_index_].filename);
  inspected_ = BkPointCloud_CreateFromPlyFile(absolute_path_);
  if (inspected_ == nullptr) {
    std::snprintf(status_, sizeof(status_), "Unloaded %s (inspect failed)",
                  name);
    return;
  }

  std::snprintf(status_, sizeof(status_), "Unloaded %s", name);
}

void AssetBrowser::Select(int index) {
  if (index < 0 || index >= kCatalogCount) {
    return;
  }

  LoadedEntry const* loaded = FindLoaded(index);
  if (index == selected_index_ &&
      (inspected_ != nullptr || loaded != nullptr)) {
    return;
  }

  selected_index_ = index;
  status_[0] = '\0';

  CatalogEntry const& entry = kCatalog[selected_index_];
  BuildAbsolutePath(entry.filename);

  // Already on screen: details come from the loaded cloud, no second CPU copy.
  if (loaded != nullptr) {
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

  if (IsCatalogLoaded(selected_index_)) {
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

  LoadedEntry entry;
  entry.catalog_index = selected_index_;
  entry.cloud = inspected_;
  inspected_ = nullptr;

  BkScene_AddCloud(scene_, entry.cloud);
  loaded_.push_back(entry);
  ScenePanel_SelectCloud(scene_, entry.cloud);
  FrameCameraOn(entry.cloud, camera_, camera_fov_deg_, camera_frame_margin_);

  std::snprintf(status_, sizeof(status_), "Loaded %s",
                kCatalog[selected_index_].name);
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
    if (IsCatalogLoaded(i)) {
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
    LoadedEntry const* loaded = FindLoaded(selected_index_);
    if (details == nullptr && loaded != nullptr) {
      details = loaded->cloud;
    }

    if (details != nullptr) {
      ImGui::Text("Points: %zu", BkPointCloud_GetCount(details));
      ImGui::Text("Colors: %s", BkPointCloud_HasColors(details) ? "yes" : "no");

      struct BkAABB const aabb = BkPointCloud_GetAABB(details);
      ImGui::Spacing();
      ImGui::Text("AABB");
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

  bool const already_loaded = IsCatalogLoaded(selected_index_);
  bool const can_load = inspected_ != nullptr && !already_loaded;
  bool const can_unload = already_loaded;

  if (!can_load) {
    ImGui::BeginDisabled();
  }
  if (ImGui::Button("Load", ImVec2(-1.0f, 0.0f))) {
    LoadSelected();
  }
  if (!can_load) {
    ImGui::EndDisabled();
  }

  if (!can_unload) {
    ImGui::BeginDisabled();
  }
  if (ImGui::Button("Unload", ImVec2(-1.0f, 0.0f))) {
    UnloadSelected();
  }
  if (!can_unload) {
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
      ScenePanel_Draw(scene_, camera_, camera_fov_deg_, camera_frame_margin_);
      ImGui::EndTabItem();
    }
    ImGui::EndTabBar();
  }

  ImGui::End();
  ImGui::PopStyleVar(2);
}

}  // namespace Studio
