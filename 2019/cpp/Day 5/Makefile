# compiler
CXX = g++

# compile flags
CXXFLAGS = -Wall -g -std=c++17 -lgtest

GTEST = /usr/local/lib/libgtest.a

# libs
LIBS = include/utils.hpp include/mode.hpp include/opcode.hpp include/instruction.hpp include/computer.hpp include/unittest.hpp include/solution.hpp

# source files
SRCS = src/instruction.cpp src/computer.cpp src/unittest.cpp src/solution.cpp

# object files
OBJS = $(SRCS:.cpp=.o)

# target
TARGET = solution

all: $(TARGET)

# Generates the target executable
$(TARGET):$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)

# Generates the output files
%.o: %.c
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Removes object files and target
clean:
	rm -f $(OBJS) $(TARG) *~
