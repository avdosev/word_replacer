#ifndef WORD_VALIDATOR_STRING_HELPER_H
#define WORD_VALIDATOR_STRING_HELPER_H

#include <string_view>
#include <string>

struct string_equal {
    using is_transparent = std::true_type ;

    bool operator()(std::string_view l, std::string_view r) const noexcept
    {
        return l == r;
    }
};


struct string_hash {
    using is_transparent = std::true_type ;

    auto operator()(std::string_view str) const noexcept {
        return std::hash<std::string_view>()(str);
    }

    auto operator()(const std::string& str) const noexcept {
        return std::hash<std::string>()(str);
    }
};

#endif //WORD_VALIDATOR_STRING_HELPER_H
