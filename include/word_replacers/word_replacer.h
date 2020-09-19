#ifndef WORD_VALIDATOR_WORD_REPLACER_H
#define WORD_VALIDATOR_WORD_REPLACER_H

#include <string>
#include <string_view>

class WordReplacer {
public:
    virtual bool need_replace(std::string_view word) = 0;
    virtual std::string replace_word(std::string_view word) = 0;
};

#endif //WORD_VALIDATOR_WORD_REPLACER_H
