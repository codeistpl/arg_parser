#include <algorithm>
#include <arg_parser.h>
#include <fmt/format.h>
#include <iostream>
#include <string_view>
#include <vector>

namespace {
std::vector<std::string> to_vector(int argc, const char *argv[]) {
    std::vector<std::string> args;
    for (unsigned int i = 1; i < static_cast<size_t>(argc); i++) {
        args.push_back(argv[i]);
    }
    return args;
}

bool has(const std::vector<std::string> &argv, std::string_view val) {
    auto found = std::find(std::begin(argv), std::end(argv), val);
    return found != std::end(argv);
}

} // namespace
namespace arg_parser {

ArgParser::ArgParser(const std::string &description)
    : description_(description) {}

ArgParser::Args ArgParser::parse_args(int argc, const char *argv[]) {
    program_name = argv[0];
    auto args = to_vector(argc, argv);
    return parse_args(args);
}

ArgParser::Args ArgParser::parse_args(std::vector<std::string> argv) {
    if (has(argv, "-h")) {
        print_help();
    }
    Args args;
    for (const auto &arg : argv) {
        auto matching_definition = get_matching_definition(arg);
        if (matching_definition == nullptr) {
            throw UndefinedArg(fmt::format("Argument: {} is not defined", arg));
        }
        args[matching_definition->name] = "true";
    }

    return args;
}

bool ArgParser::argument_is_defined(std::string_view arg) const {
    for (const auto &definition : arg_definitions_) {
        if (argument_match(definition, arg))
            return true;
    }
    return false;
}

const Argument *ArgParser::get_matching_definition(std::string_view arg) const {
    auto found =
        std::find_if(std::cbegin(arg_definitions_), std::cend(arg_definitions_),
                     [&](const Argument &def) {
                         return def.name == arg || def.short_name == arg;
                     });
    if (found != arg_definitions_.end())
        return &*found;
    return nullptr;
}

void ArgParser::add_arg(Argument arg) { arg_definitions_.push_back(arg); }

void ArgParser::print_help() const {
    std::cout << description_ << std::endl;
    std::cout << fmt::format("usage: {} ", program_name, "args");
    for (const auto &arg : arg_definitions_) {
        std::cout << " " << arg.name;
    }
    std::cout << std::endl;
}

} // namespace arg_parser