#include <glut.h>
#include "gtk/drawable.h"
#include"gtk/graphv.h"
using namespace std;

GraphV<char>* grv;
void Line::operator()() 
{
	glColor3f(r_, g_, b_);
	glLineWidth(line_width_);
	glBegin(GL_LINE_STRIP);
	for(auto& a : points_) glVertex3f(a.x(), -a.y(), 0);
	glEnd();
}

void Drawable::operator()()
{
	glColor3f(r_, g_, b_);


}

void Ellipse::operator()()
{
	glColor3f(r_, g_, b_);
	obj = gluNewQuadric();
}

Ellipse::~Ellipse() 
{
	//if(obj) gluDeleteQuadric(obj);
}

void render() 
{
	glClear(GL_COLOR_BUFFER_BIT);
	for(auto& a : *grv) (*a)();	
	glutSwapBuffers();
}
void init()
{
	glClearColor(1,1,1,1);
	glMatrixMode(GL_PROJECTION);
	glOrtho(0, 4000, -1000, 0, -1, 1);
}
