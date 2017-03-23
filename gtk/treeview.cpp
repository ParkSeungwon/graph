#define NDEBUG
#include<gtkmm.h>
#include"treeview.h"
#include"graphv.h"
#include"src/parsetree.h"
using namespace std;

extern GraphV<int>* pv;
int main(int c, char** av)
{
	Graph<int> graph;
	graph.read_file("data.txt");
	graph.prim();
	graph.bridge();
	//cout << graph.dijkstra("daejun", "kangwon") << endl;;
	GraphV<int> gv3{graph.data()};
//	graph.depth();
//	graph.greedy();
	pv = &gv3;

	string s45 = ParseTree::compose(45);
	string s126 = ParseTree::compose(126);
	ParseTree pt{"817+*"+s45+"-37+5*+2-"+s126+'+'};
	cout << pt.forward() << endl;
	assert(pt.calc() == 67);
	GraphV<char> gv{pt.data()};
	gv.treeview(pt.height());
//	pv = &gv;

	Tree<char> t;
	vector<char> v;
	for(char i=60; i<120; i++) v.push_back(i);
	shuffle(v.begin(), v.end(), random_device());
	for(auto& a : v) t.insert(a);
	t.find('Q');
	GraphV<char> gv2{t.data()};
	gv2.treeview(t.height());
//	pv = &gv2;
	
	auto app = Gtk::Application::create(c, av);
	Win win;
	return app->run(win);
}

