rm -rf build
mkdir build
cd build
cmake -G"Visual Studio 14 2015" -DGLEW_LIBRARY_PATH:PATH="extlibs/glew/lib" -DGLEW_INCLUDE_PATH:PATH="extlibs/glew/include" -DBUILD_BLACKHART_TESTS:BOOL=true -DGTEST_LIBRARY_PATH:PATH="extlibs/googletest/googletest/lib" -DGTEST_INCLUDE_PATH:PATH="extlibs/googletest/googletest/include"  ..
cd ..