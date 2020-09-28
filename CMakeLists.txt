cmake_minimum_required(VERSION 3.15)
project(word_validator)

set(CMAKE_CXX_STANDARD 20)

option(BUILD_BENCHMARKS "enable build benchmarks" ON)

#include(conanbuildinfo.cmake)
#conan_basic_setup()

include_directories(include)
add_executable(word_validator src/main.cpp)


if(BUILD_BENCHMARKS)
    add_subdirectory(benchmarks ./benchmarks)
endif()