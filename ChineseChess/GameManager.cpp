#include "GameManager.h"



GameManager::GameManager()
{

}

void GameManager::showMenu(){
    v.menu();
    v.show();
}

void GameManager::restartGame()
{
    for (int i = 0; Board::onBoard.size(); i++) {
        Board::onBoard[i]->resetChess();
    }
}

//void GameManager::pushIn(Chess* ch)
//{
//   // b.pushIn(ch);
//}