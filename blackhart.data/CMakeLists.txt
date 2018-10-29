cmake_minimum_required(VERSION 3.7)

# ~~~~~ Blackhart-Data ~~~~~

# Set blackhart.data project name
set(BLACKHART_DATA_PROJECT_NAME "blackhart.data")

message("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~")
message("${BLACKHART_DATA_PROJECT_NAME}: BUILD ENABLE")

project(${BLACKHART_DATA_PROJECT_NAME} C)

# Sets Blackhart-Editor's sources directory
set(BLACKHART_DATA_PATH "${${BLACKHART_DATA_PROJECT_NAME}_SOURCE_DIR}")

# Gets all the source code (both .c and .h files)
file(GLOB_RECURSE CFiles sources/*.c)
file(GLOB_RECURSE HFiles includes/*.h)

# Compiles Blackhart-Editor
add_executable(${BLACKHART_DATA_PROJECT_NAME} ${CFiles} ${HFiles})

# Links Blackhart's include directory
target_include_directories(${BLACKHART_DATA_PROJECT_NAME} PUBLIC "${BLACKHART_DATA_PATH}/includes")

# Sets Blackhart's library directory
set(BLACKHART_LIBRARY_PATH "${MAIN_PATH}/build_install/bin" CACHE PATH "Blackhart's library directory")

# Finds Blackhart library
# target_link_libraries(${BLACKHART_DATA_PROJECT_NAME} ${BLACKHART_PROJECT_NAME})

# Links Blackhart's include directory
target_include_directories(${BLACKHART_DATA_PROJECT_NAME} PUBLIC "${MAIN_PATH}/blackhart/includes")