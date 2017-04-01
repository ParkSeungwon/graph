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
	outline = (type == Dir ? MindNode::Rect : MindNode::Ellipse);
}

void construct_graph(Graph<shared_ptr<MindNode>>& graph, string dir, 
		shared_ptr<MindNode> parent)
{///read directory recursively and construct graph structure
	if(dir.back() != '/') dir += '/';
	auto filename_and_type = getdir(dir);
	ifstream f(dir + ".mindmap");
	vector<MindNode> vm;
	MindNode mn{"", MindNode::File};//as no default constructor
	while(f >> mn) vm.push_back(mn);

	for(auto& a : filename_and_type) {
		shared_ptr<MindNode> sp = 
			a.second == MindNode::Dir ? 
			make_shared<MindNode>(a.first, MindNode::Dir) : 
			make_shared<MindNode>(a.first, MindNode::File);
		for(auto& m : vm) if(m.name == a.first) *sp = m;//initialize data according
		sp->path = dir;
		graph.insert_vertex(sp);						//to savefile
		graph.insert_edge(parent, sp, 0);
		if(a.second == MindNode::Dir) construct_graph(graph, dir + a.first, sp);
	}
}

void save_graph(Vertex<std::shared_ptr<MindNode>>* v, std::string dir)
{///save .mindmap file at every directory
	if(dir.back() != '/') dir += '/';
	ofstream f(dir + ".mindmap");
	for(auto* e = v->edge; e; e = e->edge) f << *e->vertex->data << endl;
	for(auto* e = v->edge; e; e = e->edge) 
		if(e->vertex->data->type == MindNode::Dir)
			save_graph(e->vertex, dir + e->vertex->data->name);
}

bool MindNode::operator==(const MindNode& r) 
{
	return name == r.name;
}

istream& operator>>(istream& i, MindNode& r) {
	float x, y;
	int a, b, c, rr, rg, rb, ra;
	i >> r.name >> r.show >> x >> y >> a >> b >> c >> rr >> rg >> rb >> ra;
	r.r = rr; r.g = rg; r.b = rb; r.a = ra;
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
