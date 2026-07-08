cmake_minimum_required(VERSION 3.21)

include(FetchContent)
include("${CMAKE_CURRENT_LIST_DIR}/version.cmake")

FetchContent_Declare(
  glew
  URL https://github.com/nigels-com/glew/archive/refs/tags/glew-${BK_GLEW_VERSION}.zip
)

FetchContent_Populate(glew)

# GLEW often requires source/header generation.
# Run `make` in `auto/` and then `make extensions` if generated files are missing.
set(_bk_glew_expected_header "${glew_SOURCE_DIR}/include/GL/wglew.h")
if (NOT EXISTS "${_bk_glew_expected_header}")
  message(STATUS "GLEW: generating sources (auto + extensions) ...")
  execute_process(
    COMMAND ${CMAKE_MAKE_PROGRAM} -C "${glew_SOURCE_DIR}/auto"
    RESULT_VARIABLE _bk_glew_auto_res
  )
  execute_process(
    COMMAND ${CMAKE_MAKE_PROGRAM} extensions
    WORKING_DIRECTORY "${glew_SOURCE_DIR}"
    RESULT_VARIABLE _bk_glew_ext_res
  )

  if (NOT _bk_glew_auto_res EQUAL 0 OR NOT _bk_glew_ext_res EQUAL 0)
    message(FATAL_ERROR "GLEW: generation failed (auto=${_bk_glew_auto_res}, extensions=${_bk_glew_ext_res})")
  endif()
endif()

# Build GLEW through its CMake project (in `build/cmake`).
set(BUILD_UTILS OFF CACHE BOOL "Build GLEW utils" FORCE)

add_subdirectory("${glew_SOURCE_DIR}/build/cmake" "${CMAKE_BINARY_DIR}/_deps/glew-build")

# GLEW's CMake only sets INSTALL_INTERFACE includes; add BUILD_INTERFACE so
# consumers get headers when GLEW is built via FetchContent (not installed).
foreach(_bk_glew_target IN ITEMS glew glew_s)
  if (TARGET ${_bk_glew_target})
    target_include_directories(${_bk_glew_target}
      PUBLIC
        $<BUILD_INTERFACE:${glew_SOURCE_DIR}/include>
    )
  endif()
endforeach()

if (NOT TARGET GLEW::GLEW)
  if (TARGET glew)
    add_library(GLEW::GLEW ALIAS glew)
  elseif (TARGET glew_s)
    add_library(GLEW::GLEW ALIAS glew_s)
  endif()
endif()

