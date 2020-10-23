#ifndef WORD_VALIDATOR_STRING_HELPER_H
#define WORD_VALIDATOR_STRING_HELPER_H

#include <string_view>
#include <string>

/**
 * Struct for fast string equal checking
 * Support is_transparent for key-value containers
 */
struct string_equal {
    using is_transparent = std::true_type ;

    bool operator()(std::string_view l, std::string_view r) const noexcept {
        return l == r;
    }
};

/**
 * Struct for fast string hashing
 * Support is_transparent for key-value containers
 */
struct string_hash {
    using is_transparent = std::true_type ;

    auto operator()(std::string_view str) const noexcept {
        return std::hash<std::string_view>()(str);
    }
};

#ifdef WITH_MSVC
#define USE_STRING(s) s
#else
#define USE_STRING(s) std::string(s)
#endif

#endif //WORD_VALIDATOR_STRING_HELPER_H
