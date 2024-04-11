#include<iostream>
#include<cmath>
#include<algorithm>
#include<GL/glut.h>

using namespace std;
int xr,yr,t,m,c;

float house[11][2] = {
	{100,100},
	{140,100},
	{140,200},
	{180,200},
	{180,100},
	{220,100},
	{220,250},
	{250,250},
	{160,300},
	{70,250},
	{100,250}
};

void drawHouse(){
	glBegin(GL_LINE_LOOP);
	for(int i=0;i<11;i++)
		glVertex2fv(house[i]);
	glEnd();
}

void display1(){
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1,0,0);
	drawHouse();
	
	glPushMatrix();
	glTranslatef(xr,yr,0);
	glRotatef(t,0,0,1);
	glTranslatef(-xr,-yr,0);
	
	glColor3f(0,0,1);
	drawHouse();
	glPopMatrix();
	glFlush();
}

void display2(){
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1,0,0);
	drawHouse();
	
	glColor3f(0,1,0);
	glBegin(GL_LINES);
	glVertex2f(0,c);
	glVertex2f(500,c);
	glEnd();
	
	glPushMatrix();
	glTranslatef(0,c,0);
	glScalef(1,-1,1);
	glTranslatef(0,-c,0);
	
	glColor3f(0,0,1);
	drawHouse();
	glPopMatrix();
	glFlush();
}

void display3(){
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1,0,0);
	drawHouse();
	
	glColor3f(0,1,0);
	glBegin(GL_LINES);
	glVertex2f(c,0);
	glVertex2f(c,500);
	glEnd();
	
	glPushMatrix();
	glTranslatef(c,0,0);
	glScalef(-1,1,1);
	glTranslatef(-c,0,0);
	
	glColor3f(0,0,1);
	drawHouse();
	glPopMatrix();
	glFlush();
}

void display4(){
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1,0,0);
	drawHouse();
	
	int y1 = c;
	int y2 = m*500+c;
	glColor3f(0,1,0);
	glBegin(GL_LINES);
	glVertex2f(0,y1);
	glVertex2f(500,y2);
	glEnd();
	
	float r = atan(m) * 180 / 3.142; ///////////////////
	glPushMatrix();
	glTranslatef(0,c,0);
	glRotatef(r,0,0,1);
	glScalef(1,-1,1);
	glRotatef(-r,0,0,1);
	glTranslatef(0,-c,0);
	
	glColor3f(0,0,1);
	drawHouse();
	glPopMatrix();
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
	cout<<"Enter 1 for rotate and 2 for reflect\n";
	int ch;
	cin>>ch;
	switch(ch){
		case 1: cout<<"Enter xr,yr,t\n";
				cin>>xr>>yr>>t;
				glutCreateWindow("Rotate");
				glutDisplayFunc(display1);
				break;
		case 2: cout<<"1:X axis, 2:Y axis, 3:Y=mX+c\n";
				int ch1;
				cin>>ch1;
				if(ch1 == 1){
					cout<<"Enter c\n";
					cin>>c;
					glutCreateWindow("Reflect X axis");
					glutDisplayFunc(display2);
				}
				else if(ch1 == 2){
					cout<<"Enter c\n";
					cin>>c;
					glutCreateWindow("Reflect Y axis");
					glutDisplayFunc(display3);
				}
				else{
					cout<<"Enter m,c\n";
					cin>>m>>c;
					glutCreateWindow("Reflect about y=mx+c");
					glutDisplayFunc(display4);
				}
		break;
	}
	myInit();
	glutMainLoop();
}
