#pragma once
#include "gfx.h"

#include <d2d1.h>
#include <dwrite.h>

class Direct2DGfx :
	public Gfx
{
private:
	static const D2D1::ColorF::Enum colors[PIECE_COLOR_MAX];
	RECT rc;
	HWND hWindow;
	
	ID2D1Factory *pD2DFactory;
	ID2D1HwndRenderTarget *pRT;
	ID2D1SolidColorBrush **pBrushes;
	D2D1_RECT_F ConvertRect(D2D1_RECT_U *rect);

	IDWriteFactory *pDWriteFactory;
	IDWriteTextFormat *pDWriteTextFormat;

public:
	Direct2DGfx(HWND hWindow);
	~Direct2DGfx();
	void BeginPaint();
	void EndPaint();
	void DrawRectangle(int x, int y, int width, int height);
	void DrawPiece(int x, int y, int width, int height, int color);
	void DrawScore(int x, int y, int score);
};

