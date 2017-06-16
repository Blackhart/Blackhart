cmake_minimum_required(VERSION 3.7)

set(CAR_PROJECT_NAME "Car")

project(${CAR_PROJECT_NAME} C)

message("")
message("${CAR_PROJECT_NAME}: BUILD ENABLE")
message("~~~ ${CAR_PROJECT_NAME} ~~~")


# Car

file(GLOB_RECURSE CFiles sources/*.c)
file(GLOB_RECURSE HFiles includes/*.h)

add_executable(${CAR_PROJECT_NAME} ${CFiles} ${HFiles})

target_include_directories(${CAR_PROJECT_NAME} PUBLIC "${${CAR_PROJECT_NAME}_SOURCE_DIR}/includes")


# Blackhart

target_include_directories(${CAR_PROJECT_NAME} PUBLIC "${${BLACKHART_PROJECT_NAME}_SOURCE_DIR}/includes")
if (NOT BUILD_BLACKHART_AS_SHARED_LIBS)
	target_link_libraries(${CAR_PROJECT_NAME} Blackhart)
	target_include_directories(${CAR_PROJECT_NAME} PUBLIC "${VULKAN_INCLUDE_PATH}")
	target_include_directories(${CAR_PROJECT_NAME} PUBLIC "${GLEW_INCLUDE_PATH}")
	if (VULKAN_LIBRARY)
		target_link_libraries(${CAR_PROJECT_NAME} "${VULKAN_LIBRARY}")
	endif ()
	if (GLEW_AUTO_COMPILE)
		target_link_libraries(${CAR_PROJECT_NAME} glew)
	else ()
		target_link_libraries(${CAR_PROJECT_NAME} debug "${GLEW_DEBUG_LIBRARY}" optimized "${GLEW_RELEASE_LIBRARY}")
	endif()
endif()


# extlibs

set(CAR_EXTLIBS_PATH "${${CAR_PROJECT_NAME}_SOURCE_DIR}/extlibs")


# glfw

set(GLFW_PATH "${CAR_EXTLIBS_PATH}/glfw")

option(GLFW_AUTO_COMPILE "Will glfw must be compile with ${CAR_PROJECT_NAME}?!" OFF)
if (GLFW_AUTO_COMPILE)
	message("glfw: AUTO COMPILE")
	add_subdirectory("${GLFW_PATH}")
	target_link_libraries(${CAR_PROJECT_NAME} glfw)
else ()
	message("glfw: !(AUTO COMPILE)")
	set(GLFW_LIBRARY_PATH "${GLFW_PATH}/build/src/" CACHE PATH "")
	find_library(GLFW_DEBUG_LIBRARY NAMES glfw3 PATHS "${GLFW_LIBRARY_PATH}" PATH_SUFFIXES "Debug" "debug" NO_DEFAULT_PATH)
	find_library(GLFW_RELEASE_LIBRARY NAMES glfw3 PATHS "${GLFW_LIBRARY_PATH}" PATH_SUFFIXES "Release" "release" NO_DEFAULT_PATH)
	if (NOT GLFW_DEBUG_LIBRARY OR NOT GLFW_RELEASE_LIBRARY)
		message("glfw: Library not fount!")
	else ()
		message("glfw: Library found!")
		target_link_libraries(${CAR_PROJECT_NAME} debug "${GLFW_DEBUG_LIBRARY}" optimized "${GLFW_RELEASE_LIBRARY}")
	endif ()
	message("glfw: Debug/library_path:(${GLFW_DEBUG_LIBRARY}) | Release/library_path:(${GLFW_RELEASE_LIBRARY})")
endif ()

set(GLFW_INCLUDE_PATH "${GLFW_PATH}/include" CACHE PATH "Include directory of the glfw library")
target_include_directories(${CAR_PROJECT_NAME} PUBLIC "${GLFW_INCLUDE_PATH}")
message("glfw: include_path:(${GLFW_INCLUDE_PATH})")

message("")