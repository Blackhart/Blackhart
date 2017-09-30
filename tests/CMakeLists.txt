cmake_minimum_required(VERSION 3.7)

set(BLACKHART_TEST_PROJECT_NAME "Blackhart-test")

project(${BLACKHART_TEST_PROJECT_NAME} CXX)

message("")
message("${BLACKHART_TEST_PROJECT_NAME}: BUILD ENABLE")
message("~~~ ${BLACKHART_TEST_PROJECT_NAME} ~~~")


# Blackhart tests

file(GLOB_RECURSE CppFiles sources/*.cpp)

add_executable(${BLACKHART_TEST_PROJECT_NAME} ${CppFiles})


# Blackhart

target_include_directories(${BLACKHART_TEST_PROJECT_NAME} PUBLIC "${${BLACKHART_PROJECT_NAME}_SOURCE_DIR}/includes")
target_link_libraries(${BLACKHART_TEST_PROJECT_NAME} Blackhart)


# extlibs

set(BLACKHART_TEST_EXTLIBS_PATH "${${BLACKHART_TEST_PROJECT_NAME}_SOURCE_DIR}/extlibs")


# gtest

set(GOOGLETEST_PATH "${BLACKHART_TEST_EXTLIBS_PATH}/googletest")

option(GTEST_AUTO_COMPILE "Will gtest must be compile with ${BLACKHART_TEST_PROJECT_NAME}?!" OFF)
if (GTEST_AUTO_COMPILE)
	message("gtest: AUTO COMPILE")
	add_subdirectory("${GOOGLETEST_PATH}")
	target_link_libraries(${BLACKHART_TEST_PROJECT_NAME} gtest)
else ()
	message("gtest: !(AUTO COMPILE)")
	set(GTEST_LIBRARY_PATH "${GOOGLETEST_PATH}/build/googletest/" CACHE PATH "")
	find_library(GTEST_DEBUG_LIBRARY NAMES gtest PATHS "${GTEST_LIBRARY_PATH}" PATH_SUFFIXES "Debug" "debug" NO_DEFAULT_PATH)
	find_library(GTEST_RELEASE_LIBRARY NAMES gtest PATHS "${GTEST_LIBRARY_PATH}" PATH_SUFFIXES "Release" "release" NO_DEFAULT_PATH)
	if (NOT GTEST_DEBUG_LIBRARY OR NOT GTEST_RELEASE_LIBRARY)
		message("gtest: Library not found!")
	else ()
		message("gtest: Library found!")
		target_link_libraries(${BLACKHART_TEST_PROJECT_NAME} debug "${GTEST_DEBUG_LIBRARY}" optimized "${GTEST_RELEASE_LIBRARY}")
	endif ()
	message("gtest: Debug/library_path:(${GTEST_DEBUG_LIBRARY}) | Release/library_path:(${GTEST_RELEASE_LIBRARY})")
endif ()

set(GTEST_INCLUDE_PATH "${GOOGLETEST_PATH}/googletest/include" CACHE PATH "Include directory of the googletest library")
target_include_directories(${BLACKHART_TEST_PROJECT_NAME} PUBLIC "${GTEST_INCLUDE_PATH}")
message("gtest: include_path:(${GTEST_INCLUDE_PATH})")

message("")