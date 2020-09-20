#ifndef WORD_VALIDATOR_CHECK_TIME_H
#define WORD_VALIDATOR_CHECK_TIME_H

#include <chrono>

template <typename Func>
std::chrono::duration<double> check_time(Func&& f) {
    auto start = std::chrono::steady_clock::now();
    f();
    auto stop = std::chrono::steady_clock::now();
    return stop-start;
}

#endif //WORD_VALIDATOR_CHECK_TIME_H
