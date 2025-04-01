CC = g++

FLAGS = -lc -Wall -g -O0

EXECUTABLE = snake

SOURCES = control/*.cpp \
	  main/main.cpp \
	  model/*.cpp \
	  view/*.cpp \
	  objects/*.cpp

all:
	$(CC) $(FLAGS) $(SOURCES) -o $(EXECUTABLE)

clean:
	$(RM) *.o
	$(RM) $(EXECUTABLE)
