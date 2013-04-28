#pragma once
#include "BoardState.h"
#include "Game.h"

class Game;
class BoardState;

class GenericDisplay
{
protected:
	BoardState * mBoardState; // mBoardState declared elsewhere -- used when updating to display stuff.
	Game       * mGame;       // mGame is likewise declared elsewhere/
public:
	GenericDisplay(Game * game, BoardState * state) : mGame(game), mBoardState(state){ }
	virtual ~GenericDisplay(){ }
	virtual void Draw() = 0;

};