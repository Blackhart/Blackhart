rm -rf build
mkdir build
cd build
cmake -G"Visual Studio 14 2015" -DBUILD_BLACKHART_TESTS:BOOL=true -DUNITY_LIBRARY_PATH:PATH="extlibs/unity/lib" -DUNITY_INCLUDE_PATH:PATH="extlibs/unity/include"  ..
cd ..