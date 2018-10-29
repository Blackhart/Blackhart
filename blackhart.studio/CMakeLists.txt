cmake_minimum_required(VERSION 3.7)

# ~~~~~ Blackhart-Editor ~~~~~

# Set blackhart.studio project name
set(BLACKHART_STUDIO_PROJECT_NAME "blackhart.studio")

message("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~")
message("${BLACKHART_STUDIO_PROJECT_NAME}: BUILD ENABLE")

project(${BLACKHART_STUDIO_PROJECT_NAME} CXX)

# Sets Blackhart-Editor's sources directory
set(BLACKHART_STUDIO_PATH "${${BLACKHART_STUDIO_PROJECT_NAME}_SOURCE_DIR}")

# Gets all the source code (both .c and .h files)
file(GLOB_RECURSE CppFiles sources/*.cpp sources/*.c)
file(GLOB_RECURSE HppFiles includes/*.hpp includes/*.h)

# Compiles Blackhart-Editor
add_executable(${BLACKHART_STUDIO_PROJECT_NAME} ${CppFiles} ${HppFiles})

# Links Blackhart's include directory
target_include_directories(${BLACKHART_STUDIO_PROJECT_NAME} PUBLIC "${BLACKHART_STUDIO_PATH}/includes")

# Sets Blackhart's library directory
set(BLACKHART_LIBRARY_PATH "${MAIN_PATH}/build_install/bin" CACHE PATH "Blackhart's library directory")

# Finds Blackhart library
target_link_libraries(${BLACKHART_STUDIO_PROJECT_NAME} blackhart)

# Links Blackhart's include directory
target_include_directories(${BLACKHART_STUDIO_PROJECT_NAME} PUBLIC "${MAIN_PATH}/blackhart/includes")


# ~~~~~ glfw ~~~~~

message("")

# Sets glfw's library directory
set(GLFW_LIBRARY_PATH "" CACHE PATH "")

# Finds glfw library
find_library(GLFW_DEBUG_LIBRARY NAMES glfw3 PATHS "${GLFW_LIBRARY_PATH}" PATH_SUFFIXES "Debug" "debug" NO_DEFAULT_PATH)
find_library(GLFW_RELEASE_LIBRARY NAMES glfw3 PATHS "${GLFW_LIBRARY_PATH}" PATH_SUFFIXES "Release" "release" NO_DEFAULT_PATH)

if (NOT GLFW_DEBUG_LIBRARY OR NOT GLFW_RELEASE_LIBRARY)
	message("glfw: Library not found!")
else ()
	message("glfw: Library found!")
	message("glfw: Debug/library_path:(${GLFW_DEBUG_LIBRARY}) | Release/library_path:(${GLFW_RELEASE_LIBRARY})")
	# Links glfw library
	target_link_libraries(${BLACKHART_STUDIO_PROJECT_NAME} debug "${GLFW_DEBUG_LIBRARY}" optimized "${GLFW_RELEASE_LIBRARY}")
endif ()

# Sets glfw's include directory
set(GLFW_INCLUDE_PATH "" CACHE PATH "Include directory of the glfw library")

# Links glfw's include directory
target_include_directories(${BLACKHART_STUDIO_PROJECT_NAME} PUBLIC "${GLFW_INCLUDE_PATH}")

message("glfw: include_path:(${GLFW_INCLUDE_PATH})")


# ~~~~~ Tests ~~~~~

# Sets Blackhart-Tests directory
set(BLACKHART_STUDIO_TESTS_PATH "${BLACKHART_STUDIO_PATH}/tests")

option(BUILD_BLACKHART_STUDIO_TESTS "Build Blackhart studio's tests" OFF)
if (BUILD_BLACKHART_STUDIO_TESTS)
	add_subdirectory("${BLACKHART_STUDIO_TESTS_PATH}")
endif (BUILD_BLACKHART_STUDIO_TESTS)