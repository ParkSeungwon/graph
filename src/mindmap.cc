#include<map>
#include<dirent.h>
#include<iostream>
#include"mindmap.h"
using namespace std;


MindNode::MindNode(string fname, MindNode::Type type)
{
	name = fname;
	this->type = type;
	show = type == Dir ? true : false;
}

shared_ptr<MindNode> construct_graph(Graph<shared_ptr<MindNode>>& graph, string dir)
{
	auto p = new MindNode(dir, MindNode::Dir);
	p->name = dir;
	auto r = shared_ptr<MindNode>(p);
	graph.insert_vertex(r);

	auto fs = getdir(dir);
	for(auto& a : fs) {
		if(a.second == MindNode::Dir) 
			graph.insert_edge(r, construct_graph(graph, dir + '/' + a.first), 0);
		else graph.insert_edge(r, make_shared<MindNode>(a.first, MindNode::File), 0);
	}
	return r;
}

bool MindNode::operator==(const MindNode& r) 
{
	return name == r.name;
}

ostream& operator<<(ostream& o, const MindNode& node)
{
	o << node.name;
	return o;
}

