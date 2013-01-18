#pragma once

#include "Pieces.h"

#define BOARD_LINE_WIDTH 6
#define BLOCK_SIZE 18	
#define BOARD_POSITION 320
#define BOARD_WIDTH 10
#define BOARD_HEIGHT 20
#define MIN_VERTICAL_MARGIN 20
#define MIN_HORIZONTAL_MARGIN 20
#define PIECE_BLOCKS 5

class Board
{
public:
	Board(Pieces *pPieces, int pScreenHeight);
	~Board(void);
	void StorePiece(int pX, int pY, int pPiece, int pRotation);
	bool IsGameOver();
	void DeletePossibleLines();
	bool IsFreeBlock(int pX, int pY);
	int GetXPosInPixels(int pX);
	int GetYPosInPixels(int pY);
	bool IsPossibleMovement(int pX, int pY, int pPiece, int pRotation);

private:
	enum { POS_FREE, POS_FILLED };
	int mBoard[BOARD_WIDTH][BOARD_HEIGHT];
	Pieces *mPieces;
	int mScreenHeight;

	void InitBoard();
	void DeleteLine(int pY);
};

