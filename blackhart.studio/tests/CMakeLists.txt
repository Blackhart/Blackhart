cmake_minimum_required(VERSION 3.21)

# ~~~~~ Blackhart tests ~~~~~

set(BLACKHART_STUDIO_TEST_PROJECT_NAME "blackhart.studio.test")

message("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~")
message("${BLACKHART_STUDIO_TEST_PROJECT_NAME}: BUILD ENABLE")

if (MSVC)
	# Sets runtime library to MT
	set(CMAKE_CXX_FLAGS_RELEASE "/MT")
	set(CMAKE_CXX_FLAGS_DEBUG "/MTd")
endif (MSVC)

project(${BLACKHART_STUDIO_TEST_PROJECT_NAME} CXX)

# Gets all the source code (both .c and .h files)
file(GLOB_RECURSE CppFiles sources/*.cpp)

# Compiles Blackhart-test
add_executable(${BLACKHART_STUDIO_TEST_PROJECT_NAME} ${CppFiles})

# Links Blackhart library
target_link_libraries(${BLACKHART_STUDIO_TEST_PROJECT_NAME} PRIVATE ${BLACKHART_PROJECT_NAME})

# Links Blackhart's include directory
target_include_directories(${BLACKHART_STUDIO_TEST_PROJECT_NAME} PUBLIC "${MAIN_PATH}/blackhart/includes")


# ~~~~~ gtest ~~~~~

include("${MAIN_PATH}/cmake/deps/gtest.cmake")

# gtest already provides include directories through its target.
target_link_libraries(${BLACKHART_STUDIO_TEST_PROJECT_NAME} PRIVATE gtest)


# ~~~~~ CTest ~~~~~

include(GoogleTest)

gtest_discover_tests(${BLACKHART_STUDIO_TEST_PROJECT_NAME}
	WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)