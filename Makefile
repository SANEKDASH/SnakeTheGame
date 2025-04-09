CC = g++

FLAGS = -lc -Wall -g -O0

SFML_FLAGS =  -lsfml-graphics -lsfml-window -lsfml-system

EXECUTABLE = snake

SOURCES = control/*.cpp \
	  main/main.cpp \
	  model/*.cpp \
	  view/*.cpp \
	  objects/*.cpp

all:
	$(CC) $(SOURCES) $(FLAGS) -o $(EXECUTABLE) $(SFML_FLAGS)

clean:
	$(RM) *.o
	$(RM) $(EXECUTABLE)
