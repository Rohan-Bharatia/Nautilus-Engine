@echo off

@echo Creating build directory...
cd ..
if not exist Build mkdir Build

@echo Compiling with CMake...
cd Build
cmake -G "MinGW Makefiles" ../Sandbox
cmake --build .

@echo Done...
cd ..
exit 0
