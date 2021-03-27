#include <arg_parser.h>
#include <gtest/gtest.h>

using namespace arg_parser;
class arg_parse_test : public ::testing::Test {
  public:
};

Argument get_test_arg() {
    return {.name = "--help",
            .short_name = "-h",
            .description = "Prints Help message.",
            .allowed_values = {},
            .default_value = ""};
}

TEST_F(arg_parse_test, return_empty_args_if_no_args_defined) {
    const char *argv[] = {"executable_name"};
    int argc = 1;
    ArgParser parser("This is description of a program.");
    auto args = parser.parse_args(argc, argv);
    EXPECT_EQ(0, std::size(args));
}

TEST_F(arg_parse_test, throws_exception_on_undefined_arg) {
    const char *argv[2] = {"executable_name", "-h"};
    int argc = 2;
    ArgParser parser("This is description of a program.");
    EXPECT_THROW(parser.parse_args(argc, argv), UndefinedArg);
}

TEST_F(arg_parse_test, returns_arg_and_none_value_on_flag_argument) {
    const char *argv[2] = {"executable_name", "-h"};
    int argc = 2;
    ArgParser parser("This is description of a program.");
    parser.add_arg(get_test_arg());
    auto args = parser.parse_args(argc, argv);
    EXPECT_TRUE(args["--help"] == "");
}

TEST_F(arg_parse_test, returns_arg_with_default_value_even_if_not_passes) {
    std::vector<std::string> argv{};
    ArgParser parser("");
    auto arg = get_test_arg();
    arg.default_value = "true by default";
    parser.add_arg(arg);
    auto args = parser.parse_args(argv);
    EXPECT_EQ("true by default", args["--help"]);
}

TEST_F(arg_parse_test, returns_argument_with_passed_value) {
    std::vector<std::string> argv{"--help=false"};
    ArgParser parser("");
    auto arg = get_test_arg();
    arg.default_value = "true by default";
    parser.add_arg(arg);
    auto args = parser.parse_args(argv);
    EXPECT_EQ("false", args["--help"]);
}

TEST_F(arg_parse_test, returns_argument_with_override_empty_value) {
    std::vector<std::string> argv{"--help"};
    ArgParser parser("");
    auto arg = get_test_arg();
    arg.default_value = "true by default";
    parser.add_arg(arg);
    auto args = parser.parse_args(argv);
    EXPECT_EQ("", args["--help"]);
}
