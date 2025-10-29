cmake_minimum_required(VERSION 3.16)

project(stb)

file(GLOB stb_SRC
    ${CMAKE_CURRENT_SOURCE_DIR}/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/*.c
)

add_library(stb STATIC ${stb_SRC})

target_include_directories(stb PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
