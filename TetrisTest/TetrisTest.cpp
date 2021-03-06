// TetrisTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
//#include "UnitTest++.h"

#include "Board.h"
#include "Piece.h"



TEST(Board)
{
	Board board;
	Piece piece(0, 1);


	CHECK(
		board.IsPossibleMovement(0, 0, &piece)	
		);

	CHECK(
		board.IsPossibleMovement(-1, 0, &piece)
		);

	/*piece.Rotate();
	CHECK(
		board.IsPossibleMovement(-3, 0, &piece) == false
		);*/
}

int _tmain(int argc, _TCHAR* argv[])
{
	return UnitTest::RunAllTests();
	return 0;
}

