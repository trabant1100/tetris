#include "Direct2DGfx.h"
#include "Tetris.h"


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

	pBrushes = new ID2D1SolidColorBrush*[PieceColor::MAX];
	for(int i = 0; i < PieceColor::MAX; i ++)
	{
		if(pRT->CreateSolidColorBrush(D2D1::ColorF(colors[i]), &(pBrushes[i])) != S_OK)
			MsgError(TEXT("Cannot create brush"));
	}
}

Direct2DGfx::~Direct2DGfx()
{
	pRT->Release();
	pD2DFactory->Release();

	for(int i = 0; i < PieceColor::MAX; i ++)
	{
		pBrushes[i]->Release();
	}
	delete[] pBrushes;
}

void Direct2DGfx::BeginPaint(HDC hdc)
{
	this->hdc = hdc;
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
	pRT->DrawRectangle(D2D1::RectF(x, y, x + width, y + height), pBrushes[BLUE]);
}

void Direct2DGfx::DrawPiece(int x, int y, int width, int height, PieceColor color)
{
	pRT->FillRectangle(D2D1::RectF(x, y, x + width, y + height), pBrushes[color]);
	//pRT->DrawRectangle(D2D1::RectF(x + 0.0f, y + 0.0f, x + width + 0.0f, y + height + 0.0f), pBrushes[color]);
}

const D2D1::ColorF::Enum Direct2DGfx::colors[PieceColor::MAX] = {D2D1::ColorF::Red, D2D1::ColorF::Green, D2D1::ColorF::Blue};

