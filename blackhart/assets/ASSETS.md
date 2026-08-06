# Assets

Sample point clouds shipped with Blackhart.

| File | Contents | Notes |
|------|----------|--------|
| `bunny.ply` | Stanford bunny (~2503 points, XYZ only) | Classic geometry sample; no vertex colors. |
| `frag_colored.ply` | Indoor fragment (~8046 points, XYZ + RGB) | Subsampled from Open3D `DemoColoredICPPointClouds` / `frag_115.ply`. |

## Attribution

### bunny.ply

Derived from the Stanford 3D Scanning Repository bunny.

### frag_colored.ply

Source: [Open3D open3d_downloads — 20220201-data](https://github.com/isl-org/open3d_downloads/releases/tag/20220201-data)
(`DemoColoredICPPointClouds.zip` → `frag_115.ply`).

Open3D is MIT-licensed. Vertices were subsampled and converted to ASCII PLY with
`x y z red green blue` only (normals and faces dropped) for a lightweight
sample until vertex colors are wired in the engine.
