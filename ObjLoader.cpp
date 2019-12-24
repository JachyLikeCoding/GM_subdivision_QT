#include "ObjLoader.h"

void Object::initObject(const QString &_objName, 
										QQueue<Vertex *> &_vqueue,
										QQueue<Edge *> &_equeue,
										QQueue<Face *> &_fqueue) {
	objName = _objName;
	fqueue = _fqueue;
	vqueue = _vqueue;
	equeue = _equeue;
	bool flag = loadObj(objName);
	if (!flag) 
	{
		qDebug() << "ERROR: File loaded fail. Please check your file '.\n";
	}
}


bool Object::loadObj(const QString &objName) {
	QFile file(objName);
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
		qDebug() << "Can't open the file!" << endl;
		return false;
	}
	QStringList list;
	vqueue.clear();
	equeue.clear();
	fqueue.clear();
	QString line;
	GLfloat x, y, z;
	QQueue<Vertex *> tmpvqueue;
	while(!file.atEnd()){
		QByteArray line = file.readLine();
		QString str(line);
		if (str.length() < 2)
			continue;
		else if (str[0] == 'v' && str[1] == ' ') {
			str = str.remove(0, 1).trimmed();
			list = str.split(' ');
			GLfloat x, y, z;
			x = list[0].toFloat();
			y = list[1].toFloat();
			z = list[2].toFloat();
			tmpvqueue.push_back(new Vertex(x,y,z));
		}
		else if (str[0] == 'f' && str[1] == ' ') {
			str = str.trimmed();
			list = str.split(' ');
			if (list.length() == 4) {//三角形
				fileType = 3;
				int vid[3];
				if (list[1].contains('/')) {
					for (int i = 1; i < list.length(); i++) {
						QStringList sublist = list[i].split('/');
						vid[i-1] = sublist[0].toInt() - 1;
					}
					Face *f = new Face(tmpvqueue[vid[0]], tmpvqueue[vid[1]], tmpvqueue[vid[2]], equeue, vqueue);
					fqueue.push_back(f);
				}
				else {
					for (int i = 1; i < list.length(); i++) {
						vid[i-1] = list[i].toInt() - 1;
					}
					Face *f = new Face(tmpvqueue[vid[0]], tmpvqueue[vid[1]], tmpvqueue[vid[2]], equeue, vqueue);
					fqueue.push_back(f);
				}
			}
			else if (list.length() == 5) {//四边形
				fileType = 4;
				int vid[4];
				if (list[1].contains('/')) {
					for (int i = 1; i < list.length(); i++) {
						QStringList sublist = list[i].split('/');
						vid[i-1] = sublist[0].toInt() - 1;
					}
					Face *f = new Face(tmpvqueue[vid[0]], tmpvqueue[vid[1]], tmpvqueue[vid[2]], tmpvqueue[vid[3]], equeue, vqueue);
					fqueue.push_back(f);
				}
				else {
					for (int i = 1; i < list.length(); i++) {
						vid[i-1] = list[i].toInt() - 1;
					}
					Face *f = new Face(tmpvqueue[vid[0]], tmpvqueue[vid[1]], tmpvqueue[vid[2]], tmpvqueue[vid[3]], equeue, vqueue);
					fqueue.push_back(f);
				}
			}
		}
		else
		{
			continue;
		}
	}
	file.close();
	qDebug() << "tmpvqueue count:" << tmpvqueue.size() << endl;
	return true;
}


//just for debug
void Object::test() {
	qDebug() << "obj file type: " << fileType << endl;
	qDebug() << "face count: " << fqueue.size() << endl;
	qDebug() << "vertices count:" << vqueue.size() << endl;
	qDebug() << "edges count:" << equeue.size() << endl;
	qDebug() << endl;
}
