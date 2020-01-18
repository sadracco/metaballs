CC=g++
LFLAGS=-lSDL2
CFLAGS=-std=c++17

EXE=metaballs

SRC=src

all:
	$(CC) $(SRC)/*.cpp -o $(EXE) $(LFLAGS) $(CFLAGS)
