#include "gtk/drawable.h"
#include <glut.h>
using namespace std;

void Line::operator()() 
{
	glColor3f(r_, g_, b_);
	glBegin(GL_LINE_STRIP);
	for(auto& a : points_) glVertex3f(a.x(), x.y(), 0);
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
	glBegin();
}

Ellipse::~Ellipse() 
{
	gluDeleteQuadric(obj);
}

