# Set minimum version
cmake_minimum_required(VERSION 3.7.2)

# Set C++ version
set(CMAKE_CXX_STANDARD 14)

# Set project
project(fal LANGUAGES CXX)

# Include Boost library
set(BOOST_INCLUDEDIR "/usr/include")
find_package(Boost REQUIRED)

# Set sources to source files under src directory
file(GLOB SOURCES "src/*.cpp")

# Add FAL executable
add_executable(fal ${SOURCES})

# Include graphviz libraries
find_library(GVC_LIB gvc)
target_link_libraries(fal "${GVC_LIB}")
find_library(CGRAPH_LIB cgraph)
target_link_libraries(fal "${CGRAPH_LIB}")
find_library(CDT_LIB cdt)
target_link_libraries(fal "${CDT_LIB}")

# Include include directory
target_include_directories(fal
  PUBLIC
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

# Make warnings errors
target_compile_options(fal PRIVATE -Werror)
