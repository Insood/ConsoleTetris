#include "stdafx.h"
#include "BoardState.h"

BoardState::BoardState(Game * game) : mBoard(20,10), mAccumulatedDrop(0), mGame(game), mCurrentPiece(0)
{
	//mCurrentPiece = new PlayerPiece(REGULAR_L, this);
}

BoardState::~BoardState()
{
	delete mCurrentPiece;
}

void BoardState::Drop(int game_speed)
{
	mAccumulatedDrop += game_speed;
	while (mAccumulatedDrop > 200)
	{
		mAccumulatedDrop -= 200;
		DoDrop();
	}
}

void BoardState::DoDrop()
{
	if( !mCurrentPiece->DropOne() )
	{
		if( AddCurrentPieceToBoard() )
		{
			SpawnNewPiece();
		}
		else
		{
			GameLost();
		}
	}
}

void BoardState::GameLost()
{
	mGame->FlagAsGameOver();
}

void BoardState::SpawnNewPiece()
{
	SpaceType next_piece = mGame->AdvanceToNextPiece();

	/* ugh, wasteful */
	delete mCurrentPiece;
	mCurrentPiece = new PlayerPiece(this,next_piece);
}

bool BoardState::AddCurrentPieceToBoard()
{
	int x = mCurrentPiece->GetX();
	int y = mCurrentPiece->GetY();
	PieceArray arr = mCurrentPiece->GetPieceArray();
	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j<4; j++)
		{
			if( !(*arr)[i][j] )
				continue;

			if( (x+i) < 0)
				return false;

			mBoard.SetData( x+i, y+j, mCurrentPiece->GetPieceType());
		}
	}
	return true;
}

void BoardState::Update(int game_speed)
{
	Drop(game_speed);
	RemoveLines();
}

const TetrisMatrix & BoardState::GetBoard() const
{
	return mBoard;
}

const PlayerPiece & BoardState::GetPlayerPiece() const
{
	return *mCurrentPiece;
}

void BoardState::InitializeBoard()
{
	delete mCurrentPiece;

	mCurrentPiece = new PlayerPiece(this);
	mBoard.Clear();
}

void BoardState::DealWithInput(InputType type)
{
	switch(type)
	{
	case DROP_ALL:mCurrentPiece->DropCompletely(); break;
	case DROP_SOME:mCurrentPiece->DropOne(); break;
	case MOVE_LEFT: mCurrentPiece->MoveLeft(); break;
	case MOVE_RIGHT: mCurrentPiece->MoveRight(); break;
	case ROTATE_LEFT: mCurrentPiece->RotateLeft(); break;
	case ROTATE_RIGHT: mCurrentPiece->RotateRight(); break;
	}
}

void BoardState::RemoveLines()
{
	int lines_removed = 0;

	for(int row = 19; row > -1 ; row--)
	{
		bool found_empty = false;
		for(int col = 0; col<10; col++)
		{
			if( mBoard.GetData( row, col ) == EMPTY)
				found_empty = true;
		}

		if( !found_empty )
		{
			ShiftRowDown(row - 1);
			lines_removed += 1;
		}
	}

	if( lines_removed)
		mGame->AddRemovedLines(lines_removed);
}

// Oh shi- recursion?
void BoardState::ShiftRowDown(int row)
{
	if( row < 0 )
	{	
		for(int col = 0; col < 10; col++)
		{
			mBoard.SetData(0, col, EMPTY);
		}
		return;
	}

	for(int col = 0; col < 10; col++)
	{
		mBoard.SetData(row+1, col, mBoard.GetData(row, col));
	}

	// tail end recursion or something? hmm
	return ShiftRowDown( row - 1 );
}