#include<iostream>
#include<memory>
#include"mindmap.h"
#include"tgraph.h"
using namespace std;

extern Graph<shared_ptr<Node>> graph;

int main(int ac, char** av)
{
	init(av[1]);
	graph.view();
	//graph.depth();
}
