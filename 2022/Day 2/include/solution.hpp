#include <iostream>
#include <fstream>
#include <string>
#include <streambuf>
#include <cassert>
#include <stdio.h>

class RockPaperScissors {
    public:
        RockPaperScissors();

        void addRound(Move myMove, Move opMove);

        int getMyScore();

    private:
        Result decideRound(Move myMove, Move opMove);

        unsigned int myScore_;
        unsigned int opScore_;
};

Move classifyMove(MyMove myMove);

Move classifyMove(OpMove opMove);

int partOne(const std::string fileName);

int partTwo(const std::string fileName);

enum Move {
    rock = 1,
    paper = 2,
    scissors = 3
};

enum Result {
    loss = 0,
    draw = 3,
    win = 6
};

enum MyMove {
    rock = 'X',
    paper = 'Y',
    scissors = 'Z'
};

enum OpMove {
    rock = 'A',
    paper = 'B',
    scissors = 'C'
};
