#include "yalogc/args.h"

#include <gtest/gtest.h>

#include <string>
#include <string_view>

#define TEST_STRING "Hello world length string"


TEST(args_estimate_size, string) {
    std::string s1{TEST_STRING};
    std::string_view s2{TEST_STRING};

    EXPECT_TRUE(yalog::args::estimate_size(s1) >= s1.size());
    EXPECT_TRUE(yalog::args::estimate_size(s2) >= s2.size());
    EXPECT_TRUE(yalog::args::estimate_size(TEST_STRING) >= sizeof(TEST_STRING));
    EXPECT_TRUE(true);
}

