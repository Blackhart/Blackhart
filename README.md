# Blackhart

Blackhart is a small OpenGL engine focused on **point clouds**, written in C/C++. It comes with a library you can link against, and a desktop app (Blackhart Studio) to try it out.

## What you get

**Blackhart** (the library) handles math, data structures, and drawing with OpenGL. You load point clouds from PLY files, put them in a scene, move them around, and ask the renderer to draw.

**Blackhart Studio** is a simple GLFW window that loads a colored indoor scan sample, places the camera so you can see the whole cloud, and lets you orbit around it.

The repo also ships unit tests and a few helper tools.

## How rendering works

In short:

1. You load a PLY file into a **point cloud** (points live on the CPU, with a bounding box, optional RGB colors, and a position/orientation).
2. You add that cloud to a **scene**.
3. You call **BkRender**. The engine uploads positions and colors as two separate GPU buffers the first time they are needed, then draws.

A few practical rules:

- The **scene only holds CPU data**. GPU buffers are managed internally by the renderer. You do not upload or unload anything yourself.
- Each cloud can be **moved and rotated** (`SetPosition`, `SetOrientation`, or `GetTransform`). The points themselves stay in local space; the renderer applies the transform when drawing. Scaling is not supported yet.
- **Colors are optional.** If the PLY has no `red`/`green`/`blue`, the cloud has no color array and the GPU draw uses white.
- `GetAABB` gives the bounds in local space (computed when the file is loaded). `GetWorldAABB` gives the bounds after the transform — useful to frame the camera or, later, to cull.
- When you remove a cloud from the scene, the GPU copy is marked for cleanup. Release the CPU cloud afterward; the next render pass frees the leftover GPU data.

## Structure

```
blackhart/          Core library
blackhart.studio/   GLFW application
blackhart.data/     Data tool
cmake/deps/         Dependencies (GLEW, GLFW, RPly, gtest, Unity)
docker/ci/          Docker image for CI
```

## Requirements

- CMake ≥ 3.21
- C/C++ compiler (GCC or Clang)
- OpenGL, X11 (Linux)

## Build

```bash
cmake --preset debug
cmake --build --preset debug
```

Format sources (Google style via clang-format):

```bash
cmake --build --preset debug --target format
cmake --build --preset debug --target format-check
```

Binaries land in `_build/debug/bin/`:

- `blackhart.studio` — the app
- `blackhart.test` — unit tests

## Tests

```bash
ctest --preset debug --output-on-failure
```

## Install

```bash
cmake --preset release
cmake --build --preset release
cmake --install _build/release --prefix /usr/local
```

This installs:

- `libblackhart.so` → `lib/`
- `blackhart.studio` → `bin/`
- public headers → `include/`
- shaders → `share/blackhart/shaders/`

## Local CI (Docker)

```bash
./docker/ci/build.sh
```

This uses the `docker-debug` preset and builds into `_build/docker-debug`.

## GitHub CI

On `develop`, `feature/*`, and `fix/*`, GitHub Actions configures, builds, and tests the project inside the project Docker image.
