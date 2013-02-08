#pragma once

#include "Board.h"
#include "Gfx.h"

#define PIXEL_SIZE 20

enum GameMove { LEFT, RIGHT, DOWN, ROTATE };

class Game
{
public:
	Game(Gfx *lpGfx, Board *lpBoard);
	~Game();
	void Step();
	void DrawScene();
	void Move(GameMove move);
	void EndGame();

private:
	int xPos, yPos;
	int xNextPos, yNextPos;
	int deletedLines;
	Board *lpBoard; 
	Piece *lpPiece;
	Piece *lpNextPiece;
	Gfx *lpGfx;

	void CreateNewPiece(Piece *&lpNewPiece);
	void CreateNewPiecePosition(Piece *lpPiece, int *xPos, int *yPos, bool bRandomize);
	void DrawPiece(int xPos, int yPos, Piece *lpPiece);
	void DrawNextPiece(int xPos, int yPos, Piece *lpNextPiece);
	void DrawBoard();
	void DrawScore();
};

