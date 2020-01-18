CC=g++
LFLAGS=-lSDL2
CFLAGS=-std=c++17
EXE=metaballs
all:
	$(CC) *.cpp -o $(EXE) $(LFLAGS) $(CFLAGS)
