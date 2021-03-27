#include <arg_parser.h>
#include <gtest/gtest.h>

using namespace arg_parser;
class arg_parse_test : public ::testing::Test {
  public:
};

TEST_F(arg_parse_test, return_empty_args_if_no_args_defined) {
    const char *argv[] = {""};
    int argc = 0;
    ArgParser parser("This is description of a program.");
    auto args = parser.parse_args(argc, argv);
    EXPECT_EQ(0, std::size(args));
}

TEST_F(arg_parse_test, return_throws_exception_on_undefined_arg) {
    const char *argv[1] = {"-h"};
    int argc = 1;
    ArgParser parser("This is description of a program.");
    EXPECT_THROW(parser.parse_args(argc, argv), UndefinedArg);
}
