#ifndef CHESS_H
#define CHESS_H

#include "Header.h"


class Chess
{
public:
    Chess();
    Chess(int x, int y ,int col,string src);
    virtual void move(int x, int y); //移動棋子
    virtual void canMove(); //提示可移動位置 0515 ADD
    int getX();
    int getY();
    int getIndex();
    void resetChess(); //0513 ADD 回復初始位置
    int  color; //紀錄棋子顏色
    bool alive = true; //紀錄是否存活
    string getPic();
protected:
//    string name;
    int index;
    string pic; //圖片路徑
    int _x, _y; //棋子目前位置
    int firstX, firstY; //棋子初始位置 --> 0513 ADD

    bool crossRiver = false; //紀錄是否過河

};

class King : public Chess
{
    public:
        King();
        King(int x, int y,int col ,string src);
        void move(int x, int y);
        void canMove();

};

class Advisor : public Chess
{
    public:
        Advisor();
        Advisor(int x, int y,int col ,string src);
        void move(int x, int y);
        void canMove();
};

class Minister : public Chess
{
    public:
        Minister();
        Minister(int x, int y,int col ,string src);
        void move(int x, int y);
        void canMove();
};

class Horse : public Chess
{
    public:
        Horse();
        Horse(int x, int y,int col ,string src);
        void move(int x, int y);
        void canMove();
};

class Soldier : public Chess
{
    public:
        Soldier();
        Soldier(int x, int y,int col ,string src);
        void move(int x, int y);
        void canMove();
};
class Chariot : public Chess
{
    public:
        Chariot();
        Chariot(int x, int y,int col ,string src);
        void move(int x, int y);
        void canMove();
};

class Cannon : public Chess
{
    public:
        Cannon();
        Cannon(int x, int y,int col ,string src);
        void move(int x, int y);
        void canMove();
    private:
    bool skip=false;
};

#endif // CHESS_H
