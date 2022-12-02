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

void RockPaperScissors::addRound(GoalResult goal, Move opMove) {
  Result roundResult = RockPaperScissors::classifyGoal(goal);
  Move myMove = RockPaperScissors::findMove(goal, opMove);
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

static Move RockPaperScissors::classifyMove(MyMove myMove) {
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

static Move RockPaperScissors::classifyMove(OpMove opMove) {
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

static Result RockPaperScissors::classifyGoal(GoalResult goal) {
  Result result;

  switch(goal) {
    case GoalResult::G_loss:
      result = Result::loss;
      break;
    case GoalResult::G_draw:
      result = Result::draw;
      break;
    case GoalResult::G_win:
      result = Result::win;
      break;
  }

  return result;
}

static Move RockPaperScissors::findMove(GoalResult goal, Move opMove) {
  Move myMove;

  switch(goal) {
    case GoalResult::G_draw:
      myMove = opMove;
      break;
    case GoalResult::G_loss:
      switch(opMove) {
        case Move::paper:
          myMove = Move::rock;
          break;
        case Move::rock:
          myMove = Move::scissors;
          break;
        case Move::scissors:
          myMove = Move::paper;
          break;
      }
      break;
    case GoalResult::G_win:
      switch(opMove) {
        case Move::paper:
          myMove = Move::scissors;
          break;
        case Move::rock:
          myMove = Move::paper;
          break;
        case Move::scissors:
          myMove = Move::rock;
          break;
      }
      break;
  }

  return myMove;
}

int partOne(const std::string fileName) {
  std::ifstream File(fileName, std::fstream::in);
  char *pLineChar = nullptr;
  RockPaperScissors rpsGame;
  char myMoveChar = '\0';
  char opMoveChar = '\0';
  Move myMove;
  Move opMove;

  for(std::string line; std::getline(File, line);) {
    pLineChar = strcpy(new char[line.length() + 1], line.c_str());
    sscanf(pLineChar, "%c %c", &opMoveChar, &myMoveChar);
    myMove = RockPaperScissors::classifyMove(static_cast<MyMove>(myMoveChar));
    opMove = RockPaperScissors::classifyMove(static_cast<OpMove>(opMoveChar));
    rpsGame.addRound(myMove, opMove);
  }

  File.close();

  return rpsGame.getMyScore();
}

int partTwo(const std::string fileName) {
  std::ifstream File(fileName, std::fstream::in);
  char *pLineChar = nullptr;
  RockPaperScissors rpsGame;
  char goalChar = '\0';
  char opMoveChar = '\0';
  Move opMove;

  for(std::string line; std::getline(File, line);) {
    pLineChar = strcpy(new char[line.length() + 1], line.c_str());
    sscanf(pLineChar, "%c %c", &opMoveChar, &goalChar);
    opMove = RockPaperScissors::classifyMove(static_cast<OpMove>(opMoveChar));
    rpsGame.addRound(static_cast<GoalResult>(goalChar), opMove);
  }

  File.close();

  return rpsGame.getMyScore();
}


int main() {
  int examplePartOneResult = partOne("example.txt");
  std::cout << "Part One Example Result: " << examplePartOneResult << std::endl;
  assert(15 == examplePartOneResult);

  int partOneResult = partOne("input.txt");
  std::cout << "Part One Input Result: " << partOneResult << std::endl;
  assert(12586 == partOneResult);

  int examplePartTwoResult = partTwo("example.txt");
  std::cout << "Part Two Example Result: " << examplePartTwoResult << std::endl;
  assert(12 == examplePartTwoResult);

  int partTwoResult = partTwo("input.txt");
  std::cout << "Part Two Input Result: " << partTwoResult << std::endl;
  assert(13193 == partTwoResult);

  return 0;
}
