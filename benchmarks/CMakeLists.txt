project(benchmarks)

function(add_benchmark name)
    set(exe ${ARGN})
    string(CONCAT exe ${CMAKE_CURRENT_SOURCE_DIR} / ${exe})
    add_executable(benchmark_${name} ${exe})
endfunction()

add_benchmark(replace_from_list replace_from_list.cpp)