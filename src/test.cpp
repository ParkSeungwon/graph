#include<iostream>
#include<memory>
#include"mindmap.h"
using namespace std;

extern Graph<Node> graph;

int main(int ac, char** av)
{
	MindMap md(av[1]);
	md.view();
	//graph.depth();
}
