#pragma once
#include "Gfx.h"
#include "Game.h"

#include <Windows.h>

#define TETRIS_TIMER 1

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
	Board *lpBoard;
	Game *lpGame;

	static LRESULT CALLBACK HelperWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK HelperCBTProc(int nCode, WPARAM wParam, LPARAM lParam);
	ATOM RegisterWindowClass();
	LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
};
