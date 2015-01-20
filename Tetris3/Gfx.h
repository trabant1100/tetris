#pragma once

#include "Piece.h"

class Gfx
{

public:
	virtual void BeginPaint();
	virtual void EndPaint();
	virtual void DrawRectangle(int x, int y, int width, int height) = 0;
	virtual void DrawPiece(int x, int y, int width, int height, int color) = 0;
	virtual void DrawScore(int x, int y, int score) = 0;
};

