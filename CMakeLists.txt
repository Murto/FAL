# Set minimum version
cmake_minimum_required(VERSION 3.9.6)

# Set C++ standard to C++17
set(CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Set project name
project(FAL)


# Include include directory
include_directories(include)

# Set sources to source files under src directory
file(GLOB SOURCES "src/*.cpp")

# Add fal executable
add_executable(fal ${SOURCES})
