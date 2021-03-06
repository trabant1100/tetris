#include "Board.h"

Board::Board()
{
	for(int x = 0; x < xBlocks; x ++)
	{
		for(int y = 0; y < yBlocks; y ++)
		{
			this->blocks[x][y] = BLOCK_FREE;
		}
	}
}


Board::~Board()
{
}

int Board::DeletePossibleLines()
{
	for(int y = 0; y < yBlocks; y ++)
	{
		bool deleteLine = true;
		for(int x = 0; x < xBlocks; x ++)
		{
			if(blocks[x][y] == BLOCK_FREE) {
				deleteLine = false;
				break;
			}
		}
		if(deleteLine)
		{
			DeleteLine(y);
			return 1;
		}
	}

	return 0;
}

void Board::DeleteLine(int line)
{
	for(int y = line - 1; y >= 0; y --)
	{
		for(int x = 0; x < xBlocks; x ++)
		{
			blocks[x][y+1] = blocks[x][y];
		}
	}
}

void Board::StorePiece(int xPos, int yPos, Piece *lpPiece)
{
	for(int x = xPos, xPiece = 0; x < xPos + PIECE_WIDTH; x ++, xPiece ++)
	{
		for(int y = yPos, yPiece = 0; y < yPos + PIECE_WIDTH; y ++, yPiece++)
		{
			if(lpPiece->GetBlockType(xPiece, yPiece) != 0)
			{
				blocks[x][y] = lpPiece->GetColor(); 
			}
		}
	}
}

bool Board::IsFreeBlock(int xPos, int yPos)
{
	return blocks[xPos][yPos] == BLOCK_FREE;
}

int Board::GetBlockColor(int xPos, int yPos)
{
	return blocks[xPos][yPos];
}

bool Board::IsBlockInBoard(int xPos, int yPos)
{
	return (xPos >= 0 && xPos < xBlocks && yPos >= 0 && yPos < yBlocks);
}

bool Board::IsGameOver()
{
	for(int x = 0; x < xBlocks; x ++)
	{
		if(IsFreeBlock(x, 0) != true)
		{
			return true;
		}
	}

	return false;
}

bool Board::IsPossibleMovement(int xPos, int yPos, Piece *lpPiece)
{	
	for(int x = xPos, xPiece = 0; x < xPos + PIECE_WIDTH; x ++, xPiece ++)
	{
		for(int y = yPos, yPiece = 0; y < yPos + PIECE_HEIGHT; y ++, yPiece ++)
		{
			if(lpPiece->GetBlockType(xPiece, yPiece) != 0)
			{
				if(x < 0 || x >= xBlocks || y < 0 || y >= yBlocks || blocks[x][y] != 0)
				{
					return false;
				}
			}
		}
	}

	return true;
}

bool Board::IsPossibleRotation(int xPos, int yPos, Piece *lpPiece)
{
	Piece rotatedPiece(*lpPiece);
	rotatedPiece.Rotate();

	return IsPossibleMovement(xPos, yPos, &rotatedPiece);
}
