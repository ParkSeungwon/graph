#include<glut.h>
#include"gtk/drawable.h"
#include"gtk/graphv.h"
using namespace std;

GraphV<char>* grv;
void Line::operator()() 
{
	//Drawable::operator()();
	glColor3f(r_, g_, b_);
	glLineWidth(line_width_);
	glBegin(GL_LINE_STRIP);
	for(auto& a : points_) glVertex3f(a.x(), -a.y(), 0);
	glEnd();
}

void Drawable::operator()()
{
	glColor3f(r_, g_, b_);
	auto a = (start_ + end_) / 2.0;
	for(int i=0; i<txt_.size(); i++) {
		glRasterPos2f(a.real() - 12 + i * 10, -a.imag() - 12);
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, txt_[i]);
	}
}

void Ellipse::operator()()
{
	Drawable::operator()();
	glColor3f(r_, g_, b_);
	glLineWidth(line_width_);
	Point c{(start_ + end_ ) / 2.0};
	Point p;
	Point one{1, 0};
	int w = abs(start_.x() - end_.x());
	int h = abs(start_.y() - end_.y());
	complex<double> im{cos(M_PI / 30), sin(M_PI / 30)};
	glBegin(GL_LINE_STRIP);
	for(int i=0; i<61; i++) {
		one *= im;
		p = c + CIRCLE_SIZE * one;
		glVertex3f(p.x(), -p.y(), 0);
	}
	glEnd();
//	glTranslatef(a.real(), a.imag(), 0);
//	glutWireSphere(1.5, 50, 50);
//	glLoadIdentity();
//	obj = gluNewQuadric();
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
