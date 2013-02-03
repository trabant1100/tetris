#pragma once

#define PIECE_TYPE_COUNT 4
#define PIECE_ROTATION_COUNT 4
#define PIECE_WIDTH 5
#define PIECE_HEIGHT 5
#define PIECE_COLOR_COUNT 3
#define PIECE_COLOR_MAX (PIECE_COLOR_COUNT+1)

#define PIECE_COLOR_RED 1
#define PIECE_COLOR_GREEN 2
#define PIECE_COLOR_BLUE 3

struct PIECE_ORIGIN 
{
	int x;
	int y;
};

class Piece
{
	friend class TetrisTest;

public:
	Piece(int type, int color);
	~Piece(void);
	int GetBlockType(int x, int y);
	void Rotate();
	int GetColor();

private:
	int type;
	int rotation;
	int color;
	bool static originsCreated;
	PIECE_ORIGIN static origins[PIECE_TYPE_COUNT][PIECE_ROTATION_COUNT];
	int const static shapes[PIECE_TYPE_COUNT][PIECE_ROTATION_COUNT][PIECE_WIDTH][PIECE_HEIGHT];
	void CreateOrigins();
};

