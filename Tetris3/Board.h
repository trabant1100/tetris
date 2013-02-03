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
	bool IsPossibleMovement(int xPos, int yPos, Piece *lpPiece);
	bool IsPossibleRotation(int xPos, int yPos, Piece *lpPiece);
	void StorePiece(int xPos, int yPos, Piece *lpPiece);
	bool IsFreeBlock(int xPos, int yPos);
	int GetBlockColor(int xPos, int yPos);
	bool IsBlockInBoard(int xPos, int yPos);

private:
	int blocks[xBlocks][yBlocks];
	void DeleteLine(int line);
	
};

