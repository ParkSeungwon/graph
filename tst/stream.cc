#include<catch.hpp>
#include<iostream>
#include"src/parsetree.h"
using namespace std;

TEST_CASE("stream") {
	Tree<int> t;
	t.insert(1);
	t.insert(2);
	t.insert(3);
	t.insert(4);
	t.insert(5);
	t.insert(6);
	cout << "find 5 " << t.find(5)->data << endl;
	t.view();
}

