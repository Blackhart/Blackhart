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

target_include_directories(${BLACKHART_PROJECT_NAME} PUBLIC "${BLACKHART_PATH}/include")


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

message("")