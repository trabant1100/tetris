#include "Direct2DGfx.h"
#include "Tetris.h"

#include <stdio.h>
#include <crtdbg.h>
#include <cwchar>

Direct2DGfx::Direct2DGfx(HWND hWindow)
{
	D2D1_HWND_RENDER_TARGET_PROPERTIES hwndRTP;
	this->hWindow = hWindow;

	GetClientRect(this->hWindow, &rc);
	if(D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &pD2DFactory) != S_OK)
		MsgError(TEXT("FACTORY FAIL!"));
	hwndRTP = D2D1::HwndRenderTargetProperties(this->hWindow, D2D1::SizeU(rc.right - rc.left, rc.bottom - rc.top));

	if(pD2DFactory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(), hwndRTP, &pRT) != S_OK)
		MsgError(TEXT("Cannot create hwnd render target"));

	pBrushes = new ID2D1SolidColorBrush*[PIECE_COLOR_MAX];
	for(int i = 0; i < PIECE_COLOR_MAX; i ++)
	{
		if(pRT->CreateSolidColorBrush(D2D1::ColorF(colors[i]), &(pBrushes[i])) != S_OK)
			MsgError(TEXT("Cannot create brush"));
	}

	if(DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), 
		reinterpret_cast<IUnknown **>(&pDWriteFactory)) != S_OK)
	{
		MsgError(TEXT("Cannot create DirectWrite factory"));
	}

	if(pDWriteFactory->CreateTextFormat(L"Jokerman", NULL, DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_NORMAL, 40, L"", &pDWriteTextFormat) != S_OK)
	{
		MsgError(TEXT("Cannot create DirectWrite text format"));
	}

	pDWriteTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
	pDWriteTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
}

Direct2DGfx::~Direct2DGfx()
{
	pRT->Release();
	pD2DFactory->Release();

	for(int i = 0; i < PIECE_COLOR_MAX; i ++)
	{
		pBrushes[i]->Release();
	}
	delete[] pBrushes;
}

void Direct2DGfx::BeginPaint()
{
	pRT->BeginDraw();
	pRT->Clear(D2D1::ColorF(D2D1::ColorF::White));
}

void Direct2DGfx::EndPaint()
{
	HRESULT hRes = pRT->EndDraw();
	if(hRes != S_OK)
		MsgError(TEXT("End draw failed"));
}

void Direct2DGfx::DrawRectangle(int x, int y, int width, int height)
{
	D2D1_RECT_F rect = ConvertRect(&D2D1::RectU(x, y, x + width, y + height));
	pRT->DrawRectangle(&rect, pBrushes[0]);
}

void Direct2DGfx::DrawPiece(int x, int y, int width, int height, int color)
{
	_ASSERT(x >= 0);
	_ASSERT(y >= 0);
	D2D1_RECT_F rect = ConvertRect(&D2D1::RectU(x, y, x + width, y + height));
	pRT->FillRectangle(&rect, pBrushes[color]);
}

void Direct2DGfx::DrawScore(int x, int y, int score)
{
	WCHAR lpszScore[20] = {0};
	swprintf_s(lpszScore, L"%d", score);	

	D2D1_RECT_F rect = ConvertRect(&D2D1::RectU(x, y, x + 50, y + 50));

	pRT->DrawTextW(lpszScore, std::wcslen(lpszScore), pDWriteTextFormat, rect, pBrushes[0]);
}

const D2D1::ColorF::Enum Direct2DGfx::colors[PIECE_COLOR_MAX] = 
{D2D1::ColorF::Black, D2D1::ColorF::Red, D2D1::ColorF::Green, D2D1::ColorF::Blue};

D2D1_RECT_F Direct2DGfx::ConvertRect(D2D1_RECT_U *rect)
{
	return D2D1::RectF((FLOAT)rect->left, (FLOAT)rect->top, (FLOAT)rect->right, (FLOAT)rect->bottom);
}
