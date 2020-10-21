project(tests)

include(conanbuildinfo.cmake)
conan_basic_setup()

function(build_test name)
    set(srcs ${ARGN})
    add_executable(${name} ${srcs})
endfunction()

build_test(list_replacer_test list_replacer/list_replacer.cpp)
doctest_discover_tests(list_replacer_test)

build_test(dictionary_replacer_test dictionary_replacer/dictionary_replacer.cpp)
doctest_discover_tests(dictionary_replacer_test)
