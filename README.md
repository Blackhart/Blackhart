# Blackhart

Blackhart is a small OpenGL engine focused on **point clouds**, written in C/C++. It comes with a library you can link against, and a desktop app (Blackhart Studio) to try it out.

## What you get

**Blackhart** (the library) handles math, data structures, and drawing with OpenGL. You load point clouds from PLY files, put them in a scene, move them around, and ask the renderer to draw.

**Blackhart Studio** is a simple GLFW window with a small ImGui panel to pick a sample asset (bunny or colored fragment), inspect it, load it into the scene, and orbit the camera.

The repo also ships unit tests and a few helper tools.

## How rendering works

In short:

1. You load a PLY file into a **point cloud** (points live on the CPU, with a bounding box, optional RGB colors, and a position/orientation).
2. You add that cloud to a **scene**.
3. You call **BkRender**. The engine uploads positions and colors as two separate GPU buffers the first time they are needed, then draws.

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
