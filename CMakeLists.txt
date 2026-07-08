cmake_minimum_required(VERSION 3.21)

# URL-based FetchContent downloads use extraction timestamps (CMP0135).
if(POLICY CMP0135)
  cmake_policy(SET CMP0135 NEW)
endif()

#--------------------------------------------------------------------------------------------------
# Project configuration.
#--------------------------------------------------------------------------------------------------

# Set main project name
set(MAIN_PROJECT_NAME "Main")

project(${MAIN_PROJECT_NAME})

# Sets Blackhart's sources directory
set(MAIN_PATH "${${MAIN_PROJECT_NAME}_SOURCE_DIR}")

# Sets custom directories for both shared and static libraries
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Export compile commands for IDE support
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Enable CTest integration (IDE, ctest --preset, CI).
enable_testing()

#--------------------------------------------------------------------------------------------------
# Platform-specific settings.
#--------------------------------------------------------------------------------------------------

# This must come after project () otherwise CMAKE_SYSTEM_NAME is undefined.
if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    include (cmake/config/platform/win-vs.txt)
endif ()

#--------------------------------------------------------------------------------------------------
# Products.
#--------------------------------------------------------------------------------------------------

add_subdirectory("blackhart")
add_subdirectory("blackhart.studio")
# add_subdirectory("blackhart.studio.qt")
add_subdirectory("blackhart.data")

message("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~")