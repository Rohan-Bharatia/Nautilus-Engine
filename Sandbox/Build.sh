#!/bin/bash

echo "Creating build directory..."
cd ..
if [ ! -d "Build" ]; then
    mkdir Build
fi

echo "Compiling with CMake..."
cd Build
cmake -G "Unix Makefiles" ../Sandbox
cmake --build .

echo "Done..."
cd ..
exit 0
