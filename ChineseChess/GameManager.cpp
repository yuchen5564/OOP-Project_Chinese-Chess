#include "GameManager.h"
#include <sstream>
#include <fstream>

int GameManager::currentPlayer = 0;

GameManager::GameManager()
{
   // currentPlayer = 0;
}

void GameManager::showMenu(){
    v.menu();
    v.show();
}

void GameManager::restartGame()
{
    for (int i = 0; i < Board::onBoard.size(); i++)  {
        Board::onBoard[i]->resetChess();
    }
    GameManager::currentPlayer = 0;
}

void GameManager::loadFile(string path)
{
    fstream file;
    file.open(path);
    string input;
    int nowX, nowY, nextX, nextY;
    while (getline(file, input)) {
        for (int i = 0; i < input.length(); i++) {
            if (!isdigit(input[i])) input[i] = ' ';
        }
        cout << input << endl;
        stringstream in(input);
        in >> nowX >> nowX >> nowY >> nextX >> nextY;
        for (int i = 0; i < Board::onBoard.size(); i++) {
            if (Board::onBoard[i]->getX() == nowX && Board::onBoard[i]->getY() == nowY) {
                Board::onBoard[i]->canMove();
                if (Board::board[nextX][nextY] != 0) {
                    for (int j = 0; j < Board::onBoard.size(); j++) {
                        if (Board::onBoard[j]->getX() == nextX && Board::onBoard[j]->getY() == nextY) {
                            Board::onBoard[j]->alive = false;
                        }
                    }
                }
                Board::onBoard[i]->move(nextX, nextY);
                Board::clearMove();
            }
        }
    }
    Board::clearMove();
    file.close();
}

//void GameManager::pushIn(Chess* ch)
//{
//   // b.pushIn(ch);
//}