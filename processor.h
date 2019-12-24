#pragma once
#include "ObjLoader.h"

Edge* getEdge(Edge &edge, QQueue<Edge *> &equeue);
Vertex* getVertex(Vertex &v, QQueue<Vertex *> &vqueue);

class SubdivisionProcessor {
public:
	Object obj;
	void initProcessor(Object &_obj);
	void subdivision(int level, QQueue<Vertex *> &vqueue, QQueue<Edge *> &equeue, QQueue<Face *> &fqueue);
	void subdivision3(int level, QQueue<Vertex *> &vqueue, QQueue<Edge *> &equeue, QQueue<Face *> &fqueue);
	void subdivision4(int level, QQueue<Vertex *> &vqueue, QQueue<Edge *> &equeue, QQueue<Face *> &fqueue);
};