#include "Game.h"

#include <Windows.h>


Game::Game(Board *pBoard, Pieces *pPieces, IO *pIO, int pScreenHeight)
{

}


Game::~Game(void)
{
}

///<summary>Get a random int between two numbers</summary>
///<param name="pA">First number</param>
///<param name="pB">Second number</param>
///<returns>Random int</returns>
int Game::GetRand(int pA, int pB)
{
	return rand() % (pB - pA + 1) + pA;
}

///<summary>Init game parameters</summary>
void Game::InitGame()
{
	srand((unsigned int)time(NULL));

	mPiece = GetRand(0, 6);
	mRotation = GetRand(0, 3);
	mPosX = BOARD_WIDTH/2 + mPieces->GetXInitialPosition(mPiece, mRotation);
	mPosY = mPieces->GetYInitialPosition(mPiece, mRotation);

	mNextPiece = GetRand(0, 6);
	mNextRotation = GetRand(0, 3);
	mNextPosX = BOARD_WIDTH + 5;
	mNextPosY = 5;
}

///<summary>Create new random piece</summary>
void Game::CreateNewPiece()
{
	mPiece = mNextPiece;
	mRotation = mNextRotation;
	mPosX = BOARD_WIDTH/2 + mPieces->GetXInitialPosition(mPiece, mRotation);
	mNextPosY = mPieces->GetYInitialPosition(mPiece, mRotation);

	mNextPiece = GetRand(0, 6);
	mNextRotation = GetRand(0, 3);
}

///<<summary>Draw piece</summary>
///<param name="pX">Horizontal position in blocks</param>
///<param name="pY">Vertical position in blocks</param>
///<param name="pPiece">The piece to draw</param>
///<param name="pRotation">1 of the 4 posible rotations</param>
void Game::DrawPiece(int pX, int pY, int pPiece, int pRotation)
{
	color mColor;

	int mPixelsX = mBoard->GetXPosInPixels(pX);
	int mPixelsY = mBoard->GetYPosInPixels(pY);

	for(int i = 0; i < PIECE_BLOCKS; i ++)
	{
		for(int j = 0; j < PIECE_BLOCKS; j ++)
		{
			switch(mPieces->GetBlockType(pPiece, pRotation, pX, pY))
			{
				case 1: mColor = GREEN; break;
				case 2: mColor = BLUE; break;
			}

			if(mPieces->GetBlockType(pPiece, pRotation, pX, pY) != 0)
			{
				mIO->DrawRectangle(mPixelsX + i * BLOCK_SIZE,
					mPixelsY + j * BLOCK_SIZE,
					mPixelsX + i * BLOCK_SIZE + BLOCK_SIZE - 1,
					mPixelsY + j * BLOCK_SIZE + BLOCK_SIZE - 1,
					mCOlor);
			}
		}
	}
}

///<summary>Draw the board and the two lines that delimit the board</summary>
void Game::DrawBoard()
{
	int mX1 = BOARD_POSITION - (BLOCK_SIZE * (BOARD_WIDTH/2)) - 1;
	int mX2 = BOARD_POSITION + (BLOCK_SIZE * (BOARD_WIDTH/2));
	int mY = mScreenHeight - (BLOCK_SIZE * BOARD_HEIGHT);

	mIO->DrawRectangle(mX1 - BOARD_LINE_WIDTH, mY, mX1, mScreenHeight - 1, BLUE);
	mIO->DrawRectangle(mX2, mY, mX2 + BOARD_LINE_WIDTH, mScreenHeight - 1, BLUE);

	mX1 ++;
	for(int i = 0; i < BOARD_WIDTH; i ++)
	{
		for(int j = 0; j < BOARD_HEIGHT; j ++)
		{
			if(!mBoard->IsFreeBlock(i, j))
			{
				mIO->DrawRectangle(mX1 + i * BLOCK_SIZE, mY + j * BLOCK_SIZE,
					mX1 + i * BLOCK_SIZE + BLOCK_SIZE - 1,
					mY + j * BLOCK_SIZE + BLOCK_SIZE - 1,
					RED);
			}
		}
	}
}

///<summary>Draw all objects of the scene</summary>
void Game::DrawScene()
{
	DrawBoard();
	DrawPiece(mPosX, mPosY, mPiece, mRotation);
	DrawPiece(mNextPosX, mNextPosY, mNextPiece, mNextRotation);
}