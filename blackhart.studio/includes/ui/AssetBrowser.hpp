#ifndef __BK_STUDIO_ASSET_BROWSER_HPP__
#define __BK_STUDIO_ASSET_BROWSER_HPP__

#include <vector>

extern "C" {
#include "foundation/BkAtomicDataType.h"
}

struct BkOrbitalCamera;
struct BkPointCloud;
struct BkScene;

namespace Studio {

class AssetBrowser {
 public:
  void Initialize(BkScene* scene, BkOrbitalCamera* camera, real camera_fov_deg,
                  real camera_frame_margin);
  void Shutdown();

  /** Draws the left sidebar (Assets | Scene tabs). */
  void Draw();

 private:
  struct CatalogEntry {
    char const* name;
    char const* filename;
  };

  struct LoadedEntry {
    int catalog_index = -1;
    BkPointCloud* cloud = nullptr;
  };

  void DrawContents();
  void Select(int index);
  void LoadSelected();
  void UnloadSelected();
  void UnloadAll();
  void ReleaseInspected();
  void BuildAbsolutePath(char const* filename);

  LoadedEntry* FindLoaded(int catalog_index);
  LoadedEntry const* FindLoaded(int catalog_index) const;
  bool IsCatalogLoaded(int catalog_index) const;

  static CatalogEntry const kCatalog[];
  static int const kCatalogCount;

  BkScene* scene_ = nullptr;
  BkOrbitalCamera* camera_ = nullptr;
  real camera_fov_deg_ = BK_REAL(45);
  real camera_frame_margin_ = BK_REAL(1.25);

  int selected_index_ = -1;
  BkPointCloud* inspected_ = nullptr;
  std::vector<LoadedEntry> loaded_;

  char absolute_path_[1024] = {};
  char status_[256] = {};
};

}  // namespace Studio

#endif
