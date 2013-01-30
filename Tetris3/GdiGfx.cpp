#include "GdiGfx.h"

void GdiGfx::BeginPaint(HDC hdc)
{
	this->hdc = hdc;
}

void GdiGfx::EndPaint()
{
	//hdc = NULL;
}

void GdiGfx::DrawRectangle(int x, int y, int width, int height)
{
	Rectangle(hdc, x, y, x + width, y + height);
}

void GdiGfx::DrawPiece(int x, int y, int width, int height, PieceColor color)
{
	DWORD rgbColor;
	switch(color)
	{
	case RED:
		rgbColor = RGB(255, 0, 0);
		break;
	case GREEN:
		rgbColor = RGB(0, 255, 0);
		break;
	case BLUE:
		rgbColor = RGB(0, 0, 255);
		break;
	}

	HBRUSH hBrush = CreateSolidBrush(rgbColor);
	HGDIOBJ hOrgBrush = SelectObject(hdc, hBrush);
	
	HGDIOBJ hPen = GetStockObject(NULL_PEN);
	HGDIOBJ hOrgPen = SelectObject(hdc, hPen);
		
	Rectangle(hdc, x, y, x + width + 1, y + height + 1);

	DeleteObject(hBrush);
	SelectObject(hdc, hOrgBrush);
	SelectObject(hdc, hOrgPen);
}