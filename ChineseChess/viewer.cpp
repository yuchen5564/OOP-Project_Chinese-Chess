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
	setWindowTitle("Chinese Chess");
	setWindowIcon(QIcon(":/ChineseChess/img/icon.png"));
}

Viewer::~Viewer()
{
	delete ui;
}

void Viewer::menu() {
	Board::clearMove();
	setFixedSize(300, 250);

	title1 = new QLabel("中國象棋", this);
	title1->setFont(QFont("微軟正黑體", 20));
	title1->setGeometry(90, 20, 150, 30);

	startBtn = new QPushButton("開始遊戲", this);
	startBtn->setGeometry(90, 80, 120, 40);
	startBtn->setFlat(0);

	loadBtn = new QPushButton("讀檔開始", this);
	loadBtn->setGeometry(90, 130, 120, 40);
	loadBtn->setFlat(0);

	quitBtn = new QPushButton("結束遊戲", this);
	quitBtn->setGeometry(90, 180, 120, 40);
	quitBtn->setFlat(0);

	title1->show();
	startBtn->show();
	loadBtn->show();
	quitBtn->show();

	connect(startBtn, SIGNAL(clicked(bool)), this, SLOT(startGame_slot()));
	connect(quitBtn, SIGNAL(clicked(bool)), qApp, SLOT(quit()));
	connect(loadBtn, SIGNAL(clicked(bool)), this, SLOT(loadFile_slot()));
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

	click_label = new QLabel(" ", this);
	click_label->setFont(QFont("微軟正黑體", 15));
	click_label->setGeometry(1, 1, 150, 30);
	//label->show();

	nowPlayer_label = new QLabel(" ", this);
	if (GameManager::currentPlayer % 2 == 0) {
		nowPlayer_label->setText(QString("現在輪到\n　紅方"));
	}
	else {
		nowPlayer_label->setText(QString("現在輪到\n　黑方"));
	}
	nowPlayer_label->setFont(QFont("微軟正黑體", 15));
	nowPlayer_label->setGeometry(585, 40, 120, 60);

	restartBtn = new QPushButton("重新開始", this);
	restartBtn->setGeometry(565, 120, 120, 40);
	restartBtn->setFlat(0);
	restartBtn->show();

	surrenderBtn = new QPushButton("投降", this);
	surrenderBtn->setGeometry(565, 180, 120, 40);
	surrenderBtn->setFlat(0);
	surrenderBtn->show();

	saveGameBtn = new QPushButton("存檔", this);
	saveGameBtn->setGeometry(565, 240, 120, 40);
	saveGameBtn->setFlat(0);
	surrenderBtn->show();

	update();

	connect(restartBtn, SIGNAL(clicked(bool)), this, SLOT(restartGame_slot()));
	connect(surrenderBtn, SIGNAL(clicked(bool)), this, SLOT(surrender_slot()));
	connect(saveGameBtn, SIGNAL(clicked(bool)), this, SLOT(saveGame_slot()));
}

//***會主動更新
void Viewer::paintEvent(QPaintEvent*) {
	if (start) {
		QPainter painter(this);

		//劃出棋盤
		painter.drawPixmap(QRect(0, 0, 550, 598), QPixmap(":/ChineseChess/img/Board-4.jpg"));

		//劃出選擇框
		if (xPos < 9 && yPos < 10) {
			painter.drawPixmap(QRect(25 + 56 * xPos, 25 + 56 * yPos, 50, 50), QPixmap(":/ChineseChess/img/select.png"));
		}

		//劃出可移動位置
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 10; j++) {
				if (Board::move[i][j] == 1) {
					painter.drawPixmap(QRect(25 + 56 * i, 25 + 56 * j, 50, 50), QPixmap(":/ChineseChess/img/canMove.png"));
				}
			}
		}

		//畫出所有棋子
		for (int i = 0; i < Board::onBoard.size(); i++) {
            if(Board::onBoard[i]->alive)
            {
                int tx =  Board::onBoard[i]->getX();
                int ty = Board::onBoard[i]->getY();
                QString pic = QString::fromStdString(Board::onBoard[i]->getPic());
                painter.drawPixmap(QRect(25 + 56 * tx, 25 + 56 * ty, 50, 50), QPixmap(pic));
            }

		}
		update();
	}
}

void Viewer::mousePressEvent(QMouseEvent* pos) {
	if (start) {

		//取得滑鼠位置
		pos->globalPos();

		if (pos->x() >= 25 && pos->y() >= 25) {
			if ((((pos->x() - 25) / 56) <= 8) && (((pos->y() - 25) / 56) <= 9)) {
				xPos = (pos->x() - 25) / 56;
				yPos = (pos->y() - 25) / 56;
			}
		}
		

		click_label->setText(QString("%1, %2").arg(xPos).arg(yPos));

		

		//label->setText(QString("Current Player: %1").arg(GameManager::currentPlayer));

		//=============================================================================

		static int press = 0;
		static int index = -1;
		static int nx, ny; //第二次選取的點
		static int tmpX, tmpY; //紀錄第一次點到的棋子
        //Board::clearMove();
		int nowPlayer = GameManager::currentPlayer % 2;

		if (nowPlayer == 0) nowPlayer = 1;
		else if (nowPlayer == 1) nowPlayer = -1;

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


                if (xPos == tmpX && yPos == tmpY && Board::onBoard[i]->alive
					&& nowPlayer == Board::onBoard[i]->color) {	//第一次抓取位置
					Board::onBoard[i]->canMove();
					index = i;
					press++;
					break;
				}
				/*if (nowPlayer != Board::onBoard[i]->color) {
					xPos = 10;
					yPos = 10;
				}*/

			}
		}
		if (press == 2) {
            press = 0;
            //Board::clearMove();
            if (Board::board[nx][ny] == 0) { //移動位置為空 --> 移動棋子
                Board::onBoard[index]->move(nx, ny);
				Board::onBoard[index]->makeLog(tmpX, tmpY);
                Board::clearMove();
                //消除選取框
                xPos = 10;
				yPos = 10;
			}
            else if(Board::board[nx][ny] == Board::onBoard[index]->color*-1) //吃棋
            {
				if (Board::move[xPos][yPos] == 1) {
					for (int i = 0; i < Board::onBoard.size(); i++)
					{
						int tx = Board::onBoard[i]->getX();
						int ty = Board::onBoard[i]->getY();


						if (nx == tx && ny == ty && Board::onBoard[i]->alive) {
							Board::onBoard[i]->alive = false;

						}
					}
					Board::onBoard[index]->move(nx, ny);
					Board::onBoard[index]->makeLog(tmpX, tmpY);
					
				}
				Board::clearMove();
				//消除選取框
				xPos = 10;
				yPos = 10;
            }
			else { //移動位置有棋 --> 視為重新選定
				Board::clearMove();
				for (int i = 0; i < Board::onBoard.size(); i++) {

					//取出棋子位置
					tmpX = Board::onBoard[i]->getX();
					tmpY = Board::onBoard[i]->getY();


                    if (xPos == tmpX && yPos == tmpY && Board::onBoard[i]->alive) {	//第一次抓取位置
						Board::onBoard[i]->canMove();
						index = i;
						press++;
						break;
					}

				}
			}
		}
		if (!GameManager::checkKing()) {
			QMessageBox msg;
			if (GameManager::currentPlayer % 2 == 0) {
				msg.setText("黑方獲勝!");
			}
			else {
				msg.setText("紅方獲勝!");
			}
			msg.exec();
			if (!(QMessageBox::information(this, tr("Warning"), tr("是否要儲存檔案?"), tr("Yes"), tr("No"))))
			{
				saveGame_slot();
			}
			reset();
		}

		if (GameManager::currentPlayer % 2 == 0) {
			nowPlayer_label->setText(QString("現在輪到\n　紅方"));
		}
		else {
			nowPlayer_label->setText(QString("現在輪到\n　黑方"));
		}
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
	loadBtn->hide();
	quitBtn->hide();
	click_label->show();
	nowPlayer_label->show();
	surrenderBtn->show();
	saveGameBtn->show();
}

void Viewer::reset()
{
	menu();
	start = false;
	restartBtn->hide();
	click_label->hide();
	nowPlayer_label->hide();
	surrenderBtn->hide();
	saveGameBtn->hide();
	//0513 ADD
	GameManager::restartGame();
}

void Viewer::restartGame_slot() {
	if (!(QMessageBox::information(this, tr("Warning"), tr("是否確認重新開始遊戲?"), tr("Yes"), tr("No"))))
	{
		if (!(QMessageBox::information(this, tr("Warning"), tr("是否要儲存檔案?"), tr("Yes"), tr("No"))))
		{
			saveGame_slot();
		}
		reset();
	}
}

void Viewer::loadFile_slot()
{
	//QMessageBox::information(this, "Info", "Load File Success!");
	QString filePath = QFileDialog::getOpenFileName(NULL, QObject::tr("Open File"),
		qApp->applicationDirPath(), QObject::tr("Text (*.txt)"));

	GameManager::loadFile(filePath.toStdString());
	cout << filePath.toStdString() << endl;
	
	if (filePath != "") {
		QMessageBox msg;
		msg.setText("Load File Success!");
		startGame_slot();
		msg.exec();
	}

	if (!GameManager::checkKing()) {
		QMessageBox msg;
		if (GameManager::currentPlayer % 2 == 0) {
			msg.setText("黑方獲勝!");
		}
		else {
			msg.setText("紅方獲勝!");
		}
		msg.exec();
		reset();
	}

}

void Viewer::surrender_slot()
{
	if (!(QMessageBox::information(this, tr("Warning"), tr("是否確認投降?"), tr("Yes"), tr("No"))))
	{
		QMessageBox msg;
		if (GameManager::currentPlayer % 2 == 0) {
			msg.setText("黑方獲勝!");
		}
		else {
			msg.setText("紅方獲勝!");
		}
		msg.exec();
		if (!(QMessageBox::information(this, tr("Warning"), tr("是否要儲存檔案?"), tr("Yes"), tr("No"))))
		{
			saveGame_slot();
		}
		reset();
	}
	
}

void Viewer::saveGame_slot()
{
	QDateTime time = QDateTime::currentDateTime();
	QString str = time.toString("yyyy-MM-dd_hh-mm-ss");
	string path = "save\\" + str.toStdString() + ".txt";
	string command = "copy log.txt " + path;
	cout << command << endl;
	system(command.c_str());
	QMessageBox msg;
	msg.setText("存檔成功！\n檔案已存放至：\n目前目錄\\save\\"+str+".txt");
	msg.exec();
}
