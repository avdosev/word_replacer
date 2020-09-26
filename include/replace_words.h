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
 * @param[out] result - new line with replacement words
 * @param word_replacer
 */
void replace_words(std::string_view line, std::string& result, WordReplacer& word_replacer) {
    result.erase();
    using index_type = decltype(line)::size_type;
    for (index_type i = 0; i < line.size(); i++) {
        if (is_word_symbol(line[i])) {
            index_type word_start = i, word_end;
            for (word_end = i; word_end < line.size() && is_word_symbol(line[word_end]); ++word_end);
            auto word_size = word_end - word_start;
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
}

/**
 * Read line from `in`. Replace words in line. Write line in `out`.
 * @param in - input stream
 * @param out - output stream
 * @param word_replacer
 */
void replace_words_in_stream(std::istream& in, std::ostream& out, WordReplacer& word_replacer) {
    for (std::string line, replaced_line; std::getline(in, line);) {
        replace_words(line, replaced_line, word_replacer);
        replaced_line.push_back('\n'); // std::endl - slow
        out << replaced_line;
    }
}

#endif //WORD_VALIDATOR_REPLACE_WORDS_H
