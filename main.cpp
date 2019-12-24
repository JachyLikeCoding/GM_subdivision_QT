#include "GM_Task_ZC.h"
#include <QtWidgets/QApplication>
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	a.setStyle("macintosh");
	GM_Task_ZC w;
	w.show();
	return a.exec();
}