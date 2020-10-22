#ifndef WORD_VALIDATOR_DICTIONARY_REPLACER_H
#define WORD_VALIDATOR_DICTIONARY_REPLACER_H

#include "word_replacer.h"
#include "string_helper.h"

#include <unordered_map>
#include <vector>

/**
 * @ingroup WordReplacers
 */
class ReplacerWordToWord : public WordReplacer {
public:
    explicit ReplacerWordToWord(std::vector<std::pair<std::string, std::string>> word_to_word_pairs) :
        word_replacement_dictionary(
                std::make_move_iterator(word_to_word_pairs.begin()),
                std::make_move_iterator(word_to_word_pairs.end()))
    {
    }

    bool need_replace(std::string_view word) noexcept override {
        return word_replacement_dictionary.find(USE_STRING(word)) != word_replacement_dictionary.end();
    }

    std::string replace_word(std::string_view word) override {
        if (auto word_it = word_replacement_dictionary.find(USE_STRING(word));
            word_it != word_replacement_dictionary.end()) {
            return word_it->second;
        } else {
            return std::string(word);
        }
    }

private:
    std::unordered_map<std::string, std::string, string_hash, string_equal> word_replacement_dictionary;
};

#endif //WORD_VALIDATOR_DICTIONARY_REPLACER_H
