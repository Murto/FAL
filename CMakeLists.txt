# Set minimum version
cmake_minimum_required(VERSION 3.7.2)

# Set C++ version
set(CMAKE_CXX_STANDARD 14)

# Set project
project(fal LANGUAGES CXX)

# Set sources to source files under src directory
file(GLOB SOURCES "src/*.cpp")

# Add FAL executable
add_executable(fal ${SOURCES})

# Include include directory
target_include_directories(fal
  PUBLIC
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

# Make warnings errors
target_compile_options(fal PRIVATE -Werror)
