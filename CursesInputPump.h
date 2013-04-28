#pragma once
#include "GenericInputPump.h"

class CursesInputPump : public GenericInputPump
{
public:
	CursesInputPump();
	~CursesInputPump();

	InputType GetInput();
};