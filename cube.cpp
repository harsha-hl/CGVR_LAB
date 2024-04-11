#include<iostream>
#include<cmath>
#include<algorithm>
#include<GL/glut.h>

using namespace std;

int rot = 2;

float vertices[8][3] = {
	-1,-1,-1,
	1,-1,-1,
	1,1,-1,
	-1,1,-1,
	-1,1,1,
	1,1,1,
	1,-1,1,
	-1,-1,1
};

float colors[8][3] = {
	0,0,0,
	0,0,1,
	0,1,0,
	0,1,1,
	1,0,0,
	1,0,1,
	1,1,0,
	1,1,1
};

GLubyte elementIndices[24] = {
	0,1,2,3,
	0,6,7,1,
    3,4,5,2,
    0,3,4,7,
    2,5,6,1,
    7,4,5,6	
};

void display(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, elementIndices);
	glFlush();
	glutSwapBuffers();
}

void mouse(int button, int state, int x, int y){
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) rot = 0;
	else if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) rot = 1;
	else rot = 2;
}

void idle(){
	if(rot == 0) glRotatef(0.1,1,0,0);
	else if(rot==1) glRotatef(0.1,0,1,0);
	else glRotatef(0.1,0,0,1);
	glutPostRedisplay();
}

void myInit(){
	glEnableClientState(GL_DEPTH_TEST);
	gluPerspective(80, 1, 0.1, 10);
	glMatrixMode(GL_MODELVIEW);
	glTranslatef(0,0,-3);
}

int main(int argc, char **argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100,100);
	glutCreateWindow("Cube Spin");
	glutDisplayFunc(display);
	glutMouseFunc(mouse);
	glutIdleFunc(idle);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glVertexPointer(3, GL_FLOAT, 3*sizeof(float), vertices);
	glColorPointer(3, GL_FLOAT, 3*sizeof(float), colors);
	myInit();
	glutMainLoop();
}
