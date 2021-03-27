#include <algorithm>
#include <arg_parser.h>
#include <fmt/format.h>
#include <iostream>
#include <string_view>
#include <vector>

namespace {
std::vector<std::string_view> to_vector(int argc, const char *argv[]) {
    std::vector<std::string_view> args(static_cast<size_t>(argc));
    for (unsigned int i = 0; i < static_cast<size_t>(argc); i++) {
        args[i] = std::string_view(argv[i]);
    }
    return args;
}

bool has(const std::vector<std::string_view> &argv, std::string_view val) {
    auto found = std::find(std::begin(argv), std::end(argv), val);
    return found != std::end(argv);
}

} // namespace
namespace arg_parser {

ArgParser::ArgParser(const std::string &description)
    : description_(description) {}

ArgParser::Args ArgParser::parse_args(int argc, const char *argv[]) {
    return parse_args(to_vector(argc, argv));
}

ArgParser::Args ArgParser::parse_args(std::vector<std::string_view> argv) {
    if (has(argv, "-h")) {
        print_help();
    }

    for (const auto &arg : argv) {
        if (!argument_is_defined(arg)) {
            throw UndefinedArg(fmt::format("Argument: {} is not defined", arg));
        }
    }

    Args args;
    return args;
}

bool ArgParser::argument_is_defined(std::string_view arg) const {
    (void)arg;
    return false;
}

void ArgParser::print_help() const { std::cout << description_ << std::endl; }

} // namespace arg_parser