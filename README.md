# Blackhart

A 3D sandbox in C/C++: OpenGL rendering library, 3D math, and a GLFW application.

## Description

**Blackhart** is the core of the project: a shared library (math, data structures, OpenGL/GLEW rendering).

**Blackhart Studio** is the GLFW application that uses it to display an interactive 3D scene.

The repository also includes tools and unit tests (Unity, Google Test).

## Structure

```
blackhart/          Core library
blackhart.studio/   GLFW application
blackhart.data/     Data tool
cmake/deps/         Dependencies (GLEW, GLFW, gtest, Unity)
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

Binaries are generated in `_build/debug/bin/`:

- `blackhart.studio` — application
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

Installs:

- `libblackhart.so` → `lib/`
- `blackhart.studio` → `bin/`
- public headers → `include/`
- shaders → `share/blackhart/shaders/`

## Local CI (Docker)

```bash
./docker/ci/build.sh
```

Uses the `docker-debug` preset and a separate build directory (`_build/docker-debug`).

## GitHub CI

Linux workflow on `develop`, `feature/*`, and `fix/*` branches: configure, build, and test via the project Docker image.
