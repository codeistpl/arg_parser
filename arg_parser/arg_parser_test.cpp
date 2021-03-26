#include <arg_parser.h>
#include <gtest/gtest.h>

using namespace arg_parser;
class arg_parse_test : public ::testing::Test {
  public:
};

TEST_F(arg_parse_test, parser_prints_help_on_h_passed) {
    const char *argv[1] = {"-h"};
    int argc = 1;
    ArgParser parser("This is description of a program.");
    auto args = parser.parse_args(argc, argv);
    EXPECT_EQ("true", args["-h"]);
}
