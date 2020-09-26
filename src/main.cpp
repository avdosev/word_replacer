#include <memory>
#include <fstream>
#include <filesystem>
#include "replace_words.h"
#include "argument_parser.h"
#include "word_replacers/dictionary_replacer.h"
#include "word_replacers/list_replacer.h"

#include <exception>
#include "check_time.h"

struct file_not_found : std::runtime_error {
    using runtime_error::runtime_error;
};

/**
 * read words from input stream
 * @param in - input stream
 * @return words
 */
std::vector<std::string> read_words(std::istream& in) {
    return std::vector<std::string>{
            std::istream_iterator<std::string>(in),
            std::istream_iterator<std::string>()
    };
}

/**
 * read word pairs from input stream
 * @param in - input stream
 * @return word pairs
 */
std::vector<std::pair<std::string, std::string>> read_word_dictionary(std::istream& in) {
    std::vector<std::pair<std::string, std::string>> word_to_word;
    for (std::string line; std::getline(in, line);) {
        auto delimeter_position = line.find(':');
        if (delimeter_position == std::string::npos)
            throw std::runtime_error("Dictionary parse error");
        auto left = line.substr(0, delimeter_position);
        auto right = line.substr(delimeter_position+1);
        word_to_word.emplace_back(std::move(left), std::move(right));
    }
    return word_to_word;
}

/**
 * Build word replacer by params
 * @param file with words to replacements
 * @param is_dict flag that the file contains a dictionary
 * @param replacement_symbol
 * @return word replacer
 */
std::unique_ptr<WordReplacer> build_replacer_from_stream(std::istream &file, bool is_dict, std::optional<char> replacement_symbol) {
    if (is_dict) {
        auto word_to_word = read_word_dictionary(file);
        return std::make_unique<ReplacerWordToWord>(std::move(word_to_word));
    } else {
        return std::make_unique<ReplacerWordToChar>(
            std::move(read_words(file)),
            replacement_symbol.value_or('*')
        );
    }
}

/**
 * Replace words from `src` to `destination`.
 * Where `dest` is null length output stream is `std::cout`
 * Where flag `use_dict` is `true` words replacements to words from `replace` dictionary.
 *
 * @param src - file path to source
 * @param dest - file path to destination
 * @param replace - file path to words
 * @param replace_symbol - optional char
 * @param use_dict - flag destination is dictionary
 */
void replace_words_from_file(
        const std::string& src,
        const std::string& dest,
        const std::string& replace,
        std::optional<char> replace_symbol,
        bool use_dict
        ) {
    std::ifstream fin(src);

    if (!std::filesystem::exists(replace))
        throw file_not_found("file " + replace + " not exist");

    std::ifstream file(replace);

    if (!file.is_open())
        throw file_not_found("file " + replace + " not open");

    auto replacer = std::move(build_replacer_from_stream(file, use_dict, replace_symbol));

    if (dest.empty()) {
        replace_words_in_stream(fin, std::cout, *replacer);
    } else {
        std::ofstream fout(dest);
        if (!fout.is_open())
            throw file_not_found("file " + dest + "not created");

        replace_words_in_stream(fin, fout, *replacer);
    }
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
        auto elapsed_time = check_time([&]{
            replace_words_from_file(
                    console_args.src,
                    console_args.dest,
                    console_args.replace,
                    console_args.replace_symbol,
                    console_args.use_dict
                    );
        });
        if (console_args.check_time) {
            std::cout << "Elapsed time: " << elapsed_time.count() << "s" << std::endl;
        }
    } catch (const std::runtime_error& err) {
        std::cout << err.what() << std::endl;
        return -1;
    }

    return 0;
}
