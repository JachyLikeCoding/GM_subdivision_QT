#include "GM_Task_ZC.h"

GM_Task_ZC::GM_Task_ZC(QMainWindow *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	rTri = 0.0;
	fullscreen = false;
	groupButton1_modeChoose = new QButtonGroup(this);
	groupButton1_modeChoose->addButton(ui.faceButton, 0);
	groupButton1_modeChoose->addButton(ui.lineButton, 1);
	ui.faceButton->setChecked(true);
	
	groupButton2_levelChoose = new QButtonGroup(this);
	groupButton2_levelChoose->addButton(ui.level1, 1);
	groupButton2_levelChoose->addButton(ui.level2, 2);
	groupButton2_levelChoose->addButton(ui.level3, 3);
	groupButton2_levelChoose->addButton(ui.level4, 4);
	groupButton2_levelChoose->addButton(ui.level0, 0);
	ui.level0->setChecked(true);

	connect(ui.faceButton, SIGNAL(clicked(bool)), this, SLOT(displayModeChoose()));
	connect(ui.lineButton, SIGNAL(clicked(bool)), this, SLOT(displayModeChoose()));
	connect(ui.level1, SIGNAL(clicked(bool)), this, SLOT(levelChoose()));
	connect(ui.level2, SIGNAL(clicked(bool)), this, SLOT(levelChoose()));
	connect(ui.level3, SIGNAL(clicked(bool)), this, SLOT(levelChoose()));
	connect(ui.level4, SIGNAL(clicked(bool)), this, SLOT(levelChoose()));
	connect(ui.level0, SIGNAL(clicked(bool)), this, SLOT(levelChoose()));
	connect(ui.SubdivisionStart, SIGNAL(clicked()), this, SLOT(subdivision()));
	connect(ui.SubdivisionStart, SIGNAL(clicked()), this, SLOT(getTime()));
	connect(ui.zoomin, SIGNAL(clicked()), this, SLOT(zoomin()));
	connect(ui.zoomout, SIGNAL(clicked()), this, SLOT(zoomout()));
	connect(ui.chooseModelFile, SIGNAL(clicked()), this, SLOT(openFile()));

	ui.chooseModelFile->setStyleSheet("border:2px groove gray;border-radius:10px;padding:2px 4px;");
	ui.zoomin->setStyleSheet("border:2px groove gray;border-radius:10px;padding:2px 4px;");
	ui.zoomout->setStyleSheet("border:2px groove gray;border-radius:10px;padding:2px 4px;");
	ui.SubdivisionStart->setStyleSheet(
		"border:2px navajowhite;border-radius:10px;padding:2px 4px;"
		"background-color: navajowhite;"
		"selection-color: gray;"
		"selection-background-color: gray;");
	ui.link->setOpenExternalLinks(true);		//设置点击打开链接
	ui.link->setText("<style> a {text-decoration: none} </style> <a href=\"https://en.wikipedia.org/wiki/Catmull%E2%80%93Clark_subdivision_surface\"> Wikipedia");
}


void GM_Task_ZC::levelChoose()
{
	switch (groupButton2_levelChoose->checkedId())
	{
	case 0:
		ui.openGLWidget->level = 0;
		qDebug() << "level = 0" << endl;
		break;
	case 1:
		ui.openGLWidget->level = 1;
		qDebug() << "level = 1" << endl;
		break;
	case 2:
		ui.openGLWidget->level = 2;
		qDebug() << "level = 2" << endl;
		break;
	case 3:
		ui.openGLWidget->level = 3;
		qDebug() << "level = 3" << endl;
		break;
	case 4:
		ui.openGLWidget->level = 4;
		qDebug() << "level = 4" << endl;
		break;
	default:
		break;
	}
}

void GM_Task_ZC::getTime()
{
	QString time = QString::number(ui.openGLWidget->time);
	ui.timeLabel_2->setText(time + " ms");
	QString faceCount = QString::number(ui.openGLWidget->fcount);
	qDebug() << "face Count = " << faceCount << endl;
	ui.fcount->setText(faceCount);
	QString vCount = QString::number(ui.openGLWidget->vcount);
	qDebug() << "vertex Count = " << vCount << endl;
	ui.vcount->setText(vCount);
}

void GM_Task_ZC::subdivision()
{
	ui.openGLWidget->updateGL();
	qDebug() << "Start subdivision!!!!" << endl;
}

void GM_Task_ZC::displayModeChoose() 
{
	switch (groupButton1_modeChoose->checkedId()) 
	{
	case 0:
			ui.openGLWidget->mode = 0;
			qDebug() << "mode = 0" << endl;
			break;
	case 1:
			ui.openGLWidget->mode = 1;
			qDebug() << "mode = 1" << endl;
			break;
	default:
			break;
	}
}

void GM_Task_ZC::keyPressEvent(QKeyEvent *e)
{
	switch (e->key())
	{
		//F1键为全屏和普通屏显示切换键
	case Qt::Key_F1:
		fullscreen = !fullscreen;
		if (fullscreen)
			showFullScreen();
		else
			showNormal();
		ui.openGLWidget->updateGL();
		break;
		//Ese为退出程序键
	case Qt::Key_Escape:
		close();
	}
}

void GM_Task_ZC::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton)  //按左键旋转
	{
		qDebug() << "LeftButton" << endl;
		mousehandle();
	}
}

void GM_Task_ZC::mousehandle()
{
	rTri += 5;
	if (rTri > 360)
	{
		rTri -= 360;
	}
	glRotatef(rTri, 0.0, 1.0, 0.0);
	qDebug() << "rTri = " << rTri << endl;
	ui.openGLWidget->updateGL();
}

void GM_Task_ZC::openFile()
{
	QString openFile = "";
	QString s = QDir::currentPath();
	//QString s = QCoreApplication::applicationDirPath();
	//文件对话框获取要打开的文件名
	openFile = QFileDialog::getOpenFileName(this, "Open", s, "model file(*.obj *.txt)");
	//打印要打开的文件名
	QMessageBox::information(this, "Open", openFile);
	ui.openGLWidget->objName = openFile;
}

void GM_Task_ZC::zoomout() {
	qDebug() << "zoomout" << endl;
	glScalef(0.5, 0.5, 0.5);
	ui.openGLWidget->updateGL();
}

void GM_Task_ZC::zoomin() {
	qDebug() << "zoomin" << endl;
	glScalef(2, 2, 2);
	ui.openGLWidget->updateGL();
}