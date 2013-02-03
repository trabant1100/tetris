#include "Game.h"
#include "Board.h"
#include "Gfx.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

Game::Game(Gfx *lpGfx, Board *lpBoard)
{
	srand((unsigned)time(NULL));
	
	this->lpGfx = lpGfx;
	this->lpBoard = lpBoard;
	
	CreateNewPiece(lpPiece);
	CreateNewPiecePosition(lpPiece, &xPos, &yPos);

	CreateNewPiece(lpNextPiece);
}


Game::~Game()
{
	if(lpPiece) {
		delete lpPiece;
		lpPiece = NULL;
	}
	if(lpNextPiece) {
		delete lpNextPiece;
		lpPiece = NULL;
	}
}

void Game::Step()
{
	if(lpBoard->IsPossibleMovement(xPos, yPos + 1, lpPiece))
	{
		yPos ++;
	}
	else
	{
		lpBoard->StorePiece(xPos, yPos, lpPiece);
		delete lpPiece;

		lpPiece = lpNextPiece;

		CreateNewPiece(lpNextPiece);
		CreateNewPiecePosition(lpNextPiece, &xPos, &yPos);
	}
	lpBoard->DeletePossibleLines();
}

void Game::DrawScene()
{
	DrawBoard();
	DrawPiece(xPos, yPos, lpPiece);
	DrawPiece(Board::xBlocks, 0, lpNextPiece);
}

void Game::Move(GameMove move)
{
	switch(move)
	{
	case LEFT:
		if(lpBoard->IsPossibleMovement(xPos - 1, yPos, lpPiece))
		{
			xPos --;
		}
		break;
	case RIGHT:
		if(lpBoard->IsPossibleMovement(xPos + 1, yPos, lpPiece))
		{
			xPos ++;
		}
		break;
	case ROTATE:
		if(lpBoard->IsPossibleRotation(xPos, yPos, lpPiece))
		{
			lpPiece->Rotate();
		}
		break;
	case DOWN:
		while(lpBoard->IsPossibleMovement(xPos, yPos + 1, lpPiece))
		{
			yPos ++;
		}
		break;
	}
	lpBoard->DeletePossibleLines();
}

void Game::CreateNewPiece(Piece *&lpNewPiece)
{
	int color = rand() % PIECE_COLOR_COUNT + 1;

	lpNewPiece = new Piece(rand() % PIECE_TYPE_COUNT, color);
	//lpNewPiece = new Piece(1, 1);
}

void Game::CreateNewPiecePosition(const Piece *lpPiece, int *xPos, int *yPos)
{
	*xPos = rand() % (Board::xBlocks - PIECE_WIDTH);
	*yPos = 0;
}

void Game::DrawPiece(int xPos, int yPos, Piece *lpPiece)
{
	for(int x = 0; x < PIECE_WIDTH; x ++)
	{
		for(int y = 0; y < PIECE_WIDTH; y ++)
		{
			if(lpPiece->GetBlockType(x, y) != 0)
			{
				lpGfx->DrawPiece((xPos+x) * PIXEL_SIZE, (yPos+y) * PIXEL_SIZE, PIXEL_SIZE, PIXEL_SIZE, lpPiece->GetColor());
			}
		}
	}
}

void Game::DrawBoard()
{
	lpGfx->DrawRectangle(0, 0, Board::xBlocks * PIXEL_SIZE, Board::yBlocks * PIXEL_SIZE);
	for(int x = 0; x < Board::xBlocks; x ++)
	{
		for(int y = 0; y < Board::yBlocks; y ++)
		{
			int color = lpBoard->GetBlockColor(x, y);
			if(color)
			{
				lpGfx->DrawPiece(x * PIXEL_SIZE, y * PIXEL_SIZE, PIXEL_SIZE, PIXEL_SIZE, color);
			}
		}
	}
}
