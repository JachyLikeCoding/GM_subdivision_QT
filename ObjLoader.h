#pragma once
#ifndef OBJ_LOADER_H
#define OBJ_LOADER_H
#include "basic.h"
#include "DataStructure.h"
#include<QFile>
#include<QTextStream>
#include<QDebug>
#include<QQueue>

class Object {
public:
	int fileType;
	Object(){}
	void initObject(const QString &_objName,
		QQueue<Vertex *> &_vqueue,
		QQueue<Edge *> &_equeue,
		QQueue<Face *> &_fqueue);
	QQueue<Face *> getFqueue() { return fqueue; }
	QQueue<Edge *> getEqueue() { return equeue; }
	QQueue<Vertex *> getVqueue() { return vqueue; }
	void test();

private:
	QString objName;
	bool loadObj(const QString &objName);
	QQueue<Face *> fqueue;
	QQueue<Edge *> equeue;
	QQueue<Vertex *> vqueue;
};


#endif // !OBJ_LOADER_H