#include "Board.h"

vector<Chess*> Board::onBoard;
int Board::board[9][10] = { };

void Board::pushIn(Chess* ch)
{
	Board::onBoard.push_back(ch);
	Board::board[ch->getX()][ch->getY()] = 1;
}
