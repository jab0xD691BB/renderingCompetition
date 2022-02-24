#include "Flugzeug.h"


void Flugzeug::readfile(const char* filename)
{
	Object3d::readfile(filename);
	rb.readfile("Rotorblatt.obj");
}

float targetAngleX = 0.0f;
float targetAngleY = 0.0f;
float targetAngleZ = 0.0f;


void Flugzeug::draw(float dt, GLuint flugzeugtexture)
{
	glTranslatef(pos.x, pos.y + 2.975f, pos.z);
	glPushMatrix();

	targetAngleX += (currentDirection.xDegree - targetAngleX) * dt * 2;
	targetAngleY += (currentDirection.yDegree - targetAngleY) * dt * 2;
	targetAngleZ += (currentDirection.zDegree - targetAngleZ) * dt * 2;

	glRotatef(targetAngleX, currentDirection.xRotate, 0, 0);
	glRotatef(targetAngleY, 0, currentDirection.yRotate, 0);
	glRotatef(targetAngleZ, 0, 0, currentDirection.zRotate);
	glScalef(1.5, 1.5, 1.5);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, flugzeugtexture);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	Object3d::draw();
	glDisable(GL_TEXTURE_2D);

	glPushMatrix();
	glColor3f(1.0f, 1.0f, 0.0f);
	glTranslatef(0, 0.2, 0);
	glRotatef(fRotation, 0, 0, 1);
	rb.draw();
	glPopMatrix();

	//reifen
	glTranslatef(0, -0.4, 0.7);
	glColor3f(0.1f, 0.1f, 0.1f);
	glRotatef(-rRotation, 1,0,0),
	glPushMatrix();
		glTranslatef(0.3, 0, 0);
		glRotatef(90, 0, 1, 0);
		glutSolidTorus(0.05, 0.2, 10, 30);
			glPushMatrix();
			glTranslatef(-0.2, 0, 0);
			glRotatef(90, 0, 1, 0);
			glutSolidCylinder(0.025, 0.4, 10, 30);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(0, 0.2, 0);
			glRotatef(90, 1, 0, 0);
			glutSolidCylinder(0.025, 0.4, 10, 30);
		glPopMatrix();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-0.3, 0, 0);
		glRotatef(90, 0, 1, 0);
		glutSolidTorus(0.05, 0.2, 10, 30);
		glPushMatrix();
		glTranslatef(-0.2, 0, 0);
		glRotatef(90, 0, 1, 0);
		glutSolidCylinder(0.025, 0.4, 10, 30);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0, 0.2, 0);
		glRotatef(90, 1, 0, 0);
		glutSolidCylinder(0.025, 0.4, 10, 30);
		glPopMatrix();
	glPopMatrix();

	glPopMatrix();
}


void Flugzeug::drawDummy(glm::vec3 position, glm::vec3 color)
{

	glTranslatef(position.x, position.y, position.z);
	glScalef(1.5, 1.5, 1.5);
	glRotatef(-90, 0, 1, 0);
	glColor4f(color.x, color.y, color.z, 1.0f);
	glPushMatrix();

	Object3d::draw();

	glPushMatrix();
	glColor3f(1.0f, 1.0f, 0.0f);
	glTranslatef(0, 0.2, 0);
	glRotatef(0, 0, 0, 1);
	rb.draw();
	glPopMatrix();

	//reifen
	glTranslatef(0, -0.4, 0.7);
	glColor3f(0.1f, 0.1f, 0.1f);
	glRotatef(0, 1, 0, 0),
		glPushMatrix();
	glTranslatef(0.3, 0, 0);
	glRotatef(90, 0, 1, 0);
	glutSolidTorus(0.05, 0.2, 10, 30);
	glPushMatrix();
	glTranslatef(-0.2, 0, 0);
	glRotatef(90, 0, 1, 0);
	glutSolidCylinder(0.025, 0.4, 10, 30);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0.2, 0);
	glRotatef(90, 1, 0, 0);
	glutSolidCylinder(0.025, 0.4, 10, 30);
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.3, 0, 0);
	glRotatef(90, 0, 1, 0);
	glutSolidTorus(0.05, 0.2, 10, 30);
	glPushMatrix();
	glTranslatef(-0.2, 0, 0);
	glRotatef(90, 0, 1, 0);
	glutSolidCylinder(0.025, 0.4, 10, 30);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0.2, 0);
	glRotatef(90, 1, 0, 0);
	glutSolidCylinder(0.025, 0.4, 10, 30);
	glPopMatrix();
	glPopMatrix();

	glPopMatrix();
}


glm::vec3 Flugzeug::getNextDir()
{
	if (directions.size() > currentDirPos) {

		currentDirection = directions[currentDirPos];

		return currentDirection.currentDirection;
	}
	return glm::vec3(0, 0, 0);
}

void Flugzeug::initDirection()
{

	//start
	//float xpos = 0;
	//float ypos = 0;
	//float zpos = -180;

	//pos.x = 30;
	//pos.y = 0;
	//pos.z = -175;

	directions.push_back({ 5,glm::vec3(0, 0, -167), 0, 1, 1, 0, 0, 0 });
	directions.push_back({ 10,glm::vec3(0, 0, -140), 0, 0, 0, 0, 0, 0 });
	directions.push_back({ 15,glm::vec3(0, 0, -100), 0, 0, 0, 0, 0, 0 });
	directions.push_back({ 20,glm::vec3(0, 0, -60), 0, 0, 0, 0, 0, 0 });

	directions.push_back({ 20,glm::vec3(0, 5,  -40), 1, 0, 0, -20, 0, 0 });
	directions.push_back({ 20,glm::vec3(0, 10,  -20), 1, 0, 0, -30, 0, 0 });
	directions.push_back({ 20,glm::vec3(0, 15,  0), 1, 0, 0, -35, 0, 0 });

	//erster hindernis 90 grad rechts
	directions.push_back({ 20,glm::vec3(0, 20,  15), 1, 1, 1, -20, 0, 70 });
	directions.push_back({ 20,glm::vec3(-5, 20,  20), 1, 1, 1, -10, -70, 70 });
	directions.push_back({ 20,glm::vec3(-8, 20,  25), 0, 1, 1, 0, -70, 70 });
	directions.push_back({ 20,glm::vec3(-10, 20,  30), 0, 1, 1, 0, -70, 70 });

	//erster hindernis nach links 90
	directions.push_back({ 20,glm::vec3(-10, 20,  35), 0, 1, 1, 0, 70, -70 });
	directions.push_back({ 20,glm::vec3(-8, 20,  40), 0, 1, 1, 0, 70, -70 });
	directions.push_back({ 20,glm::vec3(-5, 20,  45), 0, 1, 1, 0, 70, -70 });
	directions.push_back({ 20,glm::vec3(0, 20,  50), 0, 1, 1, 0, 70, -45 });


	//erste mitte zu zweite anfang
	directions.push_back({ 20,glm::vec3(5, 20,  55), 0, 1, 1, 0, 0, 70 });
	directions.push_back({ 20,glm::vec3(8, 20,  60), 0, 1, 1, 0, -70, 70 });
	directions.push_back({ 20,glm::vec3(10, 20,  65), 0, 1, 1, 0, -70, 70 });


	//zweite anfang zu zweite mitte
	directions.push_back({ 20,glm::vec3(8, 20,  75), 0, 1, 1, 0, -45, 70 });
	directions.push_back({ 20,glm::vec3(5, 20,  78), 0, 1, 1, 0, -60, 70 });
	directions.push_back({ 20,glm::vec3(0, 20,  80), 0, 1, 1, 0, -70, 70 });


	//zweite mitte
	//directions.push_back({ 20,glm::vec3(-3, 20,  85), 0, 1, 1, 0, -45, 45 });
	directions.push_back({ 20,glm::vec3(-5, 20,  90), 0, 1, 1, 0, -45, 45 });
	directions.push_back({ 20,glm::vec3(-8, 20,  95), 0, 1, 1, 0, 0, 0 });
	directions.push_back({ 20,glm::vec3(-10, 20,  100), 0, 1, 1, 0, 60, -90 });


	//nach links zurück zum start
	directions.push_back({ 20,glm::vec3(-8, 20,  105), 0, 1, 1, 0, 50, -90 });
	directions.push_back({ 20,glm::vec3(-5, 20,  110), 0, 1, 1, 0, 50, -90 });
	directions.push_back({ 20,glm::vec3(0, 20,  115), 0, 1, 1, 0, 50, -90 });

	directions.push_back({ 20,glm::vec3(5, 20,  120), 0, 1, 1, 0, 70, -70 });
	directions.push_back({ 20,glm::vec3(10, 20,  125), 0, 1, 1, 0, 75, -70 });
	directions.push_back({ 20,glm::vec3(15, 20,  130), 0, 1, 1, 0, 90, -70 });


	directions.push_back({ 20,glm::vec3(30, 20,  130), 0, 1, 1, 0, 90, -70 });
	directions.push_back({ 20,glm::vec3(45, 20,  130), 0, 1, 1, 0, 90, 0 });

	directions.push_back({ 20,glm::vec3(50, 20,  125), 0, 1, 1, 0, 135, -70 });
	directions.push_back({ 20,glm::vec3(54, 20,  120), 0, 1, 1, 0, 135, -90 });
	directions.push_back({ 20,glm::vec3(56, 20,  115), 0, 1, 1, 0, 135, -90 });

	directions.push_back({ 20,glm::vec3(58, 20,  100), 0, 1, 1, 0, 180, -45 });
	directions.push_back({ 20,glm::vec3(60, 20,  50), 0, 1, 1, 0, 180, 0 });

	//landung
	directions.push_back({ 20,glm::vec3(60, 10,  25), 1, 1, 1, -15, 180, 0 });
	directions.push_back({ 20,glm::vec3(60, 5,  -25), 1, 1, 1, -10, 180, 0 });
	directions.push_back({ 20,glm::vec3(60, 5,  -50), 1, 1, 1, 0, 180, 0 });
	directions.push_back({ 20,glm::vec3(60, 0,  -80), 1, 1, 1, -10, 180, 0 });

	directions.push_back({ 20,glm::vec3(59, 0,  -135), 0, 1, 1, 0, 180, 0 });
	directions.push_back({ 10,glm::vec3(59, 0,  -175), 0, 1, 1, 0, 180, 0 });
	directions.push_back({ 5,glm::vec3(20, 0,  -175), 0, 1, 1, 0, 270, 0 });
	directions.push_back({ 5,glm::vec3(0, 0,  -175), 0, 1, 1, 0, 270, 0 });
	directions.push_back({ 5,glm::vec3(0, 0,  -170), 0, 1, 1, 0, 360, 0 });



}



