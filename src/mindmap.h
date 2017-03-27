#pragma once
#include<string>
#include<map>
#include<memory>
#include"point.h"
#include"tgraph.h"

std::map<std::string, int> getdir(std::string dir);
struct MindNode
{
	std::string name, path;//equals directory name
	bool show;
	Point pt;//realative position to parent
	enum Shape {Circle, Rect, Diamond, Ellipse} outline = Ellipse;
	enum Line {Plant, Direct} line = Direct;
	enum Type {Dir = 4, File = 8} type;
	unsigned char r,g,b,a;

	MindNode(std::string filename, MindNode::Type type);
	bool operator==(const MindNode& r);
};

void construct_graph(Graph<std::shared_ptr<MindNode>>& graph, std::string dir, 
		std::shared_ptr<MindNode> parent);
void save_graph(Vertex<std::shared_ptr<MindNode>>* v, std::string dir);

std::ostream& operator<<(std::ostream& o, const MindNode& node);
std::ostream& operator<<(std::ostream& o, Graph<std::shared_ptr<MindNode>>& r);
std::istream& operator>>(std::istream& i, MindNode& r);
