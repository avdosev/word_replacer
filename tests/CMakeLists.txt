project(tests)

include(conanbuildinfo.cmake)
conan_basic_setup()

function(build_test name)
    set(srcs ${ARGN})
    add_executable(${name} ${srcs})
    doctest_discover_tests(${name})
endfunction()

build_test(list_replacer_test list_replacer/list_replacer.cpp)

build_test(dictionary_replacer_test dictionary_replacer/dictionary_replacer.cpp)

build_test(replace_words_test replace_words/replace_words.cpp)
