#pragma once

#include <map>
#include <stdio.h>
#include <string>
#include <string_view>
#include <vector>

#include <undefined_arg_error.h>
namespace arg_parser {

class ArgParser {
  public:
    using Args = std::map<std::string, std::string>;
    using UndefinedArg = arg_parser::UndefinedArg;

    ArgParser(const std::string &description = std::string());
    Args parse_args(int argc, const char *argv[]);
    Args parse_args(std::vector<std::string_view> argv);
    void print_help() const;

  private:
    bool argument_is_defined(std::string_view arg) const;

    std::string description_;
};

} // namespace arg_parser