#include "Game.h"
#include "Board.h"

Game::Game()
{
	xPos = Board::xBlocks / 2;
	yPos = 0;

	this->lpBoard = new Board();
}


Game::~Game()
{
	
}

void Game::Step()
{
	lpBoard->DeletePossibleLines();
}
