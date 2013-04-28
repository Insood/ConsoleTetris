#pragma once

enum InputType
{
	NONE,
	EXIT_GAME,
	MOVE_LEFT,
	MOVE_RIGHT,
	ROTATE_LEFT,
	ROTATE_RIGHT,
	DROP_SOME,
	DROP_ALL,
	TOGGLE_PAUSE,
	NON_GAME
};

// Meant as a base-ish class 
class GenericInputPump
{

public:
	GenericInputPump(){ }
	virtual ~GenericInputPump(){ }
	virtual InputType GetInput() = 0;
};