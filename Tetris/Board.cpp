#include "Board.h"


Board::Board(Pieces *pieces, int pScreenHeight)
{
	mPieces = pieces;
	mScreenHeight = pScreenHeight;
	InitBoard();
}


Board::~Board(void)
{
}

///<summary>Init board blocks with free positions</summary>
void Board::InitBoard()
{
	for(int i = 0; i < BOARD_WIDTH; i ++)
	{
		for(int j = 0; j < BOARD_HEIGHT; j ++)
		{
			mBoard[i][j] = POS_FREE;
		}
	}
}

///<summary>Store a piece in the board by filling the blocks</summary>
///<param name="pX">Horizontal position in blocks</params>
///<param name="pY">Vertical position in blocks</params>
///<param name="pRotation">1 of the 4 possible rotations</param>
void Board::StorePiece(int pX, int pY, int pPiece, int pRotation)
{
	for(int i1 = pX, i2 = 0; i1 < pX + PIECE_BLOCKS; i1 ++, i2 ++)
	{
		for(int j1 = pY, j2 = 0; j1 < pY + PIECE_BLOCKS; j1 ++, j2 ++)
		{
			if(mPieces->GetBlockType(pPiece, pRotation, i2, j2) != 0)
			{
				mBoard[i1][j1] = POS_FILLED;
			}
		}
	}
}

///<summary>Check if the game is over because a piece achived the upper position</summary>
///<returns><code>true</code> if the game is over</returns>
bool Board::IsGameOver()
{
	for(int i = 0; i < BOARD_WIDTH; i ++)
	{
		if(mBoard[i][0] == POS_FILLED)
			return true;
	}
	return false;
}

///<summary>Delete a line of the board by moving all lines above down</summary>
///<param name="pY">Vertical position in blocks of line to remove</param>
void Board::DeleteLine(int pY)
{
	for(int j = pY; j > 0; j --)
	{
		for(int i = 0; i < BOARD_WIDTH; i ++)
		{
			mBoard[i][j] = mBoard[i][j-1];
		}
	}
}

///<summary>Delete all the lines that should be removed</summary>
void Board::DeletePossibleLines()
{
	for(int j = 0; j < BOARD_HEIGHT; j ++)
	{
		int i = 0;
		while(i < BOARD_WIDTH)
		{
			if(mBoard[i][j] != POS_FILLED)
				break;
			i ++;
		}
		if(i == BOARD_WIDTH)
			DeleteLine(j);
	}
}

///<summary>Check if the block is empty</summary>
///<param name="pX">Horizontal position in blocks</param>
///<param name="pY">Vertical position in blocks</param>
///<returns><code>true</code> if block is free
bool Board::IsFreeBlock(int pX, int pY)
{
	return mBoard[pX][pY] == POS_FREE;
}

///<summary>Convert horizontal position in blocks to pixels</summary>
///<param name="pX">Horizontal position in blocks</param>
///<returns>Horizontal position in pixels</returns>
int Board::GetXPosInPixels(int pX)
{
	return BOARD_POSITION - BLOCK_SIZE * (BOARD_WIDTH/2) + pX * BLOCK_SIZE;
}

///<summary>Convert vertical position in blocks to pixels</summary>
///<param name="pY">Vertical position in blocks</param>
///<returns>Vertical position in pixels</returns>
int Board::GetYPosInPixels(int pY)
{
	return mScreenHeight - BLOCK_SIZE * BOARD_HEIGHT + pY * BLOCK_SIZE;
}

///<summary>Check if the piece can be stored without collision
///<param name="pX">Horizontal position in blocks</param>
///<param name="pY">Vertical position in blocks</param>
///<param name="pPiece">Piece to draw</param>
///<param name="pRotation">1 of the 4 possible rotations</param>
///<returns><code>true</code> if move is possible</returns>
bool Board::IsPossibleMovement(int pX, int pY, int pPiece, int pRotation)
{
	for(int i1 = pX, i2 = 0; i1 < pX + PIECE_BLOCKS; i1 ++, i2 ++)
	{
		for(int j1 = pY, j2 = 0; j1 < pY + PIECE_BLOCKS; j1 ++, j2 ++)
		{
			if(i1 < 0 || j1 > BOARD_WIDTH-1 || j1 > BOARD_HEIGHT-1)
			{
				if(mPieces->GetBlockType(pPiece, pRotation, i2, j2) != 0)
					return false;
			}

			if(j1 >= 0)
			{
				if(mPieces->GetBlockType(pPiece, pRotation, i2, j2) != 0 && !IsFreeBlock(i1, j1))
				{
					return false;
				}
			}
		}
	}
	
	return true;
}