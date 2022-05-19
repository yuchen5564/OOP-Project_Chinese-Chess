#include "Chess.h"
#include "Board.h"
#include "GameManager.h"
Chess::Chess()
{
    //name="Chess";
}

Chess::Chess(int x, int y, int col, string src)
{
    _x = x;
    _y = y;
    firstX = x;
    firstY = y;
    pic = src;
    color = col;
}

void Chess::move(int x, int y)
{
    //確定該點上沒有棋子
    /*if (Board::board[x][y] == 0) {
        Board::board[_x][_y] = 0;
        _x = x;
        _y = y;
        Board::board[x][y] = 2;

    }*/
    GameManager::currentPlayer++;
    Board::printBoard();
}

int Chess::getX() {
    return this->_x;
}

int Chess::getY() {
    return this->_y;
}

int Chess::getIndex()
{
    return this->index;
}

//0513 ADD 回復初始位置
void Chess::resetChess()
{
    //Board::board[_x][_y] = 0;
    _x = firstX;
    _y = firstY;
    Board::board[_x][_y] = color;
    alive = true;
}

void Chess::makeLog(int beforeX, int beforeY)
{
    //Player: 1, Action: Soldier (6, 6) -> (6, 5)
    string log;
    if (color == 1) {
        log = "Player: 1, Action: ";
    }
    else {
        log = "Player: 2, Action: ";
    }
    log = log + name + " (" + to_string(beforeX) +
        ", " + to_string(beforeY) + ") -> (" + to_string(_x) + ", " + to_string(_y) + ")\n";
    GameManager::writeLog(log);
}

void Chess::canMove(int show)
{

    Board::clearMove();
    if (_x - 1 >= 0) Board::move[_x - 1][_y] = 1;
    if (_x + 1 <= 8) Board::move[_x + 1][_y] = 1;
    if (_y - 1 >= 0) Board::move[_x][_y - 1] = 1;
    if (_y + 1 <= 9) Board::move[_x][_y + 1] = 1;

}

string Chess::getPic()
{
    return pic;
}

King::King(int x, int y, int col, string src)
{
    _x = x;
    _y = y;
    firstX = x;
    firstY = y;
    pic = src;
    color = col;
    name = "King";
}
void King::move(int x, int y)
{
    if (Board::move[x][y] == 1)
    {
        Board::board[_x][_y] = 0;
        _x = x;
        _y = y;
        if (color == 1)
            Board::board[x][y] = 1;
        else if (color == -1)
            Board::board[x][y] = -1;
        GameManager::currentPlayer++;

    }
    Board::printBoard();
    Board::clearMove();
}
void King::canMove(int show)
{
    int x, y;
    if (show == 0) // for 可移動位置顯示 by ming
    {
        if (color == 1)
        {
            x = Board::BKing->getX();
            y = Board::BKing->getY();
            // 帥跳將
            if (x == _x)
            {
                bool haveBlock = false;
                for (int i = y + 1; i < _y; i++)
                {
                    if (Board::board[x][i] != 0)
                    {
                        haveBlock = true;
                    }
                }
                if (!haveBlock)
                {
                    Board::move[x][y] = 1;
                }

            }

            if (_x - 1 >= 3/*&&_x-1==x&&_y==y*/ && Board::board[_x - 1][_y] != 1)
            {
                Board::move[_x - 1][_y] = 1;
                /* _x = x;
                 _y = y;
                 Board::board[x][y] = 1;
                 GameManager::currentPlayer++;*/
            }
            if (_x + 1 <= 5/*&&_x+1==x&&_y==y*/ && Board::board[_x + 1][_y] != 1)
            {
                Board::move[_x + 1][_y] = 1;
                /*Board::board[_x][_y] = 0;
                _x = x;
                _y = y;
                Board::board[x][y] = 1;
                GameManager::currentPlayer++;*/
            }
            if (_y - 1 >= 7/*&&_y-1==y&&_x==x*/ && Board::board[_x][_y - 1] != 1)
            {
                Board::move[_x][_y - 1] = 1;
                /*Board::board[_x][_y] = 0;
                _x = x;
                _y = y;
                Board::board[x][y] = 1;
                GameManager::currentPlayer++;*/
            }
            if (_y + 1 <= 9/*&&_y+1==y&&_x==x*/ && Board::board[_x][_y + 1] != 1)
            {
                Board::move[_x][_y + 1] = 1;
                /*Board::board[_x][_y] = 0;
                _x = x;
                _y = y;
                Board::board[x][y] = 1;
                GameManager::currentPlayer++;*/
            }
        }
        else if (color == -1/*&&Board::board[x][y]!=-1*/)
        {
            x = Board::RKing->getX();
            y = Board::RKing->getY();
            // 帥跳將
            if (x == _x)
            {
                bool haveBlock = false;
                for (int i = _y + 1; i < y; i++)
                {
                    if (Board::board[x][i] != 0)
                    {
                        haveBlock = true;
                    }
                }
                if (!haveBlock)
                {
                    Board::move[x][y] = 1;
                }

            }

            if (_x - 1 >= 3/*&&_x - 1==x&&_y==y*/ && Board::board[_x - 1][_y] != -1)
            {
                Board::move[_x - 1][_y] = 1;
                /*Board::board[_x][_y] = 0;
                _x = x;
                _y = y;
                Board::board[x][y] = -1;
                GameManager::currentPlayer++;*/
            }

            if (_x + 1 <= 5/*&&_x + 1==x&&_y==y*/ && Board::board[_x + 1][_y] != -1)
            {
                Board::move[_x + 1][_y] = 1;
                /*Board::board[_x][_y] = 0;
                _x = x;
                _y = y;
                Board::board[x][y] = -1;
                GameManager::currentPlayer++;*/
            }
            if (_y - 1 >= 0/*&&_y - 1==y&&_x==x*/ && Board::board[_x][_y - 1] != -1)
            {
                Board::move[_x][_y - 1] = 1;
                /*Board::board[_x][_y] = 0;
                _x = x;
                _y = y;
                Board::board[x][y] = -1;
                GameManager::currentPlayer++;*/
            }
            if (_y + 1 <= 2/*&&_y + 1==y&&_x==x*/ && Board::board[_x][_y + 1] != -1)
            {
                Board::move[_x][_y + 1] = 1;
                /*Board::board[_x][_y] = 0;
                _x = x;
                _y = y;
                Board::board[x][y] = -1;
                GameManager::currentPlayer++;*/
            }
        }
    }
    else // for 將軍提示判斷 by ming
    {
        if (color == 1)
        {
            if (_x - 1 >= 3/*&&_x-1==x&&_y==y*/ && Board::board[_x - 1][_y] != 1)
            {
                Board::virtualMove[_x - 1][_y] = 1;
                /* _x = x;
                 _y = y;
                 Board::board[x][y] = 1;
                 GameManager::currentPlayer++;*/
            }
            if (_x + 1 <= 5/*&&_x+1==x&&_y==y*/ && Board::board[_x + 1][_y] != 1)
            {
                Board::virtualMove[_x + 1][_y] = 1;
                /*Board::board[_x][_y] = 0;
                _x = x;
                _y = y;
                Board::board[x][y] = 1;
                GameManager::currentPlayer++;*/
            }
            if (_y - 1 >= 7/*&&_y-1==y&&_x==x*/ && Board::board[_x][_y - 1] != 1)
            {
                Board::virtualMove[_x][_y - 1] = 1;
                /*Board::board[_x][_y] = 0;
                _x = x;
                _y = y;
                Board::board[x][y] = 1;
                GameManager::currentPlayer++;*/
            }
            if (_y + 1 <= 9/*&&_y+1==y&&_x==x*/ && Board::board[_x][_y + 1] != 1)
            {
                Board::virtualMove[_x][_y + 1] = 1;
                /*Board::board[_x][_y] = 0;
                _x = x;
                _y = y;
                Board::board[x][y] = 1;
                GameManager::currentPlayer++;*/
            }
        }
        else if (color == -1/*&&Board::board[x][y]!=-1*/)
        {
            if (_x - 1 >= 3/*&&_x - 1==x&&_y==y*/ && Board::board[_x - 1][_y] != -1)
            {
                Board::virtualMove[_x - 1][_y] = 1;
                /*Board::board[_x][_y] = 0;
                _x = x;
                _y = y;
                Board::board[x][y] = -1;
                GameManager::currentPlayer++;*/
            }

            if (_x + 1 <= 5/*&&_x + 1==x&&_y==y*/ && Board::board[_x + 1][_y] != -1)
            {
                Board::virtualMove[_x + 1][_y] = 1;
                /*Board::board[_x][_y] = 0;
                _x = x;
                _y = y;
                Board::board[x][y] = -1;
                GameManager::currentPlayer++;*/
            }
            if (_y - 1 >= 0/*&&_y - 1==y&&_x==x*/ && Board::board[_x][_y - 1] != -1)
            {
                Board::virtualMove[_x][_y - 1] = 1;
                /*Board::board[_x][_y] = 0;
                _x = x;
                _y = y;
                Board::board[x][y] = -1;
                GameManager::currentPlayer++;*/
            }
            if (_y + 1 <= 2/*&&_y + 1==y&&_x==x*/ && Board::board[_x][_y + 1] != -1)
            {
                Board::virtualMove[_x][_y + 1] = 1;
                /*Board::board[_x][_y] = 0;
                _x = x;
                _y = y;
                Board::board[x][y] = -1;
                GameManager::currentPlayer++;*/
            }
        }

    }


}

void Advisor::move(int x, int y)
{
    if (Board::move[x][y] == 1)
    {
        Board::board[_x][_y] = 0;
        _x = x;
        _y = y;
        if (color == 1)
            Board::board[x][y] = 1;
        else if (color == -1)
            Board::board[x][y] = -1;
        GameManager::currentPlayer++;

    }
    Board::printBoard();
}
Advisor::Advisor(int x, int y, int col, string src)
{
    _x = x;
    _y = y;
    firstX = x;
    firstY = y;
    pic = src;
    color = col;
    name = "Advisor";
}
void Advisor::canMove(int show)
{
    if (show == 0)   // for 可移動位置顯示 by ming
    {
        if (color == 1/*&&Board::board[x][y]!=1*/)
        {
            if (_x - 1 >= 3 && _y - 1 >= 7/*&&_x - 1==x&&_y - 1 == y*/ && Board::board[_x - 1][_y - 1] != 1)
            {
                Board::move[_x - 1][_y - 1] = 1;
                /*Board::board[_x][_y] = 0;
                _x = x;
                _y = y;
                Board::board[x][y] = 1;
                GameManager::currentPlayer++;*/
            }

            if (_x + 1 <= 5 && _y - 1 >= 7/*&&_x + 1==x&&_y - 1 ==y*/ && Board::board[_x + 1][_y - 1] != 1)
            {
                Board::move[_x + 1][_y - 1] = 1;
                /*Board::board[_x][_y] = 0;
                _x = x;
                _y = y;
                Board::board[x][y] = 1;
                GameManager::currentPlayer++;*/
            }
            if (_x - 1 >= 3 && _y + 1 <= 9/*&&_x - 1==x&&_y +1 == y*/ && Board::board[_x - 1][_y + 1] != 1)
            {
                Board::move[_x - 1][_y + 1] = 1;
                /*Board::board[_x][_y] = 0;
                _x = x;
                _y = y;
                Board::board[x][y] = 1;
                GameManager::currentPlayer++;*/
            }
            if (_x + 1 <= 5 && _y + 1 <= 9/*&&_x + 1==x&&_y + 1 == y*/ && Board::board[_x + 1][_y + 1] != 1)
            {
                Board::move[_x + 1][_y + 1] = 1;
                /*Board::board[_x][_y] = 0;
                _x = x;
                _y = y;
                Board::board[x][y] = 1;
                GameManager::currentPlayer++;*/
            }
        }
        else if (color == -1/*&&Board::board[x][y]!=-1*/)
        {
            if (_x - 1 >= 3 && _y - 1 >= 0 && Board::board[_x - 1][_y - 1] != -1/*&&_x - 1==x&&_y - 1 == y*/)
            {
                Board::move[_x - 1][_y - 1] = 1;
                /*Board::board[_x][_y] = 0;
                _x = x;
                _y = y;
                Board::board[x][y] = -1;
                GameManager::currentPlayer++;*/
            }

            if (_x + 1 <= 5 && _y - 1 >= 0 && Board::board[_x + 1][_y - 1] != -1/*&&_x + 1==x&&_y - 1 ==y*/)
            {
                Board::move[_x + 1][_y - 1] = 1;
                /*Board::board[_x][_y] = 0;
                _x = x;
                _y = y;
                Board::board[x][y] = -1;
                GameManager::currentPlayer++;*/
            }
            if (_x - 1 >= 3 && _y + 1 <= 2 && Board::board[_x - 1][_y + 1] != -1/*&&_x - 1==x&&_y +1 == y*/)
            {
                Board::move[_x - 1][_y + 1] = 1;
                /*Board::board[_x][_y] = 0;
                _x = x;
                _y = y;
                Board::board[x][y] = -1;
                GameManager::currentPlayer++;*/
            }
            if (_x + 1 <= 5 && _y + 1 <= 2 && Board::board[_x + 1][_y + 1] != -1/*&&_x + 1==x&&_y + 1 == y*/)
            {
                Board::move[_x + 1][_y + 1] = 1;
                /*Board::board[_x][_y] = 0;
                _x = x;
                _y = y;
                Board::board[x][y] = -1;
                GameManager::currentPlayer++;*/
            }
        }
    }
    else // for 將軍提示判斷 by ming
    {
        if (color == 1/*&&Board::board[x][y]!=1*/)
        {
            if (_x - 1 >= 3 && _y - 1 >= 7/*&&_x - 1==x&&_y - 1 == y*/ && Board::board[_x - 1][_y - 1] != 1)
            {
                Board::virtualMove[_x - 1][_y - 1] = 1;
                /*Board::board[_x][_y] = 0;
                _x = x;
                _y = y;
                Board::board[x][y] = 1;
                GameManager::currentPlayer++;*/
            }

            if (_x + 1 <= 5 && _y - 1 >= 7/*&&_x + 1==x&&_y - 1 ==y*/ && Board::board[_x + 1][_y - 1] != 1)
            {
                Board::virtualMove[_x + 1][_y - 1] = 1;
                /*Board::board[_x][_y] = 0;
                _x = x;
                _y = y;
                Board::board[x][y] = 1;
                GameManager::currentPlayer++;*/
            }
            if (_x - 1 >= 3 && _y + 1 <= 9/*&&_x - 1==x&&_y +1 == y*/ && Board::board[_x - 1][_y + 1] != 1)
            {
                Board::virtualMove[_x - 1][_y + 1] = 1;
                /*Board::board[_x][_y] = 0;
                _x = x;
                _y = y;
                Board::board[x][y] = 1;
                GameManager::currentPlayer++;*/
            }
            if (_x + 1 <= 5 && _y + 1 <= 9/*&&_x + 1==x&&_y + 1 == y*/ && Board::board[_x + 1][_y + 1] != 1)
            {
                Board::virtualMove[_x + 1][_y + 1] = 1;
                /*Board::board[_x][_y] = 0;
                _x = x;
                _y = y;
                Board::board[x][y] = 1;
                GameManager::currentPlayer++;*/
            }
        }
        else if (color == -1/*&&Board::board[x][y]!=-1*/)
        {
            if (_x - 1 >= 3 && _y - 1 >= 0 && Board::board[_x - 1][_y - 1] != -1/*&&_x - 1==x&&_y - 1 == y*/)
            {
                Board::virtualMove[_x - 1][_y - 1] = 1;
                /*Board::board[_x][_y] = 0;
                _x = x;
                _y = y;
                Board::board[x][y] = -1;
                GameManager::currentPlayer++;*/
            }

            if (_x + 1 <= 5 && _y - 1 >= 0 && Board::board[_x + 1][_y - 1] != -1/*&&_x + 1==x&&_y - 1 ==y*/)
            {
                Board::virtualMove[_x + 1][_y - 1] = 1;
                /*Board::board[_x][_y] = 0;
                _x = x;
                _y = y;
                Board::board[x][y] = -1;
                GameManager::currentPlayer++;*/
            }
            if (_x - 1 >= 3 && _y + 1 <= 2 && Board::board[_x - 1][_y + 1] != -1/*&&_x - 1==x&&_y +1 == y*/)
            {
                Board::virtualMove[_x - 1][_y + 1] = 1;
                /*Board::board[_x][_y] = 0;
                _x = x;
                _y = y;
                Board::board[x][y] = -1;
                GameManager::currentPlayer++;*/
            }
            if (_x + 1 <= 5 && _y + 1 <= 2 && Board::board[_x + 1][_y + 1] != -1/*&&_x + 1==x&&_y + 1 == y*/)
            {
                Board::virtualMove[_x + 1][_y + 1] = 1;
                /*Board::board[_x][_y] = 0;
                _x = x;
                _y = y;
                Board::board[x][y] = -1;
                GameManager::currentPlayer++;*/
            }
        }
    }

    //Board::printBoard();
}

void Minister::move(int x, int y)
{
    if (Board::move[x][y] == 1)
    {
        Board::board[_x][_y] = 0;
        _x = x;
        _y = y;
        if (color == 1)
            Board::board[x][y] = 1;
        else if (color == -1)
            Board::board[x][y] = -1;
        GameManager::currentPlayer++;

    }
    Board::printBoard();
}
Minister::Minister(int x, int y, int col, string src)
{
    _x = x;
    _y = y;
    firstX = x;
    firstY = y;
    pic = src;
    color = col;
    name = "Minister";
}

void Minister::canMove(int show)
{
    if (show == 0)  // for 可移動位置顯示 by ming
    {
        if (color == 1/*&&Board::board[x][y]!=1*/)
        {
            if (_x - 2 >= 0 && _y - 2 >= 5/*&&_x - 2==x&&_y - 2 == y*/ && Board::board[_x - 1][_y - 1] == 0 && Board::board[_x - 2][_y - 2] != 1)
            {
                Board::move[_x - 2][_y - 2] = 1;
                /*Board::board[_x][_y] = 0;
                _x = x;
                _y = y;
                Board::board[x][y] = 1;
                GameManager::currentPlayer++;*/
            }

            if (_x + 2 <= 8 && _y - 2 >= 5/*&&_x + 2==x&&_y - 2 ==y*/ && Board::board[_x + 1][_y - 1] == 0 && Board::board[_x + 2][_y - 2] != 1)
            {
                Board::move[_x + 2][_y - 2] = 1;
                /*Board::board[_x][_y] = 0;
                _x = x;
                _y = y;
                Board::board[x][y] = 1;
                GameManager::currentPlayer++;*/
            }
            if (_x - 2 >= 0 && _y + 2 <= 9/*&&_x - 2==x&&_y +2 == y*/ && Board::board[_x - 1][_y + 1] == 0 && Board::board[_x - 2][_y + 2] != 1)
            {
                Board::move[_x - 2][_y + 2] = 1;
                /*Board::board[_x][_y] = 0;
                _x = x;
                _y = y;
                Board::board[x][y] = 1;
                GameManager::currentPlayer++;*/
            }
            if (_x + 2 <= 8 && _y + 2 <= 9/*&&_x + 2==x&&_y + 2 == y*/ && Board::board[_x + 1][_y + 1] == 0 && Board::board[_x + 2][_y + 2] != 1)
            {
                Board::move[_x + 2][_y + 2] = 1;
                /*Board::board[_x][_y] = 0;
                _x = x;
                _y = y;
                Board::board[x][y] = 1;
                GameManager::currentPlayer++;*/
            }
        }
        else if (color == -1/*&&Board::board[x][y]!=-1*/)
        {
            if (_x - 2 >= 0 && _y - 2 >= 0/*&&_x - 2==x&&_y - 2 == y*/ && Board::board[_x - 1][_y - 1] == 0 && Board::board[_x - 2][_y - 2] != -1)
            {
                Board::move[_x - 2][_y - 2] = 1;
                /*Board::board[_x][_y] = 0;
                _x = x;
                _y = y;
                Board::board[x][y] = -1;
                GameManager::currentPlayer++;*/
            }

            if (_x + 2 <= 8 && _y - 2 >= 0/*&&_x + 2==x&&_y - 2 ==y*/ && Board::board[_x + 1][_y - 1] == 0 && Board::board[_x + 2][_y - 2] != -1)
            {
                Board::move[_x + 2][_y - 2] = 1;
                /*Board::board[_x][_y] = 0;
                _x = x;
                _y = y;
                Board::board[x][y] = -1;
                GameManager::currentPlayer++;*/
            }
            if (_x - 2 >= 0 && _y + 2 <= 4/*&&_x - 2==x&&_y +2 == y*/ && Board::board[_x - 1][_y + 1] == 0 && Board::board[_x - 2][_y + 2] != -1)
            {
                Board::move[_x - 2][_y + 2] = 1;
                /*Board::board[_x][_y] = 0;
                _x = x;
                _y = y;
                Board::board[x][y] = -1;
                GameManager::currentPlayer++;*/
            }
            if (_x + 2 <= 8 && _y + 2 <= 4/*&&_x + 2==x&&_y + 2 == y*/ && Board::board[_x + 1][_y + 1] == 0 && Board::board[_x + 2][_y + 2] != -1)
            {
                Board::move[_x + 2][_y + 2] = 1;
                /*Board::board[_x][_y] = 0;
                _x = x;
                _y = y;
                Board::board[x][y] = -1;
                GameManager::currentPlayer++;*/
            }
        }
        //Board::printBoard();
    }
    else // for 將軍提示判斷 by ming
    {
        if (color == 1/*&&Board::board[x][y]!=1*/)
        {
            if (_x - 2 >= 0 && _y - 2 >= 5/*&&_x - 2==x&&_y - 2 == y*/ && Board::board[_x - 1][_y - 1] == 0 && Board::board[_x - 2][_y - 2] != 1)
            {
                Board::virtualMove[_x - 2][_y - 2] = 1;
                /*Board::board[_x][_y] = 0;
                _x = x;
                _y = y;
                Board::board[x][y] = 1;
                GameManager::currentPlayer++;*/
            }

            if (_x + 2 <= 8 && _y - 2 >= 5/*&&_x + 2==x&&_y - 2 ==y*/ && Board::board[_x + 1][_y - 1] == 0 && Board::board[_x + 2][_y - 2] != 1)
            {
                Board::virtualMove[_x + 2][_y - 2] = 1;
                /*Board::board[_x][_y] = 0;
                _x = x;
                _y = y;
                Board::board[x][y] = 1;
                GameManager::currentPlayer++;*/
            }
            if (_x - 2 >= 0 && _y + 2 <= 9/*&&_x - 2==x&&_y +2 == y*/ && Board::board[_x - 1][_y + 1] == 0 && Board::board[_x - 2][_y + 2] != 1)
            {
                Board::virtualMove[_x - 2][_y + 2] = 1;
                /*Board::board[_x][_y] = 0;
                _x = x;
                _y = y;
                Board::board[x][y] = 1;
                GameManager::currentPlayer++;*/
            }
            if (_x + 2 <= 8 && _y + 2 <= 9/*&&_x + 2==x&&_y + 2 == y*/ && Board::board[_x + 1][_y + 1] == 0 && Board::board[_x + 2][_y + 2] != 1)
            {
                Board::virtualMove[_x + 2][_y + 2] = 1;
                /*Board::board[_x][_y] = 0;
                _x = x;
                _y = y;
                Board::board[x][y] = 1;
                GameManager::currentPlayer++;*/
            }
        }
        else if (color == -1/*&&Board::board[x][y]!=-1*/)
        {
            if (_x - 2 >= 0 && _y - 2 >= 0/*&&_x - 2==x&&_y - 2 == y*/ && Board::board[_x - 1][_y - 1] == 0 && Board::board[_x - 2][_y - 2] != -1)
            {
                Board::virtualMove[_x - 2][_y - 2] = 1;
                /*Board::board[_x][_y] = 0;
                _x = x;
                _y = y;
                Board::board[x][y] = -1;
                GameManager::currentPlayer++;*/
            }

            if (_x + 2 <= 8 && _y - 2 >= 0/*&&_x + 2==x&&_y - 2 ==y*/ && Board::board[_x + 1][_y - 1] == 0 && Board::board[_x + 2][_y - 2] != -1)
            {
                Board::virtualMove[_x + 2][_y - 2] = 1;
                /*Board::board[_x][_y] = 0;
                _x = x;
                _y = y;
                Board::board[x][y] = -1;
                GameManager::currentPlayer++;*/
            }
            if (_x - 2 >= 0 && _y + 2 <= 4/*&&_x - 2==x&&_y +2 == y*/ && Board::board[_x - 1][_y + 1] == 0 && Board::board[_x - 2][_y + 2] != -1)
            {
                Board::virtualMove[_x - 2][_y + 2] = 1;
                /*Board::board[_x][_y] = 0;
                _x = x;
                _y = y;
                Board::board[x][y] = -1;
                GameManager::currentPlayer++;*/
            }
            if (_x + 2 <= 8 && _y + 2 <= 4/*&&_x + 2==x&&_y + 2 == y*/ && Board::board[_x + 1][_y + 1] == 0 && Board::board[_x + 2][_y + 2] != -1)
            {
                Board::virtualMove[_x + 2][_y + 2] = 1;
                /*Board::board[_x][_y] = 0;
                _x = x;
                _y = y;
                Board::board[x][y] = -1;
                GameManager::currentPlayer++;*/
            }
        }
        //Board::printBoard();
    }


}
Horse::Horse(int x, int y, int col, string src)
{
    _x = x;
    _y = y;
    firstX = x;
    firstY = y;
    pic = src;
    color = col;
    name = "Horse";
}
void Horse::move(int x, int y)
{
    if (Board::move[x][y] == 1)
    {
        Board::board[_x][_y] = 0;
        _x = x;
        _y = y;
        if (color == 1)
            Board::board[x][y] = 1;
        else if (color == -1)
            Board::board[x][y] = -1;
        GameManager::currentPlayer++;

    }
    Board::printBoard();
}
void Horse::canMove(int show)
{
    if (show == 0)  // for 可移動位置顯示 by ming  
    {
        if (color == 1/*&&Board::board[x][y]!=1*/)
        {
            if (_x - 2 >= 0 && _y - 1 >= 0/*&&_x - 2==x&&_y - 1 == y*/ && Board::board[_x - 1][_y] == 0 && Board::board[_x - 2][_y - 1] != 1)
            {
                Board::move[_x - 2][_y - 1] = 1;
                /*Board::board[_x][_y] = 0;
                _x = x;
                _y = y;
                Board::board[x][y] = 1;
                GameManager::currentPlayer++;*/
            }

            if (_x + 2 <= 8 && _y - 1 >= 0/*&&_x + 2==x&&_y - 1 ==y*/ && Board::board[_x + 1][_y] == 0 && Board::board[_x + 2][_y - 1] != 1)
            {
                Board::move[_x + 2][_y - 1] = 1;
                /*Board::board[_x][_y] = 0;
                _x = x;
                _y = y;
                Board::board[x][y] = 1;
                GameManager::currentPlayer++;*/
            }
            if (_x - 2 >= 0 && _y + 1 <= 9/*&&_x - 2==x&&_y + 1 == y*/ && Board::board[_x - 1][_y] == 0 && Board::board[_x - 2][_y + 1] != 1)
            {
                Board::move[_x - 2][_y + 1] = 1;
                /*Board::board[_x][_y] = 0;
                _x = x;
                _y = y;
                Board::board[x][y] = 1;
                GameManager::currentPlayer++;*/
            }
            if (_x + 2 <= 8 && _y + 1 <= 9/*&&_x + 2==x&&_y + 1 == y*/ && Board::board[_x + 1][_y] == 0 && Board::board[_x + 2][_y + 1] != 1)
            {
                Board::move[_x + 2][_y + 1] = 1;
                /*Board::board[_x][_y] = 0;
                _x = x;
                _y = y;
                Board::board[x][y] = 1;
                GameManager::currentPlayer++;*/
            }
            if (_x + 1 <= 8 && _y - 2 >= 0/*&&_x + 1==x&&_y - 2 == y*/ && Board::board[_x][_y - 1] == 0 && Board::board[_x + 1][_y - 2] != 1)
            {
                Board::move[_x + 1][_y - 2] = 1;
                /*Board::board[_x][_y] = 0;
                _x = x;
                _y = y;
                Board::board[x][y] = 1;
                GameManager::currentPlayer++;*/
            }
            if (_x + 1 <= 8 && _y + 2 <= 9/*&&_x + 1==x&&_y + 2 == y*/ && Board::board[_x][_y + 1] == 0 && Board::board[_x + 1][_y + 2] != 1)
            {
                Board::move[_x + 1][_y + 2] = 1;
                /*Board::board[_x][_y] = 0;
                _x = x;
                _y = y;
                Board::board[x][y] = 1;
                GameManager::currentPlayer++;*/
            }
            if (_x - 1 >= 0 && _y - 2 >= 0/*&&_x - 1==x&&_y - 2 == y*/ && Board::board[_x][_y - 1] == 0 && Board::board[_x - 1][_y - 2] != 1)
            {
                Board::move[_x - 1][_y - 2] = 1;
                /*Board::board[_x][_y] = 0;
                _x = x;
                _y = y;
                Board::board[x][y] = 1;
                GameManager::currentPlayer++;*/
            }
            if (_x - 1 >= 0 && _y + 2 <= 9/*&&_x - 1==x&&_y + 2 == y*/ && Board::board[_x][_y + 1] == 0 && Board::board[_x - 1][_y + 2] != 1)
            {
                Board::move[_x - 1][_y + 2] = 1;
                /*Board::board[_x][_y] = 0;
                _x = x;
                _y = y;
                Board::board[x][y] = 1;
                GameManager::currentPlayer++;*/
            }
        }
        else if (color == -1/*&&Board::board[x][y]!=-1*/)
        {
            if (_x - 2 >= 0 && _y - 1 >= 0/*&&_x - 2==x&&_y - 1 == y*/ && Board::board[_x - 1][_y] == 0 && Board::board[_x - 2][_y - 1] != -1)
            {
                Board::move[_x - 2][_y - 1] = 1;
                /*Board::board[_x][_y] = 0;
                _x = x;
                _y = y;
                Board::board[x][y] = -1;
                GameManager::currentPlayer++;*/
            }

            if (_x + 2 <= 8 && _y - 1 >= 0/*&&_x + 2==x&&_y - 1 ==y*/ && Board::board[_x + 1][_y] == 0 && Board::board[_x + 2][_y - 1] != -1)
            {
                Board::move[_x + 2][_y - 1] = 1;
                /*Board::board[_x][_y] = 0;
                _x = x;
                _y = y;
                Board::board[x][y] = -1;
                GameManager::currentPlayer++;*/
            }
            if (_x - 2 >= 0 && _y + 1 <= 9/*&&_x - 2==x&&_y + 1 == y*/ && Board::board[_x - 1][_y] == 0 && Board::board[_x - 2][_y + 1] != -1)
            {
                Board::move[_x - 2][_y + 1] = 1;
                /*Board::board[_x][_y] = 0;
                _x = x;
                _y = y;
                Board::board[x][y] = -1;
                GameManager::currentPlayer++;*/
            }
            if (_x + 2 <= 8 && _y + 1 <= 9/*&&_x + 2==x&&_y + 1 == y*/ && Board::board[_x + 1][_y] == 0 && Board::board[_x + 2][_y + 1] != -1)
            {
                Board::move[_x + 2][_y + 1] = 1;
                /*Board::board[_x][_y] = 0;
                _x = x;
                _y = y;
                Board::board[x][y] = -1;
                GameManager::currentPlayer++;*/
            }
            if (_x + 1 <= 8 && _y - 2 >= 0/*&&_x + 1==x&&_y - 2 == y*/ && Board::board[_x][_y - 1] == 0 && Board::board[_x + 1][_y - 2] != -1)
            {
                Board::move[_x + 1][_y - 2] = 1;
                /*Board::board[_x][_y] = 0;
                _x = x;
                _y = y;
                Board::board[x][y] = -1;
                GameManager::currentPlayer++;*/
            }
            if (_x + 1 <= 8 && _y + 2 <= 9/*&&_x + 1==x&&_y + 2 == y*/ && Board::board[_x][_y + 1] == 0 && Board::board[_x + 1][_y + 2] != -1)
            {
                Board::move[_x + 1][_y + 2] = 1;
                /*Board::board[_x][_y] = 0;
                _x = x;
                _y = y;
                Board::board[x][y] = -1;
                GameManager::currentPlayer++;*/
            }
            if (_x - 1 >= 0 && _y - 2 >= 0/*&&_x - 1==x&&_y - 2 == y*/ && Board::board[_x][_y - 1] == 0 && Board::board[_x - 1][_y - 2] != -1)
            {
                Board::move[_x - 1][_y - 2] = 1;
                /*Board::board[_x][_y] = 0;
                _x = x;
                _y = y;
                Board::board[x][y] = -1;
                GameManager::currentPlayer++;*/
            }
            if (_x - 1 >= 0 && _y + 2 <= 9/*&&_x - 1==x&&_y + 2 == y*/ && Board::board[_x][_y + 1] == 0 && Board::board[_x - 1][_y + 2] != -1)
            {
                Board::move[_x - 1][_y + 2] = 1;
                /*Board::board[_x][_y] = 0;
                _x = x;
                _y = y;
                Board::board[x][y] = -1;
                GameManager::currentPlayer++;*/
            }
        }
    }
    else // for 將軍提示判斷 by ming
    {
        if (color == 1/*&&Board::board[x][y]!=1*/)
        {
            if (_x - 2 >= 0 && _y - 1 >= 0/*&&_x - 2==x&&_y - 1 == y*/ && Board::board[_x - 1][_y] == 0 && Board::board[_x - 2][_y - 1] != 1)
            {
                Board::virtualMove[_x - 2][_y - 1] = 1;
                /*Board::board[_x][_y] = 0;
                _x = x;
                _y = y;
                Board::board[x][y] = 1;
                GameManager::currentPlayer++;*/
            }

            if (_x + 2 <= 8 && _y - 1 >= 0/*&&_x + 2==x&&_y - 1 ==y*/ && Board::board[_x + 1][_y] == 0 && Board::board[_x + 2][_y - 1] != 1)
            {
                Board::virtualMove[_x + 2][_y - 1] = 1;
                /*Board::board[_x][_y] = 0;
                _x = x;
                _y = y;
                Board::board[x][y] = 1;
                GameManager::currentPlayer++;*/
            }
            if (_x - 2 >= 0 && _y + 1 <= 9/*&&_x - 2==x&&_y + 1 == y*/ && Board::board[_x - 1][_y] == 0 && Board::board[_x - 2][_y + 1] != 1)
            {
                Board::virtualMove[_x - 2][_y + 1] = 1;
                /*Board::board[_x][_y] = 0;
                _x = x;
                _y = y;
                Board::board[x][y] = 1;
                GameManager::currentPlayer++;*/
            }
            if (_x + 2 <= 8 && _y + 1 <= 9/*&&_x + 2==x&&_y + 1 == y*/ && Board::board[_x + 1][_y] == 0 && Board::board[_x + 2][_y + 1] != 1)
            {
                Board::virtualMove[_x + 2][_y + 1] = 1;
                /*Board::board[_x][_y] = 0;
                _x = x;
                _y = y;
                Board::board[x][y] = 1;
                GameManager::currentPlayer++;*/
            }
            if (_x + 1 <= 8 && _y - 2 >= 0/*&&_x + 1==x&&_y - 2 == y*/ && Board::board[_x][_y - 1] == 0 && Board::board[_x + 1][_y - 2] != 1)
            {
                Board::virtualMove[_x + 1][_y - 2] = 1;
                /*Board::board[_x][_y] = 0;
                _x = x;
                _y = y;
                Board::board[x][y] = 1;
                GameManager::currentPlayer++;*/
            }
            if (_x + 1 <= 8 && _y + 2 <= 9/*&&_x + 1==x&&_y + 2 == y*/ && Board::board[_x][_y + 1] == 0 && Board::board[_x + 1][_y + 2] != 1)
            {
                Board::virtualMove[_x + 1][_y + 2] = 1;
                /*Board::board[_x][_y] = 0;
                _x = x;
                _y = y;
                Board::board[x][y] = 1;
                GameManager::currentPlayer++;*/
            }
            if (_x - 1 >= 0 && _y - 2 >= 0/*&&_x - 1==x&&_y - 2 == y*/ && Board::board[_x][_y - 1] == 0 && Board::board[_x - 1][_y - 2] != 1)
            {
                Board::virtualMove[_x - 1][_y - 2] = 1;
                /*Board::board[_x][_y] = 0;
                _x = x;
                _y = y;
                Board::board[x][y] = 1;
                GameManager::currentPlayer++;*/
            }
            if (_x - 1 >= 0 && _y + 2 <= 9/*&&_x - 1==x&&_y + 2 == y*/ && Board::board[_x][_y + 1] == 0 && Board::board[_x - 1][_y + 2] != 1)
            {
                Board::virtualMove[_x - 1][_y + 2] = 1;
                /*Board::board[_x][_y] = 0;
                _x = x;
                _y = y;
                Board::board[x][y] = 1;
                GameManager::currentPlayer++;*/
            }
        }
        else if (color == -1/*&&Board::board[x][y]!=-1*/)
        {
            if (_x - 2 >= 0 && _y - 1 >= 0/*&&_x - 2==x&&_y - 1 == y*/ && Board::board[_x - 1][_y] == 0 && Board::board[_x - 2][_y - 1] != -1)
            {
                Board::virtualMove[_x - 2][_y - 1] = 1;
                /*Board::board[_x][_y] = 0;
                _x = x;
                _y = y;
                Board::board[x][y] = -1;
                GameManager::currentPlayer++;*/
            }

            if (_x + 2 <= 8 && _y - 1 >= 0/*&&_x + 2==x&&_y - 1 ==y*/ && Board::board[_x + 1][_y] == 0 && Board::board[_x + 2][_y - 1] != -1)
            {
                Board::virtualMove[_x + 2][_y - 1] = 1;
                /*Board::board[_x][_y] = 0;
                _x = x;
                _y = y;
                Board::board[x][y] = -1;
                GameManager::currentPlayer++;*/
            }
            if (_x - 2 >= 0 && _y + 1 <= 9/*&&_x - 2==x&&_y + 1 == y*/ && Board::board[_x - 1][_y] == 0 && Board::board[_x - 2][_y + 1] != -1)
            {
                Board::virtualMove[_x - 2][_y + 1] = 1;
                /*Board::board[_x][_y] = 0;
                _x = x;
                _y = y;
                Board::board[x][y] = -1;
                GameManager::currentPlayer++;*/
            }
            if (_x + 2 <= 8 && _y + 1 <= 9/*&&_x + 2==x&&_y + 1 == y*/ && Board::board[_x + 1][_y] == 0 && Board::board[_x + 2][_y + 1] != -1)
            {
                Board::virtualMove[_x + 2][_y + 1] = 1;
                /*Board::board[_x][_y] = 0;
                _x = x;
                _y = y;
                Board::board[x][y] = -1;
                GameManager::currentPlayer++;*/
            }
            if (_x + 1 <= 8 && _y - 2 >= 0/*&&_x + 1==x&&_y - 2 == y*/ && Board::board[_x][_y - 1] == 0 && Board::board[_x + 1][_y - 2] != -1)
            {
                Board::virtualMove[_x + 1][_y - 2] = 1;
                /*Board::board[_x][_y] = 0;
                _x = x;
                _y = y;
                Board::board[x][y] = -1;
                GameManager::currentPlayer++;*/
            }
            if (_x + 1 <= 8 && _y + 2 <= 9/*&&_x + 1==x&&_y + 2 == y*/ && Board::board[_x][_y + 1] == 0 && Board::board[_x + 1][_y + 2] != -1)
            {
                Board::virtualMove[_x + 1][_y + 2] = 1;
                /*Board::board[_x][_y] = 0;
                _x = x;
                _y = y;
                Board::board[x][y] = -1;
                GameManager::currentPlayer++;*/
            }
            if (_x - 1 >= 0 && _y - 2 >= 0/*&&_x - 1==x&&_y - 2 == y*/ && Board::board[_x][_y - 1] == 0 && Board::board[_x - 1][_y - 2] != -1)
            {
                Board::virtualMove[_x - 1][_y - 2] = 1;
                /*Board::board[_x][_y] = 0;
                _x = x;
                _y = y;
                Board::board[x][y] = -1;
                GameManager::currentPlayer++;*/
            }
            if (_x - 1 >= 0 && _y + 2 <= 9/*&&_x - 1==x&&_y + 2 == y*/ && Board::board[_x][_y + 1] == 0 && Board::board[_x - 1][_y + 2] != -1)
            {
                Board::virtualMove[_x - 1][_y + 2] = 1;
                /*Board::board[_x][_y] = 0;
                _x = x;
                _y = y;
                Board::board[x][y] = -1;
                GameManager::currentPlayer++;*/
            }
        }

    }
    //Board::printBoard();
}

Soldier::Soldier(int x, int y, int col, string src)
{
    _x = x;
    _y = y;
    firstX = x;
    firstY = y;
    pic = src;
    color = col;
    name = "Soldier";
}
void Soldier::move(int x, int y)
{
    if (Board::move[x][y] == 1)
    {
        Board::board[_x][_y] = 0;
        _x = x;
        _y = y;
        if (color == 1)
            Board::board[x][y] = 1;
        else if (color == -1)
            Board::board[x][y] = -1;
        GameManager::currentPlayer++;

    }
    Board::printBoard();
}
void Soldier::canMove(int show)
{
    if (show == 0) // for 可移動位置顯示 by ming  
    {
        if (color == 1/*&&Board::board[x][y]!=1*/)
        {
            if (_y >= 5)//尚未過河
            {
                if (_y - 1 >= 0/*&&_y - 1 == y&&_x==x*/ && Board::board[_x][_y - 1] != 1)
                {
                    Board::move[_x][_y - 1] = 1;
                    /*Board::board[_x][_y] = 0;
                    _x = x;
                    _y = y;
                    Board::board[x][y] = 1;
                    GameManager::currentPlayer++;*/
                }
            }
            else
            {
                if (_y - 1 >= 0/*&&_y - 1 == y&&_x==x*/ && Board::board[_x][_y - 1] != 1)
                {
                    Board::move[_x][_y - 1] = 1;
                    /*Board::board[_x][_y] = 0;
                    _x = x;
                    _y = y;
                    Board::board[x][y] = 1;
                    GameManager::currentPlayer++;*/
                }
                if (/*_y - 1 >= 0&&*/_x + 1 <= 8/*&&_y == y&&_x+1==x*/ && Board::board[_x + 1][_y] != 1)
                {
                    Board::move[_x + 1][_y] = 1;
                    /*Board::board[_x][_y] = 0;
                    _x = x;
                    _y = y;
                    Board::board[x][y] = 1;
                    GameManager::currentPlayer++;*/
                }
                if (/*_y == y&&_x-1==x*//*_y - 1 >= 0&&*/_x - 1 >= 0 && Board::board[_x - 1][_y] != 1)
                {
                    Board::move[_x - 1][_y] = 1;
                    /*Board::board[_x][_y] = 0;
                    _x = x;
                    _y = y;
                    Board::board[x][y] = 1;
                    GameManager::currentPlayer++;*/
                }
            }

        }
        else if (color == -1/*&&Board::board[x][y]!=-1*/)
        {
            if (_y <= 4)//尚未過河
            {
                if (_y + 1 >= 0/*&&_y + 1 == y&&_x==x*/ && Board::board[_x][_y + 1] != -1)
                {
                    Board::move[_x][_y + 1] = 1;
                    /*Board::board[_x][_y] = 0;
                    _x = x;
                    _y = y;
                    Board::board[x][y] = -1;
                    GameManager::currentPlayer++;*/
                }
            }
            else
            {
                if (_y + 1 >= 0/*&&_y + 1 == y&&_x==x*/ && Board::board[_x][_y + 1] != -1)
                {
                    Board::move[_x][_y + 1] = 1;
                    /*Board::board[_x][_y] = 0;
                    _x = x;
                    _y = y;
                    Board::board[x][y] = -1;
                    GameManager::currentPlayer++;*/
                }
                if (/*_x+1==x&&*/_x + 1 <= 8/*&&_y==y*/ && Board::board[_x + 1][_y] != -1)
                {
                    Board::move[_x + 1][_y] = 1;
                    /*Board::board[_x][_y] = 0;
                    _x = x;
                    _y = y;
                    Board::board[x][y] = -1;
                    GameManager::currentPlayer++;*/
                }
                if (/*_x-1==x&&*/_x - 1 >= 0/*&&_y==y*/ && Board::board[_x - 1][_y] != -1)
                {
                    Board::move[_x - 1][_y] = 1;
                    /*Board::board[_x][_y] = 0;
                    _x = x;
                    _y = y;
                    Board::board[x][y] = -1;
                    GameManager::currentPlayer++;*/
                }
            }
        }

    }
    else // for 將軍提示判斷 by ming
    {
        if (color == 1/*&&Board::board[x][y]!=1*/)
        {
            if (_y >= 5)//尚未過河
            {
                if (_y - 1 >= 0/*&&_y - 1 == y&&_x==x*/ && Board::board[_x][_y - 1] != 1)
                {
                    Board::virtualMove[_x][_y - 1] = 1;
                    /*Board::board[_x][_y] = 0;
                    _x = x;
                    _y = y;
                    Board::board[x][y] = 1;
                    GameManager::currentPlayer++;*/
                }
            }
            else
            {
                if (_y - 1 >= 0/*&&_y - 1 == y&&_x==x*/ && Board::board[_x][_y - 1] != 1)
                {
                    Board::virtualMove[_x][_y - 1] = 1;
                    /*Board::board[_x][_y] = 0;
                    _x = x;
                    _y = y;
                    Board::board[x][y] = 1;
                    GameManager::currentPlayer++;*/
                }
                if (/*_y - 1 >= 0&&*/_x + 1 <= 8/*&&_y == y&&_x+1==x*/ && Board::board[_x + 1][_y] != 1)
                {
                    Board::virtualMove[_x + 1][_y] = 1;
                    /*Board::board[_x][_y] = 0;
                    _x = x;
                    _y = y;
                    Board::board[x][y] = 1;
                    GameManager::currentPlayer++;*/
                }
                if (/*_y == y&&_x-1==x*//*_y - 1 >= 0&&*/_x - 1 >= 0 && Board::board[_x - 1][_y] != 1)
                {
                    Board::virtualMove[_x - 1][_y] = 1;
                    /*Board::board[_x][_y] = 0;
                    _x = x;
                    _y = y;
                    Board::board[x][y] = 1;
                    GameManager::currentPlayer++;*/
                }
            }

        }
        else if (color == -1/*&&Board::board[x][y]!=-1*/)
        {
            if (_y <= 4)//尚未過河
            {
                if (_y + 1 >= 0/*&&_y + 1 == y&&_x==x*/ && Board::board[_x][_y + 1] != -1)
                {
                    Board::virtualMove[_x][_y + 1] = 1;
                    /*Board::board[_x][_y] = 0;
                    _x = x;
                    _y = y;
                    Board::board[x][y] = -1;
                    GameManager::currentPlayer++;*/
                }
            }
            else
            {
                if (_y + 1 >= 0/*&&_y + 1 == y&&_x==x*/ && Board::board[_x][_y + 1] != -1)
                {
                    Board::virtualMove[_x][_y + 1] = 1;
                    /*Board::board[_x][_y] = 0;
                    _x = x;
                    _y = y;
                    Board::board[x][y] = -1;
                    GameManager::currentPlayer++;*/
                }
                if (/*_x+1==x&&*/_x + 1 <= 8/*&&_y==y*/ && Board::board[_x + 1][_y] != -1)
                {
                    Board::virtualMove[_x + 1][_y] = 1;
                    /*Board::board[_x][_y] = 0;
                    _x = x;
                    _y = y;
                    Board::board[x][y] = -1;
                    GameManager::currentPlayer++;*/
                }
                if (/*_x-1==x&&*/_x - 1 >= 0/*&&_y==y*/ && Board::board[_x - 1][_y] != -1)
                {
                    Board::virtualMove[_x - 1][_y] = 1;
                    /*Board::board[_x][_y] = 0;
                    _x = x;
                    _y = y;
                    Board::board[x][y] = -1;
                    GameManager::currentPlayer++;*/
                }
            }
        }

    }

    //  Board::printBoard();
}

Chariot::Chariot(int x, int y, int col, string src) // 車
{
    _x = x;
    _y = y;
    firstX = x;
    firstY = y;
    pic = src;
    color = col;
    name = "Chariot";
}
void Chariot::move(int x, int y)
{
    if (Board::move[x][y] == 1)
    {
        Board::board[_x][_y] = 0;
        _x = x;
        _y = y;
        if (color == 1)
            Board::board[x][y] = 1;
        else if (color == -1)
            Board::board[x][y] = -1;
        GameManager::currentPlayer++;

    }
    Board::printBoard();
}

void Chariot::canMove(int show)
{
    if (show == 0)  // for 可移動位置顯示 by ming
    {
        if (color == 1)
        {
            for (int x = 1; x <= 8; x++)//向右
            {
                if (_x + x <= 8 && Board::board[_x + x][_y] == 0)
                {
                    Board::move[_x + x][_y] = 1;
                }
                else  if (_x + x <= 8 && Board::board[_x + x][_y] == -1)
                {
                    Board::move[_x + x][_y] = 1;
                    break;
                }
                else  break;
            }
            for (int x = 1; x <= 8; x++)//向左
            {
                if (_x - x >= 0 && Board::board[_x - x][_y] == 0)
                {
                    Board::move[_x - x][_y] = 1;
                }
                else  if (_x - x >= 0 && Board::board[_x - x][_y] == -1)
                {
                    Board::move[_x - x][_y] = 1;
                    break;
                }
                else  break;
            }
            for (int x = 1; x <= 9; x++)
            {
                if (_y + x <= 9 && Board::board[_x][_y + x] == 0)
                {
                    Board::move[_x][_y + x] = 1;
                }
                else  if (_y + x <= 9 && Board::board[_x][_y + x] == -1)
                {
                    Board::move[_x][_y + x] = 1;
                    break;
                }
                else  break;
            }
            for (int x = 1; x <= 9; x++)
            {
                if (_y - x >= 0 && Board::board[_x][_y - x] == 0)
                {
                    Board::move[_x][_y - x] = 1;
                }
                else  if (_y - x >= 0 && Board::board[_x][_y - x] == -1)
                {
                    Board::move[_x][_y - x] = 1;
                    break;
                }
                else  break;
            }
        }
        else if (color == -1)
        {
            for (int x = 1; x <= 8; x++)//向右
            {
                if (_x + x <= 8 && Board::board[_x + x][_y] == 0)
                {
                    Board::move[_x + x][_y] = 1;
                }
                else  if (_x + x <= 8 && Board::board[_x + x][_y] == 1)
                {
                    Board::move[_x + x][_y] = 1;
                    break;
                }
                else  break;
            }
            for (int x = 1; x <= 8; x++)//向左
            {
                if (_x - x >= 0 && Board::board[_x - x][_y] == 0)
                {
                    Board::move[_x - x][_y] = 1;
                }
                else  if (_x - x >= 0 && Board::board[_x - x][_y] == 1)
                {
                    Board::move[_x - x][_y] = 1;
                    break;
                }
                else  break;
            }
            for (int x = 1; x <= 9; x++)
            {
                if (_y + x <= 9 && Board::board[_x][_y + x] == 0)
                {
                    Board::move[_x][_y + x] = 1;
                }
                else  if (_y + x <= 9 && Board::board[_x][_y + x] == 1)
                {
                    Board::move[_x][_y + x] = 1;
                    break;
                }
                else  break;
            }
            for (int x = 1; x <= 9; x++)
            {
                if (_y - x >= 0 && Board::board[_x][_y - x] == 0)
                {
                    Board::move[_x][_y - x] = 1;
                }
                else  if (_y - x >= 0 && Board::board[_x][_y - x] == 1)
                {
                    Board::move[_x][_y - x] = 1;
                    break;
                }
                else  break;
            }
        }

    }
    else  // for 將軍提示判斷 by ming
    {
        if (color == 1)
        {
            for (int x = 1; x <= 8; x++)//向右
            {
                if (_x + x <= 8 && Board::board[_x + x][_y] == 0)
                {
                    Board::virtualMove[_x + x][_y] = 1;
                }
                else  if (_x + x <= 8 && Board::board[_x + x][_y] == -1)
                {
                    Board::virtualMove[_x + x][_y] = 1;
                    break;
                }
                else  break;
            }
            for (int x = 1; x <= 8; x++)//向左
            {
                if (_x - x >= 0 && Board::board[_x - x][_y] == 0)
                {
                    Board::virtualMove[_x - x][_y] = 1;
                }
                else  if (_x - x >= 0 && Board::board[_x - x][_y] == -1)
                {
                    Board::virtualMove[_x - x][_y] = 1;
                    break;
                }
                else  break;
            }
            for (int x = 1; x <= 9; x++)
            {
                if (_y + x <= 9 && Board::board[_x][_y + x] == 0)
                {
                    Board::virtualMove[_x][_y + x] = 1;
                }
                else  if (_y + x <= 9 && Board::board[_x][_y + x] == -1)
                {
                    Board::virtualMove[_x][_y + x] = 1;
                    break;
                }
                else  break;
            }
            for (int x = 1; x <= 9; x++)
            {
                if (_y - x >= 0 && Board::board[_x][_y - x] == 0)
                {
                    Board::virtualMove[_x][_y - x] = 1;
                }
                else  if (_y - x >= 0 && Board::board[_x][_y - x] == -1)
                {
                    Board::virtualMove[_x][_y - x] = 1;
                    break;
                }
                else  break;
            }
        }
        else if (color == -1)
        {
            for (int x = 1; x <= 8; x++)//向右
            {
                if (_x + x <= 8 && Board::board[_x + x][_y] == 0)
                {
                    Board::virtualMove[_x + x][_y] = 1;
                }
                else  if (_x + x <= 8 && Board::board[_x + x][_y] == 1)
                {
                    Board::virtualMove[_x + x][_y] = 1;
                    break;
                }
                else  break;
            }
            for (int x = 1; x <= 8; x++)//向左
            {
                if (_x - x >= 0 && Board::board[_x - x][_y] == 0)
                {
                    Board::virtualMove[_x - x][_y] = 1;
                }
                else  if (_x - x >= 0 && Board::board[_x - x][_y] == 1)
                {
                    Board::virtualMove[_x - x][_y] = 1;
                    break;
                }
                else  break;
            }
            for (int x = 1; x <= 9; x++)
            {
                if (_y + x <= 9 && Board::board[_x][_y + x] == 0)
                {
                    Board::virtualMove[_x][_y + x] = 1;
                }
                else  if (_y + x <= 9 && Board::board[_x][_y + x] == 1)
                {
                    Board::virtualMove[_x][_y + x] = 1;
                    break;
                }
                else  break;
            }
            for (int x = 1; x <= 9; x++)
            {
                if (_y - x >= 0 && Board::board[_x][_y - x] == 0)
                {
                    Board::virtualMove[_x][_y - x] = 1;
                }
                else  if (_y - x >= 0 && Board::board[_x][_y - x] == 1)
                {
                    Board::virtualMove[_x][_y - x] = 1;
                    break;
                }
                else  break;
            }
        }

    }

}

Cannon::Cannon(int x, int y, int col, string src)
{
    _x = x;
    _y = y;
    firstX = x;
    firstY = y;
    pic = src;
    color = col;
    name = "Cannon";
}

void Cannon::move(int x, int y)
{
    if (Board::move[x][y] == 1)
    {
        Board::board[_x][_y] = 0;
        _x = x;
        _y = y;
        if (color == 1)
            Board::board[x][y] = 1;
        else if (color == -1)
            Board::board[x][y] = -1;
        GameManager::currentPlayer++;

    }
    Board::printBoard();
}

void Cannon::canMove(int show)
{
    if (show == 0) // for 可移動位置顯示 by ming
    {
        if (color == 1)
        {
            skip = false;//判斷跳躍(尚未)
            for (int x = 1; x <= 8; x++)
            {
                if (_x + x <= 8 && Board::board[_x + x][_y] == 0 && !skip)
                {
                    Board::move[_x + x][_y] = 1;
                }
                else  if (_x + x <= 8 && Board::board[_x + x][_y] != 0 && !skip)
                {
                    skip = true;//發現中間的棋子
                }
                else if (_x + x <= 8 && Board::board[_x + x][_y] == -1 && skip)
                {
                    Board::move[_x + x][_y] = 1;//可以殺的旗子
                    break;
                }
            }
            skip = false;
            for (int x = 1; x <= 8; x++)
            {
                if (_x - x >= 0 && Board::board[_x - x][_y] == 0 && !skip)
                {
                    Board::move[_x - x][_y] = 1;
                }
                else  if (_x - x >= 0 && Board::board[_x - x][_y] != 0 && !skip)
                {
                    skip = true;//發現中間的棋子
                }
                else if (_x - x >= 0 && Board::board[_x - x][_y] == -1 && skip)
                {
                    Board::move[_x - x][_y] = 1;//可以殺的旗子
                    break;
                }
            }
            skip = false;
            for (int x = 1; x <= 9; x++)
            {
                if (_y + x <= 9 && Board::board[_x][_y + x] == 0 && !skip)
                {
                    Board::move[_x][_y + x] = 1;
                }
                else  if (_y + x <= 9 && Board::board[_x][_y + x] != 0 && !skip)
                {
                    skip = true;//發現中間的棋子
                }
                else  if (_y + x <= 9 && Board::board[_x][_y + x] == -1 && skip)
                {
                    Board::move[_x][_y + x] = 1;//可以殺的旗子
                    break;
                }
            }
            skip = false;
            for (int x = 1; x <= 9; x++)
            {
                if (_y - x >= 0 && Board::board[_x][_y - x] == 0 && !skip)
                {
                    Board::move[_x][_y - x] = 1;
                }
                else  if (_y - x >= 0 && Board::board[_x][_y - x] != 0 && !skip)
                {
                    skip = true;//發現中間的棋子
                }
                else if (_y - x >= 0 && Board::board[_x][_y - x] == -1 && skip)
                {
                    Board::move[_x][_y - x] = 1;//可以殺的旗子
                    break;
                }
            }
        }
        else if (color == -1)
        {
            skip = false;//判斷跳躍(尚未)
            for (int x = 1; x <= 8; x++)
            {
                if (_x + x <= 8 && Board::board[_x + x][_y] == 0 && !skip)
                {
                    Board::move[_x + x][_y] = 1;
                }
                else  if (_x + x <= 8 && Board::board[_x + x][_y] != 0 && !skip)
                {
                    skip = true;//發現中間的棋子
                }
                else if (_x + x <= 8 && Board::board[_x + x][_y] == 1 && skip)
                {
                    Board::move[_x + x][_y] = 1;//可以殺的旗子
                    break;
                }
            }
            skip = false;
            for (int x = 1; x <= 8; x++)
            {
                if (_x - x >= 0 && Board::board[_x - x][_y] == 0 && !skip)
                {
                    Board::move[_x - x][_y] = 1;
                }
                else  if (_x - x >= 0 && Board::board[_x - x][_y] != 0 && !skip)
                {
                    skip = true;//發現中間的棋子
                }
                else if (_x - x >= 0 && Board::board[_x - x][_y] == 1 && skip)
                {
                    Board::move[_x - x][_y] = 1;//可以殺的旗子
                    break;
                }
            }
            skip = false;
            for (int x = 1; x <= 9; x++)
            {
                if (_y + x <= 9 && Board::board[_x][_y + x] == 0 && !skip)
                {
                    Board::move[_x][_y + x] = 1;
                }
                else  if (_y + x <= 9 && Board::board[_x][_y + x] != 0 && !skip)
                {
                    skip = true;//發現中間的棋子
                }
                else  if (_y + x <= 9 && Board::board[_x][_y + x] == 1 && skip)
                {
                    Board::move[_x][_y + x] = 1;//可以殺的旗子
                    break;
                }
            }
            skip = false;
            for (int x = 1; x <= 9; x++)
            {
                if (_y - x >= 0 && Board::board[_x][_y - x] == 0 && !skip)
                {
                    Board::move[_x][_y - x] = 1;
                }
                else  if (_y - x >= 0 && Board::board[_x][_y - x] != 0 && !skip)
                {
                    skip = true;//發現中間的棋子
                }
                else if (_y - x >= 0 && Board::board[_x][_y - x] == 1 && skip)
                {
                    Board::move[_x][_y - x] = 1;//可以殺的旗子
                    break;
                }
            }
        }
    }
    else // for 將軍提示判斷 by ming
    {
        if (color == 1)
        {
            skip = false;//判斷跳躍(尚未)
            for (int x = 1; x <= 8; x++)
            {
                if (_x + x <= 8 && Board::board[_x + x][_y] == 0 && !skip)
                {
                    Board::virtualMove[_x + x][_y] = 1;
                }
                else  if (_x + x <= 8 && Board::board[_x + x][_y] != 0 && !skip)
                {
                    skip = true;//發現中間的棋子
                }
                else if (_x + x <= 8 && Board::board[_x + x][_y] == -1 && skip)
                {
                    Board::virtualMove[_x + x][_y] = 1;//可以殺的旗子
                    break;
                }
            }
            skip = false;
            for (int x = 1; x <= 8; x++)
            {
                if (_x - x >= 0 && Board::board[_x - x][_y] == 0 && !skip)
                {
                    Board::virtualMove[_x - x][_y] = 1;
                }
                else  if (_x - x >= 0 && Board::board[_x - x][_y] != 0 && !skip)
                {
                    skip = true;//發現中間的棋子
                }
                else if (_x - x >= 0 && Board::board[_x - x][_y] == -1 && skip)
                {
                    Board::virtualMove[_x - x][_y] = 1;//可以殺的旗子
                    break;
                }
            }
            skip = false;
            for (int x = 1; x <= 9; x++)
            {
                if (_y + x <= 9 && Board::board[_x][_y + x] == 0 && !skip)
                {
                    Board::virtualMove[_x][_y + x] = 1;
                }
                else  if (_y + x <= 9 && Board::board[_x][_y + x] != 0 && !skip)
                {
                    skip = true;//發現中間的棋子
                }
                else  if (_y + x <= 9 && Board::board[_x][_y + x] == -1 && skip)
                {
                    Board::virtualMove[_x][_y + x] = 1;//可以殺的旗子
                    break;
                }
            }
            skip = false;
            for (int x = 1; x <= 9; x++)
            {
                if (_y - x >= 0 && Board::board[_x][_y - x] == 0 && !skip)
                {
                    Board::virtualMove[_x][_y - x] = 1;
                }
                else  if (_y - x >= 0 && Board::board[_x][_y - x] != 0 && !skip)
                {
                    skip = true;//發現中間的棋子
                }
                else if (_y - x >= 0 && Board::board[_x][_y - x] == -1 && skip)
                {
                    Board::virtualMove[_x][_y - x] = 1;//可以殺的旗子
                    break;
                }
            }
        }
        else if (color == -1)
        {
            skip = false;//判斷跳躍(尚未)
            for (int x = 1; x <= 8; x++)
            {
                if (_x + x <= 8 && Board::board[_x + x][_y] == 0 && !skip)
                {
                    Board::virtualMove[_x + x][_y] = 1;
                }
                else  if (_x + x <= 8 && Board::board[_x + x][_y] != 0 && !skip)
                {
                    skip = true;//發現中間的棋子
                }
                else if (_x + x <= 8 && Board::board[_x + x][_y] == 1 && skip)
                {
                    Board::virtualMove[_x + x][_y] = 1;//可以殺的旗子
                    break;
                }
            }
            skip = false;
            for (int x = 1; x <= 8; x++)
            {
                if (_x - x >= 0 && Board::board[_x - x][_y] == 0 && !skip)
                {
                    Board::virtualMove[_x - x][_y] = 1;
                }
                else  if (_x - x >= 0 && Board::board[_x - x][_y] != 0 && !skip)
                {
                    skip = true;//發現中間的棋子
                }
                else if (_x - x >= 0 && Board::board[_x - x][_y] == 1 && skip)
                {
                    Board::virtualMove[_x - x][_y] = 1;//可以殺的旗子
                    break;
                }
            }
            skip = false;
            for (int x = 1; x <= 9; x++)
            {
                if (_y + x <= 9 && Board::board[_x][_y + x] == 0 && !skip)
                {
                    Board::virtualMove[_x][_y + x] = 1;
                }
                else  if (_y + x <= 9 && Board::board[_x][_y + x] != 0 && !skip)
                {
                    skip = true;//發現中間的棋子
                }
                else  if (_y + x <= 9 && Board::board[_x][_y + x] == 1 && skip)
                {
                    Board::virtualMove[_x][_y + x] = 1;//可以殺的旗子
                    break;
                }
            }
            skip = false;
            for (int x = 1; x <= 9; x++)
            {
                if (_y - x >= 0 && Board::board[_x][_y - x] == 0 && !skip)
                {
                    Board::virtualMove[_x][_y - x] = 1;
                }
                else  if (_y - x >= 0 && Board::board[_x][_y - x] != 0 && !skip)
                {
                    skip = true;//發現中間的棋子
                }
                else if (_y - x >= 0 && Board::board[_x][_y - x] == 1 && skip)
                {
                    Board::virtualMove[_x][_y - x] = 1;//可以殺的旗子
                    break;
                }
            }
        }

    }

    Board::printMove();
}