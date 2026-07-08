cmake_minimum_required(VERSION 3.21)

# ~~~~~ Blackhart ~~~~~

# Set blackhart project name
set(BLACKHART_PROJECT_NAME "blackhart")

message("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~")
message("${BLACKHART_PROJECT_NAME}: BUILD ENABLE")
message("${BLACKHART_PROJECT_NAME}: Library:(SHARED)")

project(${BLACKHART_PROJECT_NAME} C)

set(${BLACKHART_PROJECT_NAME}_VERSION_MAJOR 0)
set(${BLACKHART_PROJECT_NAME}_VERSION_MINOR 1)
set(${BLACKHART_PROJECT_NAME}_VERSION_PATCH 0)

# Sets Blackhart's sources directory
set(BLACKHART_PATH "${${BLACKHART_PROJECT_NAME}_SOURCE_DIR}")

# Sets default shader path
add_definitions(-DBK_DEFAULT_SHADER_PATH="${BLACKHART_PATH}/shaders")

# Sets default data path
add_definitions(-DBK_DEFAULT_DATA_PATH="${BLACKHART_DATA_PATH}/data")

# Sets debug postfix
set(CMAKE_DEBUG_POSTFIX d)

# Gets all the source code (both .c and .h files)
file(GLOB_RECURSE CFiles sources/*.c)
file(GLOB_RECURSE HFiles includes/*.h)

# Compiles Blackhart as shared library
add_library(${BLACKHART_PROJECT_NAME} SHARED ${CFiles} ${HFiles})

# MSVC definitions
if (MSVC)
	target_compile_definitions(${BLACKHART_PROJECT_NAME} PUBLIC _CRT_SECURE_NO_WARNINGS)
endif (MSVC)

# Exports Blackhart's symbols
target_compile_definitions(${BLACKHART_PROJECT_NAME} PUBLIC BK_EXPORT)

# Renames Blackhart shared library to as 'blackhart'
set_target_properties(${BLACKHART_PROJECT_NAME} PROPERTIES OUTPUT_NAME "blackhart")

# Links Blackhart's include directory
target_include_directories(${BLACKHART_PROJECT_NAME} PUBLIC "${BLACKHART_PATH}/includes")

# ~~~~~ Dependencies: GLEW + OpenGL ~~~~~

include("${MAIN_PATH}/cmake/deps/glew.cmake")
find_package(OpenGL REQUIRED)

target_link_libraries(${BLACKHART_PROJECT_NAME}
  PRIVATE
    GLEW::GLEW
    OpenGL::GL
    m
)

# ~~~~~ Tests ~~~~~

# Sets Blackhart-Tests directory
set(BLACKHART_TESTS_PATH "${BLACKHART_PATH}/tests")

option(BUILD_BLACKHART_TESTS "Build Blackhart's tests" OFF)
if (BUILD_BLACKHART_TESTS)
	add_subdirectory("${BLACKHART_TESTS_PATH}")
endif (BUILD_BLACKHART_TESTS)

# ~~~~~ Install ~~~~~

install(TARGETS ${BLACKHART_PROJECT_NAME}
	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
	ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
	RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

install(DIRECTORY "${BLACKHART_PATH}/includes/"
	DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
	FILES_MATCHING PATTERN "*.h"
)

install(FILES "${BLACKHART_PATH}/export/cpp/Blackhart.hpp"
	DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/blackhart
)

install(DIRECTORY "${BLACKHART_PATH}/shaders/"
	DESTINATION ${CMAKE_INSTALL_DATADIR}/blackhart/shaders
	FILES_MATCHING PATTERN "*.glsl"
)