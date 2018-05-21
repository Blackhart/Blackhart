cmake_minimum_required(VERSION 3.7)

# ~~~~~ Main ~~~~~

set(MAIN_PROJECT_NAME "Main")

message("")
message("${MAIN_PROJECT_NAME}: BUILD ENABLE")
message("${MAIN_PROJECT_NAME}: Library:(SHARED)")

project(${MAIN_PROJECT_NAME})

# Sets Blackhart's sources directory
set(MAIN_PATH "${${MAIN_PROJECT_NAME}_SOURCE_DIR}")

# Sets custom directories for both shared and static libraries
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Sets blackhart project
set(BLACKHART_PROJECT_NAME "blackhart")
add_subdirectory("blackhart")

# Sets blackhart.studio project
set(BLACKHART_STUDIO_PROJECT_NAME "blackhart.studio")
add_subdirectory("blackhart.studio")

# Sets blackhart.studio.qt project
set(BLACKHART_STUDIO_QT_PROJECT_NAME "blackhart.studio.qt")
add_subdirectory("blackhart.studio.qt")

message("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~")