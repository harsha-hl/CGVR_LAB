#include<iostream>
#include<cmath>
#include<algorithm>
#include<GL/glut.h>

using namespace std;

int xc,yc,r;

void draw8Pixel(int xc, int yc, int x, int y){
	glPointSize(5);
	glColor3f(0,0,1);
	glBegin(GL_POINTS);
	glVertex2f(xc+x,yc+y);
	glVertex2f(xc-x,yc-y);
	glVertex2f(xc+x,yc-y);
	glVertex2f(xc-x,yc+y);
	glVertex2f(xc+y,yc+x);
	glVertex2f(xc-y,yc-x);
	glVertex2f(xc+y,yc-x);
	glVertex2f(xc-y,yc+x);
	glEnd();
}

void drawCircle(){
	int d = 3 - 2*r;
	int x = 0, y = r;
	while(x<=y){
		draw8Pixel(xc,yc,x,y);
		if(d>0){
			d += 4*(x-y) + 10; ///////////////////
			y--;
		}
		else d+= 4*x + 6; ///////////////////
		x++;
	}
	glFlush();
}

void mouse(int button, int state, int x, int y){
	static bool flag = true;
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
		if(flag){
			xc = x-250;
			yc = 250-y;
		}
		else{
			int xb = x-250;
			int yb = 250-y;
			r = hypot(xb-xc, yb-yc); ///////////////////////////
			drawCircle();
		}
		flag = !flag;
	}
}

void display(){}

void myInit(){
	glClearColor(1,1,1,1);
	gluOrtho2D(-250,250,-250,250);
}

int main(int argc, char **argv){
	cout<<"Enter 1 for mouse, 2 for keyboard\n";
	int ch;
	cin>>ch;
	if(ch == 2){
		cout<<"Enter xc,yc,r\n";
		cin>>xc>>yc>>r;
	}
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100,100);
	glutCreateWindow("Circle");
	if(ch==1){
		glutMouseFunc(mouse);
		glutDisplayFunc(display);
	}
	else glutDisplayFunc(drawCircle);
	myInit();
	glutMainLoop();
}
