#pragma once
#include <string>
#include <vector>

namespace arg_parser {

struct Argument {
    std::string name;
    std::string short_name;
    std::string description;
    std::vector<std::string> allowed_values;
    std::string default_value;
};

inline bool argument_match(const Argument &arg, std::string_view match) {
    return arg.name == match || arg.short_name == match;
}

inline Argument make_arg(const std::string &name,
                         const std::string &short_name = "",
                         const std::string &description = "",
                         const std::string &default_value = "",
                         const std::vector<std::string> &allowed_values = {}) {
    Argument arg{};
    arg.name = name;
    arg.short_name = short_name;
    arg.description = description;
    arg.default_value = default_value;
    arg.allowed_values = allowed_values;

    return arg;
}

inline Argument make_flag(const std::string &name,
                          const std::string &short_name = "",
                          const std::string &description = "") {
    Argument arg{};
    arg.name = name;
    arg.short_name = short_name;
    arg.description = description;

    return arg;
}

} // namespace arg_parser