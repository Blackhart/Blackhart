cmake_minimum_required(VERSION 3.21)

include(FetchContent)
include("${CMAKE_CURRENT_LIST_DIR}/version.cmake")

FetchContent_Declare(
  glfw
  URL https://github.com/glfw/glfw/archive/refs/tags/${BK_GLFW_VERSION}.zip
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)

FetchContent_MakeAvailable(glfw)

# Normalize the target name for the rest of the project.
if (NOT TARGET GLFW::GLFW)
  add_library(GLFW::GLFW ALIAS glfw)
endif ()

