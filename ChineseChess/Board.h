#pragma once
#include "Header.h"
#include "Chess.h"
class Board
{
public:
	static vector<Chess*> onBoard;
	static int board[9][10];
	static int move[9][10];
	static void pushIn(Chess*);
	static void printBoard();
	static void resetBoard();
	static void clearMove();
	static void printMove();
	static Chess* RKing;
	static Chess* BKing;
};

