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

void construct_graph(Graph<shared_ptr<MindNode>>& graph, string dir, 
		shared_ptr<MindNode> parent)
{
	if(dir.back() != '/') dir += '/';
	auto filename_and_type = getdir(dir);
	ifstream f(dir + ".mindmap");
	vector<MindNode> vm;
	MindNode mn{"", MindNode::File};
	while(f >> mn) vm.push_back(mn);

	for(auto& a : filename_and_type) {
		shared_ptr<MindNode> sp = 
			a.second == MindNode::Dir ? 
			make_shared<MindNode>(a.first, MindNode::Dir) : 
			make_shared<MindNode>(a.first, MindNode::File);
		for(auto& m : vm) if(m.name == a.first) *sp = m;
		graph.insert_vertex(sp);
		graph.insert_edge(parent, sp, 0);
		if(a.second == MindNode::Dir) construct_graph(graph, dir + a.first, sp);
	}
}

bool MindNode::operator==(const MindNode& r) 
{
	return name == r.name;
}

istream& operator>>(istream& i, MindNode& r) {
	float x, y;
	int a, b, c;
	i >> r.name >> r.show >> x >> y >> a >> b >> c >> r.r >> r.g >> r.b >> r.a;
	r.pt = {x, y}; 
	r.outline = static_cast<MindNode::Shape>(a); 
	r.line = static_cast<MindNode::Line>(b); 
	r.type = static_cast<MindNode::Type>(c);
	return i;
}

ostream& operator<<(ostream& o, const MindNode& node)
{
	o << node.name << ' ' << node.show << ' ';
	o << node.pt.x() << ' ' << node.pt.y() << ' ';
	o << node.outline << ' ' << node.line << ' ' << node.type << ' ' ;
	o << +node.r << ' ' << +node.g << ' ' << +node.b << ' ' << +node.a << ' ';
	return o;
}

ostream& operator<<(ostream& o, Graph<shared_ptr<MindNode>>& r) {
	for(auto* v = r.data(); v; v = v->vertex) {
		o << v << ' ' ;
		for(auto* e = v->edge; e; e = e->edge) o << e->vertex << ' ';
		o << endl << *(v->data) << endl;
	}
	return o;
}
