#define NDEBUG
#include<glut.h>
#include"gtk/graphv.h"
using namespace std;

void render();
void init();
extern GraphV<char>* grv;

int main(int ac, char** av)
{
	glutInit(&ac, av);
	glutInitWindowSize(1000, 700);
	glutInitWindowPosition(0, 0);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutCreateWindow("TreeView");
	init();

	Tree<char> t;
	vector<char> v;
	for(char i=60; i<120; i++) v.push_back(i);
	shuffle(v.begin(), v.end(), random_device());
	for(auto& a : v) t.insert(a);
	t.find('Q');
	GraphV<char> gv2{t.data()};
	gv2.treeview(t.height());
//	grv = &gv2;

	string s45 = ParseTree::compose(45);
	string s126 = ParseTree::compose(126);
	ParseTree pt{"817+*"+s45+"-37+5*+2-"+s126+'+'};
	cout << pt.forward() << endl;
	assert(pt.calc() == 67);
	GraphV<char> gv{pt.data()};
	gv.treeview(pt.height());
	grv = &gv;

	glutDisplayFunc(render);
	glutMainLoop();
}
