cmake_minimum_required(VERSION 3.7)

# ~~~~~ Blackhart-Editor ~~~~~

message("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~")
message("${BLACKHART_STUDIO_QT_PROJECT_NAME}: BUILD ENABLE")

project(${BLACKHART_STUDIO_QT_PROJECT_NAME} CXX)

# Sets Blackhart-Editor's sources directory
set(BLACKHART_STUDIO_PATH "${${BLACKHART_STUDIO_QT_PROJECT_NAME}_SOURCE_DIR}")

# Gets all the source code (both .c and .h files)
file(GLOB_RECURSE CppFiles sources/*.cpp)
file(GLOB_RECURSE HppFiles includes/*.hpp)

# Compiles Blackhart-Editor
add_executable(${BLACKHART_STUDIO_QT_PROJECT_NAME} ${CppFiles} ${HppFiles})

# Links Blackhart's include directory
target_include_directories(${BLACKHART_STUDIO_QT_PROJECT_NAME} PUBLIC "${BLACKHART_STUDIO_PATH}/includes")

# Sets Blackhart's library directory
set(BLACKHART_LIBRARY_PATH "${MAIN_PATH}/build_install/bin" CACHE PATH "Blackhart's library directory")

# Finds Blackhart library
target_link_libraries(${BLACKHART_STUDIO_QT_PROJECT_NAME} ${BLACKHART_PROJECT_NAME})

# Links Blackhart's include directory
target_include_directories(${BLACKHART_STUDIO_QT_PROJECT_NAME} PUBLIC "${MAIN_PATH}/blackhart/includes")


# # ~~~~~ Glew ~~~~~

# message("")

# # Sets glew's library directory
# set(GLEW_LIBRARY_PATH "" CACHE PATH "glew's library directory")

# # Finds glew library
# find_library(GLEW_DEBUG_LIBRARY NAMES glew32d PATHS "${GLEW_LIBRARY_PATH}" PATH_SUFFIXES "Debug" "debug" NO_DEFAULT_PATH)
# find_library(GLEW_RELEASE_LIBRARY NAMES glew32 PATHS "${GLEW_LIBRARY_PATH}" PATH_SUFFIXES "Release" "release" NO_DEFAULT_PATH)

# # Finds OpenGL package
# find_package(OpenGL REQUIRED)

# if (NOT GLEW_DEBUG_LIBRARY OR NOT GLEW_RELEASE_LIBRARY)
	# message("glew: Library not found!")
# else ()
	# message("glew: Library found!")
	# message("glew: Debug/library_path:(${GLEW_DEBUG_LIBRARY}) | Release/library_path:(${GLEW_RELEASE_LIBRARY})")
	# # Links glew library to blackhart.studio
	# target_link_libraries(${BLACKHART_STUDIO_QT_PROJECT_NAME} debug "${GLEW_DEBUG_LIBRARY}" optimized "${GLEW_RELEASE_LIBRARY}")
	# # Links opengl libraries to blackhart.studio
	# target_link_libraries(${BLACKHART_STUDIO_QT_PROJECT_NAME} "${OPENGL_LIBRARIES}")
# endif ()

# # Sets glew's include directory
# set(GLEW_INCLUDE_PATH "" CACHE PATH "glew's include directory")

# # Links glew's include directory
# target_include_directories(${BLACKHART_STUDIO_QT_PROJECT_NAME} PUBLIC "${GLEW_INCLUDE_PATH}")

# message("glew: include_path:(${GLEW_INCLUDE_PATH})")


# ~~~~~ Qt ~~~~~

message("")

# Sets the Qt directory
set(QT_DIRECTORY_PATH "" CACHE PATH "Qt directory path")

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

# Find the QtWidgets library
find_package(Qt5Widgets REQUIRED PATHS ${QT_DIRECTORY_PATH} PATH_SUFFIXES "lib/cmake/Qt5Widgets" NO_DEFAULT_PATH)

# Use the Widgets module from Qt 5.
target_link_libraries(${BLACKHART_STUDIO_QT_PROJECT_NAME} Qt5::Widgets)