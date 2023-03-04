#include "../include/unittest.hpp"

namespace {

/*
 * Day 2 unittests
*/
TEST(Day2Test, AddTest) {
    std::vector<signed int> exampleRegisters = {1, 0, 0, 0, 99};
    const std::vector<signed int> expectedResult = {2, 0, 0, 0, 99};

    Computer testComputer(exampleRegisters, false);
    testComputer.startUp();
    EXPECT_EQ(sameVectors(testComputer.getRegisters(), expectedResult),
              true);
}

TEST(Day2Test, MultiplyTest) {
    std::vector<signed int> exampleRegisters = {2, 3, 0, 3, 99};
    const std::vector<signed int> expectedResult = {2, 3, 0, 6, 99};

    Computer testComputer(exampleRegisters, false);
    testComputer.startUp();
    EXPECT_EQ(sameVectors(testComputer.getRegisters(), expectedResult),
              true);
}

TEST(Day2Test, StopCode) {
    std::vector<signed int> exampleRegisters = {2, 4, 4, 5, 99, 0};
    const std::vector<signed int> expectedResult = {2, 4, 4, 5, 99, 9801};

    Computer testComputer(exampleRegisters, false);
    testComputer.startUp();
    EXPECT_EQ(sameVectors(testComputer.getRegisters(), expectedResult),
              true);
}

TEST(Day2Test, LongBoi) {
    std::vector<signed int> exampleRegisters =     {1,  1, 1, 4, 99, 5, 6, 0, 99};
    const std::vector<signed int> expectedResult = {30, 1, 1, 4, 2,  5, 6, 0, 99};

    Computer testComputer(exampleRegisters, false);
    testComputer.startUp();
    EXPECT_EQ(sameVectors(testComputer.getRegisters(), expectedResult),
              true);
}

TEST(Day2Test, Part1) {
    Computer testComputer("day2Input.txt", false);

    testComputer.write(1, 12);
    testComputer.write(2, 2);

    testComputer.startUp();

    EXPECT_EQ(3790689, testComputer.read(0));
}

/*
 * Day 5 unittests
*/
TEST(Day5Test, ImmediateModeMultiply) {
    std::vector<signed int> exampleRegisters = {1002, 4, 3, 4, 33};
    const std::vector<signed int> expectedResult = {1002, 4, 3, 4, 99};
    Computer testComputer(exampleRegisters, false);
    testComputer.startUp();
    EXPECT_EQ(sameVectors(testComputer.getRegisters(), expectedResult),
              true);
}

TEST(Day5Test, ImmediateModeAdd) {
    std::vector<signed int> exampleRegisters = {1101, 100, -1, 4, 0};
    const std::vector<signed int> expectedResult = {1101, 100, -1, 4, 99};
    Computer testComputer(exampleRegisters, false);
    testComputer.startUp();
    EXPECT_EQ(sameVectors(testComputer.getRegisters(), expectedResult),
              true);
}

}
