#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_GM_Task_ZC.h"

class GM_Task_ZC : public QMainWindow
{
	Q_OBJECT

public:
	GM_Task_ZC(QWidget *parent = Q_NULLPTR);

private:
	Ui::GM_Task_ZCClass ui;
};
