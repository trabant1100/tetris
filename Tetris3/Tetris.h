#pragma once

#include "Direct2DGfx.h"
#include "GdiGfx.h"
#include "Game.h"

#include <Windows.h>
#include <WindowsX.h>

#define TETRIS_TIMER 1
#define TETRIS_GFX_TIMER 2
#define WM_TETRIS_GAME_OVER (WM_USER + 1)

class Tetris
{
public:
	Tetris(HINSTANCE hInstance, int nCmdMode);
	~Tetris(void);

private:
	HINSTANCE hInstance;
	int nCmdMode;
	HWND hWindow;
	UINT uTimer;
	UINT uGfxTimer;
	Board *lpBoard;
	Game *lpGame;
	Gfx *gfx;

	static LRESULT CALLBACK HelperWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK HelperCBTProc(int nCode, WPARAM wParam, LPARAM lParam);
	ATOM RegisterWindowClass();
	LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
};

void MsgError(LPCWSTR lpText); 

