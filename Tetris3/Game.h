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

private:

	unsigned int xPos, yPos;
	Board *lpBoard; 
	Piece *lpPiece;
	Gfx *lpGfx;

	void CreateNewPiece();
	void DrawPiece(int xPos, int yPos, Piece *lpPiece);
	void DrawBoard();
};

