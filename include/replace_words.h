#ifndef WORD_VALIDATOR_REPLACE_WORDS_H
#define WORD_VALIDATOR_REPLACE_WORDS_H

#include <iostream>

#include "word_replacers/word_replacer.h"

/**
 * @param ch - character for checking
 * @return flag
 */
bool is_word_symbol(char ch) {
    return std::isalnum(ch);
}

/**
 * Replace words in line
 * @param line
 * @param word_replacer
 * @return new line with replacement words
 */
std::string replace_words(std::string_view line, WordReplacer& word_replacer) {
    std::string result;
    using index_type = decltype(line)::size_type;
    for (index_type i = 0; i < line.size(); i++) {
        if (is_word_symbol(line.at(i))) {
            index_type word_start = i, word_size = 0;
            while (i+word_size < line.size() && is_word_symbol(line.at(i + word_size))) ++word_size;
            i += word_size-1;
            auto word = line.substr(word_start, word_size);
            if (word_replacer.need_replace(word))
                result.append(word_replacer.replace_word(word));
            else
                result.append(word);
        } else {
            result.push_back(line[i]);
        }
    }
    return result;
}

/**
 * Read line from `in`. Replace words in line. Write line in `out`.
 * @param in - input stream
 * @param out - output stream
 * @param word_replacer
 */
void replace_words_in_stream(std::istream& in, std::ostream& out, WordReplacer& word_replacer) {
    for (std::string line; std::getline(in, line);) {
        out << replace_words(line, word_replacer) << std::endl;
    }
}

#endif //WORD_VALIDATOR_REPLACE_WORDS_H
