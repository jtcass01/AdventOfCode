#include "../include/solution.hpp"

std::string loadFile(std::string fileName) {
    std::ifstream File(fileName, std::fstream::in);
    std::string str;

    // Alocate memory for file.
    File.seekg(0, std::ios::end);
    str.reserve(File.tellg());
    File.seekg(0, std::ios::beg);

    // Store file data inside str
    str.assign((std::istreambuf_iterator<char>(File)),
                std::istreambuf_iterator<char>());

    return str;
}

int main() {
  std::cout << "example.txt:" << std::endl << loadFile("example.txt") << std::endl;
  std::cout << "input.txt:" << std::endl << loadFile("input.txt") << std::endl;
  return 0;
}
