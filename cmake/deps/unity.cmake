cmake_minimum_required(VERSION 3.7)

include(FetchContent)
include("${CMAKE_CURRENT_LIST_DIR}/version.cmake")

FetchContent_Declare(
  unity
  GIT_REPOSITORY https://github.com/ThrowTheSwitch/Unity.git
  GIT_TAG ${BK_UNITY_TAG}
)

FetchContent_MakeAvailable(unity)

