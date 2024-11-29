#include <gtest/gtest.h>
#include "utils.h"

TEST(PurpleUtilTest, Add_1) {
    EXPECT_EQ(purple::add(1, 2), 3);
    EXPECT_EQ(purple::add(5, 7), 12);
}

TEST(PurpleUtilTest, Add_2) {
    EXPECT_EQ(purple::add(1, 2), 3);
    EXPECT_EQ(purple::add(5, 7), 12);
}

