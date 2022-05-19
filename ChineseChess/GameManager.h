#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "Header.h"
#include "viewer.h"
#include "Chess.h"
#include "Board.h"

class GameManager
{
public:
    GameManager();
    void showMenu();
    static void restartGame();
    static void loadFile(string path);
    static void writeLog(string log);
    void pushIn(Chess* ch);
    static int currentPlayer;
    //static bool 
    static bool checkKing();
    static bool isCheck(); //提示將軍
private:
    vector<Chess*> onBoard;
    Board b;
    Viewer v;
};

#endif // GAMEMANAGER_H
