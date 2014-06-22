
#include "gtest.h"

TEST(NumericPair_evaluation, empty_construction) {
    int a = 1;
    EXPECT_EQ(0, a);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}