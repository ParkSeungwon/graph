#pragma once
#include<string>
#include<map>
#include<memory>
#include"point.h"
#include"tgraph.h"

std::map<std::string, int> getdir(std::string dir);
struct MindNode
{
	enum Shape {Circle, Rect, Diamond, Ellipse} outline = Ellipse;
	enum Line {Plant, Direct} line = Direct;
	enum Type {Dir = 4, File = 8} type;
	MindNode(std::string filename, MindNode::Type type);
	Point pt;//realative position to parent
	double r,g,b,a;
	bool show;
	std::string name;//equals directory name
	bool operator==(const MindNode& r);
};

std::shared_ptr<MindNode> 
construct_graph(Graph<std::shared_ptr<MindNode>>& gr, std::string dir);

std::ostream& operator<<(std::ostream& o, const MindNode& node);

