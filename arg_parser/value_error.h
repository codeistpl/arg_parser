#pragma once
#include <stdexcept>

namespace arg_parser {
class ValueError : public std::invalid_argument {
  public:
    ValueError(const std::string &what) : std::invalid_argument(what) {}
};
} // namespace arg_parser