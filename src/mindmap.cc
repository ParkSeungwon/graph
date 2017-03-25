#include<map>
#include<dirent.h>
#include<iostream>
#include"mindmap.h"
using namespace std;


MindNode::MindNode(string fname, MindNode::Type type)
{
	name = fname;
	this->type = type;
	show = (type == Dir ? true : false);
}

shared_ptr<MindNode> construct_graph(Graph<shared_ptr<MindNode>>& graph, string dir)
{
	auto r = make_shared<MindNode>(dir, MindNode::Dir);
	graph.insert_vertex(r);

	auto filename_and_type = getdir(dir);
	for(auto& a : filename_and_type) {
		if(a.second == MindNode::Dir) {
			auto v = construct_graph(graph, dir + '/' + a.first);
	//		graph.insert_vertex(v);
			graph.insert_edge(r, v, 0);
		} else {
			auto v = make_shared<MindNode>(a.first, MindNode::File);
			graph.insert_vertex(v);
			graph.insert_edge(r, v, 0);
		}
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

