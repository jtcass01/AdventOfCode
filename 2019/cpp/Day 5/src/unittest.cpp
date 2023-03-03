#include "../include/unittest.hpp"

namespace {

TEST(Day2Test, AddTest) {
    std::vector<signed int> exampleRegisters = {1, 0, 0, 0, 99};
    const std::vector<signed int> expectedResult = {2, 0, 0, 0, 99};

    Computer testComputer(exampleRegisters);
    testComputer.startUp();
    EXPECT_EQ(sameVectors(testComputer.getRegisters(), expectedResult),
              true);
}

TEST(Day2Test, MultiplyTest) {
    std::vector<signed int> exampleRegisters = {2, 3, 0, 3, 99};
    const std::vector<signed int> expectedResult = {2, 3, 0, 6, 99};

    Computer testComputer(exampleRegisters);
    testComputer.startUp();
    EXPECT_EQ(sameVectors(testComputer.getRegisters(), expectedResult),
              true);
}

TEST(Day2Test, StopCode) {
    std::vector<signed int> exampleRegisters = {2, 4, 4, 5, 99, 0};
    const std::vector<signed int> expectedResult = {2, 4, 4, 5, 99, 9801};

    Computer testComputer(exampleRegisters);
    testComputer.startUp();
    EXPECT_EQ(sameVectors(testComputer.getRegisters(), expectedResult),
              true);
}


TEST(Day2Test, StopCode) {
    std::vector<signed int> exampleRegisters = {2, 4, 4, 5, 99, 0};
    const std::vector<signed int> expectedResult = {2, 4, 4, 5, 99, 9801};

    Computer testComputer(exampleRegisters);
    testComputer.startUp();
    EXPECT_EQ(sameVectors(testComputer.getRegisters(), expectedResult),
              true);
}

TEST(Day2Test, LongBoi) {
    std::vector<signed int> exampleRegisters =     {1,  1, 1, 4, 99, 5, 6, 0, 99};
    const std::vector<signed int> expectedResult = {30, 1, 1, 4, 2,  5, 6, 0, 99};

    Computer testComputer(exampleRegisters);
    testComputer.startUp();
    EXPECT_EQ(sameVectors(testComputer.getRegisters(), expectedResult),
              true);
}

TEST(Day2Test, Part1) {
    Computer testComputer("day2Input.txt");

    testComputer.write(1, 12);
    testComputer.write(2, 2);

    EXPECT_EQ(3790689, testComputer.read(0));
}

#if UNUSED_CODE
TEST(Day5Test, Part1Example) {
    std::vector<signed int> exampleRegisters = {1002, 4, 3, 4, 33};
    Computer testComputer(exampleRegisters);
    testComputer.startUp();
    EXPECT_EQ(testComputer.read(4), 99);
}
#endif

}
