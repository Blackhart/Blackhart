cmake_minimum_required(VERSION 3.21)

# ~~~~~ Blackhart tests ~~~~~

set(BLACKHART_TEST_PROJECT_NAME "blackhart.test")

message("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~")
message("${BLACKHART_TEST_PROJECT_NAME}: BUILD ENABLE")

project(${BLACKHART_TEST_PROJECT_NAME} C)

# Sets Blackhart test's sources directory
set(BLACKHART_TEST_PATH "${${BLACKHART_TEST_PROJECT_NAME}_SOURCE_DIR}")

# Gets all the source code (both .c and .h files)
file(GLOB_RECURSE CFiles sources/*.c)
file(GLOB_RECURSE HFiles includes/*.h)

# Compiles Blackhart-test
add_executable(${BLACKHART_TEST_PROJECT_NAME} ${CFiles} ${HFiles})

# Links Blackhart's include directory
target_include_directories(${BLACKHART_TEST_PROJECT_NAME} PUBLIC "${BLACKHART_PATH}/includes")

# Links Blackhart-Test's include directory
target_include_directories(${BLACKHART_TEST_PROJECT_NAME} PUBLIC "${BLACKHART_TEST_PATH}/includes")

# Links Blackhart library
target_link_libraries(${BLACKHART_TEST_PROJECT_NAME} PRIVATE ${BLACKHART_PROJECT_NAME})


# ~~~~~ Unity ~~~~~

include("${BLACKHART_PATH}/../cmake/deps/unity.cmake")

# `unity::framework` provides both include paths and the library.
target_link_libraries(${BLACKHART_TEST_PROJECT_NAME} PRIVATE unity::framework)


# ~~~~~ CTest ~~~~~

add_test(
	NAME ${BLACKHART_TEST_PROJECT_NAME}
	COMMAND $<TARGET_FILE:${BLACKHART_TEST_PROJECT_NAME}>
	WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)