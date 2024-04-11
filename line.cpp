#include<iostream>
#include<cmath>
#include<algorithm>
#include<GL/glut.h>

using namespace std;

int xc1,yc1,xc2,yc2; ////////////////////////////////////

void drawPixel(int x, int y){
	glPointSize(5);
	glColor3f(0,0,1);
	glBegin(GL_POINTS);
	glVertex2f(x,y);
	glEnd();
}

void drawLine(){
	int dx = abs(xc2-xc1), dy = abs(yc2-yc1), x, y;
	int incx = xc2>xc1 ? 1 : -1;
	int incy = yc2>yc1 ? 1 : -1;
	x = xc1;
	y = yc1;
	if(dx>dy){
		int p = 2*dy - dx;
		for(int i=0;i<=dx;i++){
			drawPixel(x,y);
			if(p>0){
				y += incy;
				p += 2*(dy-dx);
			}
			else p += 2*dy;
			x += incx;
		}
	}
	else{
		int p = 2*dx - dy;
		for(int i=0;i<=dy;i++){
			drawPixel(x,y);
			if(p>0){
				x += incx;
				p += 2*(dx-dy);
			}
			else p += 2*dx;
			y += incy;
		}
	}
	glFlush(); ///////////////////////////////////////////
}

void mouse(int button, int state, int x, int y){
	static bool flag = true;
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
		if(flag){
			xc1 = x-250;
			yc1 = 250-y;
		}
		else{
			xc2 = x-250;
			yc2 = 250-y;
			drawLine();
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
		cout<<"Enter x1,y1,x2,y2\n";
		cin>>xc1>>yc1>>xc2>>yc2;
	}
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100,100);
	glutCreateWindow("Line");
	if(ch==1){
		glutMouseFunc(mouse);
		glutDisplayFunc(display);
	}
	else glutDisplayFunc(drawLine);
	myInit();
	glutMainLoop();
}
