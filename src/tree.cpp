#include"tgraph.h"
#include<iostream>
#include<string>
#include<cstring>
#include<istream>
using namespace std;

int main()
{
	Graph<string> g2;
	g2.read_file("data.txt");
	g2.view();

	Tree<int> t;
	t.insert(3);
	t.insert(2);
	t.insert(5);
	t.insert(6);
	t.insert(1);
	t.view();
	std::cout << t.find(5)->data << endl;

	ParseTree<char> tr{"7*8+9/1"};
	tr.view();
	tr.forward();
	cout << endl;
	tr.middle();
	cout << endl;
	tr.back();
	cout << endl;
}
