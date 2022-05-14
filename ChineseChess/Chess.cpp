#include "Chess.h"
#include "Board.h"
Chess::Chess()
{
    //name="Chess";
}

Chess::Chess(int x, int y, string src)
{
    _x = x;
    _y = y;
    firstX = x;
    firstY = y;
    pic = src;
}

void Chess::move(int x, int y)
{
    //確定該點上沒有棋子
    if (Board::board[x][y] == 0) {
        Board::board[_x][_y] = 0;
        _x = x;
        _y = y;
        Board::board[x][y] = 1;
    }
}

void Chess::select(){

}

int Chess::getX(){
    return this->_x;
}

int Chess::getY(){
    return this->_y;
}

int Chess::getIndex()
{
    return this->index;
}

//0513 ADD 回復初始位置
void Chess::resetChess()
{
    Board::board[_x][_y] = 0;
    _x = firstX;
    _y = firstY;
    Board::board[_x][_y] = 1;
}

string Chess::getPic()
{
    return pic;
}
