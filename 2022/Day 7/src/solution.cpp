#include "../include/solution.hpp"

DeviceSystem::DeviceSystem() {
  commandChar = '$';
  homeChar = '/';
  upDirectory = "..";
}

void DeviceSystem::loadTerminalOutput(std::string fileName) {
  std::ifstream File(fileName, std::fstream::in);
  COMMAND command = COMMAND::NONE;
  COMMAND lastCommand = COMMAND::NONE;
  std::unordered_map<std::string, int> files;
  char *pLineChar = nullptr;
  std::string directoryFile = "\0";
  std::string lastDirectory = "\0";
  int directoryFileSize = 0;
  size_t findIndex = 0;

  for(std::string line; std::getline(File, line);) {
    std::cout << "Current Directory:" << lastDirectory << std::endl;
    std::cout << line << std::endl;

    if(isCommand(line)) {
      command = getCommand(line);

      if(command != COMMAND::NONE) {
        std::cout << "Command found: " << commandToString(command) << std::endl;

        lastDirectory.assign(readCommand(lastDirectory, command, line));
      } else {
        std::cout << "No Command found." << std::endl;
        if(!foundInString(line, "dir")) {
          findIndex = line.find_last_of(' ');
          directoryFileSize = std::stoi(line.substr(0, findIndex));
          directoryFile.assign(line.substr(findIndex+1));
          addFile(lastDirectory + directoryFile, directoryFileSize);
        }
      }
    }

  }

  File.close();
}

std::string DeviceSystem::readCommand(std::string lastDirectory, COMMAND command, std::string terminalLine) {
  char *pLineChar = nullptr;
  std::string newDirectory = "/";
  std::string directoryCommand = "\0";
  size_t findIndex = 0;

  switch(command) {
    case COMMAND::CHANGE_DIRECTORY:
      if(foundInString(terminalLine, homeChar)) {
        break;
      } else if (foundInString(terminalLine, upDirectory)) {
        findIndex = lastDirectory.find_last_of(homeChar);

        if(findIndex != 0) {
          newDirectory.assign(lastDirectory.substr(0, findIndex));
        }

        break;
      } else {
        findIndex = terminalLine.find_last_of(' ');
        directoryCommand.assign(terminalLine.substr(findIndex + 1));
        newDirectory.assign(lastDirectory + directoryCommand + "/");
        break;
      }
    case COMMAND::LIST:
      newDirectory.assign(lastDirectory);
      break;
  }

  return newDirectory;
}

int DeviceSystem::calculateSizeOfDirectory(std::string directory) {
  return 0;
}

int DeviceSystem::sumDirectoriesLargerThan100KB() {
  return 0;
}


std::string commandToString(COMMAND command) {
  std::string stringRepresentation = "\0";

  switch(command) {
    case COMMAND::CHANGE_DIRECTORY:
      stringRepresentation.assign("cd");
      break;
    case COMMAND::LIST:
      stringRepresentation.assign("ls");
      break;
    default:
      stringRepresentation.assign("Error parsing command.");
  }

  return stringRepresentation;
}

bool DeviceSystem::isCommand(std::string text) {
  return foundInString(text, commandChar);
}

COMMAND DeviceSystem::getCommand(std::string text) {
  size_t findIndex = 0;
  COMMAND command = COMMAND::NONE;

  for(COMMAND c: {COMMAND::CHANGE_DIRECTORY, COMMAND::LIST}) {
    if(foundInString(text, commandToString(c))) {
      command = c;
      break;
    }
  }

  return command;
}

void DeviceSystem::addFile(std::string fileName, int fileSize) {
  std::cout << "Adding file " << fileName << " with size " << fileSize << std::endl;
  fileSystem.insert(std::make_pair(fileName, fileSize));
}

// Function to print the elements of a vector; Written entirely by ChatGPT.
template <typename T>
void printVector(std::vector<T> vec) {
    std::cout << "Vector: [";
    // Loop through the vector and print each element
    for (int vector_i = 0; vector_i < vec.size(); vector_i++) {
        std::cout << vec[vector_i];

        // Add a comma after each element, except the last one
        if (vector_i != vec.size() - 1) {
            std::cout << ", ";
        }
    }
    std::cout << "]" << std::endl;
}

template <typename T>
bool foundInString(std::string target, T substring) {
  size_t targetIndex = target.find(substring);

  return targetIndex != std::string::npos;
}

int partOne(const std::string fileName) {
  std::cout << "Part 1: " << fileName << std::endl;

  DeviceSystem deviceSystem;
  deviceSystem.loadTerminalOutput(fileName);

  return deviceSystem.sumDirectoriesLargerThan100KB();
}

int partTwo(const std::string fileName) {
  std::cout << "Part 2: " << fileName << std::endl;

  DeviceSystem deviceSystem;
  deviceSystem.loadTerminalOutput(fileName);

  return 0;
}

int main() {
  int examplePartOneResult = partOne("example.txt");
  std::cout << "Part One Example Result: " << examplePartOneResult << std::endl;
  assert(48381165 == examplePartOneResult);

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
