#include "Piece.h"

#include <stdio.h>

Piece::Piece(int type, int color)
{
	this->type = type;
	this->color = color;
	rotation = 0;
	if(!originsCreated)
	{
		CreateOrigins();
		originsCreated = true;
	}
	if(!rotationsCreated)
	{
		//CreateRotations();
		rotationsCreated = true;
	}
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
	rotation ++;
	if(rotation >= PIECE_ROTATION_COUNT)
		rotation = 0;
}

int Piece::GetColor()
{
	return color;
}

PIECE_ORIGIN Piece::GetOrigin()
{
	return origins[type][rotation];
}

bool Piece::originsCreated = false;
bool Piece::rotationsCreated = false;

PIECE_ORIGIN Piece::origins[PIECE_TYPE_COUNT][PIECE_ROTATION_COUNT] = {0};

#pragma region shapes
int Piece::shapes[PIECE_TYPE_COUNT][PIECE_ROTATION_COUNT][PIECE_WIDTH][PIECE_HEIGHT] = 
{
	{ // L
		{
			{0, 0, 0, 0},
			{0, 1, 0, 0},
			{0, 1, 0, 0},
			{0, 1, 1, 0}
		},
		{
			{0, 0, 0, 0},
			{0, 0, 0, 0},
			{1, 1, 1, 0},
			{1, 0, 0, 0}
		},
		{
			{0, 0, 0, 0},
			{1, 1, 0, 0},
			{0, 1, 0, 0},
			{0, 1, 0, 0}
		},
		{
			{0, 0, 0, 0},
			{0, 0, 1, 0},
			{1, 1, 1, 0},
			{0, 0, 0, 0}
		}
	},
	{ // []
		{
			{0, 0, 0, 0},
			{0, 1, 1, 0},
			{0, 1, 1, 0},
			{0, 0, 0, 0}
		},
		{
			{0, 0, 0, 0},
			{0, 1, 1, 0},
			{0, 1, 1, 0},
			{0, 0, 0, 0}
		},
		{
			{0, 0, 0, 0},
			{0, 1, 1, 0},
			{0, 1, 1, 0},
			{0, 0, 0, 0}
		},
		{
			{0, 0, 0, 0},
			{0, 1, 1, 0},
			{0, 1, 1, 0},
			{0, 0, 0, 0}
		}
	},
	{ // |-
		{
			{0, 0, 0, 0},
			{0, 1, 0, 0},
			{0, 1, 1, 0},
			{0, 1, 0, 0}
		},
		{
			{0, 0, 0, 0},
			{0, 1, 1, 1},
			{0, 0, 1, 0},
			{0, 0, 0, 0}
		},
		{
			{0, 0, 0, 0},
			{0, 0, 0, 1},
			{0, 0, 1, 1},
			{0, 0, 0, 1}
		},
		{
			{0, 0, 0, 0},
			{0, 0, 0, 0},
			{0, 0, 1, 0},
			{0, 1, 1, 1}
		}
	},
	{ // |
		{
			{0, 0, 1, 0},
			{0, 0, 1, 0},
			{0, 0, 1, 0},
			{0, 0, 1, 0}
		},
		{
			{0, 0, 0, 0},
			{1, 1, 1, 1},
			{0, 0, 0, 0},
			{0, 0, 0, 0}
		},
		{
			{0, 0, 1, 0},
			{0, 0, 1, 0},
			{0, 0, 1, 0},
			{0, 0, 1, 0}
		},
		{
			{0, 0, 0, 0},
			{1, 1, 1, 1},
			{0, 0, 0, 0},
			{0, 0, 0, 0}
		}
	}
};
#pragma endregion shapes

void Piece::CreateOrigins()
{
	for(int type = 0; type < PIECE_TYPE_COUNT; type ++)
	{
		for(int rotation = 0; rotation < PIECE_ROTATION_COUNT; rotation ++)
		{
			PIECE_ORIGIN origin = {0};
			bool originFound = false;
			
			#pragma region loop
			for(int x = 0; x < PIECE_WIDTH && !originFound; x ++)
			{
				for(int y = 0; y < PIECE_HEIGHT; y ++) 
				{
					if(shapes[type][rotation][y][x] != 0)
					{
						origin.x = x;
						origin.y = y;
						originFound = true;
						break;
					}
				}
			}
			#pragma endregion loop

			origins[type][rotation] = origin;
		}
	}
}

void Piece::CreateRotations()
{
	for(int type = 0; type < PIECE_TYPE_COUNT; type ++)
	{
		for(int rotation = 1; rotation < PIECE_ROTATION_COUNT; rotation ++)
		{
			for(int y = 0; y < PIECE_HEIGHT; y ++)
			{
				for(int x = 0; x < PIECE_WIDTH; x ++)
				{
					shapes[type][rotation][x][PIECE_HEIGHT-1-y] = shapes[type][rotation-1][y][x];
				}
			}
		}
	}
}