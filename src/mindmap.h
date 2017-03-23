#pragma once
#include<string>
#include<map>
#include<set>
#include"tgraph.h"

struct Node
{
	int x,y;//realative position to parent
	double r,g,b,a;
	std::string name;//equals directory name
	std::set<std::string> files;
	enum Shape {Circle, Rect, Diamond, Ellipse} outline;
	enum Line {Plant, Direct} line;
	enum Type {Dir = 4, File = 8} type;
	bool operator==(const Node& r);
};
std::ostream& operator<<(std::ostream& o, const Node& node);

class MindMap : public Graph<Node>
{
public:
	MindMap(std::string s);

private:
	Node init(std::string s);
};


