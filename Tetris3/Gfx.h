#pragma once

#include "Piece.h"

#include <Windows.h>

class Gfx
{
protected:
	HDC hdc;

public:
	virtual void BeginPaint(HDC hdc);
	virtual void EndPaint();
	virtual void DrawRectangle(int x, int y, int width, int height) = 0;
	virtual void DrawPiece(int x, int y, int width, int height, int color) = 0;
};

