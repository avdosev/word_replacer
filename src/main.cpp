#include <memory>
#include <fstream>
#include <filesystem>
#include "replace_words.h"
#include "argument_parser.h"
#include "word_replacers/dictionary_replacer.h"
#include "word_replacers/list_replacer.h"

#include <exception>

struct file_not_found : std::runtime_error {
    using runtime_error::runtime_error;
};

std::vector<std::string> read_words(std::istream& in) {
    return std::vector<std::string>{
            std::istream_iterator<std::string>(in),
            std::istream_iterator<std::string>()
    };
}

std::vector<std::pair<std::string, std::string>> read_word_dictionary(std::istream& in) {
    std::vector<std::pair<std::string, std::string>> word_to_word;
    while (!in.eof()) {
        std::string left, right;
        in >> left >> right;
        word_to_word.emplace_back(left, right);
    }
    return word_to_word;
}

std::unique_ptr<WordReplacer> build_replacer(std::istream &file, bool is_dict, char replacement_symbol) {
    if (is_dict) {
        auto word_to_word = read_word_dictionary(file);
        return std::make_unique<ReplacerWordToWord>(std::move(word_to_word));
    } else {
        return std::make_unique<ReplacerWordToChar>(
            std::move(read_words(file)),
            replacement_symbol
        );
    }
}

void replace_words_from_file(ConsoleArgs console_args) {
    std::ifstream fin(console_args.src);

    if (!std::filesystem::exists(console_args.replace))
        throw file_not_found("file " + console_args.replace + " not exist");

    std::ifstream file(console_args.replace);

    if (!file.is_open())
        throw file_not_found("file " + console_args.replace + " not open");

    auto symbol = console_args.replace_symbol;
    auto replacer = std::move(build_replacer(file, false, symbol.has_value() ? symbol.value() : '*'));
    replace_words_in_stream(fin, std::cout, *replacer);
}

int main(int argc, char* argv[]) {
    ConsoleArgs console_args;
    try {
        console_args = ConsoleArgs::parse(argc, argv);
    } catch (const std::runtime_error& err) {
        std::cout << err.what() << std::endl;
        std::cout << ConsoleArgs::help();
        return 1;
    }

    if (console_args.show_help) {
        std::cout << ConsoleArgs::help();
        return 0;
    }

    try {
        replace_words_from_file(console_args);
    } catch (const std::runtime_error& err) {
        std::cout << err.what() << std::endl;
        return 1;
    }

    return 0;
}
