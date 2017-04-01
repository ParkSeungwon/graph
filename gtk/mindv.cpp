#define NDEBUG
#include<gtkmm.h>
#include"treeview.h"
#include"graphv.h"
#include"src/parsetree.h"
#include"mindmap.h"
#include"special.h"
using namespace std;

extern GraphV<shared_ptr<MindNode>>* PV;//treeview.cc
int main(int c, char** av)
{
	if(c < 2) return 0;
	Graph<shared_ptr<MindNode>> graph;
	auto par = make_shared<MindNode>(av[1], MindNode::Dir);
	graph.insert_vertex(par);
	construct_graph(graph, av[1], par);
	//cout << graph.dijkstra("daejun", "kangwon") << endl;;
	GraphV<shared_ptr<MindNode>> gv3{graph.data()};
//	graph.depth();
//	graph.greedy();
	PV = &gv3;

	int i=0;
	auto app = Gtk::Application::create(i, av);
	Win win;
//	Gtk::Button bt("save");
//	win.vb_.pack_start(bt, Gtk::PACK_SHRINK);
//	bt.signal_clicked().connect(bind(save_graph, graph.data(), av[1]));
	win.show_all_children();
	return app->run(win);
}


