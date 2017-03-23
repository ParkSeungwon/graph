#include"mindmap.h"
using namespace std;

int main()
{
	Graph<shared_ptr<MindNode>> graph;
	construct_graph(graph, ".");
	graph.view();
}
	

