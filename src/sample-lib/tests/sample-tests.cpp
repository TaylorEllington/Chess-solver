#include <gtest/gtest.h>
#include "sample.h"

// Demonstrate some basic assertions.
TEST(HelloTest, BasicAssertions) {
  // Expect two strings not to be equal.
  EXPECT_STRNE("hello", "world");
  // Expect equality.
    EXPECT_EQ(7 * 6, 42);
}

TEST(HelloTest, testAThing) {
    EXPECT_EQ(aThing(4, 3), 4 + 3);
}

TEST(HelloTest, testAMoreComplicatedThing) {
    EXPECT_EQ(aMoreComplicatedThing(6, 7, true), 7);
}