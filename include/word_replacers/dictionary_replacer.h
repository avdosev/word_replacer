#ifndef WORD_VALIDATOR_DICTIONARY_REPLACER_H
#define WORD_VALIDATOR_DICTIONARY_REPLACER_H

#include "word_replacer.h"

#include <map>

class ReplacerWordToWord : public WordReplacer {
public:
    ReplacerWordToWord(std::vector<std::pair<std::string, std::string>> word_to_word_pairs) :
        word_replacement_dictionary(
                std::make_move_iterator(word_replacement_dictionary.begin()),
                std::make_move_iterator(word_replacement_dictionary.end()))
    {
    }

    bool need_replace(std::string_view word) override {
        return word_replacement_dictionary.find(word) != word_replacement_dictionary.end();
    }

    std::string replace_word(std::string_view word) override {
        return need_replace(word) ? word_replacement_dictionary.find(word)->second : std::string(word);
    }

private:
    std::map<std::string, std::string, std::less<>> word_replacement_dictionary;
};

#endif //WORD_VALIDATOR_DICTIONARY_REPLACER_H
