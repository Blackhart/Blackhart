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

#--------------------------------------------------------------------------------------------------
# Debug
#--------------------------------------------------------------------------------------------------

# Export compile commands for IDE support
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Symlink compile_commands.json at the project root for clangd / IDE support.
if (CMAKE_EXPORT_COMPILE_COMMANDS)
  execute_process(
    COMMAND ${CMAKE_COMMAND} -E rm -f "${CMAKE_SOURCE_DIR}/compile_commands.json"
  )
  execute_process(
    COMMAND ${CMAKE_COMMAND} -E create_symlink
      "${CMAKE_BINARY_DIR}/compile_commands.json"
      "${CMAKE_SOURCE_DIR}/compile_commands.json"
  )
endif ()

#--------------------------------------------------------------------------------------------------
# Platform-specific settings.
#--------------------------------------------------------------------------------------------------

# This must come after project () otherwise CMAKE_SYSTEM_NAME is undefined.
if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    include (cmake/config/platform/win-vs.txt)
endif ()

#--------------------------------------------------------------------------------------------------
# Test
#--------------------------------------------------------------------------------------------------

# Enable CTest integration (IDE, ctest --preset, CI).
enable_testing()

#--------------------------------------------------------------------------------------------------
# Install
#--------------------------------------------------------------------------------------------------

include(GNUInstallDirs)

#--------------------------------------------------------------------------------------------------
# Formatting
#--------------------------------------------------------------------------------------------------

include("${MAIN_PATH}/cmake/clang-format.cmake")

#--------------------------------------------------------------------------------------------------
# Products.
#--------------------------------------------------------------------------------------------------

add_subdirectory("blackhart")
add_subdirectory("blackhart.studio")
add_subdirectory("blackhart.data")

message("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~")
