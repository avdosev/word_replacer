#include "word_replacers/list_replacer.h"
#include "replace_words.h"
#include "check_time.h"

#include <random>
#include <array>
//#include <ranges>

class StringGenerator {
public:
    std::string generate_word(std::uniform_int_distribution<size_t> word_len_distribution) {
        size_t len = word_len_distribution(engine);
        return generate_word(len);
    }

    std::string generate_word(size_t len) {
        std::string word;
        std::uniform_int_distribution<> distrib('a', 'z');
        for (size_t i = 0; i < len; i++)
            word.push_back(char(distrib(engine)));
        return word;
    }

    std::string generate_line(size_t count_words, std::uniform_int_distribution<size_t> word_len_distribution) {
        std::string line;
        line.reserve(count_words * word_len_distribution.max());

        for (size_t i = 0; i < count_words; i++) {
            line.append(generate_word(word_len_distribution));
            if (i != count_words-1) line.push_back(' ');
        }

        return line;
    }

    std::mt19937 engine;

};

struct BenchmarkData {
    size_t words_in_line;
    size_t words_to_replace;
};

auto benchmark(std::uniform_int_distribution<size_t> word_len, BenchmarkData bench_info) {
    StringGenerator string_generator;
    std::vector<std::string> words(bench_info.words_to_replace);
    for (auto& word: words) {
        word = string_generator.generate_word(word_len);
    }

    ReplacerWordToChar replacer(std::move(words), '*');

    std::string line = string_generator.generate_line(bench_info.words_in_line, word_len);

    auto duration = check_time([&]{
        std::string replaced;
        replace_words(line, replaced, replacer);
    });

    return duration;
}

int main() {
    std::uniform_int_distribution<size_t> word_len{5, 10};

    std::vector<BenchmarkData> benchmarks;
    for (size_t in_replace = 1000; in_replace <= 10000000; in_replace *= 10)
        for (size_t in_line = 1000; in_line <= 10000000; in_line *= 10)
            benchmarks.push_back({in_line, in_replace});

    for (auto bench: benchmarks) {
        auto elapsed_time = benchmark(word_len, bench);
        std::cout << "info: " << bench.words_in_line << ";\t" << bench.words_to_replace << "\t" << "time: " << elapsed_time.count() << "s" << std::endl;
    }

}