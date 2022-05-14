#pragma once
#include "Header.h"
#include "Chess.h"
class Board
{
public:
	static vector<Chess*> onBoard;
	static int board[9][10];
	static void pushIn(Chess*);
	
};

