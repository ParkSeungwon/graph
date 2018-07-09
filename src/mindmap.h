#pragma once
#include<string>
#include<map>
#include<memory>
#include"point.h"
#include"tgraph.h"

std::map<std::string, int> getdir(std::string dir);
struct MindNode
{
	std::string name, full_path;//equals directory name
	bool show, shrink;
	Point pt;//realative position to parent
	enum Shape {Picture, Rect, Diamond, Ellipse} outline = Ellipse;
	enum Line {Plant, Direct} line = Direct;
	enum Type {Dir = 4, File = 8, Memo = 0} type;//add memo type
	unsigned char color[3][4];//3 : text arrow shape, 4 : r g b a
	short width, height;
	std::string memo;

	MindNode(std::string filename, MindNode::Type type);
	bool operator==(const MindNode& r);
};

std::ostream& operator<<(std::ostream& o, const MindNode& node);
std::istream& operator>>(std::istream& i, MindNode& r);
