#pragma once

#include <argument.h>
#include <map>
#include <memory>
#include <optional>
#include <stdio.h>
#include <string>
#include <string_view>
#include <vector>

#include <undefined_arg_error.h>
#include <value_error.h>
namespace arg_parser {

class ArgParser {
  public:
    using Args = std::map<std::string, std::string>;
    using UndefinedArg = arg_parser::UndefinedArg;
    using ValueError = arg_parser::ValueError;

    ArgParser(const std::string &description = std::string());
    Args parse_args(int argc, const char *argv[]);
    Args parse_args(std::vector<std::string> argv);
    void print_help() const;
    void add_arg(Argument arg);

  private:
    bool argument_is_defined(std::string_view arg) const;
    const Argument *get_matching_definition(std::string_view arg) const;
    std::string program_name;
    std::vector<Argument> arg_definitions_;
    std::string description_;
};

} // namespace arg_parser