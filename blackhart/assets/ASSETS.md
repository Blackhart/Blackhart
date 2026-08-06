# Assets

Sample point clouds shipped with Blackhart.

| File | Contents | Notes |
|------|----------|--------|
| `bunny.ply` | Stanford Bunny (~36k points, XYZ) | Full `bun_zipper` reconstruction. |
| `dragon.ply` | Stanford Dragon (~438k points, XYZ) | Full `dragon_vrip` reconstruction. |
| `happy.ply` | Stanford Happy Buddha (~544k points, XYZ) | Full `happy_vrip` reconstruction. |
| `armadillo.ply` | Stanford Armadillo (~173k points, XYZ) | Full `Armadillo.ply` reconstruction. |
| `drill.ply` | Stanford Drill shaft (~2.0k points, XYZ) | Full `drill_shaft_vrip` reconstruction. |
| `eagle_large.ply` | Eagle sculpture (~797k points, XYZ + RGB) | Full Open3D `EaglePointCloud.ply` (binary). |

## Attribution

### Stanford models (`bunny`, `dragon`, `happy`, `armadillo`, `drill`)

Source: [Stanford 3D Scanning Repository](https://graphics.stanford.edu/data/3Dscanrep/).
Full reconstructions converted to binary little-endian PLY with `x y z` only
(faces / confidence / intensity dropped). Upstream Stanford scans do **not**
include per-vertex RGB — Cyberware laser range data is geometry only — so
these assets stay uncolored.

### Colored Open3D sample

Source: [Open3D open3d_downloads — 20220201-data](https://github.com/isl-org/open3d_downloads/releases/tag/20220201-data)
(Open3D is MIT-licensed).

| Asset | Upstream |
|-------|----------|
| `eagle_large.ply` | `EaglePointCloud.ply` (full, binary little-endian XYZ+RGB) |
