#include<glut.h>
#include"gtk/graphv.h"
using namespace std;

int main(int c, char** v)
{
	glutInit(&c, v);
	glutInitWindowSize(2000, 1000);
	glutInitWindowPosition(0, 0);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutCreateWindow("TreeView");

	glutDisplayFunc();
	glutMainLoop();
}
