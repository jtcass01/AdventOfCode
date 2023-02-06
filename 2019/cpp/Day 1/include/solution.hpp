#include <iostream>
#include <fstream>
#include <string>
#include <streambuf>
#include <cassert>
#include <stdio.h>
#include <cstring>
#include <vector>

int calculateFuel(int mass);

int calculateMassFuel(std::vector<int> masses);

int calculateTotalFuel(std::vector<int> masses);

int partOne(const std::string fileName);

int partTwo(const std::string fileName);
