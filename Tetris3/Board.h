#pragma once

#define BLOCK_FREE 0
#define BLOCK_FILLED 1

class Board
{
public:
	static const unsigned int xBlocks = 10, yBlocks = 20;
	Board();
	~Board();
	void DeletePossibleLines();

private:
	int blocks[xBlocks][yBlocks];
	void DeleteLine(int line);
};

