#include<gtkmm.h>
#include"treeview.h"
#include"graphv.h"
#include"src/parsetree.h"
using namespace std;

extern GraphV<int>* pv;
int main(int c, char** av)
{
	Graph<string> graph;
	graph.read_file("data.txt");
	graph.prim();
	graph.bridge();
	cout << graph.dijkstra("daejun", "kangwon") << endl;;
	graph.depth();
	graph.greedy();

	//ParseTree pt{"817+*37+5*+2-"};
	ParseTree pt{-358};
	pt.back();
	//cout << "height is " << pt.height() << endl;


	Tree<int> t;
	srand(time(0));
	for(int i=0; i<10; i++) t.insert(rand() % 100);
	t.insert(3);
	t.insert(2);
	t.insert(5);
	t.insert(6);
	t.insert(1);
	t.view();
	GraphV<int> gv{t.data()};
	pv = &gv;
	gv.treeview(t.height());
	
	auto app = Gtk::Application::create(c, av);
	Win win;
	return app->run(win);
}

