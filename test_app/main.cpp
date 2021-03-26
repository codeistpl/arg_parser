#include <arg_parser.h>

using namespace arg_parser;

int main(int argc, char const *argv[]) {
    ArgParser parser;
    parser.parse_args(argc, argv);
    return 0;
}
