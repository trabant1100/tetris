#pragma once
#include "gfx.h"

#include <d2d1.h>

class Direct2DGfx :
	public Gfx
{
private:
	static const D2D1::ColorF::Enum colors[MAX];
	RECT rc;
	HWND hWindow;
	
	ID2D1Factory *pD2DFactory;
	ID2D1HwndRenderTarget *pRT;
	ID2D1SolidColorBrush **pBrushes;

public:
	Direct2DGfx(HWND hWindow);
	~Direct2DGfx();
	void BeginPaint(HDC hdc);
	void EndPaint();
	void DrawRectangle(int x, int y, int width, int height);
	void DrawPiece(int x, int y, int width, int height, PieceColor color);
};
