#include"parsetree.h"
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

	ParseTree tr{"817+*37+5*+2-"};
	tr.view();
	tr.forward();
	cout << endl;
	tr.middle();
	cout << endl;
	tr.back();
	cout << endl;
	cout << tr.calc() << endl;

	ParseTree pt{-345};
	pt.view();
	pt.forward();
	cout << endl;
	pt.middle();
	cout << endl;
	pt.back();
	cout << endl;
	cout << pt.calc() << endl;
}
