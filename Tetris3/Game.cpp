#include "Game.h"
#include "Board.h"

Game::Game(Board *lpBoard)
{

	xPos = Board::xBlocks / 2;
	yPos = 0;

	this->lpBoard = lpBoard;
}


Game::~Game()
{
	
}

void Game::Step()
{
	lpBoard->DeletePossibleLines();
	
}
