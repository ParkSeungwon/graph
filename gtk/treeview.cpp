#include<gtkmm.h>
#include"treeview.h"
#include"graphv.h"
#include"src/parsetree.h"
using namespace std;

extern GraphV<string>* pv;
int main(int c, char** av)
{
	Graph<string> graph;
	graph.read_file("data.txt");
	graph.prim();
	graph.bridge();
	cout << graph.dijkstra("daejun", "kangwon") << endl;;
	graph.depth();
	GraphV<string> gv{graph.data()};
	graph.greedy();
//	gv.treeview(pt.height());
	pv = &gv;

	ParseTree pt{"817+*37+5*+2-"};
	//ParseTree pt{-358};
	pt.back();
//	GraphV<char> gv{pt.data()};
//	gv.treeview(pt.height());
//	pv = &gv;

	//cout << "height is " << pt.height() << endl;


	Tree<char> t;
	vector<char> v;
	for(char i=60; i<120; i++) v.push_back(i);
	shuffle(v.begin(), v.end(), random_device());
	for(auto& a : v) t.insert(a);
//	GraphV<char> gv{t.data()};
//	gv.treeview(t.height());
//	pv = &gv;
	
	auto app = Gtk::Application::create(c, av);
	Win win;
	return app->run(win);
}

