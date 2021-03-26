#pragma once

#include <stdio.h>

namespace arg_parser {

class ArgParser {
  public:
    ArgParser() = default;
    void parse_args(int argc, const char *argv[]) {
        for (int i = 0; i < argc; i++) {
            printf("%s ", argv[i]);
        }
    }
};

} // namespace arg_parser