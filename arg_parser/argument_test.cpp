#include <argument.h>
#include <gtest/gtest.h>

using namespace arg_parser;

Argument get_test_arg() {
    return {.name = "--help",
            .short_name = "-h",
            .description = "Prints Help message.",
            .allowed_values = {},
            .default_value = ""};
}

TEST(argument_parser, test_setting_value) {
    Argument arg = get_test_arg();

    Argument copy;
    copy = arg;
    EXPECT_EQ(arg.name, copy.name);
}

TEST(arg_parser, test_matching_value) {
    Argument arg = get_test_arg();
    EXPECT_TRUE(argument_match(arg, "--help"));
    EXPECT_TRUE(argument_match(arg, "-h"));
    EXPECT_FALSE(argument_match(arg, "--undefined"));
}