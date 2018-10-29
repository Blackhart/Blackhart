cmake_minimum_required(VERSION 3.7)

# ~~~~~ Blackhart-Editor ~~~~~

# Set blackhart.studio.qt project name
set(BLACKHART_STUDIO_QT_PROJECT_NAME "blackhart.studio.qt")

message("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~")
message("${BLACKHART_STUDIO_QT_PROJECT_NAME}: BUILD ENABLE")

project(${BLACKHART_STUDIO_QT_PROJECT_NAME} CXX)

# Sets Blackhart-Editor's sources directory
set(BLACKHART_STUDIO_PATH "${${BLACKHART_STUDIO_QT_PROJECT_NAME}_SOURCE_DIR}")

# Gets all the source code (both .c and .h files)
file(GLOB_RECURSE CppFiles sources/*.cpp)
file(GLOB_RECURSE HppFiles includes/*.hpp)

# Compiles Blackhart-Editor
add_executable(${BLACKHART_STUDIO_QT_PROJECT_NAME} ${CppFiles} ${HppFiles})

# Links Blackhart's include directory
target_include_directories(${BLACKHART_STUDIO_QT_PROJECT_NAME} PUBLIC "${BLACKHART_STUDIO_PATH}/includes")

# Sets Blackhart's library directory
set(BLACKHART_LIBRARY_PATH "${MAIN_PATH}/build_install/bin" CACHE PATH "Blackhart's library directory")

# Finds Blackhart library
target_link_libraries(${BLACKHART_STUDIO_QT_PROJECT_NAME} ${BLACKHART_PROJECT_NAME})

# Links Blackhart's include directory
target_include_directories(${BLACKHART_STUDIO_QT_PROJECT_NAME} PUBLIC "${MAIN_PATH}/blackhart/includes")


# ~~~~~ Qt ~~~~~

message("")

# Sets the Qt directory
set(QT_DIRECTORY_PATH "" CACHE PATH "Qt directory path")

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

# Find the QtWidgets library
find_package(Qt5Widgets REQUIRED PATHS ${QT_DIRECTORY_PATH} PATH_SUFFIXES "lib/cmake/Qt5Widgets" NO_DEFAULT_PATH)

# Use the Widgets module from Qt 5.
target_link_libraries(${BLACKHART_STUDIO_QT_PROJECT_NAME} Qt5::Widgets)