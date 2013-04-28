#include "stdafx.h"
#include "Pieces.h"

// Newly created pieces will have negative x coordinates of being "above" the board.
// The coordinates will be such that the piece is higher than it is wide --
//    56  56  56  56  56
// -4 X   
// -3 X   @    0       Z
// -2 X   @    0  NN  ZZ
// -1 X   @@  00  NN   Z
// ----------------------------- invisible boundry
// 0                             actual game booard c_c
// The piece will be spawned roughly in the middle of the board..

PieceTypeArray GetArrayPointerBy(SpaceType type)
{
	PieceTypeArray arr = 0;

	switch(type)
	{
	case LONG_PIECE: arr = &LongArray; break;
	case REGULAR_L : arr = &RegularArray; break;
	case REVERSE_L : arr = &ReverseArray; break;
	case SQUARE    : arr = &SquareArray; break;
	case T_SHAPE   : arr = &TArray; break;
	case S_SHAPE   : arr = &SArray; break;
	case Z_SHAPE   : arr = &ZArray; break;
	}

	return arr;
}

PlayerPiece::PlayerPiece(BoardState * state, SpaceType type) : mPieceType(type), mBoardState(state), mOrientation(UP)
{
	mX= -4;
	mY = 2;

	if(type == EMPTY)
	{
		type = Game::GenerateRandomPiece();
	}

	switch(type)
	{                                        
	case LONG_PIECE: mArray = &LongArray[0]; break;                   
	case REGULAR_L:  mArray = &RegularArray[0]; break;
	case REVERSE_L:  mArray = &ReverseArray[0]; break;
	case SQUARE:     mArray = &SquareArray[0]; break;
	case T_SHAPE:    mArray = &TArray[0]; break;
	case S_SHAPE:    mArray = &SArray[0]; break;
	case Z_SHAPE:    mArray = &ZArray[0]; break;
	}
}

bool PlayerPiece::DropOne()
{
	if( IsValidMove(1,0,mArray) ) // if we can move down one ....
	{
		ShiftPiece(1,0);
		return true;
	}
	else
		return false;
}

void PlayerPiece::MoveLeft()
{
	if( IsValidMove(0,-1,mArray) && IsPieceVisible() )
		ShiftPiece(0,-1);
}

void PlayerPiece::MoveRight()
{
	if( IsValidMove(0,1,mArray) && IsPieceVisible() )
		ShiftPiece(0,1);
}

bool PlayerPiece::IsPieceVisible()
{
	for(int i = 0; i<4; i++)
	{
		for(int j =0; j<4;j++)
		{
			if( !(*mArray)[i][j] ) // is empty space..?
				continue;

			if( (mX+i) < 0)
				return false;
		}
	}
	return true;
}

// Aren't array pointers exciting?
void PlayerPiece::RotateLeft()
{
	PieceTypeArray arr = GetArrayPointerBy(mPieceType);
	PieceArray new_orient_arr;
	Orientation new_orient;

	switch(mOrientation)
	{
	case UP:     new_orient_arr = &(*arr)[3]; new_orient = LEFT;  break;
	case RIGHT:  new_orient_arr = &(*arr)[0]; new_orient = UP;    break;
	case DOWN:   new_orient_arr = &(*arr)[1]; new_orient = RIGHT; break;
	case LEFT:   new_orient_arr = &(*arr)[2]; new_orient = DOWN;  break;
	}

	if( !IsValidMove(0,0,new_orient_arr) )
		return;

	mArray = new_orient_arr;
	mOrientation = new_orient;
}

void PlayerPiece::RotateRight()
{
	PieceTypeArray arr = GetArrayPointerBy(mPieceType);
	PieceArray new_orient_arr;
	Orientation new_orient;

	switch(mOrientation)
	{
	case UP:     new_orient_arr = &(*arr)[1]; new_orient = RIGHT; break;
	case RIGHT:  new_orient_arr = &(*arr)[2]; new_orient = DOWN;  break;
	case DOWN:   new_orient_arr = &(*arr)[3]; new_orient = LEFT;  break;
	case LEFT:   new_orient_arr = &(*arr)[0]; new_orient = UP;    break;
	}

	if( !IsValidMove(0,0, new_orient_arr) )
		return;

	mArray = new_orient_arr;
	mOrientation = new_orient;
}

bool PlayerPiece::IsValidMove(int x_change, int y_change, PieceArray array_ptr)
{
	int x = mX + x_change; // temp variables for the new position of the bitmap..
	int y = mY + y_change;
	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j <4; j++)
		{
			if( !(*array_ptr)[i][j]) // we have a totally blank space in our "bitmap"
				continue;
			
			if( (x+i)< 0 ) // checking for a space above the board
				continue;

			if( !IsValidCoordinate( x+i, y+j))
				return false;
		}
	}

	return true;
}

bool PlayerPiece::IsValidCoordinate(int x, int y)
{
	if( (x < 0) || (x>19) || (y<0) || (y>9)  || (mBoardState->GetBoard().GetData(x,y) != EMPTY))
		return false;
	else
		return true;
}

void PlayerPiece::ShiftPiece(int d_x, int d_y)
{
	mX += d_x;
	mY += d_y;
}

void PlayerPiece::DropCompletely()
{
	while( DropOne() ) // keep dropping until we hit bottom or something.
		 ;
}

PieceArray PlayerPiece::GetPieceArray() const
{
	return mArray;
}

int PlayerPiece::GetX() const
{
	return mX;
}

int PlayerPiece::GetY() const
{
	return mY;
}

SpaceType PlayerPiece::GetPieceType() const 
{
	return mPieceType;
}