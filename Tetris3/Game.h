#pragma once

#include "Board.h"

class Game
{
public:
	Game();
	~Game();
	void Step();

private:
	unsigned int xPos, yPos;
	Board *lpBoard;
};

