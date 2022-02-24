#pragma once
#include <GL/freeglut.h> 
#include "Obj3d.h"
#include <vector>

#include "Rotorblatt.h"
#include "glm/glm.hpp"

class Flugzeug : public Object3d {

	struct direction {
		float speed = 0;
		glm::vec3 currentDirection;
		int xRotate = 0;
		int yRotate = 0;
		int zRotate = 0;
		float xDegree = 0;
		float yDegree = 0;
		float zDegree = 0;

	};


public:

	float fRotation = 315.0;
	float rRotation = 315.0;
	float xpos = 0.0f, ypos = 0.0f, zpos = -100.0f;
	glm::vec3 pos = glm::vec3(0, 0, -169);
	bool isInAir = false;

	direction currentDirection;
	int currentDirPos = 0;
	bool once = false;
	std::vector<direction> directions;
	float rotationSpeed = 20.0f;


	void readfile(const char* filename);
	void draw(float dt, GLuint flugzeugtexture);
	void drawDummy(glm::vec3,glm::vec3);

	void initDirection();

	glm::vec3 getNextDir();
		

private:

	Rotorblatt rb;


};