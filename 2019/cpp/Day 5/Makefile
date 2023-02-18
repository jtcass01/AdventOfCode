# compiler
CC = g++

# compile flags
CFLAGS = -wall -g

# libs
LIBS = include/utils.hpp include/mode.hpp include/opcode.hpp include/instruction.hpp include/computer.hpp include/solution.hpp

# source files
SRCS = src/instruction.cpp src/computer.cpp src/solution.cpp

# object files
OBJS = $(SRCS:.cpp=.o)

# target
TARGET = solution

all: $(TARGET)

# Generates the target executable
$(TARGET):$(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(LIBS)

# Generates the output files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Removes object files and target
clean:
	rm -f $(OBJS) $(TARG) *~
