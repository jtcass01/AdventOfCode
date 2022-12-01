# compiler
CC = g++

# compile flags
CFLAGS = -wall -g

# libs
LIBS = solution.hpp

# source files
SRCS = solution.cpp

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
