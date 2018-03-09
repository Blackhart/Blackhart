cmake_minimum_required(VERSION 3.7)

# ~~~~~ Blackhart ~~~~~

message("")
message("${BLACKHART_PROJECT_NAME}: BUILD ENABLE")
message("${BLACKHART_PROJECT_NAME}: Library:(SHARED)")

set(BLACKHART_PROJECT_NAME "Blackhart")

project(${BLACKHART_PROJECT_NAME} C)

set(${BLACKHART_PROJECT_NAME}_VERSION_MAJOR 0)
set(${BLACKHART_PROJECT_NAME}_VERSION_MINOR 1)
set(${BLACKHART_PROJECT_NAME}_VERSION_PATCH 0)

# Sets Blackhart's sources directory
set(BLACKHART_PATH "${${BLACKHART_PROJECT_NAME}_SOURCE_DIR}")

# Sets debug postfix
set(CMAKE_DEBUG_POSTFIX d)

# Sets custom directories for both Blackhart's shared and static libraries
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

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

# Creates install target
set(CMAKE_INSTALL_PREFIX "${${BLACKHART_PROJECT_NAME}_SOURCE_DIR}/build_install")
install(TARGETS ${BLACKHART_PROJECT_NAME}
		RUNTIME DESTINATION bin
		LIBRARY DESTINATION lib
		ARCHIVE DESTINATION lib/static)
install(DIRECTORY "${BLACKHART_PATH}/includes" DESTINATION "${BLACKHART_PATH}/build_install" FILES_MATCHING PATTERN "*.h")


# ~~~~~ Tests ~~~~~

# Sets Blackhart-Tests directory
set(BLACKHART_TESTS_PATH "${BLACKHART_PATH}/tests")

option(BUILD_BLACKHART_TESTS "Build Blackhart's tests" OFF)
if (BUILD_BLACKHART_TESTS)
	add_subdirectory("${BLACKHART_TESTS_PATH}")
endif (BUILD_BLACKHART_TESTS)