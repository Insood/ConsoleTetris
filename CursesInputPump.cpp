#include "stdafx.h"
#include "CursesInputPump.h"

CursesInputPump::CursesInputPump()
{
	keypad(stdscr,true);
	nodelay(stdscr,true);
	noecho();
}

CursesInputPump::~CursesInputPump()
{
}

InputType CursesInputPump::GetInput()
{
	int input = getch();
	switch(input)
	{
	case ERR:       return NONE;
	case KEY_CLOSE: return EXIT_GAME; // escape key, I think o_O?
	case KEY_LEFT:  return MOVE_LEFT;
	case KEY_RIGHT: return MOVE_RIGHT;
	case KEY_DOWN:  return DROP_SOME;
	case KEY_UP:    return ROTATE_LEFT;
	case ' ':       return DROP_ALL;
	default:        return NON_GAME;
	}
}