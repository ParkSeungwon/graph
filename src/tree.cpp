#include"tgraph.h"
using namespace std;

int main()
{
	Graph<int> g;
	for(int i=0; i<10; i++) g.insert_vertex(i);
	g.insert_edge(1,2,3);
	g.insert_edge(3,2,4);
	g.insert_edge(5,2,4);
	g.insert_edge(7,2,4);
	g.insert_edge(3,6,1);
	g.insert_edge(0,1,4);
	g.insert_edge(2,3,1);
	g.insert_edge(0,5,1);
	g.view();
	g.depth();

	Tree<int> t;
	t.insert(3);
	t.insert(2);
	t.insert(5);
	t.insert(6);
	t.insert(1);
	t.view();
	std::cout << t.find(5)->data;
}
