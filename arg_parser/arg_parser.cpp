#include <arg_parser.h>

#include <details/find.h>
#include <details/split.h>

#include <algorithm>
#include <iostream>
#include <string_view>
#include <vector>

#include <fmt/format.h>

namespace {
std::vector<std::string> to_vector(int argc, const char *argv[]) {
    std::vector<std::string> args;
    for (unsigned int i = 1; i < static_cast<size_t>(argc); i++) {
        args.push_back(argv[i]);
    }
    return args;
}

bool is_value_allowed(const std::string &value,
                      const std::vector<std::string> &allowed_values) {
    return std::size(allowed_values) == 0 ? true : have(allowed_values, value);
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
    Args args;

    for (const auto &def : arg_definitions_) {
        if (def.default_value != "") {
            args[def.name] = def.default_value;
        }
    }

    for (const auto &arg : argv) {
        auto argument_and_value = split(arg, '=');
        auto matching_definition =
            get_matching_definition(argument_and_value[0]);
        if (matching_definition == nullptr) {
            throw UndefinedArg(fmt::format("Argument: {} is not defined", arg));
        }

        if (std::size(argument_and_value) > 1) {
            args[matching_definition->name] = argument_and_value[1];
        } else {
            args[matching_definition->name] = "";
        }

        if (not is_value_allowed(args[matching_definition->name],
                                 matching_definition->allowed_values)) {
            throw ValueError(fmt::format(
                "Argument: {} has incorrect value! Allowed Values are {}", arg,
                fmt::join(matching_definition->allowed_values, ", ")));
        }
    }
    return args;
}

bool ArgParser::argument_is_defined(const std::string_view arg) const {
    for (const auto &definition : arg_definitions_) {
        if (argument_match(definition, arg))
            return true;
    }
    return false;
}

const Argument *
ArgParser::get_matching_definition(const std::string_view arg) const {
    auto found = find_if(arg_definitions_, [&](const Argument &def) {
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