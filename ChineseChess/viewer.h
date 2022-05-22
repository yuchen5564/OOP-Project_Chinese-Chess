#ifndef VIEWER_H
#define VIEWER_H

#include <QWidget>
#include <QPalette>
#include <QBrush>
#include <QPushButton>
#include <QMouseEvent>
#include <QMessageBox>
#include <QLabel>
#include <QPainter>
#include <QToolTip>
#include <QString>
#include <QFileDialog>
#include <QTimer>
#include <QLCDNumber>

QT_BEGIN_NAMESPACE
namespace Ui { class Viewer; }
QT_END_NAMESPACE

class Viewer : public QWidget
{
	Q_OBJECT

public:
	Viewer(QWidget* parent = nullptr);
	~Viewer();

	void setBoard(); //設定初始棋盤
	void menu();
	void paintEvent(QPaintEvent*);
	void mousePressEvent(QMouseEvent*);
	void mouseMoveEvent(QMouseEvent*);
	void reset();
	void afterMove();

public slots:
	void startGame_slot();
	void restartGame_slot(int f = 1);
	void loadFile_slot();
	void surrender_slot();
	void saveGame_slot(int f = 1);
	void timeout_slot();
	void startWithAI_slot();
	//void timeEvent(QTimerEvent *event);

private:
	Ui::Viewer* ui;

	QPushButton* startBtn; //開始遊戲
	QPushButton* quitBtn; //結束遊戲
	QPushButton* restartBtn; //重新開始
	QPushButton* loadBtn; //載入黨案
	QPushButton* surrenderBtn; //投降
	QPushButton* saveGameBtn; //存檔
	QPushButton* aiBtn;

	QLabel* title1; //封面標題
	QLabel* click_label; //顯示點選位置
	QLabel* nowPlayer_label;
	QLabel* time_label;	
	QLabel* checkKing_label;
	QLabel* gameMode_label;

	QTimer* timer;

	bool start = false;
	bool ai = false;

	int xPos = 10, yPos = 10; //點擊位置

	int counter = 0;
	const int setTime = 40;
};
#endif // VIEWER_H
