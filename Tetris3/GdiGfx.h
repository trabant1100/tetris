#pragma once

#include <Windows.h>

#include "Gfx.h"
#include "Piece.h"

class GdiGfx : public Gfx
{
public:
	void BeginPaint(HDC hdc);
	void EndPaint();
	void DrawRectangle(int x, int y, int width, int height);
	void DrawPiece(int x, int y, int width, int height, PieceColor color);
};

