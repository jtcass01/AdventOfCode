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

TEST(Day5Test, Part1) {
    std::stringstream exampleInput("1\n");
    std::streambuf *oldCinBuffer = std::cin.rdbuf(exampleInput.rdbuf());

    Computer testComputer("input.txt", false);
    testComputer.startUp();

    std::cin.rdbuf(oldCinBuffer);

    EXPECT_EQ(16225258, testComputer.getLastOutput());
}

TEST(Day5Test, EqualPositionTrue) {
    std::vector<signed int> exampleRegisters = {3, 9, 8, 9, 10, 9, 4, 9, 99, -1, 8};
    std::stringstream exampleInput("8\n");

    std::streambuf *oldCinBuffer = std::cin.rdbuf(exampleInput.rdbuf());

    Computer testComputer(exampleRegisters, false);
    testComputer.startUp();

    std::cin.rdbuf(oldCinBuffer);

    EXPECT_EQ(1, testComputer.getLastOutput());
}

TEST(Day5Test, EqualPositionFalse) {
    std::vector<signed int> exampleRegisters = {3, 9, 8, 9, 10, 9, 4, 9, 99, -1, 8};
    std::stringstream exampleInput("1\n");

    std::streambuf *oldCinBuffer = std::cin.rdbuf(exampleInput.rdbuf());

    Computer testComputer(exampleRegisters, false);
    testComputer.startUp();

    std::cin.rdbuf(oldCinBuffer);

    EXPECT_EQ(0, testComputer.getLastOutput());
}

TEST(Day5Test, LessThanPositionTrue) {
    std::vector<signed int> exampleRegisters = {3, 9, 7, 9, 10, 9, 4, 9, 99, -1, 8};
    std::stringstream exampleInput("1\n");

    std::streambuf *oldCinBuffer = std::cin.rdbuf(exampleInput.rdbuf());

    Computer testComputer(exampleRegisters, false);
    testComputer.startUp();

    std::cin.rdbuf(oldCinBuffer);

    EXPECT_EQ(1, testComputer.getLastOutput());
}

TEST(Day5Test, LessThanPositionFalse) {
    std::vector<signed int> exampleRegisters = {3, 9, 7, 9, 10, 9, 4, 9, 99, -1, 8};
    std::stringstream exampleInput("9\n");

    std::streambuf *oldCinBuffer = std::cin.rdbuf(exampleInput.rdbuf());

    Computer testComputer(exampleRegisters, false);
    testComputer.startUp();

    std::cin.rdbuf(oldCinBuffer);

    EXPECT_EQ(0, testComputer.getLastOutput());
}

TEST(Day5Test, EqualImmediateTrue) {
    std::vector<signed int> exampleRegisters = {3, 3, 1108, -1, 8, 3, 4, 3, 99};
    std::stringstream exampleInput("8\n");

    std::streambuf *oldCinBuffer = std::cin.rdbuf(exampleInput.rdbuf());

    Computer testComputer(exampleRegisters, false);
    testComputer.startUp();

    std::cin.rdbuf(oldCinBuffer);

    EXPECT_EQ(1, testComputer.getLastOutput());
}

TEST(Day5Test, EqualImmediateFalse) {
    std::vector<signed int> exampleRegisters = {3, 3, 1108, -1, 8, 3, 4, 3, 99};
    std::stringstream exampleInput("1\n");

    std::streambuf *oldCinBuffer = std::cin.rdbuf(exampleInput.rdbuf());

    Computer testComputer(exampleRegisters, false);
    testComputer.startUp();

    std::cin.rdbuf(oldCinBuffer);

    EXPECT_EQ(0, testComputer.getLastOutput());
}

TEST(Day5Test, LessThanImmediateTrue) {
    std::vector<signed int> exampleRegisters = {3, 3, 1107, -1, 8, 3, 4, 3, 99};
    std::stringstream exampleInput("1\n");

    std::streambuf *oldCinBuffer = std::cin.rdbuf(exampleInput.rdbuf());

    Computer testComputer(exampleRegisters, false);
    testComputer.startUp();

    std::cin.rdbuf(oldCinBuffer);

    EXPECT_EQ(1, testComputer.getLastOutput());
}

TEST(Day5Test, LessThanImmediateFalse) {
    std::vector<signed int> exampleRegisters = {3, 3, 1107, -1, 8, 3, 4, 3, 99};
    std::stringstream exampleInput("9\n");

    std::streambuf *oldCinBuffer = std::cin.rdbuf(exampleInput.rdbuf());

    Computer testComputer(exampleRegisters, false);
    testComputer.startUp();

    std::cin.rdbuf(oldCinBuffer);

    EXPECT_EQ(0, testComputer.getLastOutput());
}

TEST(Day5Test, JumpPositionModeTrue) {
    std::vector<signed int> exampleRegisters = {3, 12, 6, 12, 15, 1, 13, 14, 13, 4, 13, 99, -1, 0, 1, 9};
    std::stringstream exampleInput("3\n");

    std::streambuf *oldCinBuffer = std::cin.rdbuf(exampleInput.rdbuf());

    Computer testComputer(exampleRegisters, false);
    testComputer.startUp();

    std::cin.rdbuf(oldCinBuffer);

    EXPECT_EQ(1, testComputer.getLastOutput());
}

TEST(Day5Test, JumpPositionModeFalse) {
    std::vector<signed int> exampleRegisters = {3, 12, 6, 12, 15, 1, 13, 14, 13, 4, 13, 99, -1, 0, 1, 9};
    std::stringstream exampleInput("0\n");

    std::streambuf *oldCinBuffer = std::cin.rdbuf(exampleInput.rdbuf());

    Computer testComputer(exampleRegisters, false);
    testComputer.startUp();

    std::cin.rdbuf(oldCinBuffer);

    EXPECT_EQ(0, testComputer.getLastOutput());
}

TEST(Day5Test, JumpImmediateModeTrue) {
    std::vector<signed int> exampleRegisters = {3, 3, 1105, -1, 9, 1101, 0, 0, 12, 4, 12, 99, 1};
    std::stringstream exampleInput("3\n");

    std::streambuf *oldCinBuffer = std::cin.rdbuf(exampleInput.rdbuf());

    Computer testComputer(exampleRegisters, false);
    testComputer.startUp();

    std::cin.rdbuf(oldCinBuffer);

    EXPECT_EQ(1, testComputer.getLastOutput());
}

TEST(Day5Test, JumpImmediateModeFalse) {
    std::vector<signed int> exampleRegisters = {3, 3, 1105, -1, 9, 1101, 0, 0, 12, 4, 12, 99, 1};
    std::stringstream exampleInput("0\n");

    std::streambuf *oldCinBuffer = std::cin.rdbuf(exampleInput.rdbuf());

    Computer testComputer(exampleRegisters, false);
    testComputer.startUp();

    std::cin.rdbuf(oldCinBuffer);

    EXPECT_EQ(0, testComputer.getLastOutput());
}


}
