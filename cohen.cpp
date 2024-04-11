#include<iostream>
#include<cmath>
#include<algorithm>
#include<GL/glut.h>

using namespace std;

float xmin=-100,ymin=-100,xmax=100,ymax=100;

const int LEFT=8,RIGHT=4,TOP=2,BOTTOM=1;

int computeOutcode(float x, float y){
	int code = 0;
	if(x<xmin) code |= LEFT;
	else if(x>xmax) code |= RIGHT;
	if(y<ymin) code |= BOTTOM;
	else if(y>ymax) code |= TOP;
	return code;
}

void cohen(float x0, float y0, float x1, float y1){
	int out0 = computeOutcode(x0,y0);
	int out1 = computeOutcode(x1,y1);
	float x,y,m;
	bool accept  = false;
	do{
		if(!(out0 | out1)){
			accept = true;
			break;
		}
		else if(out0 & out1) break;
		else{
			m = (y1-y0)/(x1-x0);
			int o = out0 ? out0 : out1;
			if(o & TOP){
				y = ymax;
				x = (ymax-y1)/m + x1;
			}
			else if(o & BOTTOM){
				y = ymin;
				x = (ymin-y1)/m + x1;
			}
			if(o & LEFT){
				x = xmin;
				y = (xmin-x1)*m + y1;
			}
			else if(o & RIGHT){
				x = xmax;
				y = (xmax-x1)*m + y1;
			}
			
			if(o == out0){
				x0 = x;
				y0 = y;
				out0 = computeOutcode(x0, y0);
			}
			else{
				x1 = x;
				y1 = y;
				out1 = computeOutcode(x1, y1);
			}
		}
	}
	while(true);
	
	if(accept){
		glColor3f(0,1,0);
		glBegin(GL_LINES);
		glVertex2f(x0,y0);
		glVertex2f(x1,y1);
		glEnd();
	}	
}

void display(){
	glClear(GL_COLOR_BUFFER_BIT);
	static bool flag = true;
	float x0 = -120, y0 = -120, x1 = 160, y1 = 80;
	float x2 = 60, y2 = 30, x3 = 90, y3 = 120;
	float x4 = 0, y4 = 0, x5 = -90, y5 = 20;
	float x6 = -150, y6 = -150, x7 = 50, y7 = -150;
	
	if(flag){
		glColor3f(1,0,0);
		glBegin(GL_LINES);
		glVertex2f(x0,y0);
		glVertex2f(x1,y1);
		glVertex2f(x2,y2);
		glVertex2f(x3,y3);
		glVertex2f(x4,y4);
		glVertex2f(x5,y5);
		glVertex2f(x6,y6);
		glVertex2f(x7,y7);
		glEnd();
		flag = false;
	}
	
	glColor3f(0,0,1);
	glBegin(GL_LINE_LOOP);
	glVertex2f(xmin, ymin);
	glVertex2f(xmin, ymax);
	glVertex2f(xmax, ymax);
	glVertex2f(xmax, ymin);
	glEnd();
	
	cohen(x0,y0,x1,y1);
	cohen(x2,y2,x3,y3);
	cohen(x4,y4,x5,y5);
	cohen(x6,y6,x7,y7);
	
	glFlush();
}

void myInit(){
	glClearColor(1,1,1,1);
	gluOrtho2D(-250,250,-250,250);
}

int main(int argc, char **argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	
	glutInitWindowPosition(100,100);
	glutCreateWindow("Clipping");
	glutDisplayFunc(display);
	myInit();
	
	glutInitWindowPosition(800,100);
	glutCreateWindow("Results");
	glutDisplayFunc(display);
	myInit();
	
	glutMainLoop();
}
