#pragma once
#include "BoardState.h"
#include "SpaceType.h"
#include "Game.h"

class BoardState;

const int LongArray[4][4][4] =
{
	{ 
		{0,0,1,0},
		{0,0,1,0},
		{0,0,1,0},
		{0,0,1,0}
	},
	{ 
		{0,0,0,0},
		{0,0,0,0},
		{1,1,1,1},
		{0,0,0,0}
	},
	{ 
		{0,0,1,0},
		{0,0,1,0},
		{0,0,1,0},
		{0,0,1,0}
	},
	{ 
		{0,0,0,0},
		{0,0,0,0},
		{1,1,1,1},
		{0,0,0,0}
	}
};

const int RegularArray[4][4][4] =
{
	{
		{0,1,0,0},
		{0,1,0,0},
		{0,1,1,0},
		{0,0,0,0}
	},
	{
		{0,0,0,0},
		{0,1,1,1},
		{0,1,0,0},
		{0,0,0,0}
	},
	{
		{0,1,1,0},
		{0,0,1,0},
		{0,0,1,0},
		{0,0,0,0}
	},
	{
		{0,0,0,0},
		{0,0,0,1},
		{0,1,1,1},
		{0,0,0,0}
	}
};

const int ReverseArray[4][4][4] =
{
	{
		{0,0,1,0},
		{0,0,1,0},
		{0,1,1,0},
		{0,0,0,0}
	},
	{
		{0,0,0,0},
		{0,1,0,0},
		{0,1,1,1},
		{0,0,0,0}
	},
	{
		{0,1,1,0},
		{0,1,0,0},
		{0,1,0,0},
		{0,0,0,0}
	},
	{
		{0,0,0,0},
		{0,1,1,1},
		{0,0,0,1},
		{0,0,0,0}
	}
};

const int SquareArray[4][4][4] =
{
	{
		{0,0,0,0},
		{0,1,1,0},
		{0,1,1,0},
		{0,0,0,0}
	},
	{
		{0,0,0,0},
		{0,1,1,0},
		{0,1,1,0},
		{0,0,0,0}
	},
	{
		{0,0,0,0},
		{0,1,1,0},
		{0,1,1,0},
		{0,0,0,0}
	},
	{
		{0,0,0,0},
		{0,1,1,0},
		{0,1,1,0},
		{0,0,0,0}
	}
};

const int TArray[4][4][4] =
{
	{
		{0,0,1,0},
		{0,1,1,0},
		{0,0,1,0},
		{0,0,0,0}
	},
	{
		{0,0,1,0},
		{0,1,1,1},
		{0,0,0,0},
		{0,0,0,0}
	},
	{
		{0,0,1,0},
		{0,0,1,1},
		{0,0,1,0},
		{0,0,0,0}
	},
	{
		{0,0,0,0},
		{0,1,1,1},
		{0,0,1,0},
		{0,0,0,0}
	}
};

const int ZArray[4][4][4] =
{
	{
		{0,0,0,0},
		{0,1,1,0},
		{0,0,1,1},
		{0,0,0,0}
	},
	{
		{0,0,1,0},
		{0,1,1,0},
		{0,1,0,0},
		{0,0,0,0}
	},
	{
		{0,0,0,0},
		{0,1,1,0},
		{0,0,1,1},
		{0,0,0,0}
	},
	{
		{0,0,1,0},
		{0,1,1,0},
		{0,1,0,0},
		{0,0,0,0}
	}
};

const int SArray[4][4][4] =
{
	{
		{0,0,0,0},
		{0,0,1,1},
		{0,1,1,0},
		{0,0,0,0}
	},
	{
		{0,1,0,0},
		{0,1,1,0},
		{0,0,1,0},
		{0,0,0,0}
	},
	{
		{0,0,0,0},
		{0,0,1,1},
		{0,1,1,0},
		{0,0,0,0}
	},
	{
		{0,1,0,0},
		{0,1,1,0},
		{0,0,1,0},
		{0,0,0,0}
	}
};

enum Orientation
{
	UP,
	RIGHT,
	DOWN,
	LEFT
};

// Meant to point to the array of a certain piece in a certain orientation
typedef const int (*PieceArray)[4][4];

// Meant to point to all of the array of all of the orientations of a certain piece
typedef const int (*PieceTypeArray)[4][4][4];

PieceTypeArray GetArrayPointerBy(SpaceType type);


class PlayerPiece
{
	int mX, mY;                       // The coordinates of the piece
	PieceArray mArray;

	SpaceType mPieceType;
	BoardState * mBoardState;
	Orientation  mOrientation;

	bool IsValidMove(int x_change, int y_change,PieceArray array_ptr);

	/* This function returns true only if all of the parts of the piece are visible -- added to prevent DropOne()
	 * returning 'false' when a piece has been moved using Move*() while it wasn't completely visible ( IsValidMove()
	 * retardedly skips over those lines -- this way a piece can be accidentally half off the board leading to a game
	 * over condition.)
	 */
	bool IsPieceVisible();
	void ShiftPiece(int x, int y);

	PlayerPiece(const PlayerPiece & other);
	PlayerPiece & operator=(const PlayerPiece & other);

	bool IsValidCoordinate(int x, int y);
public:
	PlayerPiece(BoardState * state, SpaceType type = EMPTY);

	// That is, counter clockwise
	void RotateLeft();

	// That is, clockwise
	void RotateRight();

	void MoveLeft();
	void MoveRight();

	// returns "false" if the piece is unable to drop anymore -- this'll cause the piece to "stick"
	// and spawn the next piece.
	bool DropOne();

	// For when we want to drop all the way down...
	void DropCompletely();

	PieceArray GetPieceArray() const;
	SpaceType GetPieceType() const;
	int GetX() const;
	int GetY() const;
};