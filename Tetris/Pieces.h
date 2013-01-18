#pragma once
class Pieces
{
public:
	Pieces(void);
	~Pieces(void);
	
	int GetBlockType(int pPiece, int pRotation, int pX, int pY);
	int GetXInitialPosition(int pPiece, int pRotation);
	int GetYInitialPosition(int pPiece, int pRotation);
};

