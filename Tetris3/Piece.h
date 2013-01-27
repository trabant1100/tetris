#pragma once

#define PIECE_TYPE_COUNT 2
#define PIECE_ROTATION_COUNT 2
#define PIECE_WIDTH 5
#define PIECE_HEIGHT 5

enum PieceColor { RED, GREEN, BLUE };

class Piece
{

public:
	Piece(int type, PieceColor color);
	~Piece(void);
	int GetBlockType(int x, int y);
	void Rotate();
	PieceColor GetColor();

private:
	int type;
	int rotation;
	PieceColor color;
	int const static shapes[PIECE_TYPE_COUNT][PIECE_ROTATION_COUNT][PIECE_WIDTH][PIECE_HEIGHT];
};

