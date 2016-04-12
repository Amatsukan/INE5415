# Declaration of variables
CC = ccache g++
CC_FLAGS = -std=c++14
CC_DEBUG = -g3 -O0

# File names
EXEC = Automata
SOURCES = $(wildcard *.cpp)
OBJECTS = $(SOURCES:.cpp=.o)

all:
	make clean
	make os

# Main target
os: $(OBJECTS)
	$(CC) $(OBJECTS) -o $(EXEC)

debug: $(OBJECTS)
	$(CC) $(OBJECTS) $(CC_DEBUG) -o $(EXEC)


# To obtain object files
%.o: %.cpp
	$(CC) -c $(CC_FLAGS) $(CC_DEBUG) $< -o $@

# To remove generated files
clean:
	rm -f $(EXEC) $(OBJECTS)
