cmake_minimum_required(VERSION 3.12)

project(glad)

set(GLAD_BUILD_STATIC_LIBRARY OFF CACHE BOOL "Build static library")
set(GLAD_BUILD_SHARED_LIBRARY ON CACHE BOOL "Build shared library")

if(NOT GLAD_BUILD_STATIC_LIBRARY AND NOT GLAD_BUILD_SHARED_LIBRARY)
    message(FATAL_ERROR "No library type selected for glad")
endif()

if(GLAD_BUILD_STATIC_LIBRARY)
    add_library(glad STATIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include/KHR/khrplatform.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/glad/gl.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/gl.c
    )
endif()
if(GLAD_BUILD_SHARED_LIBRARY)
    add_library(glad SHARED
        ${CMAKE_CURRENT_SOURCE_DIR}/include/KHR/khrplatform.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/glad/gl.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/gl.c
    )
endif()

target_include_directories(glad PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include/KHR
    ${CMAKE_CURRENT_SOURCE_DIR}/include/glad
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)
