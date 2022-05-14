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
#include <qobject.h>

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

public slots:
	void startGame_slot();
	void restartGame_slot();

private:
	Ui::Viewer* ui;

	QPushButton* startBtn;
	QPushButton* quitBtn;
	QPushButton* restartBtn;

	QLabel* title1; //封面標題
	QLabel* label; //顯示點選位置

	bool start = false;
	int xPos = 10, yPos = 10; //點擊位置
};
#endif // VIEWER_H