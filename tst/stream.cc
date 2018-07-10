#include<catch.hpp>
#include<iostream>
#include"src/parsetree.h"
#include"src/mindnode.h"
using namespace std;

TEST_CASE("stream") {
	Tree<int> t;
	t.insert(1);
	t.insert(2);
	t.insert(3);
	t.insert(4);
	t.insert(5);
	t.insert(6);
//	cout << "find 5 " << t.find(5)->data << endl;
//	cout << t << endl;
}

TEST_CASE("graph") {
	Graph<int> g;
	g.insert_vertex(1);
	g.insert_vertex(2);
	g.insert_vertex(3);
	g.insert_vertex(4);
	g.insert_vertex(5);
	g.insert_vertex(6);
	g.insert_vertex(7);
	g.insert_edge(1, 2, 3);
	g.insert_edge(1, 3, 2);
	g.insert_edge(2, 6, 2);
	g.insert_edge(6, 5, 2);
	g.insert_edge(3, 1, 0);
	g.insert_edge(4, 5, 1);
	g.remove_edge(1, 3);
	g.remove_vertex(1);
	g.insert_vertex(1);
	g.insert_edge(2, 1, 0);
	g.sub_apply(2, [](int& k) { k+=10; });
	stringstream ss;
	ss << g;
	REQUIRE(ss.str() == "7\n2\n3\n4\n15\n16\n7\n11\n\n2\n16\n2\n2\n11\n0\n4\n15\n1\n16\n15\n2\n");
	Graph<int> h;
	ss >> h;
	REQUIRE(h.data()->data == 2);
}

TEST_CASE("mindnode") {
	MindNode m{"a.txt", MindNode::Virtual};
	stringstream ss;
	ss << m;
	MindNode n{"a.2", MindNode::Virtual};
	ss >> n;
	REQUIRE(n.name == "a.txt");
}

