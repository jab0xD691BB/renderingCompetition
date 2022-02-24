#include "Camera.h"

#include <iostream>

void Camera::cameraMovement(int x, int y)
{
	if (firstMouse) // initially set to true
	{
		lastMouseX = x;
		lastMouseY = y;
		firstMouse = false;
	}

	float xMouseOffset = x - lastMouseX;
	float yMouseOffset = lastMouseY - y; // reversed since y-coordinates range from bottom to top
	lastMouseX = x;
	lastMouseY = y;

	const float sense = .2f;
	xMouseOffset *= sense;
	yMouseOffset *= sense;

	yaw += xMouseOffset;
	pitch += yMouseOffset;

	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	dirx = cos(((yaw * PI_F) / 180)) * cos(((pitch * PI_F) / 180));
	diry = sin((pitch * PI_F) / 180);
	dirz = sin(((yaw * PI_F) / 180)) * cos(((pitch * PI_F) / 180));

	dirl = sqrt(powf(dirx, 2) + powf(diry, 2) + powf(dirz, 2));
	float ndirx = (1 / dirl) * dirx;
	float ndiry = (1 / dirl) * diry;
	float ndirz = (1 / dirl) * dirz;

	cameraFrontX = ndirx;
	cameraFrontY = ndiry;
	cameraFrontZ = ndirz;

	//std::cout << "camerafrontx: " << cameraFrontX << " camerafronty: " << cameraFrontY << " camerafrontz: " << cameraFrontZ <<  std::endl;
}

void Camera::cameraMoveForward(float speed)
{
	cameraPosX += speed * cameraFrontX;
	cameraPosY += speed * cameraFrontY;
	cameraPosZ += speed * cameraFrontZ;
}


void Camera::cameraMoveBackward(float speed)
{
	cameraPosX -= speed * cameraFrontX;
	cameraPosY -= speed * cameraFrontY;
	cameraPosZ -= speed * cameraFrontZ;
}

float kreuzX = 0.0f;
float kreuzY = 0.0f;
float kreuzZ = 0.0f;

float length = 0.0f;

float normalizeX = 0.0f;
float normalizeY = 0.0f;
float normalizeZ = 0.0f;

void Camera::cameraMoveLeft(float speed)
{
	kreuzX = (cameraFrontY * cameraUpZ) - (cameraFrontZ * cameraUpY);
	kreuzY = (cameraFrontZ * cameraUpX) - (cameraFrontX * cameraUpZ);
	kreuzZ = (cameraFrontX * cameraUpY) - (cameraFrontY * cameraUpX);

	length = sqrt(powf(kreuzX, 2) + powf(kreuzY, 2) + powf(kreuzZ, 2));

	normalizeX = (1 / length) * kreuzX;
	normalizeY = (1 / length) * kreuzY;
	normalizeZ = (1 / length) * kreuzZ;

	cameraPosX -= speed * normalizeX;
	cameraPosY -= speed * normalizeY;
	cameraPosZ -= speed * normalizeZ;
}

void Camera::cameraMoveRight(float speed)
{
	kreuzX = (cameraFrontY * cameraUpZ) - (cameraFrontZ * cameraUpY);
	kreuzY = (cameraFrontZ * cameraUpX) - (cameraFrontX * cameraUpZ);
	kreuzZ = (cameraFrontX * cameraUpY) - (cameraFrontY * cameraUpX);

	length = sqrt(powf(kreuzX, 2) + powf(kreuzY, 2) + powf(kreuzZ, 2));

	normalizeX = (1 / length) * kreuzX;
	normalizeY = (1 / length) * kreuzY;
	normalizeZ = (1 / length) * kreuzZ;

	cameraPosX += speed * normalizeX;
	cameraPosY += speed * normalizeY;
	cameraPosZ += speed * normalizeZ;
}

void Camera::save()
{
	std::ofstream myfile;
	std::stringstream ss;
	myfile.open("settings.txt");

	ss << cameraPosX << "\n" << cameraPosY << "\n" << cameraPosZ << "\n"
		<< cameraFrontX << "\n" << cameraFrontY << "\n" << cameraFrontX << "\n"
		<< cameraUpX << "\n" << cameraUpY << "\n" << cameraUpZ << "\n"
		<< yaw << "\n" << pitch;

	myfile << ss.str();


}

void Camera::load()
{
	std::string line0, line1, line2, line3, line4, line5, line6, line7, line8, line9, line10;
	std::ifstream myfile("settings.txt");
	if (myfile.is_open())
	{

		getline(myfile, line0);
		cameraPosX = std::stof(line0);
		getline(myfile, line1);
		cameraPosY = std::stof(line1);
		getline(myfile, line2);
		cameraPosZ = std::stof(line2);

		getline(myfile, line3);
		cameraFrontX = std::stof(line3);
		getline(myfile, line4);
		cameraFrontY = std::stof(line4);
		getline(myfile, line5);
		cameraFrontZ = std::stof(line5);

		getline(myfile, line6);
		cameraUpX = std::stof(line6);
		getline(myfile, line7);
		cameraUpY = std::stof(line7);
		getline(myfile, line8);
		cameraUpZ = std::stof(line8);

		getline(myfile, line9);
		yaw = std::stof(line9);
		getline(myfile, line10);
		pitch = std::stof(line10);


	}
	myfile.close();
}

