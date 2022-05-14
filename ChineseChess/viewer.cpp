//定位: 25+56*x ,25+56*y
//棋子大小: 50*50

#include "viewer.h"
#include "ui_viewer.h"
#include "GameManager.h"
#include "Board.h"
#include <iostream>

Viewer::Viewer(QWidget* parent)
	: QWidget(parent)
	, ui(new Ui::Viewer)
{
	ui->setupUi(this);
}

Viewer::~Viewer()
{
	delete ui;
}

void Viewer::menu() {
	setFixedSize(300, 250);

	title1 = new QLabel("中國象棋", this);
	title1->setFont(QFont("微軟正黑體", 20));
	title1->setGeometry(90, 20, 150, 30);

	startBtn = new QPushButton("開始遊戲", this);
	startBtn->setGeometry(90, 100, 120, 40);
	startBtn->setFlat(0);

	quitBtn = new QPushButton("結束遊戲", this);
	quitBtn->setGeometry(90, 150, 120, 40);
	quitBtn->setFlat(0);

	title1->show();
	startBtn->show();
	quitBtn->show();

	connect(startBtn, SIGNAL(clicked(bool)), this, SLOT(startGame_slot()));
	connect(quitBtn, SIGNAL(clicked(bool)), qApp, SLOT(quit()));
}

//設定初始棋盤
void Viewer::setBoard() {
	//棋盤背景
//    QPixmap pixChessBoard(":/ChineseChess/img/Board.jpg");
//    setFixedSize(pixChessBoard.size());
//    QPalette palette(this->palette());
//    palette.setBrush( QPalette::Window,QBrush(pixChessBoard));
//    this->setPalette(palette);

	setFixedSize(700, 598);

	label = new QLabel(" ", this);
	label->setFont(QFont("微軟正黑體", 15));
	label->setGeometry(1, 1, 150, 30);
	//label->show();

	restartBtn = new QPushButton("重新開始", this);
	restartBtn->setGeometry(565, 40, 120, 40);
	restartBtn->setFlat(0);
	restartBtn->show();

	update();

	connect(restartBtn, SIGNAL(clicked(bool)), this, SLOT(restartGame_slot()));
}

//***會主動更新
void Viewer::paintEvent(QPaintEvent*) {
	if (start) {
		QPainter painter(this);

		painter.drawPixmap(QRect(0, 0, 550, 598), QPixmap(":/ChineseChess/img/Board-4.jpg")); //畫出棋盤

		if (xPos < 9 && yPos < 10) {
			painter.drawPixmap(QRect(25 + 56 * xPos, 25 + 56 * yPos, 50, 50), QPixmap(":/ChineseChess/img/select.png")); //畫出選擇框
		}

		for (int i = 0; i < Board::onBoard.size(); i++) {
			int tx =  Board::onBoard[i]->getX();
			int ty = Board::onBoard[i]->getY();
			QString pic = QString::fromStdString(Board::onBoard[i]->getPic());
			painter.drawPixmap(QRect(25 + 56 * tx, 25 + 56 * ty, 50, 50), QPixmap(pic));
		}
		update();
	}
}

void Viewer::mousePressEvent(QMouseEvent* pos) {
	// QToolTip::showText();
	 //QMessageBox::about(this,"Information",);
 //    label = new QLabel("pos",this);
 //    pos->globalPosition();
 //    label->setText();
 //    label->setGeometry(1,1,100,100);
	// update();

	//取得滑鼠位置
	pos->globalPos();
	xPos = (pos->x() - 25) / 56;
	yPos = (pos->y() - 25) / 56;
	label->setText(QString("%1, %2").arg(xPos).arg(yPos));

	//=============================================================================

	static int press = 0;
	static int index;
	static int nx, ny; //第二次選取的點
	static int tmpX, tmpY; //紀錄第一次點到的棋子
	if (press == 1) {
		nx = xPos;
		ny = yPos;
		press++;
		
	}
	else if (press == 0) {
		for (int i = 0; i < Board::onBoard.size(); i++) {

			//取出棋子位置
			tmpX = Board::onBoard[i]->getX();
			tmpY = Board::onBoard[i]->getY();

			if (xPos == tmpX && yPos == tmpY) {	//第一次抓取位置
				index = i;
				press++;
				break;
			}

		}
	}
	if(press == 2){
		Board::onBoard[index]->move(nx, ny);
		press = 0;
	}
	//=============================================================================
}

void Viewer::mouseMoveEvent(QMouseEvent* pos) {
	update();

	QToolTip::showText(pos->globalPos(), QString("%1, %2").arg(pos->x()).arg(pos->y()));;

}

//信號槽
void Viewer::startGame_slot() {
	xPos = 10;
	yPos = 10;
	setBoard();
	start = true;
	title1->hide();
	startBtn->hide();
	quitBtn->hide();
	label->show();
}

void Viewer::restartGame_slot() {
	menu();
	start = false;
	restartBtn->hide();
	label->hide();

	//0513 ADD
	GameManager::restartGame();
	/*for (int i = 0; i < Board::onBoard.size(); i++) {
		Board::onBoard[i]->resetChess();
	}*/
}
