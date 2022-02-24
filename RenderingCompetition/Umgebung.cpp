#include "Umgebung.h"
#include <iostream>
#include <time.h>
#include <stdlib.h>
using namespace std;


//Global
//Cone
GLdouble co_base = 2, co_height = 30;
GLint co_slices = 25, co_stack = 25;
//Cylinder
GLdouble cy_radius = 1, cy_height = 32;
GLint cy_slices = 5, cy_stack = 5;
//CylinderTree
GLdouble cyt_radius = 0.8, cyt_height = 15;
GLint cyt_slices = 5, cyt_stack = 5;

void Umgebung::draw()
{
	//3 CubeCylinder Objects 
	glPushMatrix();
	glTranslatef(0, 0, 95);
	CubeCylinder();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, 65);
	CubeCylinder();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, 35);
	CubeCylinder();
	glPopMatrix();

	glPushMatrix();
	DodecahedronRight();
	DodecahedronLeft();
	glPopMatrix();

	//Baum
	glPushMatrix();
	TreesPrinter();
	glPopMatrix();

	//DoubleCone Object 
	glPushMatrix();
	DoubleCone();
	glPopMatrix();
}

void Umgebung::Rectangle(GLfloat fSeitenL)
{
	glColor3f(1,1,1);

	glBegin(GL_POLYGON);//Oben
	glNormal3f(0.0f, 0.0f, 1.0f);
	glVertex3f(-fSeitenL / 0.5f, -fSeitenL / 2.0f, +fSeitenL / 2.0f);
	glVertex3f(+fSeitenL / 0.5f, -fSeitenL / 2.0f, +fSeitenL / 2.0f);
	glVertex3f(+fSeitenL / 0.5f, +fSeitenL / 2.0f, +fSeitenL / 2.0f);
	glVertex3f(-fSeitenL / 0.5f, +fSeitenL / 2.0f, +fSeitenL / 2.0f);
	glEnd();


	glBegin(GL_POLYGON);//Links
	glNormal3f(1.0f, 0.0f, 0.0f);
	glVertex3f(+fSeitenL / 0.5f, -fSeitenL / 2.0f, +fSeitenL / 2.0f);
	glVertex3f(+fSeitenL / 0.5f, -fSeitenL / 2.0f, -fSeitenL / 2.0f);
	glVertex3f(+fSeitenL / 0.5f, +fSeitenL / 2.0f, -fSeitenL / 2.0f);
	glVertex3f(+fSeitenL / 0.5f, +fSeitenL / 2.0f, +fSeitenL / 2.0f);
	glEnd();


	glBegin(GL_POLYGON);//Boden
	glNormal3f(0.0f, 0.0f, -1.0f);
	glVertex3f(+fSeitenL / 0.5f, +fSeitenL / 2.0f, -fSeitenL / 2.0f);
	glVertex3f(+fSeitenL / 0.5f, -fSeitenL / 2.0f, -fSeitenL / 2.0f);
	glVertex3f(-fSeitenL / 0.5f, -fSeitenL / 2.0f, -fSeitenL / 2.0f);
	glVertex3f(-fSeitenL / 0.5f, +fSeitenL / 2.0f, -fSeitenL / 2.0f);
	glEnd();


	glBegin(GL_POLYGON);//Rechts
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(-fSeitenL / 0.5f, +fSeitenL / 2.0f, -fSeitenL / 2.0f);
	glVertex3f(-fSeitenL / 0.5f, -fSeitenL / 2.0f, -fSeitenL / 2.0f);
	glVertex3f(-fSeitenL / 0.5f, -fSeitenL / 2.0f, +fSeitenL / 2.0f);
	glVertex3f(-fSeitenL / 0.5f, +fSeitenL / 2.0f, +fSeitenL / 2.0f);
	glEnd();

	glBegin(GL_POLYGON);//Vorne
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-fSeitenL / 0.5f, +fSeitenL / 2.0f, +fSeitenL / 2.0f);
	glVertex3f(+fSeitenL / 0.5f, +fSeitenL / 2.0f, +fSeitenL / 2.0f);
	glVertex3f(+fSeitenL / 0.5f, +fSeitenL / 2.0f, -fSeitenL / 2.0f);
	glVertex3f(-fSeitenL / 0.5f, +fSeitenL / 2.0f, -fSeitenL / 2.0f);
	glEnd();

	glBegin(GL_POLYGON);//Hinten
	glNormal3f(0.0f, -1.0f, 0.0f);
	glVertex3f(-fSeitenL / 0.5f, -fSeitenL / 2.0f, -fSeitenL / 2.0f);
	glVertex3f(+fSeitenL / 0.5f, -fSeitenL / 2.0f, -fSeitenL / 2.0f);
	glVertex3f(+fSeitenL / 0.5f, -fSeitenL / 2.0f, +fSeitenL / 2.0f);
	glVertex3f(-fSeitenL / 0.5f, -fSeitenL / 2.0f, +fSeitenL / 2.0f);
	glEnd();

	return;
}

void Umgebung::DoubleCone()
{
	glRotated(-90, 1, 0, 0);
	glTranslatef(-5, 0, 0);
	glColor3f(1, 0, 0);
	glutSolidCone(co_base, co_height, co_slices, co_stack); // Cone Rechts
	glTranslatef(10, 0, 0);
	glutSolidCone(co_base, co_height, co_slices, co_stack); // Cone Links
	glTranslatef(-5, 0, 0); // -x rechts +x links (vom Flugzeug aus)
	Rectangle(4);
}

void Umgebung::CubeCylinder()
{
	glRotated(-90, 10, 0, 0);
	glColor3f(0.7, 0, 0.9);
	glutSolidCylinder(cy_radius, cy_height, cy_slices, cy_stack);
	glColor3f(1, 1, 1);
	glutSolidCube(4);
}

void Umgebung::DodecahedronLeft()
{

	glPushMatrix();
	glColor3f(0.62, 0.51, 0.42); //0.8, 0.4, 0.15
	glTranslatef(30, 2, -150);
	glutSolidDodecahedron();
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.9, 0.5, 0.17); //0.8, 0.4, 0.15
	glTranslatef(120, 0.5, -20);
	glutSolidDodecahedron();
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.92, 0.6, 0.18); //0.8, 0.4, 0.15
	glTranslatef(160, 0.3, -25);
	glutSolidDodecahedron();
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.93, 0.7, 0.19); //0.8, 0.4, 0.15
	glTranslatef(40, 2, -30);
	glutSolidDodecahedron();
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.6, 0.5, 0.4); //0.8, 0.4, 0.15
	glTranslatef(60, 2, -50);
	glutSolidDodecahedron();
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.62, 0.51, 0.42); //0.8, 0.4, 0.15
	glTranslatef(70, 2, -60);
	glutSolidDodecahedron();
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.65, 0.5, 0.4); //0.8, 0.4, 0.15
	glTranslatef(50, 2, -70);
	glutSolidDodecahedron();
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.65, 0.52, 0.43); //0.8, 0.4, 0.15
	glTranslatef(80, 2, -90);
	glutSolidDodecahedron();
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.63, 0.51, 0.42); //0.8, 0.4, 0.15
	glTranslatef(40, 2, -90);
	glutSolidDodecahedron();
	glPopMatrix();
}

void Umgebung::DodecahedronRight()
{
	glPushMatrix();
	glColor3f(0.7, 0.51, 0.42); //0.8, 0.4, 0.15
	glTranslatef(-70, 2, -160);
	glutSolidDodecahedron();
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.5, 0.51, 0.42); //0.8, 0.4, 0.15
	glTranslatef(-30, 2, -170);
	glutSolidDodecahedron();
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.9, 0.5, 0.17); //0.8, 0.4, 0.15
	glTranslatef(-60, 0.5, -20);
	glutSolidDodecahedron();
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.92, 0.6, 0.18); //0.8, 0.4, 0.15
	glTranslatef(-85, 0.4, -25);
	glutSolidDodecahedron();
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.93, 0.7, 0.19); //0.8, 0.4, 0.15
	glTranslatef(-150, 2, -30);
	glutSolidDodecahedron();
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.68, 0.57, 0.45); //0.8, 0.4, 0.15
	glTranslatef(-180, 2, -150);
	glutSolidDodecahedron();
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.7, 0.6, 0.2); //0.8, 0.4, 0.15
	glTranslatef(-70, 2, -60);
	glutSolidDodecahedron();
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.62, 0.51, 0.42); //0.8, 0.4, 0.15
	glTranslatef(-140, 2, -110);
	glutSolidDodecahedron();
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.62, 0.51, 0.42); //0.8, 0.4, 0.15
	glTranslatef(-50, 2, -90);
	glutSolidDodecahedron();
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.62, 0.51, 0.42); //0.8, 0.4, 0.15
	glTranslatef(-170, 2, -180);
	glutSolidDodecahedron();
	glPopMatrix();
}

void Umgebung::CubeTreeGenerator()
{
	glPushMatrix();
	glColor3f(0.4, 0.6, 0.2);
	glTranslatef(0, 20, 0);
	glutSolidCube(2);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.4, 0.6, 0.2);
	glTranslatef(0, 18, 0);
	glutSolidCube(4);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.4, 0.6, 0.2);
	glTranslatef(0, 15, 0);
	glutSolidCube(5);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.8, 0.3, 0.1);
	glRotated(-90, 10, 0, 0);
	glutSolidCylinder(cyt_radius, cyt_height, cyt_slices, cyt_stack);
	glPopMatrix();
}

void Umgebung::ShrubTreeGenerator()
{
	glPushMatrix();
	glColor3f(0.4, 0.6, 0.2);
	glTranslatef(0, 15, 0);
	glutSolidSphere(5,5,5);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.8, 0.3, 0.1);
	glRotated(-90, 10, 0, 0);
	glutSolidCylinder(cyt_radius, cyt_height, cyt_slices, cyt_stack);
	glPopMatrix();
}

void Umgebung::PineTreeGenerator()
{
	glPushMatrix();
	glColor3f(0.3, 0.5, 0.1);
	glTranslatef(0, 5, 0);
	glRotated(-90, 10, 0, 0);
	glutSolidCone(4,15,5,5);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.8, 0.3, 0.1);
	glRotated(-90, 10, 0, 0);
	glutSolidCylinder(cyt_radius, cyt_height, cyt_slices, cyt_stack);
	glPopMatrix();
}

void Umgebung::TreesPrinter()
{
	glPushMatrix();
	glTranslatef(40, 2, -150);
	ShrubTreeGenerator();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-75, 2, -160);
	CubeTreeGenerator();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-60, 2, -160);
	PineTreeGenerator();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-80, 2, -150);
	PineTreeGenerator();
	glPopMatrix();




	glPushMatrix();
	glTranslatef(-100, 2, -80);
	CubeTreeGenerator();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-130, 2, -150);
	PineTreeGenerator();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-147, 0, -110);
	ShrubTreeGenerator();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-60, 2, -80);
	PineTreeGenerator();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-85, 2, -120);
	ShrubTreeGenerator();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-180, 2, -180);
	PineTreeGenerator();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-170, 2, -70);
	ShrubTreeGenerator();
	glPopMatrix();



}




