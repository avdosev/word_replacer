#ifndef WORD_VALIDATOR_REPLACER_BUILDER_H
#define WORD_VALIDATOR_REPLACER_BUILDER_H

#include <vector>
#include <string>
#include <string_view>
#include <optional>

#include "errors.h"

/**
 * Parsed the console arguments
 */
struct ConsoleArgs {
    std::string src;
    std::string dest;
    std::string replace;
    bool use_dict = false;
    bool show_help = false;
    bool check_time = false;
    std::optional<char> replace_symbol = std::nullopt;

    /**
     * @return help string for console
     */
    static std::string_view help() {
        return {""
                "positional arguments:\n"
                "src  - Path to source file\n"
                "dest - Path to destination file\n"
                "required parameters:\n"
                "-r; --replace - Path to file with replacements words\n"
                "optional parameters:\n"
                "-w; --with - Symbol for replace\n"
                "-d; --dict - Use dict replacements word\n"
                "-t; --time - Check time\n"
                "-h; --help - Show help"
        };
    }

    /**
     * Parse console arguments
     * @param args - arguments from console
     * @return parsed arguments
     */
    static ConsoleArgs parse(std::vector<std::string_view> args) {
        ConsoleArgs result;
        size_t max_positional_argument = 2;
        size_t positional_argument = 0;
        for (size_t i = 0; i < args.size(); i++) {
            auto arg = args[i]; bool has_args = i+1 < args.size();
            if (arg == "-h" || arg == "--help") { result.show_help = true; break; }
            else if (arg == "-d" || arg == "--dict") result.use_dict = true;
            else if (arg == "-t" || arg == "--time") result.check_time = true;
            else if (arg == "-r" || arg == "--replace") {
                if (!has_args || args[i+1].starts_with("-")) {
                    throw argument_parse_error("Not found value for [--replace; -r] parameter");
                }

                result.replace = args[++i];
            } else if (arg == "-w" || arg == "--with") {
                if (!has_args || args[i+1].starts_with('-')) {
                    throw argument_parse_error("Not found value for [--with; -w] parameter");
                }

                if (args[i+1].size() > 1) {
                    throw argument_parse_error("Replace symbol can`t have symbols more 1");
                }

                result.replace_symbol = args[++i].front();
            } else if (arg.starts_with('-')) {
                throw argument_parse_error("Found unknown named argument");
            } else {
                constexpr size_t SRC_POSTION = 0;
                constexpr size_t DEST_POSTION = 1;
                switch (positional_argument) {
                    case SRC_POSTION:
                        result.src = arg;
                        break;
                    case DEST_POSTION:
                        result.dest = arg;
                        break;
                    default:
                        throw argument_parse_error("Found positional argument for unknown position");
                }

                positional_argument += 1;
            }
        }
        if (result.use_dict && result.replace_symbol.has_value()) {
            throw argument_parse_error("Use single --dict or --with");
        }
        return result;
    }

    /**
     * Parse console arguments using similar arguments to main
     * @param argc - count args
     * @param argv - string args
     * @return parsed arguments
     */
    static ConsoleArgs parse(int argc, char* argv[]) {
        std::vector<std::string_view> args;
        args.reserve(argc);
        for (int arg = 1; arg < argc; arg++)
            args.emplace_back(argv[arg]);
        return parse(args);
    }
};

#endif //WORD_VALIDATOR_REPLACER_BUILDER_H
