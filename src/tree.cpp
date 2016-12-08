#include"tgraph.h"
#include<iostream>
#include<string>
#include<cstring>
#include<istream>

using namespace std;
//struct H {
//	char s[30];
//	bool operator==(const H& r) {
//		return !strcmp(s, r.s);
//	}
//	void operator=(const H& r) {
//		strcpy(s, r.s);
//	}
//};
//
//istream& operator>>(istream& i, H& r) {
//	string s;
//	i >> s;
//	strcpy(r.s, s.data());
//	return i;
//}
//ostream& operator<<(ostream& o, H& r) {
//	cout << r.s;
//	return o;
//}

//istream& operator>>(istream& i, const char* r) {
//	static char bf[30][30];
//	static int c = 0;
//	i >> bf[c];
//	r = bf[c++];
//}
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
	std::cout << t.find(5)->data;
}
