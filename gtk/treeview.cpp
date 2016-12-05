#include<gtkmm.h>
#include"treeview.h"
#include"graphv.h"
#include"src/tgraph.h"
using namespace std;

extern GraphView<Vertex<array<int, 5>>, Edge<array<int, 5>>, array<int, 5>>* tgv;
extern GraphView<Vertex<const char*>, Edge<const char*>, const char*>* pgv;
int main(int c, char** av)
{

	Tree<array<int, 5>> t;
	t.insert({5, -1, 2, 1, -4});
	t.insert({3, 4, -1, -1, 3});
	t.insert({7, -1, 1, -3, 1});
	t.insert({4, 3, -1, -1, 2});
	t.insert({3, -1, 1, 1, -5});
	t.view();
	GraphView<Vertex<array<int, 5>>, Edge<array<int, 5>>, array<int, 5>> gv{t.data()};
	tgv = &gv;

	Graph<const char*> city;
	city.insert_vertex("Seoul");
	city.insert_vertex("Suwon");
	city.insert_vertex("Incheon");
	city.insert_vertex("Pusan");
	city.insert_vertex("Daejun");
	city.insert_edge("Seoul", "Suwon", 60);
	city.insert_edge("Seoul", "Incheon", 80);
	city.insert_edge("Suwon", "Incheon", 70);
	city.insert_edge("Suwon", "Daejun", 150);
	city.insert_edge("Seoul", "Pusan", 500);
	city.view();
	city.prim();
	city.clearv();
	city.topology();
	cout << "from 서울 - 인천 : " << city.floyd("Seoul", "Daejun") << endl;
	GraphView<Vertex<const char*>, Edge<const char*>, const char*> gvv{city.data()};

	pgv = &gvv;
	auto app = Gtk::Application::create(c, av);
	Win win;
	return app->run(win);
}

