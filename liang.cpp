#include<iostream>
#include<cmath>
#include<algorithm>
#include<GL/glut.h>

using namespace std;

float xmin=-100,ymin=-100,xmax=100,ymax=100;

bool cliptest(float p, float q, float &t1, float &t2){
	if(p==0){
		if(q<0) return false;
	}
	else{
		float r = q/p;
		if(p>0){
			t2 = min(t2, r);
			if(r<t1) return false; //////////////////
		}
		else{
			t1 = max(t1, r);
			if(r>t2)return false; ///////////////////
		}
	}
	return true;
}

void liang(float x0, float y0, float x1, float y1){
	float dx = x1-x0, dy = y1-y0, t1 = 0.0, t2 = 1.0;
	if(cliptest(-dx, x0-xmin, t1, t2) &&
		cliptest(dx, xmax-x0, t1, t2) &&
		 cliptest(-dy, y0-ymin, t1, t2) &&
		  cliptest(dy, ymax-y0, t1, t2)){
		  if(t2<1.0){
		  	x1 = x0 + dx*t2;
		  	y1 = y0 + dy*t2;
		  }
		  if(t1>0.0){
		  	x0 = x0 + dx*t1;
		  	y0 = y0 + dy*t1;
		  }
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
	
	liang(x0,y0,x1,y1);
	liang(x2,y2,x3,y3);
	liang(x4,y4,x5,y5);
	liang(x6,y6,x7,y7);
	
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
