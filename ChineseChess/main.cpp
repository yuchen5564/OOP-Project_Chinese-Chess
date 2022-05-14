//#include "viewer.h"
#include "GameManager.h"
#include "Board.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GameManager game;
    Chess ch01(1, 1, ":/ChineseChess/img/B_ma.png");
    Chess ch02(2, 2, ":/ChineseChess/img/B_shi.png");

    ch01 = Chess(8, 9, ":/ChineseChess/img/R_bing");
    Board::pushIn(&ch01);
    Board::pushIn(&ch02);
  
    game.showMenu();
    return a.exec();
}
