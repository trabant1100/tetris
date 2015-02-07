#ifdef _WIN32
#include <Windows.h>
#include "Tetris.h"

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR lpCmdLine, int nCmdMode)
{
	Tetris tetris(hInstance, nCmdMode);

	return 0;
}

#endif

#ifdef EMSCRIPTEN
#include "TetrisEM.h"
#include <stdio.h>

int main()
{
	printf("hello, world!\n");
	TetrisEM tetris;
	printf("Hello!");
	return 0;
}

#endif
