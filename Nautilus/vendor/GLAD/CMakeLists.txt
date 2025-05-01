cmake_minimum_required(VERSION 3.10.0)

project(GLAD)

file(GLOB GLAD_LIB_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/include/KHR/khrplatform.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/glad/glad.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/glad.c
)
add_library(glad STATIC ${GLAD_LIB_FILES})

target_include_directories(glad PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
