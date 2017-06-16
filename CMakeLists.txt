cmake_minimum_required(VERSION 3.7)

set(BLACKHART_PROJECT_NAME "Blackhart")

project(${BLACKHART_PROJECT_NAME} C)

set(${BLACKHART_PROJECT_NAME}_VERSION_MAJOR 0)
set(${BLACKHART_PROJECT_NAME}_VERSION_MINOR 1)
set(${BLACKHART_PROJECT_NAME}_VERSION_PATCH 0)

message("")
message("${BLACKHART_PROJECT_NAME}: BUILD ENABLE")
message("~~~ ${BLACKHART_PROJECT_NAME} ~~~")


# Blackhart

set(BLACKHART_PATH "${${BLACKHART_PROJECT_NAME}_SOURCE_DIR}")

file(GLOB_RECURSE CFiles sources/*.c)
file(GLOB_RECURSE HFiles includes/*.h)

option(BUILD_BLACKHART_AS_SHARED_LIBS "Build Blackhart as shared libs ?" OFF)
if (BUILD_BLACKHART_AS_SHARED_LIBS)
	message("${BLACKHART_PROJECT_NAME}: Library:(SHARED)")
	add_library(${BLACKHART_PROJECT_NAME} SHARED ${CFiles} ${HFiles})
else (BUILD_BLACKHART_AS_SHARED_LIBS)
	message("${BLACKHART_PROJECT_NAME}: Library:(STATIC)")
	add_library(${BLACKHART_PROJECT_NAME} STATIC ${CFiles} ${HFiles})
endif (BUILD_BLACKHART_AS_SHARED_LIBS)

target_include_directories(${BLACKHART_PROJECT_NAME} PUBLIC "${BLACKHART_PATH}/includes")


# extlibs

set(BLACKHART_EXTLIBS_PATH "${BLACKHART_PATH}/extlibs")


# Vulkan

set(VULKAN_PATH "${BLACKHART_EXTLIBS_PATH}/vulkan")

set(VULKAN_LIBRARY_PATH "${VULKAN_PATH}/Lib32" CACHE PATH "Vulkan's library directory")
find_library(VULKAN_LIBRARY NAMES vulkan-1 PATHS "${VULKAN_LIBRARY_PATH}" NO_DEFAULT_PATH)
if (NOT VULKAN_LIBRARY)
	message("vulkan: Library not found!")
else ()
	message("vulkan: Library found!")
	target_link_libraries(${BLACKHART_PROJECT_NAME} "${VULKAN_LIBRARY}")
endif ()
message("vulkan: library_path:(${VULKAN_LIBRARY})")

set(VULKAN_INCLUDE_PATH "${VULKAN_PATH}/Include" CACHE PATH "Vulkan's include directory")
target_include_directories(${BLACKHART_PROJECT_NAME} PUBLIC "${VULKAN_INCLUDE_PATH}")
message("vulkan: include_path:(${VULKAN_INCLUDE_PATH})")


# Glew

message("")
set(GLEW_PATH "${BLACKHART_EXTLIBS_PATH}/glew")

option(GLEW_AUTO_COMPILE "Will glew must be compile with ${BLACKHART_PROJECT_NAME}?!" OFF)
if (GLEW_AUTO_COMPILE)
	message("glew: AUTO COMPILE")
	add_subdirectory("${GLEW_PATH}/build/cmake")
	target_link_libraries(${BLACKHART_PROJECT_NAME} glew)
else ()
	message("glew: !(AUTO COMPILE)")
	set(GLEW_LIBRARY_PATH "${GLEW_PATH}/lib" CACHE PATH "Library directory of the glew library")
	find_library(GLEW_DEBUG_LIBRARY NAMES glew32d PATHS "${GLEW_LIBRARY_PATH}" PATH_SUFFIXES "Debug" "debug" NO_DEFAULT_PATH)
	find_library(GLEW_RELEASE_LIBRARY NAMES glew32 PATHS "${GLEW_LIBRARY_PATH}" PATH_SUFFIXES "Release" "release" NO_DEFAULT_PATH)
	if (NOT GLEW_DEBUG_LIBRARY OR NOT GLEW_RELEASE_LIBRARY)
		message("glew: Library not found!")
	else ()
		message("glew: Library found!")
		target_link_libraries(${BLACKHART_PROJECT_NAME} debug "${GLEW_DEBUG_LIBRARY}" optimized "${GLEW_RELEASE_LIBRARY}")
	endif ()
	message("glew: Debug/library_path:(${GLEW_DEBUG_LIBRARY}) | Release/library_path:(${GLEW_RELEASE_LIBRARY})")
endif()

set(GLEW_INCLUDE_PATH "${GLEW_PATH}/include" CACHE PATH "Include directory of the glew library")
target_include_directories(${BLACKHART_PROJECT_NAME} PUBLIC "${GLEW_INCLUDE_PATH}")
message("glew: include_path:(${GLEW_INCLUDE_PATH})")


# Samples

set(BLACKHART_SAMPLES_PATH "${BLACKHART_PATH}/samples")

option(BUILD_BLACKHART_SAMPLES "Build the Blackhart's samples" OFF)
if (BUILD_BLACKHART_SAMPLES)
	add_subdirectory("${BLACKHART_SAMPLES_PATH}")
endif (BUILD_BLACKHART_SAMPLES)


message("")