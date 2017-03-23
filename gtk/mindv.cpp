#define NDEBUG
#include<gtkmm.h>
#include"treeview.h"
#include"graphv.h"
#include"src/parsetree.h"
#include"mindmap.h"
#include"special.h"
using namespace std;

extern GraphV<shared_ptr<MindNode>>* pv;
int main(int c, char** av)
{
	Graph<shared_ptr<MindNode>> graph;
	construct_graph(graph, ".");
	//cout << graph.dijkstra("daejun", "kangwon") << endl;;
	GraphV<shared_ptr<MindNode>> gv3{graph.data()};
//	graph.depth();
//	graph.greedy();
	pv = &gv3;
	
	auto app = Gtk::Application::create(c, av);
	Win win;
	return app->run(win);
}


