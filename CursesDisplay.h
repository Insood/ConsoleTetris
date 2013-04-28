#pragma once
#include "GenericDisplay.h"

class CursesDisplay : public GenericDisplay
{
	bool CheckScreen();

	void DrawBorder();
	void DrawText();
	void DrawBricks();
	void DrawBrick(int x, int y, SpaceType brick);

	void DrawPlayerPiece();
	void DrawNext();
	void DrawGameOver();

	WINDOW * GameWindow;
	WINDOW * ScoreWindow;
	WINDOW * NextWindow;
public:
	CursesDisplay(Game * game, BoardState * state);
	~CursesDisplay();

	void Draw();
};