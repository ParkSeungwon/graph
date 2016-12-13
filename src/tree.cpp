#include"parsetree.h"
#include<iostream>
#include<string>
#include<cstring>
#include<istream>
using namespace std;

int main(int c, char** v)
{
	Tree<int> t;
	t.insert(1);
	t.insert(2);
	t.insert(3);
	t.insert(4);
	t.insert(5);
	t.insert(6);
	t.view();
}
