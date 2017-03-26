#include<iostream>
#include"mindmap.h"
using namespace std;

int main()
{
	MindNode r("", MindNode::File);
	int x, y;
	int a, b, c;
	while(cin >> r.name >> r.show >> x >> y >> a >> b >> c >> dec >> r.r >> dec >> r.g >> dec >> r.b >> dec >> r.a)
		cout << ' ' << r.name << ' ' << r.show << ' ' << x << ' ' << y << ' ' << a << ' ' << b << ' ' << c << ' ' << r.r << ' ' << r.g << ' ' << r.b << ' ' << r.a << ' ' << endl;
}
