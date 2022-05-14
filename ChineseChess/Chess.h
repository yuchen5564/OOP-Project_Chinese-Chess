#ifndef CHESS_H
#define CHESS_H

#include "Header.h"


class Chess
{
public:
    Chess();
    Chess(int x, int y, string src);
    virtual void move(int x, int y);
    virtual void select();
    int getX();
    int getY();
    int getIndex();
    void resetChess(); //0513 ADD 回復初始位置

    string getPic();
protected:
//    string name;
    int index;
    string pic; //圖片路徑
    int _x, _y; //棋子目前位置
    int firstX, firstY; //棋子初始位置 --> 0513 ADD
    bool alive = true; //紀錄是否存活
    bool crossRiver = false; //紀錄是否過河
    int  color; //紀錄棋子顏色
};

#endif // CHESS_H
