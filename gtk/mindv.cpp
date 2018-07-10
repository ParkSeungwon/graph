#include<gtkmm.h>
#include"sketch.h"
#include"graphv.h"
#include"src/parsetree.h"
#include"mindmap.h"
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

	int i=0;
	auto app = Gtk::Application::create(i, av);
	Win win{graph};
	win.set_title("File Browser inspired by MindMap");
	win.show_all_children();
	return app->run(win);
}


