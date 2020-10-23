#ifndef WORD_VALIDATOR_WORD_REPLACER_H
#define WORD_VALIDATOR_WORD_REPLACER_H

#include <string>
#include <string_view>

/**
 * @defgroup WordReplacers Word replacers group
 */

/**
 * @ingroup WordReplacers
 * Interface for replace words.
 */
class WordReplacer {
public:
    /**
     * @param word
     * @return need to replace `word`
     */
    virtual bool need_replace(std::string_view word) = 0;
    /**
     * @param word to replace
     * @return replaced word
     */
    virtual std::string replace_word(std::string_view word) = 0;

    virtual ~WordReplacer() = default;
};

#endif //WORD_VALIDATOR_WORD_REPLACER_H
