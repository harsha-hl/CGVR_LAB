#include<iostream>
#include<cmath>
#include<algorithm>
#include<GL/glut.h>

using namespace std;

void sphere(){
	float c = 3.142 / 180;
	float x,y,z,phir,phir2,thetar;
	glColor3f(0,0,1);
	for(int phi = -80; phi<80; phi +=10){
		phir = phi * c;
		phir2 = (phi+10)*c;
		glBegin(GL_QUAD_STRIP);
		for(int theta=-180;theta<180;theta+=10){
			thetar = theta*c;
			x = sin(thetar) * cos(phir);
			y = cos(thetar) * cos(phir);
			z = sin(phir);
			glVertex3f(x,y,z);
			
			x = sin(thetar) * cos(phir2);
			y = cos(thetar) * cos(phir2);
			z = sin(phir2);
			glVertex3f(x,y,z);
		}
		glEnd();
	}
	glColor3f(1,0,0);
	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(0,0,1);
	float c80 = 80 * c;
	for(int theta=-180;theta<180;theta+=10){
		thetar = theta*c;
		x = sin(thetar) * cos(c80);
		y = cos(thetar) * cos(c80);
		z = sin(c80);
		glVertex3f(x,y,z);
	}
	glEnd();
	
	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(0,0,-1);
	for(int theta=-180;theta<180;theta+=10){
		thetar = theta*c;
		x = sin(thetar) * cos(c80);
		y = cos(thetar) * cos(c80);
		z = -sin(c80);
		glVertex3f(x,y,z);
	}
	glEnd();
}

void display(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPolygonMode(GL_FRONT_AND_BACK,GL_LINE); ///////////////////
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0,0,-1);
	glRotatef(60,1,1,0);
	sphere();
	glFlush();
}

void myInit(){
	glEnable(GL_DEPTH_TEST);
	glClearColor(1,1,1,1);
	glOrtho(-1,1,-1,1,-1,1);
}

int main(int argc, char **argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100,100);
	glutCreateWindow("Sphere");
	glutDisplayFunc(display);
	myInit();
	glutMainLoop();
}
