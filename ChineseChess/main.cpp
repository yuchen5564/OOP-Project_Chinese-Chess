//#include "viewer.h"
#include "GameManager.h"
#include "Board.h"
#include <QApplication>

int main(int argc, char* argv[])
{
	QApplication a(argc, argv);
	GameManager game;
	//Chess ch01(6, 6,-1, ":/ChineseChess/img/R_bing.png");
	//Chess ch02(0, 0, 1,":/ChineseChess/img/B_che.png");
	//Chess ch03(1, 7, 1,":/ChineseChess/img/R_pao.png");
	King ch04(4, 0, -1, ":/ChineseChess/img/B_jiang.png");
	King ch05(4, 9, 1, ":/ChineseChess/img/R_jiang.png");
	Advisor ch06(3, 0, -1, ":/ChineseChess/img/B_shi.png");
	Advisor ch07(5, 0, -1, ":/ChineseChess/img/B_shi.png");
	Advisor ch08(3, 9, 1, ":/ChineseChess/img/R_shi.png");
	Advisor ch09(5, 9, 1, ":/ChineseChess/img/R_shi.png");
	Minister ch10(2, 0, -1, ":/ChineseChess/img/B_siang.png");
	Minister ch11(6, 0, -1, ":/ChineseChess/img/B_siang.png");
	Minister ch12(2, 9, 1, ":/ChineseChess/img/R_siang.png");
	Minister ch13(6, 9, 1, ":/ChineseChess/img/R_siang.png");
	Horse ch14(1, 0, -1, ":/ChineseChess/img/B_ma.png");
	Horse ch15(7, 0, -1, ":/ChineseChess/img/B_ma.png");
	Horse ch16(1, 9, 1, ":/ChineseChess/img/R_ma.png");
	Horse ch17(7, 9, 1, ":/ChineseChess/img/R_ma.png");
	Soldier ch18(0, 3, -1, ":/ChineseChess/img/B_bing.png");
	Soldier ch19(2, 3, -1, ":/ChineseChess/img/B_bing.png");
	Soldier ch20(4, 3, -1, ":/ChineseChess/img/B_bing.png");
	Soldier ch21(6, 3, -1, ":/ChineseChess/img/B_bing.png");
	Soldier ch22(8, 3, -1, ":/ChineseChess/img/B_bing.png");
	Soldier ch23(0, 6, 1, ":/ChineseChess/img/R_bing.png");
	Soldier ch24(2, 6, 1, ":/ChineseChess/img/R_bing.png");
	Soldier ch25(4, 6, 1, ":/ChineseChess/img/R_bing.png");
	Soldier ch26(6, 6, 1, ":/ChineseChess/img/R_bing.png");
	Soldier ch27(8, 6, 1, ":/ChineseChess/img/R_bing.png");
	Chariot ch28(0, 0, -1, ":/ChineseChess/img/B_che.png");
	Chariot ch29(8, 0, -1, ":/ChineseChess/img/B_che.png");
	Chariot ch30(0, 9, 1, ":/ChineseChess/img/R_che.png");
	Chariot ch31(8, 9, 1, ":/ChineseChess/img/R_che.png");
	Cannon ch32(1, 2, -1, ":/ChineseChess/img/B_pao.png");
	Cannon ch33(7, 2, -1, ":/ChineseChess/img/B_pao.png");
	Cannon ch34(1, 7, 1, ":/ChineseChess/img/R_pao.png");
	Cannon ch35(7, 7, 1, ":/ChineseChess/img/R_pao.png");
	//ch01 = Chess(8, 9, ":/ChineseChess/img/R_jiang.png");
   // Board::pushIn(&ch01);
   // Board::pushIn(&ch02);
	//Board::pushIn(&ch03);
	Board::pushIn(&ch04);
	Board::pushIn(&ch05);
	Board::pushIn(&ch06);
	Board::pushIn(&ch07);
	Board::pushIn(&ch08);
	Board::pushIn(&ch09);
	Board::pushIn(&ch10);
	Board::pushIn(&ch11);
	Board::pushIn(&ch12);
	Board::pushIn(&ch13);
	Board::pushIn(&ch14);
	Board::pushIn(&ch15);
	Board::pushIn(&ch16);
	Board::pushIn(&ch17);
	Board::pushIn(&ch18);
	Board::pushIn(&ch19);
	Board::pushIn(&ch20);
	Board::pushIn(&ch21);
	Board::pushIn(&ch22);
	Board::pushIn(&ch23);
	Board::pushIn(&ch24);
	Board::pushIn(&ch25);
	Board::pushIn(&ch26);
	Board::pushIn(&ch27);
	Board::pushIn(&ch28);
	Board::pushIn(&ch29);
	Board::pushIn(&ch30);
	Board::pushIn(&ch31);
	Board::pushIn(&ch32);
	Board::pushIn(&ch33);
	Board::pushIn(&ch34);
	Board::pushIn(&ch35);
	Board::printBoard();
	game.showMenu();
	return a.exec();
}
