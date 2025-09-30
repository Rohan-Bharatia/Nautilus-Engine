cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(${CMAKE_CURRENT_SOURCE_DIR}/../cmake/runtime.cmake)

project(Nautilus)

file(GLOB Nautilus_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/Src/**/*.cpp
)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)
use_runtime("static")
add_library(Nautilus STATIC ${Nautilus_SOURCES})
target_precompile_headers(Nautilus PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/Src/PCH.h)

find_package(TBB REQUIRED)
target_link_libraries(Nautilus PRIVATE TBB::tbb)

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
