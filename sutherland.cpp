#include<iostream>
#include<cmath>
#include<algorithm>
#include<GL/glut.h>

using namespace std;

float xmin=-100,ymin=-100,xmax=100,ymax=100;

enum EDGE {LEFT, RIGHT, TOP, BOTTOM};

struct Point{
	float x,y;
};

void drawPoly(Point pts[], int n){
	glPolygonMode(GL_FRONT_AND_BACK,GL_LINE); /////////////////////
	glBegin(GL_POLYGON); //////////////////////
	for(int i=0;i<n;i++)
		glVertex2f(pts[i].x, pts[i].y);
	glEnd();
}

bool insideEdge(Point p, int edge){
	switch(EDGE(edge)){ //////////////////////////
		case LEFT : return p.x >= xmin;
		case RIGHT : return p.x <= xmax;
		case TOP : return p.y <= ymax;
		case BOTTOM : return p.y >= ymin;
	}
	return false;
}

Point getIntersect(Point s, Point p, int edge){
	Point p1;
	float m = (p.y-s.y)/(p.x-s.x);
	switch(EDGE(edge)){
		case LEFT : p1.x = xmin;
					p1.y = (xmin - p.x)*m + p.y;
					break;
		case RIGHT : p1.x = xmax;
					 p1.y = (xmax - p.x)*m + p.y;
					 break;
		case TOP : p1.y = ymax;
				   p1.x = (ymax - p.y)/m + p.x;
				   break;
		case BOTTOM : p1.y = ymin;
					  p1.x = (ymin - p.y)/m + p.x;
					  break;
	}
	return p1;
} 

void sutherland(Point pts[], int n){
	Point inp[10], outp[10];
	int inn, outn;
	copy(pts, pts+n, inp);
	inn = n;
	for(int i=0;i<4;i++){
		outn = 0;
		Point s = inp[inn-1];
		for(int j=0;j<inn;j++){
			Point p = inp[j];
			if(insideEdge(p, i)){
				if(insideEdge(s,i)) outp[outn++] = p;
				else{
					outp[outn++] = getIntersect(s,p,i);
					outp[outn++] = p;
				}
			}
			else{
				if(insideEdge(s,i)) outp[outn++] = getIntersect(s,p,i);
			}
			s = p;
		}
		copy(outp, outp+outn, inp);
		inn = outn;
	}
	glColor3f(0,1,0);
	drawPoly(outp, outn);
}

void display(){
	glClear(GL_COLOR_BUFFER_BIT);
	static bool flag = true;
	Point inp[] = {
		{-150,-150},
		{60,150},
		{80,80},
		{150,100}
	};
	
	if(flag){
		glColor3f(1,0,0);
		drawPoly(inp, 4);
		flag = false;
	}
	
	glColor3f(0,0,1);
	glBegin(GL_LINE_LOOP);
	glVertex2f(xmin, ymin);
	glVertex2f(xmin, ymax);
	glVertex2f(xmax, ymax);
	glVertex2f(xmax, ymin);
	glEnd();
	
	sutherland(inp, 4);
	
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
