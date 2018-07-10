#pragma once
#include<string>
#include<map>
#include<memory>
#include<complex>
#include"graph.h"

struct Point : public std::complex<double>
{
	Point(int x=0, int y=0);
	Point(std::complex<double> im);
	int x() const; 		
	int y() const; 	
};

std::map<std::string, int> getdir(std::string dir);
struct MindNode
{//will use weight as relative position : weight / 10000 = x, weight % 10000 = y
	std::string name, full_path;//equals directory name
	bool show;//show this node or not
	bool shrink = false;//show sub nodes or not
	enum Shape {Picture, Rect, Diamond, Ellipse} outline;
	enum Line {Plant, Direct} line = Direct;
	enum Type {Dir = 4, File = 8, Virtual = 0} type;//add memo type
	unsigned char color[3][4];//3 : text arrow shape, 4 : r g b a
	short width, height;
	std::string tooltip;

	MindNode();
	MindNode(std::string filename, MindNode::Type type);
	bool operator==(const MindNode& r);
};

std::ostream& operator<<(std::ostream& o, const MindNode& node);
std::istream& operator>>(std::istream& i, MindNode& r);
