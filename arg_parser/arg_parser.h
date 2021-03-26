#pragma once

#include <map>
#include <stdio.h>
#include <string_view>
#include <vector>
namespace arg_parser {

class ArgParser {
  public:
    ArgParser() = default;
    void parse_args(int argc, const char *argv[]);
    void parse_args(std::vector<std::string_view> argv);
};

} // namespace arg_parser