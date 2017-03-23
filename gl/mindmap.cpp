#define NDEBUG
#include<glut.h>
#include"gtk/graphv.h"
#include"src/mindmap.h"
using namespace std;

void render();
void init();
extern GraphV<MindNode>* grv;//drawing module will use this
extern Graph<MindNode> graph;//declared in mindmap.cc

int main(int ac, char** av)
{
/*	MindMap md(av[1]);//populate graph
	GraphV<MindNode> gv2{md.data()};//make view from data
	grv = &gv2;//그림을 그리는 gldrawable에 있는 포인터에 할당한다.

	glutInit(&ac, av);
	glutInitWindowSize(1000, 700);
	glutInitWindowPosition(0, 0);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutCreateWindow("MindMap");
	init();

	glutDisplayFunc(render);
	glutMainLoop();*/
}
