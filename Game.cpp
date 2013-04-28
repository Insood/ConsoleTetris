#include "stdafx.h"
#include "Game.h"

Game::Game() : mRunning(true), mScore(0), mLevel(1), mLines(0), mGameSpeed(DEFAULT_GAME_SPEED), mInProgress(true)
{
}

Game::~Game()
{
	delete mDisplay;
	delete mInput;
	delete mBoardState;
}

void Game::Initialize()
{
	mBoardState = new BoardState(this);
	mBoardState->InitializeBoard();
	mDisplay = new CursesDisplay(this, mBoardState);
	mInput = new CursesInputPump;
}

void Game::ProcessInput()
{
	InputType input = mInput->GetInput();

	if( input == NONE)
		return;

	if( input == EXIT_GAME)
		mRunning = false;

	if( IsGameInProgress() )
		ProcessGameInput(input);
	else
		RestartGame();
}
 
void Game::ProcessGameInput(InputType input)
{
	if(input == NON_GAME)
		return;
	
	mBoardState->DealWithInput(input);
}

void Game::RestartGame()
{
	mScore = 0;
	mLevel = 1;
	mLines = 0;
	mGameSpeed = mLevel * DEFAULT_GAME_SPEED;
	mInProgress = true;
	mBoardState->InitializeBoard();
}

void Game::operator()(void)
{
	while(mRunning)
	{
		UpdatePieceQueue();
		ProcessInput();
		mBoardState->Update(mGameSpeed);
		mDisplay->Draw();
		
		SleepTwentyMS(); // Going for 50 updates per second here.
	}
}

void Game::SleepTwentyMS()
{
		boost::xtime time;
		boost::xtime_get(&time, boost::TIME_UTC);
		time.nsec += 20000000;
		boost::thread::sleep(time);
}

SpaceType Game::GenerateRandomPiece()
{
	int piece = rand() % 7;
	SpaceType next = EMPTY;

	switch(piece)
	{
	case 0: next = LONG_PIECE; break;
	case 1: next = REGULAR_L; break;
	case 2: next = REVERSE_L; break;
	case 3: next = SQUARE; break;
	case 4: next = T_SHAPE; break;
	case 5: next = S_SHAPE; break;
	case 6: next = Z_SHAPE; break;
	}

	return next;
}

void Game::UpdatePieceQueue()
{
	while( mPieces.size() < 5)
	{
		mPieces.push( GenerateRandomPiece() );
	}
}

SpaceType Game::WhatIsNextPiece() const
{
	return mPieces.front();
}

SpaceType Game::AdvanceToNextPiece()
{
	SpaceType return_value = mPieces.front();
	mPieces.pop();
	return return_value;
}

void Game::FlagAsGameOver()
{
	mInProgress = false;
}

bool Game::IsGameInProgress() const
{
	return mInProgress;
}

void Game::AddRemovedLines(int lines)
{
	mLines += lines;
	mScore += ( ( pow( (lines*100), 1.6) * mLevel) );

	if( mLines > (mLevel * 20 * 1.6) )
		mLevel++;

	mGameSpeed = DEFAULT_GAME_SPEED * mLevel;
}