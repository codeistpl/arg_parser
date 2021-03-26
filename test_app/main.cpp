#include <arg_parser.h>
#include <iostream>

using namespace arg_parser;

int main(int argc, char const *argv[]) {
    ArgParser parser(
        "This is just an example program presenting argument parser working.");
    auto args = parser.parse_args(argc, argv);

    for (const auto &pair : args) {
        std::cout << pair.first << "\t" << pair.second << std::endl;
    }
    return 0;
}
