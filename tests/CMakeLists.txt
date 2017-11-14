cmake_minimum_required(VERSION 3.7)

set(BLACKHART_TEST_PROJECT_NAME "Blackhart-Test")

project(${BLACKHART_TEST_PROJECT_NAME} CXX)


# ~~~~~ Blackhart tests ~~~~~

message("")
message("${BLACKHART_TEST_PROJECT_NAME}: BUILD ENABLE")

if (MSVC)
	# Sets runtime library to MT
	set(CMAKE_CXX_FLAGS_RELEASE "/MT")
	set(CMAKE_CXX_FLAGS_DEBUG "/MTd")
endif (MSVC)

# Gets all the source code (both .c and .h files)
file(GLOB_RECURSE CppFiles sources/*.cpp)

# Compiles Blackhart-test
add_executable(${BLACKHART_TEST_PROJECT_NAME} ${CppFiles})

# Links Blackhart's include directory
target_include_directories(${BLACKHART_TEST_PROJECT_NAME} PUBLIC "${${BLACKHART_PROJECT_NAME}_SOURCE_DIR}/includes")

# Links Blackhart library
target_link_libraries(${BLACKHART_TEST_PROJECT_NAME} Blackhart)


# ~~~~~ gtest ~~~~~

message("")

# Sets googletest's library directory
set(GTEST_LIBRARY_PATH "" CACHE PATH "googletest's library directory")

# Finds googletest library
find_library(GTEST_DEBUG_LIBRARY NAMES gtest PATHS "${GTEST_LIBRARY_PATH}" PATH_SUFFIXES "Debug" "debug" NO_DEFAULT_PATH)
find_library(GTEST_RELEASE_LIBRARY NAMES gtest PATHS "${GTEST_LIBRARY_PATH}" PATH_SUFFIXES "Release" "release" NO_DEFAULT_PATH)

if (NOT GTEST_DEBUG_LIBRARY OR NOT GTEST_RELEASE_LIBRARY)
	message("gtest: Library not found!")
else ()
	message("gtest: Library found!")
	message("gtest: Debug/library_path:(${GTEST_DEBUG_LIBRARY}) | Release/library_path:(${GTEST_RELEASE_LIBRARY})")
	# Links googletest library to Blackhart-test
	target_link_libraries(${BLACKHART_TEST_PROJECT_NAME} debug "${GTEST_DEBUG_LIBRARY}" optimized "${GTEST_RELEASE_LIBRARY}")
endif ()

# Sets googletest's include directory
set(GTEST_INCLUDE_PATH "" CACHE PATH "googletest's include directory")

# Links googletest's include directory
target_include_directories(${BLACKHART_TEST_PROJECT_NAME} PUBLIC "${GTEST_INCLUDE_PATH}")

message("gtest: include_path:(${GTEST_INCLUDE_PATH})")

message("")