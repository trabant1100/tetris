#include <Windows.h>

#include "Tetris.h"

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR lpCmdLine, int nCmdMode)
{
	Tetris tetris(hInstance, nCmdMode);

	return 0;
}
