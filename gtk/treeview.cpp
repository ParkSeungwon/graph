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
	//cout << graph.dijkstra("seoul", "kangwon") << endl;;
	graph.depth();
	GraphV<string> gv{graph.data()};
	pv = &gv;

	auto app = Gtk::Application::create(c, av);
	Win win;
	return app->run(win);
}

