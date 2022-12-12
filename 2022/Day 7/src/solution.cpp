#include "../include/solution.hpp"

DeviceSystem::DeviceSystem() {
  commandChar_ = '$';
  homeChar_ = '/';
  upDirectory_ = "..";
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
    if(isCommand(line)) {
      command = getCommand(line);

      if(command != COMMAND::NONE) {
        lastDirectory.assign(readCommand(lastDirectory, command, line));
      }
    }  else {
      if(foundInString(line, "dir")) {
      } else {
        findIndex = line.find_last_of(' ');
        directoryFileSize = std::stoi(line.substr(0, findIndex));
        directoryFile.assign(line.substr(findIndex+1));
        directoryFile.assign(lastDirectory + directoryFile);
        addFile(directoryFile, directoryFileSize);
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
      if(foundInString(terminalLine, homeChar_)) {
        break;
      } else if (foundInString(terminalLine, upDirectory_)) {
        findIndex = lastDirectory.substr(0, lastDirectory.size()-1).find_last_of(homeChar_);

        if(findIndex != 0) {
          newDirectory.assign(lastDirectory.substr(0, findIndex + 1));
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

bool DeviceSystem::withinDirectory(std::string directory, std::string filePath) {
  size_t directorySubstringPosition = filePath.find(directory);

  std::cout << "withinDirectory: " << std::endl;
  std::cout << "\t directory: " << directory << std::endl;
  std::cout << "\t filePath: " << filePath << std::endl;
  std::cout << "\t directorySubstringPosition: " << directorySubstringPosition << std::endl;
  std::cout << "\t directory.size(): " << directory.size() << std::endl;

  return directorySubstringPosition+1 == directory.size();
}

std::unordered_map<std::string, int> DeviceSystem::calculateDirectorySizes() {
  std::unordered_map<std::string, int> directorySizes;
  std::string directory;
  std::string filePath;
  int fileSize;

  for (int directoryIndex = 0; directoryIndex < directories_.size(); directoryIndex++) {
    directory = directories_[directoryIndex];

    for (std::unordered_map<std::string, int>::iterator fileIt = files_.begin();
         fileIt != files_.end();
         ++fileIt) {
      filePath = fileIt->first;
      fileSize = fileIt->second;

      if(withinDirectory(directory, filePath)) {
        if(directorySizes.count(directory)) {
          directorySizes[directory] += fileSize;
        } else {
          directorySizes[directory] = fileSize;
        }
      }
    }

    std::cout << " size of directory " << directory << " is " << directorySizes[directory] << std::endl;
  }

  return directorySizes;
}

int DeviceSystem::sumDirectoriesLargerThan100KB() {
  std::unordered_map<std::string, int> directorySizes = calculateDirectorySizes();

  std::cout << "directorySizes:" << std::endl;
  for (std::unordered_map<std::string, int>::iterator it = directorySizes.begin();
       it != directorySizes.end();
       ++it) {
    std::cout << "\t" << it->first << ":" << it->second << std::endl;
  }

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
  return foundInString(text, commandChar_);
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
  files_.insert(std::make_pair(fileName, fileSize));
  std::string directoryName = fileName.substr(0, fileName.find_last_of('/')+1);

  // Add directory to directories vector if it hasn't already been included
  if(!foundInVector(directories_, directoryName)) {
    directories_.push_back(directoryName);
  }
}

void DeviceSystem::printFiles() {
  std::cout << "DeviceSystem printing FileSystem..." << std::endl;

  // Loop through the mapping and print the keys and values
  for (std::unordered_map<std::string, int>::iterator it = files_.begin();
       it != files_.end();
       ++it) {
    std::cout << "\t" << it->first << ":" << it->second << std::endl;
  }

  printVector("directories_", directories_);
}

// Function to print the elements of a vector; Written entirely by ChatGPT.
template <typename T>
void printVector(std::string vectorName, std::vector<T> vec) {
    std::cout << vectorName << ": [";
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
  size_t findIndex = target.find(substring);

  return findIndex != std::string::npos;
}

template <typename T>
bool foundInVector(const std::vector<T> &vector, const T &element) {
  auto findIndex = std::find(vector.begin(), vector.end(), element);

  return findIndex != vector.end();
}

int partOne(const std::string fileName) {
  std::cout << "Part 1: " << fileName << std::endl;

  DeviceSystem deviceSystem;
  deviceSystem.loadTerminalOutput(fileName);
  deviceSystem.printFiles();
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
