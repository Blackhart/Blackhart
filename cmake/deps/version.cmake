cmake_minimum_required(VERSION 3.7)

# Centralized dependency versions.
# This file is the single source of truth for modules in `cmake/deps/`.

set(BK_GLEW_VERSION "2.3.1" CACHE STRING "GLEW version to fetch")
set(BK_GLFW_VERSION "3.3.9" CACHE STRING "GLFW version to fetch")
set(BK_GTEST_TAG "v1.14.0" CACHE STRING "Googletest tag to fetch")
set(BK_UNITY_TAG "v2.6.0" CACHE STRING "Unity tag to fetch")
