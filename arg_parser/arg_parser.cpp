#include <algorithm>
#include <arg_parser.h>
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

void ArgParser::parse_args(int argc, const char *argv[]) {
    parse_args(to_vector(argc, argv));
}

void ArgParser::parse_args(std::vector<std::string_view> argv) {
    if (has(argv, "-h")) {
        std::cout << "help";
    }
}

} // namespace arg_parser