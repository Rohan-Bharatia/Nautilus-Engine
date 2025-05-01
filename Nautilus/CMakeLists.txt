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
    message(FATAL_ERROR "Unsupported platform detected: ${CMAKE_SYSTEM_NAME}! Supported platforms: Windows, Linux, macOS")
endif()
add_compile_definitions(NT_BUILD_SHARED)

# Gather source files
file(GLOB_RECURSE Nautilus_LIB_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Nautilus/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Nautilus/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Nautilus/Events/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Nautilus/Events/*.cpp
)
file(GLOB_RECURSE Nautilus_PCH_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/PCH.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/PCH.cpp
)

# Create the Nautilus library
add_library(Nautilus SHARED ${Nautilus_LIB_FILES})
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/vendor/spdlog)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/vendor/GLFW)

target_compile_options(Nautilus PUBLIC -include ${CMAKE_CURRENT_SOURCE_DIR}/src/PCH.h)

# Include the source directory
target_include_directories(Nautilus PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Nautilus
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Nautilus/Events
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/spdlog/include
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/GLFW/include
)

# Link any dependencies
target_link_libraries(Nautilus PUBLIC
    ${SPDLOG_LIBRARIES}
    ${GLFW_LIBRARIES}
)

# Set the output directories
set_target_properties(Nautilus PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/../bin
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/../lib
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/../lib
)
