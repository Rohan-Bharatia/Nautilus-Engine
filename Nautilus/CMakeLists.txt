cmake_minimum_required(VERSION 3.10.0)

project(Nautilus LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Create required compiler definitions
if(WIN32)
    add_compile_definitions(NT_PLATFORM_WINDOWS)
elseif(UNIX AND NOT APPLE)
    add_compile_definitions(NT_PLATFORM_LINUX)
elseif(APPLE AND NOT CMAKE_SYSTEM_NAME MATCHES "iOS")
    add_compile_definitions(NT_PLATFORM_MACOS)
else()
    message(FATAL_ERROR "Unsupported platform detected: ${CMAKE_SYSTEM_NAME}")
endif()

# Create the Nautilus library
add_library(Nautilus SHARED
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Test.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Test.cpp
)

# Include the source directory
target_include_directories(Nautilus PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Link any dependencies
target_link_libraries(Nautilus
    # Add any dependencies required by Nautilus (None so far)
)

# Set the output directories
set_target_properties(Nautilus PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/lib
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/lib
)
