# compiler
CC = g++

# compile flags
CFLAGS = -wall -g

# libs
LIBS = include/solution.hpp

# source files
SRCS = src/solution.cpp

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
