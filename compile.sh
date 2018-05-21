rm -rf build
mkdir build
cd build
cmake -G"Visual Studio 14 2015 Win64" -DBUILD_BLACKHART_TESTS:BOOL=true -DBUILD_BLACKHART_STUDIO_TESTS:BOOL=false -DUNITY_LIBRARY_PATH:PATH="../../extlibs/unity/lib" -DUNITY_INCLUDE_PATH:PATH="../../extlibs/unity/include" -DGLEW_LIBRARY_PATH:PATH="../extlibs/glew/lib" -DGLEW_INCLUDE_PATH:PATH="../extlibs/glew/include" -DGLFW_LIBRARY_PATH:PATH="../extlibs/glfw/lib" -DGLFW_INCLUDE_PATH:PATH="../extlibs/glfw/include" -DGTEST_LIBRARY_PATH:PATH="../../extlibs/googletest/googletest/lib" -DGTEST_INCLUDE_PATH:PATH="../../extlibs/googletest/googletest/include" -DQT_DIRECTORY_PATH:PATH="D:/Program/Qt/5.10.1/5.10.1/msvc2015_64" ..
cd ..