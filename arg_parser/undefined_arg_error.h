#pragma once
#include <stdexcept>

namespace arg_parser {
class UndefinedArg : public std::invalid_argument {
  public:
    UndefinedArg(const std::string &what) : std::invalid_argument(what) {}
};
} // namespace arg_parser