#include<gtkmm.h>
#include"treeview.h"
#include"graphv.h"
#include"src/tgraph.h"
using namespace std;

extern GraphV<string>* pv;
int main(int c, char** av)
{
	Graph<string> graph;
	graph.read_file("data.txt");
	graph.prim();
	graph.clearv();
	graph.bridge();
	graph.clearv();
	cout << graph.dijkstra("daejun", "kangwon") << endl;;
	graph.clearv();
	graph.depth();
	graph.clearv();
	graph.greedy();
	GraphV<string> gv{graph.data()};
	graph.clearv();
	pv = &gv;

	auto app = Gtk::Application::create(c, av);
	Win win;
	return app->run(win);
}

