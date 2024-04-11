#include<iostream>
#include<cmath>
#include<algorithm>
#include<GL/glut.h>

using namespace std;

int iter;
typedef GLfloat point[3];
point tetra[4] = {{0,0,250},{0,250,-250},{250,-250,-250},{-250,-250,-250}};

void drawTriangle(point a, point b, point c){
	glVertex3fv(a);
	glVertex3fv(b);
	glVertex3fv(c);
}

void drawTetrahedron(point a, point b, point c, point d){
	glColor3f(1,0,0);
	drawTriangle(a,b,c);
	glColor3f(0,1,0);
	drawTriangle(a,c,d);
	glColor3f(0,0,1);
	drawTriangle(a,b,d);
	glColor3f(1,1,0);
	drawTriangle(d,b,c);
}

void divideTetrahedron(point a, point b, point c, point d, int iter){
	if(iter>0){
		point ab,ac,ad,bc,bd,cd;
		for(int i=0;i<3;i++){
			ab[i] = (a[i] + b[i])/2;
			ac[i] = (a[i] + c[i])/2;
			ad[i] = (a[i] + d[i])/2;
			bc[i] = (c[i] + b[i])/2;
			bd[i] = (d[i] + b[i])/2;
			cd[i] = (c[i] + d[i])/2;
		}
		divideTetrahedron(a,ab,ac,ad,iter-1);
		divideTetrahedron(ab,b,bc,bd,iter-1);
		divideTetrahedron(ac,bc,c,cd,iter-1);
		divideTetrahedron(ad,bd,cd,d,iter-1);
	}
	else{
		drawTetrahedron(a,b,c,d);
		
	}	
}

void display(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glBegin(GL_TRIANGLES);
	divideTetrahedron(tetra[0],tetra[1],tetra[2],tetra[3],iter);
	glEnd();
	glFlush();
}

void myInit(){
	glEnable(GL_DEPTH_TEST);
	glClearColor(1,1,1,1);
	glOrtho(-250,250,-250,250,-250,250);
}

int main(int argc, char **argv){
	cout<<"Enter number of iterations\n";
	cin>>iter;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100,100);
	glutCreateWindow("Sierpinski");
	glutDisplayFunc(display);
	myInit();
	glutMainLoop();
}
