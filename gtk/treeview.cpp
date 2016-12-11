#include<gtkmm.h>
#include"treeview.h"
#include"graphv.h"
#include"src/tgraph.h"
using namespace std;

extern GraphV<char>* pv;
int main(int c, char** av)
{
	Graph<string> graph;
	graph.read_file("data.txt");
	graph.prim();
	graph.bridge();
	cout << graph.dijkstra("daejun", "kangwon") << endl;;
	graph.depth();
	graph.greedy();

	ParseTree<char> pt{"817+*37+5*+2-"};
	GraphV<char> gv{pt.data()};

	pv = &gv;

	auto app = Gtk::Application::create(c, av);
	Win win;
	return app->run(win);
}

