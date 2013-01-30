#include "Piece.h"

Piece::Piece(int type, PieceColor color)
{
	this->type = type;
	this->color = color;
	rotation = 0;
}


Piece::~Piece(void)
{
}

int Piece::GetBlockType(int x, int y)
{
	return shapes[type][rotation][y][x];
}

void Piece::Rotate()
{
	if(rotation == 0)
		rotation = 1;
	else
		rotation = 0;
}

PieceColor Piece::GetColor()
{
	return color;
}

int const Piece::shapes[PIECE_TYPE_COUNT][PIECE_ROTATION_COUNT][PIECE_WIDTH][PIECE_HEIGHT] =   
{
	{ // L
		{
			{0, 0, 0, 0, 0},
			{0, 0, 1, 0, 0},
			{0, 0, 1, 0, 0},
			{0, 0, 1, 1, 0},
			{0, 0, 0, 0, 0}
		},
		{
			{0, 0, 0, 0, 0},
			{0, 0, 0, 0, 0},
			{0, 1, 1, 1, 0},
			{0, 1, 0, 0, 0},
			{0, 0, 0, 0, 0}
		}
	},
	{ // []
		{
			{0, 0, 0, 0, 0},
			{0, 0, 0, 0, 0},
			{0, 0, 1, 1, 0},
			{0, 0, 1, 1, 0},
			{0, 0, 0, 0, 0}
		},
		{
			{0, 0, 0, 0, 0},
			{0, 0, 0, 0, 0},
			{0, 0, 1, 1, 0},
			{0, 0, 1, 1, 0},
			{0, 0, 0, 0, 0}
		}
	},
	{ // |-
		{
			{0, 0, 0, 0, 0},
			{0, 0, 1, 0, 0},
			{0, 0, 1, 1, 0},
			{0, 0, 1, 0, 0},
			{0, 0, 0, 0, 0}
		},
		{
			{0, 0, 0, 0, 0},
			{0, 0, 0, 0, 0},
			{0, 1, 1, 1, 0},
			{0, 0, 1, 0, 0},
			{0, 0, 0, 0, 0}
		}
	}
};
