#include "Tetris.h"

#include <crtdbg.h>
#include <utility>

Tetris::Tetris(HINSTANCE hInstance, int nCmdMode)
{
	this->hInstance = hInstance;
	this->nCmdMode = nCmdMode;
	ATOM uid = this->RegisterWindowClass();
	_ASSERT(uid);

	HHOOK hHook = SetWindowsHookEx(WH_CBT, HelperCBTProc, NULL, GetCurrentThreadId());
	_ASSERT(hHook);

	std::pair<Tetris *, HHOOK> pair(this, hHook);
	this->hWindow = CreateWindow(TEXT("Tetris"), TEXT("Tetris"), WS_OVERLAPPEDWINDOW, 
		CW_USEDEFAULT, CW_USEDEFAULT, PIXEL_SIZE * (Board::xBlocks+5), PIXEL_SIZE * (Board::yBlocks+2), 
		0, 0, this->hInstance, &pair);
	UnhookWindowsHookEx(hHook);
	hHook = NULL;

	ShowWindow(hWindow, this->nCmdMode);

	MSG msg;
	gfx = new Direct2DGfx(hWindow);
	//gfx = new GdiGfx();
	lpBoard = new Board();
	lpGame = new Game(gfx, lpBoard);

	uTimer = SetTimer(hWindow, TETRIS_TIMER, 200, NULL);
	uGfxTimer = SetTimer(hWindow, TETRIS_GFX_TIMER, 100 / 60, NULL);

	while(GetMessage(&msg, hWindow, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}


Tetris::~Tetris(void)
{
}

LRESULT CALLBACK Tetris::HelperWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	Tetris *tetris = (Tetris *)GetWindowLong(hWnd, GWL_USERDATA);

	_ASSERT(tetris);

	return tetris->WndProc(hWnd, uMsg, wParam, lParam);
}

LRESULT CALLBACK Tetris::HelperCBTProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	if(nCode < 0 || nCode != HCBT_CREATEWND)
		return CallNextHookEx(NULL, nCode, lParam, wParam);

	std::pair<Tetris *, HHOOK> *lpPair = 
		(std::pair<Tetris *, HHOOK> *)LPCBT_CREATEWND(lParam)->lpcs->lpCreateParams;

	if(lpPair && lpPair->first)
	{
		SetWindowLong((HWND)wParam, GWL_USERDATA, (LONG)lpPair->first);
		lpPair->first = 0;
	}

	return CallNextHookEx(NULL, nCode, wParam, lParam);
}

ATOM Tetris::RegisterWindowClass()
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_VREDRAW | CS_HREDRAW;
	wcex.lpfnWndProc = HelperWndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = sizeof(Tetris *);
	wcex.hInstance = this->hInstance;
	wcex.hIcon = NULL;
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = TEXT("Tetris");
	wcex.hIconSm = NULL;

	return RegisterClassEx(&wcex);
}

LRESULT CALLBACK Tetris::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg)
	{
	case WM_TIMER:
		if(wParam == TETRIS_TIMER)
		{
			lpGame->Step();
			return 0;
		} 
		else if(wParam == TETRIS_GFX_TIMER)
		{
			InvalidateRgn(hWnd, NULL, true);
			return 0;
		}
		break;

	case WM_DESTROY:
		KillTimer(hWindow, uTimer);
		KillTimer(hWindow, uGfxTimer);
		delete lpBoard;
		delete lpGame;
		delete gfx;
		PostQuitMessage(WM_QUIT);
		break;

	case WM_KEYDOWN:
		switch(wParam)
		{
		case VK_LEFT:
			lpGame->Move(LEFT);
			break;
		case VK_RIGHT:
			lpGame->Move(RIGHT);
			break;
		case VK_UP:
			lpGame->Move(ROTATE);
			break;
		case VK_DOWN:
			lpGame->Move(DOWN);
			break;
		}
		break;

	case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hWnd, &ps);
			
			gfx->BeginPaint(hdc);
			lpGame->DrawScene();
			gfx->EndPaint();
			
			EndPaint(hWnd, &ps);
		}
		break;		

	case WM_ERASEBKGND:
		return (LPARAM)1;

	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}

	return 0;
}

void MsgError(LPCWSTR lpText)
{
	MessageBox(NULL, lpText, TEXT("FAIL"), MB_ICONERROR | MB_OK);
}