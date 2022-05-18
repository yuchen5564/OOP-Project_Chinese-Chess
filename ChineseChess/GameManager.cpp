#include "GameManager.h"
#include <sstream>
#include <fstream>

int GameManager::currentPlayer = 0;

GameManager::GameManager()
{
    Board::onBoard = onBoard;
    fstream file;
    file.open("log.txt", ios::out|ios::trunc);
    file.close();
   // currentPlayer = 0;
}

void GameManager::showMenu(){
    v.menu();
    v.show();
}

void GameManager::restartGame()
{
    Board::resetBoard();
    for (int i = 0; i < Board::onBoard.size(); i++)  {
        Board::onBoard[i]->resetChess();
    }
    GameManager::currentPlayer = 0;
    fstream file;
    file.open("log.txt", ios::out | ios::trunc);
    file.close();
    Board::printBoard();
}

void GameManager::loadFile(string path)
{
    fstream file;
    file.open(path, ios::in);
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
                cout << "find!\n";
                if (Board::board[nextX][nextY] != 0) {
                    
                    for (int j = 0; j < Board::onBoard.size(); j++) {
                        if (Board::onBoard[j]->getX() == nextX && Board::onBoard[j]->getY() == nextY) {
                            Board::onBoard[j]->alive = false;
                            
                        }
                    }
                }
                Board::onBoard[i]->move(nextX, nextY);
                Board::onBoard[i]->makeLog(nowX, nowY);
                Board::clearMove();
            }
        }
    }
    
    Board::clearMove();
    file.close();
}

void GameManager::writeLog(string log)
{
    fstream file;
    file.open("log.txt", ios::out | ios::app);
    file << log;
    cout << log << endl;
    file.close();
}

void GameManager::pushIn(Chess* ch)
{
    onBoard.push_back(ch);
    Board::board[ch->getX()][ch->getY()] = ch->color;
    //Board::pushIn(ch);
    Board::onBoard = onBoard;
}


bool GameManager::checkKing()
{
    if (Board::RKing->alive && Board::BKing->alive) {
        return true;
    }
    else {
        return false;
    }
}

//void GameManager::pushIn(Chess* ch)
//{
//   // b.pushIn(ch);
//}