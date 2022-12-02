#include "../include/solution.hpp"

RockPaperScissors::RockPaperScissors() {
  myScore_ = 0;
  opScore_ = 0;
}

void RockPaperScissors::addRound(Move myMove, Move opMove) {
  Result roundResult = RockPaperScissors::decideRound(myMove, opMove);
  int movePoints = static_cast<int>(myMove);
  int resultPoints = static_cast<int>(roundResult);

  myScore_ += movePoints + resultPoints;
}

Result RockPaperScissors::decideRound(Move myMove, Move opMove) {
  if(myMove == opMove) {
    return Result::draw;
  }

  if((myMove == Move::rock && opMove == Move::scissors)
  || (myMove == Move::scissors && opMove == Move::paper)
  || (myMove == Move::paper && opMove == Move::rock)) {
    return Result::win;
  }

  return Result::loss;
}

int RockPaperScissors::getMyScore() {
  return myScore_;
}

Move classifyMove(MyMove myMove) {
  Move move;

  switch(myMove) {
    case MyMove::MM_rock:
      move = Move::rock;
      break;
    case MyMove::MM_paper:
      move = Move::paper;
      break;
    case MyMove::MM_scissors:
      move = Move::scissors;
      break;
  }

  return move;
}

Move classifyMove(OpMove opMove) {
  Move move;

  switch(opMove) {
    case OpMove::OM_rock:
      move = Move::rock;
      break;
    case OpMove::OM_paper:
      move = Move::paper;
      break;
    case OpMove::OM_scissors:
      move = Move::scissors;
      break;
  }

  return move;
}

int partOne(const std::string fileName) {
  std::ifstream File(fileName, std::fstream::in);
  RockPaperScissors rpsGame();
  char myMoveChar = '\0';
  char opMoveChar = '\0';
  Move myMove;
  Move opMove;

  for(std::string line; std::getline(File, line);) {
    scanf("%c %c", &opMoveChar, &myMoveChar);
    myMove = classifyMove(static_cast<MyMove>(myMoveChar));
    opMove = classifyMove(static_cast<OpMove>(opMoveChar));
    rpsGame.addRound(myMove, opMove);
  }

  return rpsGame.getMyScore();
}

int partTwo(const std::string fileName) {
  return 0;
}


int main() {
  int examplePartOneResult = partOne("example.txt");
  std::cout << "Part One Example Result: " << examplePartOneResult << std::endl;
  assert(15 == examplePartOneResult);

  int partOneResult = partOne("input.txt");
  std::cout << "Part One Input Result: " << partOneResult << std::endl;
  assert(0 == partOneResult);

  int examplePartTwoResult = partTwo("example.txt");
  std::cout << "Part Two Example Result: " << examplePartTwoResult << std::endl;
  assert(0 == examplePartTwoResult);

  int partTwoResult = partTwo("input.txt");
  std::cout << "Part Two Input Result: " << partTwoResult << std::endl;
  assert(0 == partTwoResult);

  return 0;
}
