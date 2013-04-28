#include "stdafx.h"
#include "CursesDisplay.h"

CursesDisplay::CursesDisplay(Game * game, BoardState * state) : GenericDisplay(game,state)
{
	initscr();
	start_color();

	if( CheckScreen() )
	{
 		GameWindow  = newwin(22,12, 0,  20); // 22x12 window (20x10 useable area) for the main tetris window. Sort of centered.
		ScoreWindow = newwin(7, 22, 0,  35); // 7x22 window (5x20 useable) for the score window.
		NextWindow  = newwin(5, 22, 10, 35);
	}
	else
	{
		std::cin.get(); // pause here to display the message about the too tiny of a screen..
	}

	init_pair(LONG_PIECE, COLOR_RED   , COLOR_BLACK);
	init_pair(REGULAR_L , COLOR_YELLOW, COLOR_BLACK);
	init_pair(REVERSE_L , COLOR_MAGENTA,COLOR_BLACK);
	init_pair(SQUARE    , COLOR_GREEN,  COLOR_BLACK);
	init_pair(T_SHAPE   , COLOR_CYAN,   COLOR_BLACK);
	init_pair(S_SHAPE   , COLOR_WHITE,  COLOR_BLACK); 
	init_pair(Z_SHAPE   , COLOR_BLUE,   COLOR_BLACK);
}

CursesDisplay::~CursesDisplay()
{
	delwin(GameWindow);
	delwin(ScoreWindow);
	delwin(NextWindow);
	endwin();
}


bool CursesDisplay::CheckScreen()
{

	int row, col;
	getmaxyx(stdscr, row, col);
	if( (row < 24) || (col < 50) )
	{
		std::stringstream ss;
		ss<<"Your screen is too damn small -- try enlarging it. Currently: ";
		ss<<row<<" rows by "<<col<<" columns. Needs to be at least 24x50.";
		printw(ss.str().c_str());
		return false;
	}
	return true;
}


//          +----------+   +---------------+
//          |          |   |GhettoTetris   |
//          |          |   |               |
//          |          |   |Level:         |             
//		    |          |   |               |
//		    |          |   |Score:         |
//		    |          |   +---------------+
//		    |          |
//		    |          |   +---------------+
//		    |          |   |Next Piece:    |
//		    |          |   |               |
//		    |          |   |               |
//		    |          |   +---------------+
//		    |          |
//		    |          |
//		    |          |
//		    |          |
//		    |          |
//		    |          |
//          |          |
//          |          |
//          +----------+


void CursesDisplay::Draw()
{
	wclear(GameWindow);
	wclear(ScoreWindow);
	wclear(NextWindow);
	
	DrawBorder();
	DrawText();

	if( mGame->IsGameInProgress() )
	{
		DrawBricks();
		DrawPlayerPiece();
		DrawNext();
	}
	else
		DrawGameOver();

	wrefresh(GameWindow);
	wrefresh(ScoreWindow);
	wrefresh(NextWindow);
}

void CursesDisplay::DrawBorder()
{
	box(GameWindow,  0, 0);
	box(ScoreWindow, 0, 0);
	box(NextWindow,  0, 0);

}

void CursesDisplay::DrawText()
{
	mvwaddstr(ScoreWindow, 1, 1, "Ghetto Tetris");

	std::stringstream ss;
	ss<<"Score :"<< mGame->GetScore();
	mvwaddstr(ScoreWindow, 2, 1, ss.str().c_str());

	ss.str("");
	ss<<"Level :"<<mGame->GetLevel();
	mvwaddstr(ScoreWindow, 3, 1, ss.str().c_str());

	ss.str("");
	ss<<"Lines: "<<mGame->GetLines();
	mvwaddstr(ScoreWindow, 4, 1, ss.str().c_str());	
}

void CursesDisplay::DrawBricks()
{
	const TetrisMatrix & matrix = mBoardState->GetBoard();
	int x = matrix.GetX();
	int y = matrix.GetY();
	for(int i = 0; i < x; i++)
	{
		for(int j = 0; j < y; j++)
		{
			DrawBrick(i,j, matrix.GetData(i,j) );
		}
	}
}

void CursesDisplay::DrawBrick(int x, int y, SpaceType brick)
{
	wmove(GameWindow, x+1, y+1);
	chtype ch;
	/*
	switch(brick)
	{
	case EMPTY: break;
	case LONG_PIECE: waddch(GameWindow, 'X'); break;
	case REGULAR_L:  waddch(GameWindow, '@'); break;
	case REVERSE_L:  waddch(GameWindow, '0'); break;
	case SQUARE:     waddch(GameWindow, 'N'); break;
	case T_SHAPE:    waddch(GameWindow, 'Z'); break;
	case S_SHAPE:    waddch(GameWindow, 'Q'); break;
	case Z_SHAPE:    waddch(GameWindow, '#'); break;
	}*/

	switch(brick)
	{
	case EMPTY: return; 
	case LONG_PIECE: ch = 'X'; break;
	case REGULAR_L:  ch = '@'; break;
	case REVERSE_L:  ch = '0'; break;
	case SQUARE:     ch = 'N'; break;
	case T_SHAPE:    ch = 'Z'; break;
	case S_SHAPE:    ch = 'Q'; break;
	case Z_SHAPE:    ch = '#'; break;
	}
	ch |= COLOR_PAIR(brick) | A_BOLD;
	waddch(GameWindow, ch);
}

void CursesDisplay::DrawPlayerPiece()
{
	PieceArray arr = mBoardState->GetPlayerPiece().GetPieceArray();

	int x = mBoardState->GetPlayerPiece().GetX();
	int y = mBoardState->GetPlayerPiece().GetY();

	SpaceType type = mBoardState->GetPlayerPiece().GetPieceType();

	for(int i = 0; i<4; i++)
	{
		if( (x+i) < 0)
			continue;

		for(int j = 0; j<4; j++)
		{
			if( !(*arr)[i][j] )
				continue;
			else
				DrawBrick( x+i, y+j, type);
		}
	}
}

void CursesDisplay::DrawGameOver()
{
	                          //|1234567890|
	mvwaddstr(GameWindow, 10,1, "Game Over ");
	mvwaddstr(GameWindow, 11,1, "  Score   ");
	
	std::stringstream ss;
	ss<<mGame->GetScore();
	mvwaddstr(GameWindow, 13,1, ss.str().c_str());

	mvwaddstr(GameWindow, 15,1, " Push any ");
	mvwaddstr(GameWindow, 16,1, "  key to  ");
	mvwaddstr(GameWindow, 17,1, "play again");

}

void CursesDisplay::DrawNext()
{
	mvwaddstr(NextWindow, 1,1, "Next piece: ");
	SpaceType type = mGame->WhatIsNextPiece();
	
	wattron(NextWindow, COLOR_PAIR(type) | A_BOLD);
	switch(type)
	{
	case LONG_PIECE: mvwaddstr(NextWindow, 2,5, "XXXX"); break;
	case REGULAR_L:  mvwaddstr(NextWindow, 2,5, "  @ ");
		             mvwaddstr(NextWindow, 3,5, "@@@ "); break;
	case REVERSE_L:  mvwaddstr(NextWindow, 2,5, "0   ");
		             mvwaddstr(NextWindow, 3,5, "000 "); break;
	case SQUARE   :  mvwaddstr(NextWindow, 2,5, " NN "); 
					 mvwaddstr(NextWindow, 3,5, " NN "); break;
	case T_SHAPE  :  mvwaddstr(NextWindow, 2,5, "ZZZ ");
		             mvwaddstr(NextWindow, 3,5, " Z  "); break;
	case S_SHAPE  :  mvwaddstr(NextWindow, 2,5, " QQ ");
		             mvwaddstr(NextWindow, 3,5, "QQ  "); break;
	case Z_SHAPE   : mvwaddstr(NextWindow, 2,5, "##  ");
					 mvwaddstr(NextWindow, 3,5, " ## "); break;

	}
	wattroff(NextWindow, COLOR_PAIR(type) | A_BOLD);
}