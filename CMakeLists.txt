cmake_minimum_required(VERSION 3.15)
project(word_validator)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    # using Visual Studio C++
    add_compile_definitions(WITH_MSVC)
endif()

option(BUILD_BENCHMARKS "enable build benchmarks" ON)
option(BUILD_TESTS "enable build tests" ON)

include_directories(include)
add_executable(word_validator src/main.cpp)

if(BUILD_BENCHMARKS)
    add_subdirectory(benchmarks ./benchmarks)
endif()

if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests ./tests)
endif()