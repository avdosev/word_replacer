#ifndef WORD_VALIDATOR_LIST_REPLACER_H
#define WORD_VALIDATOR_LIST_REPLACER_H

#include "word_replacer.h"

#include <unordered_set>

#include "string_helper.h"

/**
 * @ingroup WordReplacers
 */
class ReplacerWordToChar : public WordReplacer {
public:
    ReplacerWordToChar(std::vector<std::string> words, char ch) :
            words_to_be_replaced(
                    std::make_move_iterator(words.begin()),
                    std::make_move_iterator(words.end())),
            replacement_symbol(ch)
    {
    }

    bool need_replace(std::string_view word) const noexcept override {
        return words_to_be_replaced.find(USE_STRING(word)) != words_to_be_replaced.end();
    }

    std::string replace_word(std::string_view word) const override {
        return std::string(word.size(), replacement_symbol);
    }

private:
    std::unordered_set<std::string, string_hash, string_equal> words_to_be_replaced;
    char replacement_symbol;
};

#endif //WORD_VALIDATOR_LIST_REPLACER_H
