cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

project(Tidebox)

file(GLOB Tidebox_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/Src/*.cpp
)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)
add_executable(Tidebox ${Tidebox_SOURCES})

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../Nautilus ${CMAKE_CURRENT_BINARY_DIR}/Nautilus)
target_link_libraries(Tidebox Nautilus)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

target_include_directories(Nautilus PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/..
)

set_target_properties(Tidebox PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)
