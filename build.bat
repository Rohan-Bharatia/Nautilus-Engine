@echo off

setlocal EnableDelayedExpansion

set NO_INSTALL=false
set NO_DEBUG_BUILD=false
set CLEAN_OUTPUT=false
:check_args
if "%~1"=="" goto args_checked
if /I "%~1"=="--no-install" set NO_INSTALL=true
if /I "%~1"=="--no-debug-build" set NO_DEBUG_BUILD=true
if /I "%~1"=="--clean-output" set CLEAN_OUTPUT=true
shift
goto check_args
:args_checked

if "%CLEAN_OUTPUT%"=="true" (
    @echo Cleaning output...
    rmdir /s /q build
)

if "%NO_INSTALL%"=="false" (
    @echo Installing dependencies...
    call scripts/install_windows_deps.bat
)

@echo Creating build directory...
mkdir /s /q build

@echo Compiling with CMake...
cd build

if "%NO_DEBUG_BUILD%"=="false" (
    @echo Debug build...
    mkdir /s /q debug
    cd debug
    cmake -G "Ninja" -S ../../Tidebox -DCMAKE_BUILD_TYPE=Debug
    cmake --build .
    cd ..
)

@echo Release build...
mkdir /s /q release
cd release
cmake -G "Ninja" -S ../../Tidebox -DCMAKE_BUILD_TYPE=Release
cmake --build .
cd ..

@echo Done...
cd ..
exit 0
