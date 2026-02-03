cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

include(${CMAKE_CURRENT_SOURCE_DIR}/../scripts/runtime.cmake)

project(Nautilus)

function(link_dependency directory target)
    if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/Vendor/${directory}/CMakeLists.txt)
        add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Vendor/${directory})
    endif()
    target_link_libraries(Nautilus PUBLIC ${target})
    foreach(header IN LISTS ARGN)
        target_include_directories(Nautilus PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Vendor/${directory}/${header})
    endforeach()
    if(NOT ${target} STREQUAL "SDL3")
        set_target_properties(${target} PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
            LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
            ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
        )
    endif()
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
set(SDL_SHARED OFF CACHE BOOL "Build SDL as shared library" FORCE)
set(SDL_TESTS OFF CACHE BOOL "Disable SDL tests" FORCE)
set(SDL_EXAMPLES OFF CACHE BOOL "Disable SDL examples" FORCE)
set(GLM_BUILD_TESTS OFF CACHE BOOL "Disable GLM tests" FORCE)
set(GLAD_BUILD_STATIC_LIBRARY ON CACHE BOOL "Build GLAD as static library" FORCE)
set(GLAD_BUILD_SHARED_LIBRARY OFF CACHE BOOL "Build GLAD as shared library" FORCE)
set(MSDF_ATLAS_USE_VCPKG OFF CACHE BOOL "Disable MSDF-Atlas-Gen VCPKG support" FORCE)
set(MSDF_ATLAS_USE_SKIA OFF CACHE BOOL "Disable MSDF-Atlas-Gen Skia support" FORCE)
set(IMGUI_BACKEND_SDL3 ON CACHE BOOL "Enable ImGui SDL3 backend" FORCE)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Vendor)
link_dependency("SDL" "SDL3" "include")
link_dependency("glm" "glm" ".")
link_dependency("glad" "glad" "include")
link_dependency("stb" "stb" ".")
link_dependency("msdf-atlas-gen" "msdf-atlas-gen" "msdf-atlas-gen")
link_dependency("imgui" "imgui" ".")
link_dependency("entt" "EnTT" "src")

target_include_directories(Nautilus PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/..
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/Vendor
    ${CMAKE_CURRENT_SOURCE_DIR}/Src
    ${CMAKE_CURRENT_SOURCE_DIR}/Src/Core
    ${CMAKE_CURRENT_SOURCE_DIR}/Src/Math
    ${CMAKE_CURRENT_SOURCE_DIR}/Src/Renderer
    ${CMAKE_CURRENT_SOURCE_DIR}/Src/GUI
)

set_target_properties(Nautilus PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)
