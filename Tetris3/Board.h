#pragma once

#include "Piece.h"

#define BLOCK_FREE 0
#define BLOCK_FILLED 1

class Board
{
public:
	static const unsigned int xBlocks = 10, yBlocks = 20;
	Board();
	~Board();
	void DeletePossibleLines();
	bool IsPosibleMovement(int xPos, int yPos, Piece *lpPiece);

private:
	int blocks[xBlocks][yBlocks];
	void DeleteLine(int line);
};

