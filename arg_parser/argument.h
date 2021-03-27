#pragma once
#include <string>
#include <vector>

namespace argument_parser {

struct Argument {
    std::string name;
    std::string short_name;
    std::string meta_name;
    std::string description;
    std::vector<std::string> allowed_values;
    std::string default_value;
};

} // namespace argument_parser