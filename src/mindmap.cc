#include"mindmap.h"
#include"tgraph.h"
#include<memory>
using namespace std;

Graph<shared_ptr<Node>> graph;

shared_ptr<Node> init(string dir)
{
	auto p = new Node;
	p->name = dir;
	auto r = shared_ptr<Node>(p);
	graph.insert_vertex(r);

	auto fs = getdir(dir);
	for(auto& a : fs) {
		if(a.second == Node::Dir) {
			graph.insert_edge(r, init(dir + '/' + a.first), 0);
		} else p->files.insert(a.first);
	}
	return r;
}

ostream& operator<<(ostream& o, const shared_ptr<Node>& node)
{
	o << node->name;
	//for(auto& a : node->files) cout << a << ' ';
	return o;
}
