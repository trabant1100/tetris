#pragma once

#define PIECE_TYPE_COUNT 1
#define PIECE_WIDTH 3
#define PIECE_HEIGHT 3

enum PieceType { PIECE_TYPE_1 };

class Piece
{
public:
	Piece(PieceType type);
	~Piece(void);
	int GetBlockType(int x, int y);
	
private:
	PieceType type;
	int const static shapes[PIECE_TYPE_COUNT][PIECE_WIDTH][PIECE_HEIGHT];
};

