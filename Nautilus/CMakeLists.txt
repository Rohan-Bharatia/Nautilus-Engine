cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(${CMAKE_CURRENT_SOURCE_DIR}/../cmake/runtime.cmake)

project(Nautilus)

function(link_dependency directory target)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Vendor/${directory})
    target_link_libraries(Nautilus PUBLIC ${target})
    foreach(header IN LISTS ARGN)
        target_include_directories(Nautilus PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Vendor/${directory}/${header})
    endforeach()
endfunction()

file(GLOB Nautilus_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/Src/**/*.cpp
)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)
use_runtime("static")
add_library(Nautilus STATIC ${Nautilus_SOURCES})
target_precompile_headers(Nautilus PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/Src/PCH.h)

find_package(TBB REQUIRED)
target_link_libraries(Nautilus PRIVATE TBB::tbb)

set(SDL_STATIC ON CACHE BOOL "Build SDL as static library" FORCE)
set(SDL_SHARED OFF CACHE BOOL "Disable SDL shared library" FORCE)
set(BGFX_BUILD_TOOLS OFF CACHE BOOL "Disable bgfx tools" FORCE)
set(BGFX_BUILD_EXAMPLES OFF CACHE BOOL "Disable bgfx examples" FORCE)
set(BGFX_BUILD_TOOLS_SHADER ON CACHE BOOL "Enable bgfx shader tools" FORCE)
set(BX_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Vendor/BGFX/bx")
set(BIMG_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Vendor/BGFX/bimg")
set(BGFX_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Vendor/BGFX/bgfx")
link_dependency("SDL" "SDL3::SDL3-static" "include")
link_dependency("BGFX" "bgfx" "bx/include" "bimg/include" "bgfx/include" "bgfx/tools")
link_dependency("glm" "glm")

target_include_directories(Nautilus PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/..
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/Src
    ${CMAKE_CURRENT_SOURCE_DIR}/Src/Core
)

set_target_properties(Nautilus PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)
