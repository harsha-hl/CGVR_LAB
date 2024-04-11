#include<iostream>
#include<cmath>
#include<algorithm>
#include<GL/glut.h>

using namespace std;

void drawCircle(int xc, int yc, int r){
	glColor3f(1,0,0); /////////////////////
	glBegin(GL_POINTS);
	for(float t=0; t<2*3.142;t+=0.01){
		float x = xc + r*cos(t);
		float y = yc + r*sin(t);
		glVertex2f(x,y);
	}
	glEnd();
}

void drawCylinder(){
	int xc=250,yc=250,r=60,n=200;
	for(int i=0;i<n;i+=3)
		drawCircle(xc,yc+i,r);
}

void drawRectangle(int x1, int x2, int y1, int y2){
	glColor3f(0,0,1); ////////////////////////
	glBegin(GL_LINE_LOOP);
	glVertex2f(x1,y1);
	glVertex2f(x1,y2);
	glVertex2f(x2,y2);
	glVertex2f(x2,y1);
	glEnd();
}

void drawParallelopiped(){
	int x1=150,x2=350,y1=150,y2=250,n=100;
	for(int i=0;i<n;i+=3)
		drawRectangle(x1+i,x2+i,y1+i,y2+i);
}

void display1(){
	glClear(GL_COLOR_BUFFER_BIT);
	drawCylinder();
	glFlush();
}

void display2(){
	glClear(GL_COLOR_BUFFER_BIT);
	drawParallelopiped();
	glFlush();
}

void myInit(){
	glClearColor(1,1,1,1);
	gluOrtho2D(0,500,0,500);
}

int main(int argc, char **argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	
	glutInitWindowPosition(100,100);
	glutCreateWindow("Cylinder");
	glutDisplayFunc(display1); ///////////
	myInit();
	
	glutInitWindowPosition(800,100);
	glutCreateWindow("Parallelopiped");
	glutDisplayFunc(display2); //////////////
	myInit();
	
	glutMainLoop();
}
