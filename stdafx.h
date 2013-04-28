#pragma once

#include <boost/thread.hpp>
#include <boost/ref.hpp>
#include <vector>
#include <string>
#include <curses.h>
#include <sstream>
#include <iostream>
#include <queue>
#include <cmath>

#ifndef __MSCVER
	#pragma comment(lib, "pdcurses.lib")
#endif