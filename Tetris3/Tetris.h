#pragma once
#include "Gfx.h"
#include "Game.h"

#include <Windows.h>
#include <WindowsX.h>

#define TETRIS_TIMER 1
#define TETRIS_GFX_TIMER 2

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

	static LRESULT CALLBACK HelperWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK HelperCBTProc(int nCode, WPARAM wParam, LPARAM lParam);
	ATOM RegisterWindowClass();
	LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
};
