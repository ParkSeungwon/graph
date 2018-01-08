#include<gtkmm.h>
#include"treeview.h"
#include"graphv.h"
#include"src/parsetree.h"
#include"mindmap.h"
#include"special.h"
using namespace std;

int main(int c, char** av)
{
	if(c < 2) return 0;
	Graph<shared_ptr<MindNode>> graph;
	auto par = make_shared<MindNode>(av[1], MindNode::Dir);
	par->width = 100;
	par->height = 50;
	auto pos = par->name.rfind('/');
	par->path = par->name.substr(0, pos+1);
	par->name = par->name.substr(par->name.rfind('/')+1);
	graph.insert_vertex(par);
	construct_graph(graph, av[1], par);
	//cout << graph.dijkstra("daejun", "kangwon") << endl;;
	GraphV<shared_ptr<MindNode>> gv3{graph.data()};
//	graph.depth();
//	graph.greedy();

	int i=0;
	auto app = Gtk::Application::create(i, av);
	Win win{&gv3};
	win.set_title("File Browser inspired by MindMap");
//	Gtk::Button bt("save");
//	win.vb_.pack_start(bt, Gtk::PACK_SHRINK);
//	bt.signal_clicked().connect(bind(save_graph, graph.data(), av[1]));
	win.show_all_children();
	return app->run(win);
}


