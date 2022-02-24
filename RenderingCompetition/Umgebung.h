#pragma once
#include <GL/freeglut.h> 


class Umgebung {


public:
	const float GROUND_HEIGHT = 2.0f;
	const float WATER_HEIGHT = 0.0f;


	void draw();
	void Rectangle(GLfloat fSeitenL);
	void DoubleCone();
	void CubeCylinder();
	void DodecahedronLeft();
	void DodecahedronRight();

	void CubeTreeGenerator();
	void ShrubTreeGenerator();
	void PineTreeGenerator();
	void TreesPrinter();
private:




};