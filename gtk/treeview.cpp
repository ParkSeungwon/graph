#include<gtkmm.h>
#include"treeview.h"
#include"graphv.h"
#include"src/parsetree.h"
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
//	GraphV<string> gv{graph.data()};
	graph.greedy();
//	gv.treeview(pt.height());
//	pv = &gv;

	string s = ParseTree::compose(45);
	ParseTree pt{"817+*"+s+"-37+5*+2-"};
	cout << pt.forward() << endl;
	assert(pt.calc() == 67);
	GraphV<char> gv{pt.data()};
	gv.treeview(pt.height());
	pv = &gv;

	//cout << "height is " << pt.height() << endl;


	Tree<char> t;
	vector<char> v;
	for(char i=60; i<120; i++) v.push_back(i);
	shuffle(v.begin(), v.end(), random_device());
	for(auto& a : v) t.insert(a);
	t.find('Q');
//	GraphV<char> gv{t.data()};
//	gv.treeview(t.height());
//	pv = &gv;
	
	auto app = Gtk::Application::create(c, av);
	Win win;
	return app->run(win);
}

