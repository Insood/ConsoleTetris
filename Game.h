#pragma once
#include "BoardState.h"
#include "CursesInputPump.h"
#include "CursesDisplay.h"

class GenericInputPump;
class GenericDisplay;
class PlayerPiece;
class BoardState;

const int DEFAULT_GAME_SPEED = 10;

class Game
{
	BoardState       * mBoardState;
	GenericInputPump * mInput;
	GenericDisplay   * mDisplay;

	bool       mRunning;
	
	bool       mInProgress;

	int        mGameSpeed;
	int        mScore;
	int        mLevel;
	int        mLines;

	void ProcessInput();
	void ProcessGameInput(InputType input);
	void SleepTwentyMS();

	std::queue<SpaceType> mPieces; // always keep 5 in here, if possible..

	void UpdatePieceQueue();

	void RestartGame();
public:
	Game();
	
	void Initialize();

	~Game();
	void operator()(void); // game thread entry point.

	SpaceType WhatIsNextPiece() const ;

	// Pops off the next piece from the queue..
	SpaceType AdvanceToNextPiece();

	void FlagAsGameOver();
	bool IsGameInProgress() const;

	static SpaceType GenerateRandomPiece();

	void AddRemovedLines(int lines);

	inline int GetScore() const { return mScore; }
	inline int GetLevel() const { return mLevel; }
	inline int GetLines() const { return mLines; }
};