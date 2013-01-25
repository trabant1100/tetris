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

void Board::DeletePossibleLines()
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
			DeleteLine(y);
	}
}

void Board::DeleteLine(int line)
{
	for(int y = line - 1; y --; y >= 0)
	{
		for(int x = 0; x < xBlocks; x ++)
		{
			blocks[x][y+1] = blocks[x][y];
		}
	}
}
