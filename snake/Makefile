CC=g++
CFLAGS=-c -Wall -std=c++0x -lglut -lGL -lGLU
SOURCES=main.cpp Snake.cpp
OBJECTS=$(SOURCES:.cpp=.o)
NAME=snake

all: objects install clean

install: $(OBJECTS)
	$(CC) $(OBJECTS) -o $(NAME)

objects: $(SOURCES)
	$(CC) $(CFLAGS) $(SOURCES)

clean:
	rm -rf *.o $(NAME)
