#include "Piece.h"

Piece::Piece(PieceType type)
{
	this->type = type;
}


Piece::~Piece(void)
{
}

int Piece::GetBlockType(int x, int y)
{
	return shapes[this->type][x][y];
}

int const Piece::shapes[PIECE_TYPE_COUNT][PIECE_WIDTH][PIECE_HEIGHT] =   
{
	{
		{0, 1, 0},
		{0, 1, 0},
		{0, 1, 1}
	}
};
