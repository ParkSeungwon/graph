//this is a Cairomm drawable class, just give a cairo context as argument to draw.
#pragma once
#include<complex>
#include<vector>
#include<initializer_list>
#include<string>
#include<sstream>
#include<gtkmm.h>
#include"mindnode.h"

class Drawable
{///all the drawing dependent part should be inside the operator()()
public:
	virtual void operator()(const Cairo::RefPtr<Cairo::Context>& cr);
	virtual void operator()();
	void line_width(int w);
	void set_rgb(double r, double g, double b);
	void set_rgba(double r, double g, double b, double a);
	template <typename T> void txt(T s) { 
		std::stringstream ss;
		ss << s;
		txt_ = ss.str(); 
	}
	void set_size(int size);
	void set_family(std::string family);
	void set_weight(int weight);
	
protected:
	double r_ = 0, g_ = 0, b_ = 0, a_ = 1;
	double color[4];
	int line_width_ = 3;
	std::string txt_;
	Point start_, end_;
	Pango::FontDescription font_;
};

class Line : public Drawable 
{
public:
	Line(std::initializer_list<Point> li);
	virtual void operator()(const Cairo::RefPtr<Cairo::Context>& cr);
	virtual void operator()();
protected:
	Line();
	std::vector<Point> points_;
};

class Arrow : public Line 
{
public:
	Arrow(Point s, Point e, int tip = 1);

protected:
	
};

class Box : public Line
{
public:
	Box(Point s, Point e);

protected:
};

class Diamond : public Line
{
public:
	Diamond(Point s, Point e);
};

class Ellipse : public Drawable
{
public:
	Ellipse(Point s, Point e);
	virtual void operator()(const Cairo::RefPtr<Cairo::Context>& cr);
	virtual void operator()();
};
