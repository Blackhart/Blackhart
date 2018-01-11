cmake_minimum_required(VERSION 3.7)

set(BLACKHART_PROJECT_NAME "Blackhart")

project(${BLACKHART_PROJECT_NAME} C)

set(${BLACKHART_PROJECT_NAME}_VERSION_MAJOR 0)
set(${BLACKHART_PROJECT_NAME}_VERSION_MINOR 1)
set(${BLACKHART_PROJECT_NAME}_VERSION_PATCH 0)


# ~~~~~ Blackhart ~~~~~

message("")
message("${BLACKHART_PROJECT_NAME}: BUILD ENABLE")
message("${BLACKHART_PROJECT_NAME}: Library:(SHARED)")

# Sets Blackhart's sources directory
set(BLACKHART_PATH "${${BLACKHART_PROJECT_NAME}_SOURCE_DIR}")

# Sets debug postfix
set(CMAKE_DEBUG_POSTFIX d)

# MSVC definitions
if (MSVC)
	add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif (MSVC)

# Sets custom directories for both Blackhart's shared and static libraries
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Gets all the source code (both .c and .h files)
file(GLOB_RECURSE CFiles sources/*.c)
file(GLOB_RECURSE HFiles includes/*.h)

# Sets default shader path
add_definitions(-DBK_DEFAULT_SHADER_PATH="${BLACKHART_PATH}/shaders")

# Compiles Blackhart as shared library
add_definitions(-DBK_EXPORT)
add_library(${BLACKHART_PROJECT_NAME} SHARED ${CFiles} ${HFiles})

# Renames Blackhart shared library to as 'blackhart32'
set_target_properties(${BLACKHART_PROJECT_NAME} PROPERTIES OUTPUT_NAME "blackhart32")

# Links Blackhart's include directory
target_include_directories(${BLACKHART_PROJECT_NAME} PUBLIC "${BLACKHART_PATH}/includes")


# ~~~~~ Glew ~~~~~

message("")

# Sets glew's library directory
set(GLEW_LIBRARY_PATH "" CACHE PATH "glew's library directory")

# Finds glew library
find_library(GLEW_DEBUG_LIBRARY NAMES glew32d PATHS "${GLEW_LIBRARY_PATH}" PATH_SUFFIXES "Debug" "debug" NO_DEFAULT_PATH)
find_library(GLEW_RELEASE_LIBRARY NAMES glew32 PATHS "${GLEW_LIBRARY_PATH}" PATH_SUFFIXES "Release" "release" NO_DEFAULT_PATH)

find_package(OpenGL REQUIRED)

if (NOT GLEW_DEBUG_LIBRARY OR NOT GLEW_RELEASE_LIBRARY)
	message("glew: Library not found!")
else ()
	message("glew: Library found!")
	message("glew: Debug/library_path:(${GLEW_DEBUG_LIBRARY}) | Release/library_path:(${GLEW_RELEASE_LIBRARY})")
	# Links glew library to Blackhart
	target_link_libraries(${BLACKHART_PROJECT_NAME} debug "${GLEW_DEBUG_LIBRARY}" optimized "${GLEW_RELEASE_LIBRARY}")
	# Links opengl libraries to Blackhart
	target_link_libraries(${BLACKHART_PROJECT_NAME} "${OPENGL_LIBRARIES}")
endif ()

# Sets glew's include directory
set(GLEW_INCLUDE_PATH "" CACHE PATH "glew's include directory")

# Links glew's include directory
target_include_directories(${BLACKHART_PROJECT_NAME} PUBLIC "${GLEW_INCLUDE_PATH}")

message("glew: include_path:(${GLEW_INCLUDE_PATH})")


# ~~~~~ Tests ~~~~~

message("")

# Sets Blackhart-Tests directory
set(BLACKHART_TESTS_PATH "${BLACKHART_PATH}/tests")

option(BUILD_BLACKHART_TESTS "Build Blackhart's tests" OFF)
if (BUILD_BLACKHART_TESTS)
	add_subdirectory("${BLACKHART_TESTS_PATH}")
endif (BUILD_BLACKHART_TESTS)