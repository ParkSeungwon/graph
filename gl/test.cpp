#include<glut.h>
using namespace std;
float light_position[] = {3, 3, 3, 0};
void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glEnable(GL_LIGHTING);
	glShadeModel(GL_SMOOTH);

	glutSolidSphere(1.5, 50, 50);
	glutSwapBuffers();
}
void MyInit() {
	glClearColor(1,1,1,1);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-2, 2, -2, 2, -2, 2);
}

int main(int ac, char** av) {
	glutInit(&ac, av);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Graphics Primitives");
	MyInit();
	glutDisplayFunc(MyDisplay);

	glutMainLoop();
}
