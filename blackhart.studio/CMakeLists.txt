cmake_minimum_required(VERSION 3.21)

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

# Links Blackhart-Editor include directory
target_include_directories(${BLACKHART_STUDIO_PROJECT_NAME} PUBLIC "${BLACKHART_STUDIO_PATH}/includes")

# Link against the Blackhart library
target_link_libraries(${BLACKHART_STUDIO_PROJECT_NAME} PRIVATE blackhart)
target_include_directories(${BLACKHART_STUDIO_PROJECT_NAME} PUBLIC "${MAIN_PATH}/blackhart/includes")

# OpenGL (glViewport, glClear, ...)
find_package(OpenGL REQUIRED)

# ~~~~~ Dependency: GLFW ~~~~~

include("${MAIN_PATH}/cmake/deps/glfw.cmake")
target_link_libraries(${BLACKHART_STUDIO_PROJECT_NAME} PRIVATE GLFW::GLFW)

# main.cpp uses OpenGL symbols directly.
target_link_libraries(${BLACKHART_STUDIO_PROJECT_NAME} PRIVATE OpenGL::GL)

# ~~~~~ Tests ~~~~~

# Sets Blackhart-Tests directory
set(BLACKHART_STUDIO_TESTS_PATH "${BLACKHART_STUDIO_PATH}/tests")

option(BUILD_BLACKHART_STUDIO_TESTS "Build Blackhart studio's tests" OFF)
if (BUILD_BLACKHART_STUDIO_TESTS)
	add_subdirectory("${BLACKHART_STUDIO_TESTS_PATH}")
endif (BUILD_BLACKHART_STUDIO_TESTS)

# ~~~~~ Install ~~~~~

install(TARGETS ${BLACKHART_STUDIO_PROJECT_NAME}
	RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)