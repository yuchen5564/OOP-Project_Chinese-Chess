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
   // void pushIn(Chess* ch);

private:
    Board b;
    int currentPlayer;
    Viewer v;
};

#endif // GAMEMANAGER_H
