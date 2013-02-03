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

	pBrushes = new ID2D1SolidColorBrush*[PIECE_COLOR_MAX];
	for(int i = 0; i < PIECE_COLOR_MAX; i ++)
	{
		if(pRT->CreateSolidColorBrush(D2D1::ColorF(colors[i]), &(pBrushes[i])) != S_OK)
			MsgError(TEXT("Cannot create brush"));
	}
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
	D2D1_RECT_F rect = ConvertRect(&D2D1::RectU(x, y, x + width, y + height));
	pRT->DrawRectangle(&rect, pBrushes[0]);
}

void Direct2DGfx::DrawPiece(int x, int y, int width, int height, int color)
{
	D2D1_RECT_F rect = ConvertRect(&D2D1::RectU(x, y, x + width, y + height));
	pRT->FillRectangle(&rect, pBrushes[color]);
}

const D2D1::ColorF::Enum Direct2DGfx::colors[PIECE_COLOR_MAX] = 
{D2D1::ColorF::Black, D2D1::ColorF::Red, D2D1::ColorF::Green, D2D1::ColorF::Blue};

D2D1_RECT_F Direct2DGfx::ConvertRect(D2D1_RECT_U *rect)
{
	return D2D1::RectF((FLOAT)rect->left, (FLOAT)rect->top, (FLOAT)rect->right, (FLOAT)rect->bottom);
}
