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

template<typename T> std::ostream& operator<<(std::ostream& o, Graph<T>& r) {
	for(Vertex<T>* v = r.data(); v; v = v->vertex) {
		o << v << ' ' ;
		for(Edge<T>* e = v->edge; e; e = e->edge) o << e << ' ';
		o << std::endl << *(v->data) << std::endl;
	}
	return o;
}

