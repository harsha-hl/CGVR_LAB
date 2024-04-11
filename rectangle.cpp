#include<iostream>
#include<cmath>
#include<algorithm>
#include<GL/glut.h>

using namespace std;
int win1,win2;

void display(){
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POLYGON);
	glColor3f(1,0,0);
	glVertex2f(-150,-50); ///////////////////
	glColor3f(0,1,0);
	glVertex2f(150,-50); ////////////////////
	glColor3f(0,0,1);
	glVertex2f(150,50); ////////////////////
	glColor3f(1,1,0);
	glVertex2f(-150,50); ///////////////////
	glEnd();
	glFlush();
	glutSwapBuffers();
}

void idle(){
	glutSetWindow(win1);
	glRotatef(0,0,0,1);
	glutPostRedisplay();
	
	glutSetWindow(win2);
	glRotatef(1,0,0,1);
	glutPostRedisplay();
}

void myInit(){
	glClearColor(1,1,1,1);
	gluOrtho2D(-250,250,-250,250); /////////////////
}

int main(int argc, char **argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	
	glutInitWindowPosition(100,100);
	win1 = glutCreateWindow("Stationary");
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	myInit();
	
	glutInitWindowPosition(800,100);
	win2 = glutCreateWindow("Rotating");
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	myInit();
	
	glutMainLoop();
}
