CC = g++
SOURCES = Electre.cpp
CFLAGS = -Wall -g
.PHONY = clean

all: main

main: $(SOURCES:.cpp=.o)

clean: 
	rm ./*.o
