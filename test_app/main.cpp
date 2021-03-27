#include <arg_parser.h>
#include <iostream>

using namespace arg_parser;

int main(int argc, char const *argv[]) {
    ArgParser parser(
        "This is just an example program presenting argument parser working.");
    parser.add_arg(make_flag("--help", "-h", "Prints help page."));
    parser.add_arg(make_flag("--verbose", "-V", "Enables verbose output!"));
    parser.add_arg(
        make_arg("--level", "-l", "Level", "low", {"low", "medium", "high"}));
    auto args = parser.parse_args(argc, argv);

    std::cout << "args and values:" << std::endl;

    for (const auto &pair : args) {
        std::cout << pair.first << "\t" << pair.second << std::endl;
    }
    return 0;
}
