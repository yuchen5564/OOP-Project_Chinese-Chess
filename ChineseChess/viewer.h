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

public slots:
	void startGame_slot();
	void restartGame_slot();
	void loadFile_slot();
	void surrender_slot();
	void saveGame_slot();

private:
	Ui::Viewer* ui;

	QPushButton* startBtn; //開始遊戲
	QPushButton* quitBtn; //結束遊戲
	QPushButton* restartBtn; //重新開始
	QPushButton* loadBtn; //載入黨案
	QPushButton* surrenderBtn; //投降
	QPushButton* saveGameBtn; //存檔

	QLabel* title1; //封面標題
	QLabel* click_label; //顯示點選位置
	QLabel* nowPlayer_label;

	bool start = false;
	int xPos = 10, yPos = 10; //點擊位置
};
#endif // VIEWER_H
