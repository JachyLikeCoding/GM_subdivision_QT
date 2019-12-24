#pragma once
#include <QtWidgets/QWidget>
#include <QtWidgets/QMainWindow>
#include "ui_GM_Task_ZC.h"
#include <QDebug>
#include <QButtonGroup>
#include <QtGui>
#include <QtCore>
#include <QRect>
#include <QFileDialog>
#include <QMessageBox>

class GM_Task_ZC : public QMainWindow
{
	Q_OBJECT

public:
	GM_Task_ZC(QMainWindow *parent = Q_NULLPTR);

public slots:
	void displayModeChoose();
	void levelChoose();
	void getTime();
	void subdivision();
	void zoomin();
	void zoomout();
	void keyPressEvent(QKeyEvent *e);
	void mousePressEvent(QMouseEvent *event);
	void mousehandle();
	void openFile();

private:
	QButtonGroup* groupButton1_modeChoose;
	QButtonGroup* groupButton2_levelChoose;
	QLabel* link;
	Ui::GM_Task_ZCClass ui;
	GLfloat rTri;
	bool fullscreen;
};