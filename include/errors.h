#ifndef WORD_VALIDATOR_ERRORS_H
#define WORD_VALIDATOR_ERRORS_H

#include <stdexcept>

/**
 * @defgroup Errors Errors group
 */

/// @ingroup Errors
struct file_not_found : std::runtime_error {
    using runtime_error::runtime_error;
};

#endif //WORD_VALIDATOR_ERRORS_H
