#pragma once

#include "Board.h"


class Game
{
public:
	Game(Board *lpBoard);
	~Game();
	void Step();

private:
	unsigned int xPos, yPos;
	Board *lpBoard;
};

