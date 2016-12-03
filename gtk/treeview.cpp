#include<gtkmm.h>
#include"treeview.h"
#include"graphv.h"
#include"src/tgraph.h"
using namespace std;

int main(int c, char** av)
{
	Tree<int> t;
	t.insert(5);
	t.insert(3);
	t.insert(4);
	t.insert(7);
	t.insert(2);
	t.insert(11);
	t.insert(6);

	auto app = Gtk::Application::create(c, av);
//	for(auto& a : tv) win.draw(a);

	GraphView<Vertex<int>, Edge<int>, int> gv{t.data()};
	Win<GraphView<Vertex<int>, Edge<int>, int>> win(gv);
	return app->run(win);
}

