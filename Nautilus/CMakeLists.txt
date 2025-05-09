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
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_definitions(NT_DEBUG)
endif()
add_compile_definitions(_CRT_SECURE_NO_WARNINGS)

# Gather source files
file(GLOB Nautilus_LIB_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Nautilus/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Nautilus/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Nautilus/Core/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Nautilus/Core/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Nautilus/Events/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Nautilus/Events/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Nautilus/ImGui/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Nautilus/ImGui/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Nautilus/Renderer/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Nautilus/Renderer/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Platform/OpenGL/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Platform/OpenGL/*.cpp
)
if(WIN32)
    list(APPEND Nautilus_LIB_FILES
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Platform/Windows/WindowsWindow.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Platform/Windows/WindowsWindow.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Platform/Windows/WindowsInput.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Platform/Windows/WindowsInput.cpp
    )
elseif(UNIX AND NOT APPLE)
    list(APPEND Nautilus_LIB_FILES
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Platform/Linux/LinuxWindow.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Platform/Linux/LinuxWindow.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Platform/Linux/LinusInput.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Platform/Linux/LinusInput.cpp
    )
elseif(APPLE AND NOT CMAKE_SYSTEM_NAME MATCHES "iOS")
    list(APPEND Nautilus_LIB_FILES
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Platform/MacOS/MacOSWindow.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Platform/MacOS/MacOSWindow.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Platform/MacOS/MacOsInput.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Platform/MacOS/MacOsInput.cpp
    )
endif()

# Create the Nautilus library
add_library(Nautilus SHARED ${Nautilus_LIB_FILES})
target_compile_options(Nautilus PUBLIC -fPIC -pthread)

# Add dependencies
find_package(OpenGL REQUIRED)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/vendor/spdlog)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/vendor/GLFW)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/vendor/GLAD)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/vendor/glm)

# Include the source directory
target_include_directories(Nautilus PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Nautilus
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Nautilus/Events
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/spdlog/include
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/GLFW/include
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/GLAD/include
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/ # ImGui doesn't use a header directory so we need to add this manually
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/glm
)

# Link dependencies
target_link_libraries(Nautilus PUBLIC
    ${OPENGL_LIBRARIES}
    spdlog::spdlog
    glfw
    glad
    imgui
    glm
)

option(IMGUI_BACKEND_GLFW "Enable GLFW backend for ImGui" ON)

# Set the output directories
set_target_properties(Nautilus PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/../bin
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/../lib
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/../lib
)
