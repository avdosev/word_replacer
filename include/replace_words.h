#ifndef WORD_VALIDATOR_REPLACE_WORDS_H
#define WORD_VALIDATOR_REPLACE_WORDS_H

#include <iostream>

#include "word_replacers/word_replacer.h"

bool is_word_symbol(unsigned char ch) {
    return std::isalnum(ch);
}

std::string replace_words(std::string_view line, WordReplacer& word_replacer) {
    std::string result;
    using index_type = decltype(line)::size_type;
    for (index_type i = 0; i != line.size(); i++) {
        if (is_word_symbol(line.at(i))) {
            index_type word_start = i, word_size = 0;
            while (is_word_symbol(line.at(i + word_size))) ++word_size;
            i += word_size;
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

void replace_words_in_stream(std::istream& in, std::ostream& out, WordReplacer& word_replacer) {
    for (std::string line; std::getline(in, line);) {
        out << replace_words(line, word_replacer);
    }
}

#endif //WORD_VALIDATOR_REPLACE_WORDS_H
