#include "GameManager.h"
#include <sstream>
#include <fstream>
#include <ctime>
#include <cstdlib>

int GameManager::currentPlayer = 0;

GameManager::GameManager()
{
    srand(time(NULL));
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
    //Board::printBoard();
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
                Board::onBoard[i]->canMove(0);
                cout << "find!\n";

                if (Board::board[nextX][nextY] != 0) {
                    
                    for (int j = 0; j < Board::onBoard.size(); j++) {
                        if (Board::onBoard[j]->getX() == nextX && Board::onBoard[j]->getY() == nextY) {
                            Board::onBoard[j]->alive = false;
                            Board::onBoard[j]->fakeAlive = false;
                        }
                    }
                }
                
                Board::onBoard[i]->move(nextX, nextY);
                Board::onBoard[i]->makeLog(nowX, nowY);
                Board::clearMove();
                break;  //======================================================有更改
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
    //cout << log << endl;
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

//0519 提示將軍
bool GameManager::isCheck(int flag) //flag 1:正常 0:欠行
{
    if (flag == 1) {
        for (int i = 0; i < Board::onBoard.size(); i++)
        {
            if (currentPlayer % 2 == 0) // red   ( need check 
            {
                if (Board::onBoard[i]->color == -1 && Board::onBoard[i]->alive) // black chess
                {
                    Board::onBoard[i]->canMove(1);
                    int x = Board::RKing->getX();
                    int y = Board::RKing->getY();

                    if (Board::virtualMove[x][y] == 1)
                    {
                        return true;
                    }

                }

            }
            else  // black
            {
                if (Board::onBoard[i]->color == 1 && Board::onBoard[i]->alive) // red chess
                {
                    Board::onBoard[i]->canMove(1);
                    int x = Board::BKing->getX();
                    int y = Board::BKing->getY();

                    if (Board::virtualMove[x][y] == 1)
                    {
                        return true;
                    }

                }

            }



        }
        return false;
    }
    else if (flag == 0) {
        for (int i = 0; i < Board::onBoard.size(); i++)
        {
            if (currentPlayer % 2 == 0) // red   ( need check 
            {
                
                if (Board::onBoard[i]->color == -1 && Board::onBoard[i]->fakeAlive) // black chess
                {//cout << "RED\n";
                    Board::onBoard[i]->canMove(1);
                    int x = Board::RKing->getFakeX();
                    int y = Board::RKing->getFakeY();

                    if (Board::virtualMove[x][y] == 1)
                    {
                        return true;
                    }

                }

            }
            else  // black
            {
                
                if (Board::onBoard[i]->color == 1 && Board::onBoard[i]->fakeAlive) // red chess
                {//cout << "BLACK\n";
                    Board::onBoard[i]->canMove(1);
                    int x = Board::BKing->getFakeX();
                    int y = Board::BKing->getFakeY();

                    if (Board::virtualMove[x][y] == 1)
                    {
                        return true;
                    }

                }

            }

        }
        return false;
    }
    
}

typedef struct Position {
    int x;
    int y;
};

void GameManager::aiGame()
{
    //cout << "===================aiai\n";
    int randNum = rand() % Board::onBoard.size() / 2 + 1; //edit
   // int randNum2 = rand();
    int count = 0;
   // cout << randNum1 << " " << randNum2 << endl;
    //cout << randNum%16 << endl;
    for (int i = 0; i < Board::onBoard.size(); i++) {
        if (Board::onBoard[i]->color == -1) { //遇到黑
            count++;
        }
        if (count == randNum && Board::onBoard[i]->alive) {
            Board::onBoard[i]->canMove(0);
            //cout << "''''''''''''''''''''\n";
            //Board::printMove();
            vector<Position> list;
            list.clear();
            for (int j = 0; j < 9; j++) {
                for (int k = 0; k < 10; k++) {
                    if (Board::move[j][k] == 1) {
                        list.push_back({ j,k });
                        
                    }
                }
            }
            cout << list.size() << endl;
            randNum = rand() % list.size();
            //cout <<"--------------------------------------"<<randNum << " " << list[randNum].x << " " << list[randNum].y << endl;
            if (Board::board[list[randNum].x][list[randNum].y] != 0) {
                for (int j = 0; j < Board::onBoard.size(); j++) {
                    if (Board::onBoard[j]->getX() == list[randNum].x && Board::onBoard[j]->getY() == list[randNum].y) {
                        Board::onBoard[j]->alive = false;
                        Board::onBoard[j]->fakeAlive = false;

                    }
                }
            }
            Board::onBoard[i]->move(list[randNum].x, list[randNum].y);
            Board::clearMove();
            break;
        }
        else if(count == randNum && !Board::onBoard[i]->alive) {
            randNum++;
        }
    }
}

bool GameManager::stalemate()
{
    Board::clearVirtualMove();
   // bool isStalemate = false;
    int nowTurn = currentPlayer % 2;
    if (nowTurn == 0) nowTurn = 1;
    else nowTurn = -1;
    cout << "nowTurn : " << nowTurn << endl;
    for (int i = 0; i < Board::onBoard.size(); i++) {
        Board::clearMove();
        if (Board::onBoard[i]->color == nowTurn) {
            Board::onBoard[i]->canMove(0); //取得可移動位置
            vector<Position> list; //抓出所有可移動
            list.clear();
            for (int j = 0; j < 9; j++) {
                for (int k = 0; k < 10; k++) {
                    if (Board::move[j][k] == 1)  list.push_back({ j,k });
                }
            }
            for (int k = 0; k < list.size(); k++) {
                int col = Board::board[list[k].x][list[k].y];

                int tmpIndex = -1;
                if (Board::board[list[k].x][list[k].y] != 0) {
                    for (int j = 0; j < Board::onBoard.size(); j++) {
                        if (Board::onBoard[j]->getX() == list[k].x && Board::onBoard[j]->getY() == list[k].y) {
                            Board::onBoard[j]->fakeAlive = false;
                            tmpIndex = j;
                        }
                    }
                }

                Board::onBoard[i]->fakeMove(list[k].x, list[k].y, 0); //移動到下一點
                
                //cout << "===========================\n";
               // cout << "real:" << Board::onBoard[i]->getX() << " " << Board::onBoard[i]->getY() << endl;
               // cout << "fake:" << Board::onBoard[i]->getFakeX() << " " << Board::onBoard[i]->getFakeY() << endl;
               // cout << "BKing fake:" << Board::BKing->getFakeX()  << endl;
               // cout << "RKing fake:" << Board::RKing->getFakeX()  << endl;
                //Board::printBoard();
                //cout<<Board::virtualMove
                //Board::printVirtualMove();
                if (!isCheck(0)) {
                    //Board::printVirtualMove();
                    Board::onBoard[i]->fakeMove(Board::onBoard[i]->getX(), Board::onBoard[i]->getY(), col); 
                    if (tmpIndex != -1) Board::onBoard[tmpIndex]->fakeAlive = true;
                    Board::clearVirtualMove();
                    return false;
                }
                else {
                    //Board::printVirtualMove();
                    Board::onBoard[i]->fakeMove(Board::onBoard[i]->getX(), Board::onBoard[i]->getY(),col );
                    if (tmpIndex != -1) Board::onBoard[tmpIndex]->fakeAlive = true;
                    Board::clearVirtualMove();
                }
                
            }
        }
       
    }
    
    return true;
}
