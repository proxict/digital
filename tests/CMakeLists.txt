cmake_minimum_required(VERSION 3.21)
project(digital-unittests VERSION 1.0.0 LANGUAGES CXX)

include(cmake/asan.cmake)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable(unittests
    unittests.cpp
)

if(NOT CMAKE_CXX_STANDARD)
    set_property(TARGET unittests PROPERTY CXX_STANDARD 17)
endif()

set_property(TARGET unittests PROPERTY CXX_STANDARD_REQUIRED TRUE)
set_property(TARGET unittests PROPERTY CXX_EXTENSIONS OFF)

# Fetch Boost.UT testing framework
include(FetchContent)
FetchContent_Declare(doctest
    GIT_REPOSITORY https://github.com/doctest/doctest.git
    GIT_TAG        v2.4.11
)
FetchContent_MakeAvailable(doctest)

target_link_libraries(unittests
    PRIVATE proxict::digital
    PRIVATE doctest::doctest
)

add_custom_target(run-unittests
    COMMAND $<TARGET_FILE:unittests> -s -d -fc
    DEPENDS unittests
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)

if(NOT WIN32)
target_compile_options(unittests PRIVATE
    --coverage
    -Wall
    -Wextra
    -Wpedantic
    -Wshadow
    -Wnon-virtual-dtor
    -Wctor-dtor-privacy
    -Wold-style-cast
    -Woverloaded-virtual
    -Wnull-dereference
    -Wformat=2
    -Wsign-conversion
    -Wunused-result
    -Wunused-but-set-variable
    -Wunused-function
    -fdiagnostics-show-option
    -Wconversion
    -Wlogical-op
    -Wundef
    -Wredundant-decls
    -Wstrict-overflow=5
    -Wwrite-strings
    -Wpointer-arith
    -Wcast-qual
    -Wcast-align
    -Wcast-align=strict
    -Wswitch-default
    -Wswitch-enum
    -Wdisabled-optimization
    -Wmissing-declarations
    -Wsuggest-override
    -Wsuggest-final-methods
    -Wsuggest-final-types
    -Wcatch-value
    -Wnoexcept
    -Wno-missing-field-initializers
    -Wdouble-promotion
    -Wtrampolines
    -Wzero-as-null-pointer-constant
    -Wuseless-cast
    -Wvector-operation-performance
    -Wshift-overflow=2
    -Wduplicated-cond
    -Wduplicated-branches
)

target_link_options(unittests
    PRIVATE --coverage
)

add_custom_target(coverage
    COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/coverage.sh ${CMAKE_SOURCE_DIR}
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)

add_dependencies(coverage unittests)
endif()
