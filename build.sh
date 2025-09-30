#!/bin/bash

set -e

NO_INSTALL=false
NO_DEBUG_BUILD=false
CLEAN_OUTPUT=false
for arg in "$@"; do
    case "$arg" in
        --no-install)
            NO_INSTALL=true
            ;;
        --no-debug-build)
            NO_DEBUG_BUILD=true
            ;;
        --clean-output)
            CLEAN_OUTPUT=true
            ;;
    esac
done

if [ "$CLEAN_OUTPUT" = true ]; then
    echo "Cleaning output..."
    rm -rf build
fi

if [ "$NO_INSTALL" = false ]; then
    echo "Installing dependencies..."
    chmod +x scripts/*.sh

    case "$(uname -s)" in
        Darwin)
            ./scripts/install_macos_deps.sh
            ;;
        Linux)
            ./scripts/install_linux_deps.sh
            ;;
        *)
            echo "Unknown OS: $(uname -s)"
            exit 1
            ;;
    esac
fi

echo "Creating build directory..."
mkdir -p build

echo "Compiling with CMake..."
cd build

if [ "$NO_DEBUG_BUILD" = false ]; then
    echo "Debug build..."
    mkdir -p debug
    cd debug
    cmake -G "Ninja" -S ../../Tidebox -DCMAKE_BUILD_TYPE=Debug
    cmake --build .
    cd ..
fi

echo "Release build..."
mkdir -p release
cd release
cmake -G "Ninja" -S ../../Tidebox -DCMAKE_BUILD_TYPE=Release
cmake --build .
cd ..

echo "Done..."
cd ..
exit 0
