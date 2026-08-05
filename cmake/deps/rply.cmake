cmake_minimum_required(VERSION 3.21)

include(FetchContent)
include("${CMAKE_CURRENT_LIST_DIR}/version.cmake")

# Upstream has no CMake project and no release tags: fetch sources and
# define our own static target (same pattern as glew.cmake Populate path).
FetchContent_Declare(
  rply
  URL https://github.com/diegonehab/rply/archive/${BK_RPLY_TAG}.zip
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)

FetchContent_GetProperties(rply)
if (NOT rply_POPULATED)
  FetchContent_Populate(rply)

  add_library(rply STATIC "${rply_SOURCE_DIR}/rply.c")
  # Required: blackhart is a shared library.
  set_target_properties(rply PROPERTIES
    POSITION_INDEPENDENT_CODE ON
    C_STANDARD 99
    C_STANDARD_REQUIRED ON
  )
  target_include_directories(rply
    PUBLIC
      $<BUILD_INTERFACE:${rply_SOURCE_DIR}>
  )
endif ()

if (NOT TARGET RPly::RPly)
  add_library(RPly::RPly ALIAS rply)
endif ()
