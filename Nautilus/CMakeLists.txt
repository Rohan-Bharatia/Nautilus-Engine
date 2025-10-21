cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

include(${CMAKE_CURRENT_SOURCE_DIR}/../cmake/runtime.cmake)

project(Nautilus)

function(link_dependency directory target)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Vendor/${directory})
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
link_dependency("SDL" "SDL3" "include")
link_dependency("glm" "glm")

target_include_directories(Nautilus PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/..
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/Src
    ${CMAKE_CURRENT_SOURCE_DIR}/Src/Core
    ${CMAKE_CURRENT_SOURCE_DIR}/Src/Math
    ${CMAKE_CURRENT_SOURCE_DIR}/Src/Renderer
)

set_target_properties(Nautilus PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)
