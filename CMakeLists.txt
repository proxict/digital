cmake_minimum_required(VERSION 3.21)
project(digital VERSION 1.0.0 LANGUAGES CXX)

set(PROJECT_NAMESPACE "prox::digital" CACHE STRING "The namespace encompassing the 'unit' definition")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_library(digital INTERFACE)

if(NOT TARGET proxict::digital)
    add_library(proxict::digital ALIAS digital)
endif()

target_include_directories(digital
    INTERFACE include
)
target_compile_definitions(digital
    INTERFACE "PROX_DIGITAL_NAMESPACE_NAME=${PROJECT_NAMESPACE}"
)

option(BUILD_TESTS "Build unittests" OFF)
if (BUILD_TESTS)
    add_subdirectory(tests)
endif()

