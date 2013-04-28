#pragma once
#include "Matrix.h"
#include "Pieces.h"
#include "SpaceType.h"
#include "Game.h"
#include "GenericInputPump.h"

typedef Matrix<SpaceType> TetrisMatrix;

class PlayerPiece;
class Game;
 
class BoardState
{
	TetrisMatrix mBoard; // The game board >_>.. (0,0) is upper left, (9,19) is lower right

	Game * mGame;

	// Pieces will drop down whenever the accumulated drop reaches 200. With a speed of "1" and
	// 50 updates per second, I think that at level 1 that is a decent drop speed.
	// This accumulated drop will also be used to determine when the currently controlled piece,
	// if it resting on top of something, will "stick".
	int    mAccumulatedDrop;

	PlayerPiece * mCurrentPiece;

	// If the current piece coudln't be added in its entirety to the board, means that a part of it
	// is sticking up above the game board and so... you lose </3
	bool AddCurrentPieceToBoard();
	void GameLost();
	void SpawnNewPiece();

	// Moves everything down depending on the game speed...
	void Drop(int game_speed);
	void RemoveLines();
	void ShiftRowDown(int row);

	void DoDrop();
public:
	BoardState(Game * g);
	~BoardState();

	// Calls Drop and then forces whatever we're using to draw the board to be redrawn.
	void Update(int game_speed);

	// Yeah, ugly, but ... what can you do, eh? We gotta draw the board somehow.
	const TetrisMatrix & GetBoard() const;
	const PlayerPiece  & GetPlayerPiece() const;

	// Also takes clear of cleaning up, if there's anything to clean up.
	void InitializeBoard();

	void DealWithInput(InputType input);
};