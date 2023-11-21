# Compiler
CC = g++

# Compiler flags
CFLAGS = -std=c++11

# Libraries
SFML_LIBS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

# Source files
SRCS = button.cpp game.cpp main.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Target executable
EXEC = main

# Make all target (builds the executable)
all: $(EXEC)

# Linking object files to create the executable
$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(EXEC) $(SFML_LIBS)

# Compile individual source files to object files
%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

# Clean target to remove object files and executable
clean:
	rm -f $(OBJS) $(EXEC)
