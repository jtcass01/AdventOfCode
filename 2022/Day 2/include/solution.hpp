#include <iostream>
#include <fstream>
#include <string>
#include <streambuf>
#include <cassert>
#include <stdio.h>
#include <cstring>

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
    MM_rock = 'X',
    MM_paper = 'Y',
    MM_scissors = 'Z'
};

enum OpMove {
    OM_rock = 'A',
    OM_paper = 'B',
    OM_scissors = 'C'
};

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
