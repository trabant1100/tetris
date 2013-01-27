#pragma once

#include "Piece.h"

#include <Windows.h>

class Gfx
{
public:
	static HDC hdc;

	static void DrawRectangle(int x, int y, int width, int height);
	static void DrawPiece(int x, int y, int width, int height, PieceColor color);
};

