#pragma once
#include<string>
#include<memory>
#include<map>
#include<set>

struct Node
{
	int x,y;
	double r,g,b,a;
	std::string name;
	std::set<std::string> files;
	enum Shape {Circle, Rect, Diamond, Ellipse} outline;
	enum Line {Plant, Direct} line;
	enum Type {Dir = 4, File = 8} type;
};
std::ostream& operator<<(std::ostream& o, const std::shared_ptr<Node>& node);
std::map<std::string, int> getdir(std::string dir);
std::shared_ptr<Node> init(std::string dir);

#include"tgraph.h"

class MindMap : public Graph<std::shared_ptr<Node>>
{
public:
	MindMap(std::string s);

private:
	std::shared_ptr<Node> init(std::string s);
};


