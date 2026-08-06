#ifndef __BK_STUDIO_ASSET_BROWSER_HPP__
#define __BK_STUDIO_ASSET_BROWSER_HPP__

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

  /** Draws the Assets panel in the left sidebar strip. */
  void Draw();

  BkPointCloud* LoadedCloud() const { return loaded_; }

 private:
  struct CatalogEntry {
    char const* name;
    char const* filename;
  };

  void Select(int index);
  void LoadSelected();
  void UnloadLoaded();
  void ReleaseInspected();
  void FrameCameraOn(BkPointCloud* cloud);
  void BuildAbsolutePath(char const* filename);

  static CatalogEntry const kCatalog[];
  static int const kCatalogCount;

  BkScene* scene_ = nullptr;
  BkOrbitalCamera* camera_ = nullptr;
  real camera_fov_deg_ = BK_REAL(45);
  real camera_frame_margin_ = BK_REAL(1.25);

  int selected_index_ = -1;
  int loaded_index_ = -1;
  BkPointCloud* inspected_ = nullptr;
  BkPointCloud* loaded_ = nullptr;

  char absolute_path_[1024] = {};
  char status_[256] = {};
};

}  // namespace Studio

#endif
