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

	timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(timeout_slot()));
	timer->stop();
}

Viewer::~Viewer()
{
	delete ui;
}

void Viewer::menu() {

	start = false;
	ai = false;
	timer->stop();

	Board::clearMove();
	setFixedSize(300, 300);

	title1 = new QLabel("中國象棋", this);
	title1->setFont(QFont("微軟正黑體", 20));
	title1->setGeometry(90, 20, 150, 30);

	startBtn = new QPushButton("開始遊戲", this);
	startBtn->setGeometry(90, 80, 120, 40);
	startBtn->setFlat(0);

	loadBtn = new QPushButton("讀檔開始", this);
	loadBtn->setGeometry(90, 130, 120, 40);
	loadBtn->setFlat(0);

	aiBtn = new QPushButton("人機對弈", this);
	aiBtn->setGeometry(90, 180, 120, 40);
	aiBtn->setFlat(0);

	quitBtn = new QPushButton("結束遊戲", this);
	quitBtn->setGeometry(90, 230, 120, 40);
	quitBtn->setFlat(0);

	title1->show();
	startBtn->show();
	loadBtn->show();
	quitBtn->show();
	aiBtn->show();

	GameManager::restartGame();

	connect(startBtn, SIGNAL(clicked(bool)), this, SLOT(startGame_slot()));
	connect(quitBtn, SIGNAL(clicked(bool)), qApp, SLOT(quit()));
	connect(loadBtn, SIGNAL(clicked(bool)), this, SLOT(loadFile_slot()));
	connect(aiBtn, SIGNAL(clicked(bool)), this, SLOT(startWithAI_slot()));
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

	timer->start(1000);

	gameMode_label = new QLabel(" ", this);
	gameMode_label->setFont(QFont("微軟正黑體", 15));
	gameMode_label->setGeometry(40, 1, 200, 30);
	if (ai) gameMode_label->setText("目前模式：人機對弈");
	else gameMode_label->setText("目前模式：一般");

	click_label = new QLabel(" ", this);
	click_label->setFont(QFont("微軟正黑體", 15));
	click_label->setGeometry(1, 1, 150, 30);

	time_label = new QLabel(" ", this);
	time_label->setFont(QFont("微軟正黑體", 15));
	time_label->setGeometry(556, 5, 150, 30);

	checkKing_label = new QLabel(" ", this);
	checkKing_label->setFont(QFont("微軟正黑體", 25));
	checkKing_label->setGeometry(550, 300, 150, 120);
	if (ai) checkKing_label->setText(QString(" "));
	

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

		//=============================================================================

		static int press = 0;
		static int index = -1;
		static int nx, ny; //第二次選取的點
		static int tmpX, tmpY; //紀錄第一次點到的棋子
		int nowPlayer = GameManager::currentPlayer % 2;

		if (nowPlayer == 0) nowPlayer = 1;
		else if (nowPlayer == 1) nowPlayer = -1;

		if (press == 1) {
			nx = xPos;
			ny = yPos;
			press++;
		}
		else if (press == 0) {
			//Board::printVirtualMove();
			for (int i = 0; i < Board::onBoard.size(); i++) {

				//取出棋子位置
				tmpX = Board::onBoard[i]->getX();
				tmpY = Board::onBoard[i]->getY();


                if (xPos == tmpX && yPos == tmpY && Board::onBoard[i]->alive
					&& nowPlayer == Board::onBoard[i]->color) {	//第一次抓取位置
					Board::onBoard[i]->canMove(0);
					//Board::printMove();
					index = i;
					press++;
					break;
				}

			}
		}
		if (press == 2) {
            press = 0;
            //Board::clearMove();
            if (Board::board[nx][ny] == 0 && Board::move[nx][ny] == 1) { //移動位置為空 --> 移動棋子
				
                Board::onBoard[index]->move(nx, ny);
				
			
				//Board::clearVirtualMove();
				Board::onBoard[index]->makeLog(tmpX, tmpY);
				afterMove();
                Board::clearMove();
                //消除選取框
                xPos = 10;
				yPos = 10;

				if (ai && GameManager::currentPlayer % 2 == 1) {
					GameManager::aiGame();
					if (GameManager::currentPlayer % 2 == 0) {
						nowPlayer_label->setText(QString("現在輪到\n　紅方"));
					}
					else {
						nowPlayer_label->setText(QString("現在輪到\n　黑方"));
					}
					//cout << GameManager::currentPlayer << endl;
				}

			}
            else if(Board::board[nx][ny] == Board::onBoard[index]->color*-1 ) //吃棋
            {
				if (Board::move[xPos][yPos] == 1) {
					for (int i = 0; i < Board::onBoard.size(); i++)
					{
						int tx = Board::onBoard[i]->getX();
						int ty = Board::onBoard[i]->getY();


						if (nx == tx && ny == ty && Board::onBoard[i]->alive) {
							Board::onBoard[i]->alive = false;
							Board::onBoard[i]->fakeAlive = false;


						}
					}
					Board::onBoard[index]->move(nx, ny);
					
	
					//Board::clearVirtualMove();
					Board::onBoard[index]->makeLog(tmpX, tmpY);
					afterMove();
				}
				Board::clearMove();
				//消除選取框
				xPos = 10;
				yPos = 10;
				if (ai && GameManager::currentPlayer % 2 == 1) {
					GameManager::aiGame();
					if (GameManager::currentPlayer % 2 == 0) {
						nowPlayer_label->setText(QString("現在輪到\n　紅方"));
					}
					else {
						nowPlayer_label->setText(QString("現在輪到\n　黑方"));
					}
					//cout << GameManager::currentPlayer << endl;
				}
            }
			else { //移動位置有棋 --> 視為重新選定 && 不能移動(canMove!=1)
				Board::clearMove();
				for (int i = 0; i < Board::onBoard.size(); i++) {

					//取出棋子位置
					tmpX = Board::onBoard[i]->getX();
					tmpY = Board::onBoard[i]->getY();


                    if (xPos == tmpX && yPos == tmpY && Board::onBoard[i]->alive) {	//第一次抓取位置
						Board::onBoard[i]->canMove(0);
						index = i;
						press++;
						break;
					}

				}
			}
		}

		//cout << "\n\nmousePressEvent:\n\n";
		//Board::printBoard();

		Board::clearVirtualMove();
		if (GameManager::isCheck(1))
		{
			//Board::printVirtualMove();
			checkKing_label->setText(QString("<font color=red>注意!將軍!</font>"));

		}
		else
		{
			checkKing_label->setText(QString(" "));

		}
		Board::clearVirtualMove();
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
	aiBtn->hide();

	time_label->show();
	checkKing_label->show();
	
	gameMode_label->show();
	time_label->setText(QString("<font color=black>剩餘時間: %1 秒</font>").arg(setTime));
	counter =-1;

	click_label->show();
	nowPlayer_label->show();
	surrenderBtn->show();
	saveGameBtn->show();
	timer->start(1000);
	checkKing_label->show();
}

void Viewer::reset()
{
	//0513 ADD
	if (!(QMessageBox::information(this, tr("Info"), tr("是否再來一局?"), tr("再來一局"), tr("回到主畫面")))) {
		counter = -1;
		GameManager::restartGame();
		if (GameManager::currentPlayer % 2 == 0) {
			nowPlayer_label->setText(QString("現在輪到\n　紅方"));
		}
		else {
			nowPlayer_label->setText(QString("現在輪到\n　黑方"));
		}
		timer->start(1000);
		counter = -1;
	}
	else {
		menu();
		click_label->hide();
		time_label->hide();
		checkKing_label->hide();
		checkKing_label->setText(QString(" "));
		gameMode_label->hide();
		nowPlayer_label->hide();
	}
}

//重設計時器、判斷結束、切換下棋方、判斷欠行
void Viewer::afterMove()
{
	counter = -1;
	timer->stop();
	timer->start(1000);

	
	if (!GameManager::checkKing()) {
		timer->stop();
		QMessageBox msg;
		if (GameManager::currentPlayer % 2 == 0) {
			msg.setText("黑方獲勝!");
		}
		else {
			msg.setText("紅方獲勝!");
		}
		msg.exec();
		saveGame_slot(0);
		reset();
	}

	if (GameManager::currentPlayer % 2 == 0) {
		nowPlayer_label->setText(QString("現在輪到\n　紅方"));
	}
	else {
		nowPlayer_label->setText(QString("現在輪到\n　黑方"));
	}

	Board::clearVirtualMove();
	if (GameManager::stalemate() && start) {//move

		cout << "is stalemate~\n";
		timer->stop();
		QMessageBox msg;
		if (GameManager::currentPlayer % 2 == 0) {
			msg.setText("紅方欠行，黑方獲勝!");
		}
		else {
			msg.setText("黑方欠行，紅方獲勝!");
		}
		msg.exec();
		saveGame_slot(0);
		reset();
	}
	Board::clearVirtualMove();
}

void Viewer::restartGame_slot(int f) {
	timer->stop();
	if (!(QMessageBox::information(this, tr("Warning"), tr("是否確認重新開始遊戲?"), tr("Yes"), tr("No"))))
	{
		counter = -1;
		saveGame_slot();
		GameManager::restartGame();
		if (GameManager::currentPlayer % 2 == 0) {
			nowPlayer_label->setText(QString("現在輪到\n　紅方"));
		}
		else {
			nowPlayer_label->setText(QString("現在輪到\n　黑方"));
		}
		timer->start(1000);
	}
	else {
		if(f == 1)timer->start(1000);
	}
}

void Viewer::loadFile_slot()
{
	//nowPlayer_label->setText(" ");
	GameManager::restartGame();
	QString filePath = QFileDialog::getOpenFileName(NULL, QObject::tr("Open File"),
		qApp->applicationDirPath(), QObject::tr("Text (*.txt)"));

	GameManager::loadFile(filePath.toStdString());
	cout << filePath.toStdString() << endl;
	
	if (filePath != "") {
		QMessageBox msg;
		msg.setText("Load File Success!");
		startGame_slot();
		msg.exec();
		afterMove();
		Board::clearMove();
	}

	
	/*if (!GameManager::checkKing()) {
		QMessageBox msg;
		if (GameManager::currentPlayer % 2 == 0) {
			msg.setText("黑方獲勝!");
		}
		else {
			msg.setText("紅方獲勝!");
		}
		msg.exec();
		reset();
	}*/
	
}

void Viewer::surrender_slot()
{
	timer->stop();
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
		saveGame_slot(0);
		reset();
	}
	else {
		timer->start(1000);
	}
	
}

void Viewer::saveGame_slot(int f)
{
	timer->stop();
	if (!(QMessageBox::information(this, tr("Warning"), tr("是否要儲存檔案?"), tr("Yes"), tr("No"))))
	{
		QDateTime time = QDateTime::currentDateTime();
		QString str = time.toString("yyyy-MM-dd_hh-mm-ss");
		string path = "save\\" + str.toStdString() + ".txt";
		string command = "copy log.txt " + path;
		cout << command << endl;
		system(command.c_str());
		QMessageBox msg;
		msg.setText("存檔成功！\n檔案已存放至：\n目前目錄\\save\\" + str + ".txt");
		msg.exec();
		timer->start(1000);
	}
	else {
		if (f == 1) timer->start(1000);
		else if (start) timer->start(1000);
	}
}

void Viewer::timeout_slot()
{
	if (counter == setTime) {
		
		QMessageBox::warning(this, "timer", QString("時間到"));
		timer->stop();
		QMessageBox msg;
		if (GameManager::currentPlayer % 2 == 0) {
			msg.setText("黑方獲勝!");
		}
		else {
			msg.setText("紅方獲勝!");
		}
		msg.exec();
		//start = false;
		saveGame_slot(0);
		reset();
	}
	else {
		counter++;
		if (setTime - counter < 10) {
			time_label->setText(QString("<font color=red>剩餘時間: %1 秒</font>").arg(setTime-counter));
		}
		else {
			time_label->setText(QString("<font color=black>剩餘時間: %1 秒</font>").arg(setTime - counter));
		}
		
	}
	
}

void Viewer::startWithAI_slot()
{
	GameManager::restartGame();
	//Board::printVirtualMove();
	ai = true;
	startGame_slot();
	GameManager::currentPlayer = 0;
	//GameManager::aiGame();
}


