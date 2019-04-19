# Set minimum version
cmake_minimum_required(VERSION 3.9.6)

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

target_compile_options(fal PRIVATE -Werror)
target_compile_features(fal PRIVATE cxx_std_17)
