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
	
	lpPiece = NULL;
	CreateNewPiece();
}


Game::~Game()
{
	delete lpPiece;
}

void Game::Step()
{
	lpBoard->DeletePossibleLines();
	
	if(lpBoard->IsPosibleMovement(xPos, yPos + 1, lpPiece))
	{
		yPos ++;
	}
	else
	{
		lpBoard->StorePiece(xPos, yPos, lpPiece);
		CreateNewPiece();
	}
}

void Game::DrawScene()
{
	DrawBoard();
	DrawPiece(xPos, yPos, lpPiece);
}

void Game::Move(GameMove move)
{
	switch(move)
	{
	case LEFT:
		if(lpBoard->IsPosibleMovement(xPos - 1, yPos, lpPiece))
		{
			xPos --;
		}
		break;
	case RIGHT:
		if(lpBoard->IsPosibleMovement(xPos + 1, yPos, lpPiece))
		{
			xPos ++;
		}
		break;
	case ROTATE:
		lpPiece->Rotate();
		break;
	case DOWN:
		while(lpBoard->IsPosibleMovement(xPos, yPos + 1, lpPiece))
		{
			yPos ++;
		}
		lpBoard->DeletePossibleLines();
	}
}

void Game::CreateNewPiece()
{
	if(lpPiece)
		delete lpPiece;

	PieceColor color = static_cast<PieceColor> (rand() % 3);

	lpPiece = new Piece(rand() % PIECE_TYPE_COUNT, color);
	//lpPiece = new Piece(1);
	xPos = rand() % (Board::xBlocks - PIECE_WIDTH);
	yPos = 0;
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
			if(!lpBoard->IsFreeBlock(x, y))
			{
				lpGfx->DrawPiece(x * PIXEL_SIZE, y * PIXEL_SIZE, PIXEL_SIZE, PIXEL_SIZE, BLUE);
			}
		}
	}
}
