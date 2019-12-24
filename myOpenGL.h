#pragma once
#include<GL/glut.h>
#include<QGLWidget>
#include "basic.h"
#include "ObjLoader.h"
#include "processor.h"

class myOpenGL : public QGLWidget
{
	Q_OBJECT
public:
	explicit myOpenGL(QWidget *parent = nullptr);
	~myOpenGL();
	bool mode = false;  // mode: show face or line : 0->face; 1->line
	int level = 0;
	int vcount = 0;
	int fcount = 0;
	double time = 0;
	QQueue<Vertex*> getVqueue() { return vqueue; }
	void zoomin();
	void zoomout();
	QString objName = "Models/cube.obj";

protected:
	void initializeGL();
	void paintGL();
	void resizeGL(int width, int height);
	
private:
	Object obj;
	QQueue<Face*> fqueue;
	QQueue<Edge*> equeue;
	QQueue<Vertex*> vqueue;
	int width, height;
	bool in;
	int angleX = 0, angleY = 0;
	SubdivisionProcessor processor;
	void displayModel();


};

