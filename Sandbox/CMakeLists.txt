cmake_minimum_required(VERSION 3.10.0)

project(Sandbox LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

function(link_lib TARGET)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../${TARGET} ${CMAKE_CURRENT_BINARY_DIR}/${TARGET})
    target_link_libraries(Sandbox PUBLIC ${TARGET})
endfunction()

# Create the sandbox executable
add_executable(Sandbox ${CMAKE_CURRENT_SOURCE_DIR}/src/Sandbox.cpp)

# Link the Nautilus library
link_lib(Nautilus)

# Include the source directory
target_include_directories(Sandbox PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

# Set the output directories
set_target_properties(Sandbox PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/lib
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/lib
)
