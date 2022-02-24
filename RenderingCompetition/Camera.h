#pragma once
#include <math.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <glm/glm.hpp>

class Camera {

public:

	float cameraPosX = 0.0f, cameraPosY = 0.0f, cameraPosZ = 10.0f;
	float cameraFrontX = 0.0f, cameraFrontY = 0.0f, cameraFrontZ = -1.0f;
	float cameraUpX = 0.0f, cameraUpY = 1.0f, cameraUpZ = 0.0f;

	bool firstMouse = false;

	float yaw = -90.0f, pitch = 0.0f;
	float dirx = 0.0f, diry = 0.0f, dirz = 0.0f;
	//radians = (degrees * pi) / 180;
	const float  PI_F = 3.14159265358979f;
	float dirNormX = 0.0f, dirNormY = 0.0f, dirNormZ = 0.0f;
	float dirl = 0.0;
	float lastMouseX = 400, lastMouseY = 300;

	bool cameraHotkey = false;

	glm::vec3 cameraPosHotkey = glm::vec3(0, 10, -200);
	glm::vec3 cameraLookAtHotkey = glm::vec3(0,0,0);

	void cameraMovement(int x, int y);
	void cameraMoveForward(float);
	void cameraMoveBackward(float);
	void cameraMoveLeft(float);
	void cameraMoveRight(float);

	void save();
	void load();

private:



};