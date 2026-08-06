cmake_minimum_required(VERSION 3.21)

include(FetchContent)
include("${CMAKE_CURRENT_LIST_DIR}/version.cmake")

FetchContent_Declare(
  imgui
  GIT_REPOSITORY https://github.com/ocornut/imgui.git
  GIT_TAG ${BK_IMGUI_TAG}
  GIT_SHALLOW TRUE
)

FetchContent_GetProperties(imgui)
if (NOT imgui_POPULATED)
  FetchContent_Populate(imgui)
endif ()

if (NOT TARGET imgui)
  add_library(imgui STATIC
    "${imgui_SOURCE_DIR}/imgui.cpp"
    "${imgui_SOURCE_DIR}/imgui_draw.cpp"
    "${imgui_SOURCE_DIR}/imgui_tables.cpp"
    "${imgui_SOURCE_DIR}/imgui_widgets.cpp"
    "${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.cpp"
    "${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp"
  )

  target_include_directories(imgui
    PUBLIC
      "${imgui_SOURCE_DIR}"
      "${imgui_SOURCE_DIR}/backends"
  )

  target_link_libraries(imgui
    PUBLIC
      GLFW::GLFW
      OpenGL::GL
  )

  add_library(imgui::imgui ALIAS imgui)
endif ()
