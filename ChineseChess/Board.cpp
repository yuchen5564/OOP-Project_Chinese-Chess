#include "Board.h"

vector<Chess*> Board::onBoard;
int Board::board[9][10] = { };
int Board::move[9][10] = { };

void Board::pushIn(Chess* ch)
{
	Board::onBoard.push_back(ch);

    Board::board[ch->getX()][ch->getY()] = ch->color;
}

void Board::printBoard()
{
	for (int i = 0; i < 10; i++) {
		if (i == 5) cout << "\n";
		for (int j = 0; j < 9; j++) {
            cout << board[j][i] << " ";
		}
		cout << endl;
	}
	cout << "------------------------------\n";
}


void Board::clearMove()
{
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 10; j++) {
			Board::move[i][j] = 0;
		}
	}
}

void Board::printMove()
{
	for (int i = 0; i < 10; i++) {
		if (i == 5) cout << "\n";
		for (int j = 0; j < 9; j++) {
			cout << move[j][i] << " ";
		}
		cout << endl;
	}
}
