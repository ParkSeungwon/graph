#include"mindmap.h"
using namespace std;

int main(int ac, char** av)
{
	if(ac < 2) {
		cout << "need parameter" << endl;
		return 0;
	}
	Graph<shared_ptr<MindNode>> graph;
	construct_graph(graph, av[1]);
	graph.view();
	auto* dp = graph.data();
	while(dp) {
		cout << dp->data->name << endl;
		for(auto* e = dp->edge; e; e = e->edge) 
			cout << e->weight << ' ' << e->v << ' ' << e->vertex->data->name << endl;
		dp = dp->vertex;
	}
	auto b = make_shared<MindNode>("fff", MindNode::File);
	cout << b->name << endl;

	cout << graph;
}
	
