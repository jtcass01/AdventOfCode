#include "../include/unittest.hpp"

namespace {

TEST(ComputerTest, HelloWorld) {
    bool test = true;

    EXPECT_EQ(true, test) << " Hello world. ";
}

}
