#include "../include/solution.hpp"

DeviceSystem::DeviceSystem() {
  commandChar_ = '$';
  homeChar_ = '/';
  upDirectory_ = "..";
  totalDiskSpace_ = 70000000;
  requiredUpdateSpace_ = 30000000;

  directories_.push_back("/");
}

void DeviceSystem::loadTerminalOutput(std::string fileName) {
  std::ifstream File(fileName, std::fstream::in);
  COMMAND command = COMMAND::NONE;
  COMMAND lastCommand = COMMAND::NONE;
  std::unordered_map<std::string, int> files;
  char *pLineChar = nullptr;
  std::string directoryFile = "\0";
  std::string lastDirectory = "\0";
  std::string newDirectory = "\0";
  int directoryFileSize = 0;
  size_t findIndex = 0;

  for(std::string line; std::getline(File, line);) {
    if(isCommand(line)) {
      command = getCommand(line);

      switch(command) {
        case COMMAND::CHANGE_DIRECTORY:
          lastDirectory.assign(changeDirectory(lastDirectory, line));
          break;
        default:
          break;
      }
    }  else {
      if(foundInString(line, "dir")) {
        findIndex = line.find_last_of(' ');
        newDirectory.assign(line.substr(findIndex+1));
        addDirectory(lastDirectory + newDirectory + "/");
      } else {
        findIndex = line.find_last_of(' ');
        directoryFileSize = std::stoi(line.substr(0, findIndex));
        directoryFile.assign(line.substr(findIndex+1));
        addFile(lastDirectory + directoryFile, directoryFileSize);
      }
    }
  }

  File.close();
}

std::string DeviceSystem::changeDirectory(std::string lastDirectory, std::string terminalLine) {
  char *pLineChar = nullptr;
  std::string newDirectory = "/";
  size_t findIndex = 0;

  if(foundInString(terminalLine, upDirectory_)) {
    findIndex = lastDirectory.substr(0, lastDirectory.size()-1).find_last_of(homeChar_);
    newDirectory.assign(lastDirectory.substr(0, findIndex + 1));
  } else if (!foundInString(terminalLine, homeChar_)) {
    findIndex = terminalLine.find_last_of(' ');
    newDirectory.assign(lastDirectory + terminalLine.substr(findIndex + 1) + "/");
  }

  return newDirectory;
}

bool DeviceSystem::withinDirectory(std::string directory, std::string filePath) {
  return filePath.find(directory) == 0;
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
         fileIt++) {
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
  }

  return directorySizes;
}

int DeviceSystem::sumDirectoriesSmallerThan100KB() {
  int sum = 0;
  std::unordered_map<std::string, int> directorySizes = calculateDirectorySizes();

  for (std::unordered_map<std::string, int>::iterator it = directorySizes.begin();
       it != directorySizes.end();
       it++) {
    if (it->second <= 100000) {
      sum += it->second;
    }
  }

  return sum;
}

int DeviceSystem::suggestDirectoryToDelete() {
  int minimumDirectoryReductionSize = 0;
  int fileSystemSize = 0;
  int directorySize = 0;
  std::unordered_map<std::string, int> directorySizes = calculateDirectorySizes();
  fileSystemSize = directorySizes["/"];
  minimumDirectoryReductionSize = fileSystemSize;

  if(fileSystemSize > totalDiskSpace_ - requiredUpdateSpace_) {
    for (std::unordered_map<std::string, int>::iterator it = directorySizes.begin();
        it != directorySizes.end();
        it++) {
      directorySize = it->second;

      if((fileSystemSize-directorySize <= requiredUpdateSpace_)
       && minimumDirectoryReductionSize < directorySize) {
        minimumDirectoryReductionSize = directorySize;
      }
    }
  }

  return minimumDirectoryReductionSize;
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
}

void DeviceSystem::addDirectory(std::string directoryName) {
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
  return deviceSystem.sumDirectoriesSmallerThan100KB();
}

int partTwo(const std::string fileName) {
  std::cout << "Part 2: " << fileName << std::endl;

  DeviceSystem deviceSystem;
  deviceSystem.loadTerminalOutput(fileName);
  return deviceSystem.suggestDirectoryToDelete();
}

int main() {
  int examplePartOneResult = partOne("example.txt");
  std::cout << "Part One Example Result: " << examplePartOneResult << std::endl;
  assert(95437 == examplePartOneResult);

  int example0PartOneResult = partOne("example0.txt");
  std::cout << "Part One Example Result: " << example0PartOneResult << std::endl;
  assert(99999 == example0PartOneResult);

  int example1PartOneResult = partOne("example1.txt");
  std::cout << "Part One Example Result: " << example1PartOneResult << std::endl;
  assert(5 == example1PartOneResult);

  int example2PartOneResult = partOne("example2.txt");
  std::cout << "Part One Example Result: " << example2PartOneResult << std::endl;
  assert(7 == example2PartOneResult);

  int partOneResult = partOne("input.txt");
  std::cout << "Part One Input Result: " << partOneResult << std::endl;
  assert(1432936 == partOneResult);

  int examplePartTwoResult = partTwo("example.txt");
  std::cout << "Part Two Example Result: " << examplePartTwoResult << std::endl;
  assert(24933642 == examplePartTwoResult);

  int partTwoResult = partTwo("input.txt");
  std::cout << "Part Two Input Result: " << partTwoResult << std::endl;
  assert(0 == partTwoResult);

  return 0;
}
