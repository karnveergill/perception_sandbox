cmake_minimum_required(VERSION 3.16)

# Project version
include(version.cmake)
project(
    perception_sandbox
    VERSION
    ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}
    LANGUAGES CXX
)

# Setup C++ version and turn off extension to ensure using c++20 not gnu++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Generate version header
configure_file(
    ${PROJECT_SOURCE_DIR}/cmake/version.h.in
    ${PROJECT_BINARY_DIR}/generated/perception/core/VersionGenerated.hpp
    @ONLY
)

# Gather library sources
file(
    GLOB_RECURSE 
    LIBRARY_SOURCES
    CONFIGURE_DEPENDS
    src/*.cpp
)

# Create project library
add_library(
    ${PROJECT_NAME}
    ${LIBRARY_SOURCES}
)

# Make libaray alias name
add_library(
    perception::core
    ALIAS
    ${PROJECT_NAME}
)

# Add headers (from include & generated) to project root
target_include_directories(
    ${PROJECT_NAME}
    PUBLIC
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_BINARY_DIR}/generated
)

# Enable compiler warnings
include(cmake/CompilerWarnings.cmake)
enable_project_warnings(${PROJECT_NAME})

# Add applications
add_subdirectory(apps)

# Enable Testing
enable_testing()
add_subdirectory(tests)