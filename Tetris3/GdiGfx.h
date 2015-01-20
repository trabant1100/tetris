#pragma once

#include <Windows.h>

#include "Gfx.h"
#include "Piece.h"

class GdiGfx : public Gfx
{
private:
	HDC hdc = NULL;
public:
	void BeginPaint();
	void EndPaint();
	void DrawRectangle(int x, int y, int width, int height);
	void DrawPiece(int x, int y, int width, int height, int color);
};

