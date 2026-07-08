cmake_minimum_required(VERSION 3.21)

include(FetchContent)
include("${CMAKE_CURRENT_LIST_DIR}/version.cmake")

# Limit what gets built (we only need gtest).
set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)
set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG ${BK_GTEST_TAG}
)

FetchContent_MakeAvailable(googletest)

