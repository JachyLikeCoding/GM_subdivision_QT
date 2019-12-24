#include "myOpenGL.h"
#include "ui_GM_Task_ZC.h"
#include<QFile>
#include<QDebug>
#include<QTextStream>

myOpenGL::myOpenGL(QWidget *parent) :QGLWidget(parent) {
}

myOpenGL::~myOpenGL(){}

void myOpenGL::zoomin()
{
	for (auto v : vqueue)
		v->coord *= 2;
}

void myOpenGL::zoomout()
{
	for (auto v : vqueue)
		v->coord /= 2;
}

void myOpenGL::initializeGL(){}

void myOpenGL::resizeGL(int _width, int _height) {
	width = _width;
	height = _height;
	glMatrixMode(GL_PROJECTION);
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
	glLoadIdentity();
	gluPerspective(60.0, (GLdouble)width / (GLdouble)height, 1.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(10, 10, 10, 0, 0, 0, 0, 1, 0);
}

void myOpenGL::displayModel()
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_LIGHT0);
	// glEnable(GL_LIGHT1);
	GLfloat mat_specular[] = { 0.8, 0.8, 0.8, 1.0 };
	GLfloat mat_shininess[] = { 40.0 };
	GLfloat Light_ambient[] = { 0.5, 0.5, 0.5, 1.0 };            //环境光参数
	GLfloat Light_specular[] = { 0.8, 0.8, 0.8, 1.0f };          //镜面反射参数
	GLfloat Light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };        //漫反射参数
	GLfloat light0_position[] = { 28.0f, 18.0f, 4.0f, 0.0f };    // 0：平行光，1：点光源
	GLfloat light1_position[] = { -28.0f, -18.0f, 4.0f, 0.0f };  // 0：平行光，1：点光源
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	//灯光设置
	glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, Light_diffuse);    //散射光属性
	glLightfv(GL_LIGHT0, GL_SPECULAR, Light_specular);  //镜面反射光
	glLightfv(GL_LIGHT0, GL_AMBIENT, Light_ambient);    //环境光参数
	glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, Light_diffuse);    //散射光属性
	glLightfv(GL_LIGHT1, GL_SPECULAR, Light_specular);  //镜面反射光
	glLightfv(GL_LIGHT1, GL_AMBIENT, Light_ambient);    //环境光参数
	glEnable(GL_LIGHTING);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	GLfloat cube_mat_ambient[] = { 1.0, 0.8, 0.8, 1.0f };
	GLfloat cube_mat_diffuse[] = { 0.5, 0.5, 0.5, 1.0f };
	GLfloat cube_mat_specular[] = { 0.6, 0.6, 0.6, 1.0f };
	glMaterialfv(GL_FRONT, GL_AMBIENT, cube_mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, cube_mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, cube_mat_specular);
	glPushMatrix();
	{
		glRotatef(angleX, 1.0f, 0.0f, 0.0f);
		glRotatef(angleY, 0.0f, 1.0f, 0.0f);
		if (!mode) {//face mode
			glBegin(GL_QUADS);
			for (int i = 0; i < fqueue.size(); i++) {
				fqueue[i]->faceDisplay();
			}
		}
		else{//line frame mode
			glBegin(GL_LINES);
			for (int i = 0; i < equeue.size(); i++) {
				equeue[i]->edgeDisplay();
			}
		}
	}
	glPopMatrix();
	glEnd();
	glFlush();
}

void myOpenGL::paintGL() {
	obj.initObject(objName, vqueue, equeue, fqueue);
	obj.test();
	vqueue = obj.getVqueue();
	equeue = obj.getEqueue();
	fqueue = obj.getFqueue();

	if (mode == 0) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	else
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	qDebug() << " before subdivision: " << endl;
	qDebug() << " faceQueue.size()" << fqueue.size() << endl;
	qDebug() << " edgeQueue.size()" << equeue.size() << endl;
	qDebug() << " vertexQueue.size()" << vqueue.size() << endl;
	clock_t start, end;
	start = clock();
	processor.subdivision(level, vqueue, equeue, fqueue);
	end = clock();
	displayModel();
	qDebug() << " after subdivision: " << endl;
	qDebug() << " faceQueue.size()" << fqueue.size() << endl;
	qDebug() << " edgeQueue.size()" << equeue.size() << endl;
	qDebug() << " vertexQueue.size()" << vqueue.size() << endl;
	fcount = fqueue.size();
	vcount = vqueue.size();
	time = (end - start) * 1000.0 / CLOCKS_PER_SEC;
}