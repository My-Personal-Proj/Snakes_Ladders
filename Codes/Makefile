PLAYER="player.h"
SNAKE="snake.h"
LADDER="ladder.h"
BOARD="board.h"
TILE="tile.h"
CC=g++


all: Board
Board: run.cpp
	$(CC) $(INCFLAGS) run.cpp $(PLAYER) $(SNAKE) $(LADDER) $(BOARD) $(TILE) -o run
clean:
	rm run
