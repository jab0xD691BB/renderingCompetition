// GD-Praktikum:   teil_1.cpp  (Teil 1: Start-Programm)
// Hergenroether / Groch    Last Update: 05.07.2014
#define GL_CLAMP_TO_EDGE 0x812F

#include <iostream> 
#include <GL/freeglut.h>         //lädt alles für OpenGL
#include <GL/glut.h>
#include <GL/SOIL.h>

#include <vector>
#include <string>

#include "Camera.h"
#include "Flugzeug.h"
#include "Umgebung.h"
#include "Obj3d.h"


#include "glm/glm.hpp"

using namespace std;

void zeichneBodenSkybox();
void mousecallback(int button, int state, int x, int y);
void mouseMove(int x, int y);
void processNormalKeys(unsigned char key, int x, int y);
void initLight();
void mainMenu(int item);
void changeFlugzeugTexture(int item);

float lightx = 60.0f, lighty = 150.0f, lightz = 150.0f;

bool rightClick = false;

float cubx = 0.0f;

Camera camera;

//deltatime
float lastFrame = 0;
float deltaTime = 0.0f;


Umgebung ug;
Flugzeug flugzeug;
Flugzeug fzDummy1, fzDummy2, fzDummy3;

GLuint* textures = new GLuint[10];

GLint flugzeugtexture;

void Init()
{
	glGenTextures(10, textures);

	textures[0] = SOIL_load_OGL_texture("textures/waldtarnung.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_LOAD_RGB |
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	glBindTexture(GL_TEXTURE_2D, textures[0]);


	textures[1] = SOIL_load_OGL_texture("textures/skybox/Daylight Box_Top.bmp", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_LOAD_RGB |
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	glBindTexture(GL_TEXTURE_2D, textures[1]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	textures[2] = SOIL_load_OGL_texture("textures/skybox/Daylight Box_Left.bmp", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_LOAD_RGB |
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	glBindTexture(GL_TEXTURE_2D, textures[2]);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	textures[3] = SOIL_load_OGL_texture("textures/skybox/Daylight Box_Front.bmp", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_LOAD_RGB |
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	glBindTexture(GL_TEXTURE_2D, textures[3]);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	textures[4] = SOIL_load_OGL_texture("textures/skybox/Daylight Box_Right.bmp", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_LOAD_RGB |
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	glBindTexture(GL_TEXTURE_2D, textures[4]);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	textures[5] = SOIL_load_OGL_texture("textures/skybox/Daylight Box_Back.bmp", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_LOAD_RGB |
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	glBindTexture(GL_TEXTURE_2D, textures[5]);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);


	textures[7] = SOIL_load_OGL_texture("textures/grass.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_LOAD_RGB |
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	glBindTexture(GL_TEXTURE_2D, textures[7]);

	textures[8] = SOIL_load_OGL_texture("textures/sand.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_LOAD_RGB |
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	glBindTexture(GL_TEXTURE_2D, textures[8]);

	textures[9] = SOIL_load_OGL_texture("textures/ddpat.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_LOAD_RGB |
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	glBindTexture(GL_TEXTURE_2D, textures[9]);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	flugzeugtexture = textures[0];

	camera.load();

	cout << "load object" << endl;
	flugzeug.readfile("flugzeugbody.obj");

	fzDummy1.readfile("flugzeugbody.obj");
	fzDummy2.readfile("flugzeugbody.obj");
	fzDummy3.readfile("flugzeugbody.obj");

	flugzeug.initDirection();

	camera.cameraMovement(640, 360);

	//glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	//glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	//glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	//glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
	glEnable(GL_COLOR_MATERIAL);

	// Hier finden jene Aktionen statt, die zum Programmstart einmalig 
	// durchgeführt werden müssen
	glEnable(GL_DEPTH_TEST);
	glClearDepth(1.0);

	glutMouseFunc(mousecallback);
	glutMotionFunc(mouseMove);

	// Unter-Menu
	int submenu1;
	submenu1 = glutCreateMenu(changeFlugzeugTexture);
	glutAddMenuEntry("Waldtarnung", 1);
	glutAddMenuEntry("DDPAT", 2);

	// Haupt-Menu
	glutCreateMenu(mainMenu);
	glutAddSubMenu("Flugzeug Texture", submenu1);
	glutAddMenuEntry("Exit", 1);
	glutAttachMenu(GLUT_LEFT_BUTTON);

	glutKeyboardFunc(processNormalKeys);
	glEnable(GL_NORMALIZE);
}


void RenderScene() //Zeichenfunktion
{
	// Hier befindet sich der Code der in jedem Frame ausgefuehrt werden muss
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.f, 0.f, 0.f, 1.0f);


	glLoadIdentity();   // Aktuelle Model-/View-Transformations-Matrix zuruecksetzen

	if (camera.cameraHotkey) {
		gluLookAt(camera.cameraPosHotkey.x, camera.cameraPosHotkey.y, camera.cameraPosHotkey.z,
			camera.cameraLookAtHotkey.x, camera.cameraLookAtHotkey.y, camera.cameraLookAtHotkey.z,
			camera.cameraUpX, camera.cameraUpY, camera.cameraUpZ);
	}
	else {
		gluLookAt(camera.cameraPosX, camera.cameraPosY, camera.cameraPosZ,
		camera.cameraPosX + camera.cameraFrontX, camera.cameraPosY + camera.cameraFrontY, camera.cameraPosZ + camera.cameraFrontZ,
		camera.cameraUpX, camera.cameraUpY, camera.cameraUpZ);
	}
	


	ug.draw();


	glPushMatrix();
	flugzeug.draw(deltaTime, flugzeugtexture);
	glPopMatrix();

	glPushMatrix();
		fzDummy1.drawDummy(glm::vec3(95, 3, -135), glm::vec3(1,0,0));
	glPopMatrix();

	glPushMatrix();
		fzDummy2.drawDummy(glm::vec3(95, 3, -125), glm::vec3(0, 1, 0));
	glPopMatrix();

	glPushMatrix();
		fzDummy3.drawDummy(glm::vec3(95, 3, -115), glm::vec3(0, 0, 1));
	glPopMatrix();

	zeichneBodenSkybox();


	initLight();
	//glEnd();
	glutSwapBuffers();
}

void Reshape(int width, int height)
{
	// Hier finden die Reaktionen auf eine Veränderung der Größe des 
	// Graphikfensters statt
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, width, height);
	//glOrtho(-1., 1., -1., 1., 0.0, 2.); // von 0.3 auf 0.0 geändert, mann sieht jetzt die fläche weil sie davor zu klein war um sie zu sehen // glOrtho(-x, bis x, -y, bis y, nearPlane, farPlane)
	gluPerspective(45., 1., 1, 1000);
	glMatrixMode(GL_MODELVIEW);
}

bool moving = false;


void Animate(int value)
{
	// Hier werden Berechnungen durchgeführt, die zu einer Animation der Szene  
	// erforderlich sind. Dieser Prozess läuft im Hintergrund und wird alle 
	// 1000 msec aufgerufen. Der Parameter "value" wird einfach nur um eins 
	// inkrementiert und dem Callback wieder uebergeben. 
	//std::cout << "value=" << value << std::endl;
	// RenderScene aufrufen

	/* Delta time in seconds. */

	float currentFrame = glutGet(GLUT_ELAPSED_TIME);
	deltaTime = (currentFrame - lastFrame) / 1000;
	lastFrame = currentFrame;

	if (flugzeug.pos.y > 7) {
		flugzeug.isInAir = true;
	}
	else {
		flugzeug.isInAir = false;
	}

	if (moving) {
		flugzeug.fRotation = flugzeug.fRotation - 20.0;
		if (flugzeug.fRotation <= 0.0) {
			flugzeug.fRotation = flugzeug.fRotation + 360.0;
		}

		if (!flugzeug.isInAir) {
			flugzeug.rRotation = flugzeug.rRotation - 20.0;
			if (flugzeug.fRotation <= 0.0) {
				flugzeug.fRotation = flugzeug.fRotation + 360.0;
			}
		}
	}


	if (moving) {


		float distance = glm::distance(flugzeug.pos, flugzeug.getNextDir());
		glm::vec3 direction = glm::normalize(flugzeug.getNextDir() - flugzeug.pos);

		flugzeug.pos += direction * flugzeug.currentDirection.speed * deltaTime;

		if (distance < 2) {
			flugzeug.currentDirPos++;

			if (flugzeug.directions.size() == flugzeug.currentDirPos || flugzeug.directions.size() == flugzeug.currentDirPos) {
				moving = false;

				flugzeug.currentDirPos = 1;

			}

		}

		cout << "x: " << flugzeug.pos.x << "\ty: " << flugzeug.pos.y << "\tz: " << flugzeug.pos.z << endl;
	}



	glutPostRedisplay();
	// Timer wieder registrieren - Animate wird so nach 10 msec mit value+=1 aufgerufen.
	int wait_msec = 10;
	glutTimerFunc(wait_msec, Animate, ++value);
}


int main(int argc, char** argv)
{

	glutInit(&argc, argv);                // GLUT initialisieren
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1280, 720);         // Fenster-Konfiguration
	glutCreateWindow("Joseph Acost-Becker; Soner Sen");   // Fenster-Erzeugung
	glutDisplayFunc(RenderScene);         // Zeichenfunktion bekannt machen
	glutReshapeFunc(Reshape);
	// TimerCallback registrieren; wird nach 10 msec aufgerufen mit Parameter 0  
	glutTimerFunc(10, Animate, 0);
	Init();
	glutMainLoop();

	delete textures;

	return 0;
}

void zeichneBodenSkybox() {

	//ground
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textures[7]);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glBegin(GL_POLYGON);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glColor4f(.0f, 1.0f, .0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-200.0f, ug.GROUND_HEIGHT, -200.0f);		//camera positiv z // vornelinks
	glTexCoord2f(1.0f, 0.0f); glVertex3f(200.0f, ug.GROUND_HEIGHT, -200.0f);		//vornerechts
	glTexCoord2f(1.0f, 1.0f); glVertex3f(200.0f, ug.GROUND_HEIGHT, -34.865f);		//hinten links
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-200.0f, ug.GROUND_HEIGHT, -34.865f);      //hinten rechts
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	//asphalt
	glPushMatrix();
	glColor4f(.5f, .5f, .5f, 1.0f);
	glBegin(GL_POLYGON);
	glNormal3f(0.f, 1.0f, 0.0f);
	glVertex3f(-10.0f, ug.GROUND_HEIGHT + 0.01f, -180.0f);		//camera positiv z // vornelinks
	glVertex3f(10.0f, ug.GROUND_HEIGHT + 0.01, -180.0f);		//vornerechts
	glVertex3f(10.0f, ug.GROUND_HEIGHT + 0.01, -34.865f);		//hinten links
	glVertex3f(-10.0f, ug.GROUND_HEIGHT + 0.01, -34.865f);      //hinten rechts
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(0.f, 1.0f, 0.0f);
	glVertex3f(50.0f, ug.GROUND_HEIGHT + 0.01f, -180.0f);		//camera positiv z // vornelinks
	glVertex3f(70.0f, ug.GROUND_HEIGHT + 0.01, -180.0f);		//vornerechts
	glVertex3f(70.0f, ug.GROUND_HEIGHT + 0.01, -75.0f);		//hinten links
	glVertex3f(50.0f, ug.GROUND_HEIGHT + 0.01, -75.0f);      //hinten rechts
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(0.f, 1.0f, 0.0f);
	glVertex3f(10.0f, ug.GROUND_HEIGHT + 0.01f, -180.0f);		//camera positiv z // vornelinks
	glVertex3f(50.0f, ug.GROUND_HEIGHT + 0.01, -180.0f);		//vornerechts
	glVertex3f(50.0f, ug.GROUND_HEIGHT + 0.01, -160.0f);		//hinten links
	glVertex3f(10.0f, ug.GROUND_HEIGHT + 0.01, -160.0f);      //hinten rechts
	glEnd();

	//parkplatz
	glBegin(GL_POLYGON);
	glColor4f(.5f, .5f, .5f, 1.0f);
	glNormal3f(0.f, 1.0f, 0.0f);
	glVertex3f(90.0f, ug.GROUND_HEIGHT + 0.01f, -180.0f);		//camera positiv z // vornelinks
	glVertex3f(120.0f, ug.GROUND_HEIGHT + 0.01, -180.0f);		//vornerechts
	glVertex3f(120.0f, ug.GROUND_HEIGHT + 0.01, -100.0f);		//hinten links
	glVertex3f(90.0f, ug.GROUND_HEIGHT + 0.01, -100.0f);      //hinten rechts
	glEnd();

	//parkplatz verbindung
	glBegin(GL_POLYGON);
	glColor4f(.5f, .5f, .5f, 1.0f);
	glNormal3f(0.f, 1.0f, 0.0f);
	glVertex3f(70.0f, ug.GROUND_HEIGHT + 0.01f, -170.0f);		//camera positiv z // vornelinks
	glVertex3f(120.0f, ug.GROUND_HEIGHT + 0.01, -170.0f);		//vornerechts
	glVertex3f(120.0f, ug.GROUND_HEIGHT + 0.01, -160.0f);		//hinten links
	glVertex3f(70.0f, ug.GROUND_HEIGHT + 0.01, -160.0f);      //hinten rechts
	glEnd();

	//parkplatz trennlinien
	glBegin(GL_LINES);
	glLineWidth(10);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glVertex3f(90.0f, ug.GROUND_HEIGHT + 0.05f, -110.0f);
	glVertex3f(105.0f, ug.GROUND_HEIGHT + 0.05f, -110.0f);
	glEnd();

	glBegin(GL_LINES);
	glLineWidth(10);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glVertex3f(90.0f, ug.GROUND_HEIGHT + 0.05f, -120.0f);
	glVertex3f(105.0f, ug.GROUND_HEIGHT + 0.05f, -120.0f);
	glEnd();

	glBegin(GL_LINES);
	glLineWidth(10);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glVertex3f(90.0f, ug.GROUND_HEIGHT + 0.05f, -130.0f);
	glVertex3f(105.0f, ug.GROUND_HEIGHT + 0.05f, -130.0f);
	glEnd();

	glBegin(GL_LINES);
	glLineWidth(10);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glVertex3f(90.0f, ug.GROUND_HEIGHT + 0.05f, -140.0f);
	glVertex3f(105.0f, ug.GROUND_HEIGHT + 0.05f, -140.0f);
	glEnd();

	glBegin(GL_LINES);
	glLineWidth(10);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glVertex3f(90.0f, ug.GROUND_HEIGHT + 0.05f, -150.0f);
	glVertex3f(105.0f, ug.GROUND_HEIGHT + 0.05f, -150.0f);
	glEnd();


		
	glPopMatrix();

	//sand
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textures[8]);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glTranslatef(0, -1.05, 0);
	glRotatef(5, 1, 0, 0);
	glBegin(GL_POLYGON);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glColor4f(.87f, .72f, .52f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-200.0f, ug.WATER_HEIGHT, -35.0f);		//camera positiv z // vornelinks
	glTexCoord2f(1.0f, 0.0f); glVertex3f(200.0f, ug.WATER_HEIGHT, -35.0f);		//vornerechts
	glTexCoord2f(1.0f, 1.0f); glVertex3f(200.0f, ug.WATER_HEIGHT, 10.0f);		//hinten links
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-200.0f, ug.WATER_HEIGHT, 10.0f);      //hinten rechts
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	//water
	float colorxRange = 0.0f;
	float coloryRange = 0.0f;
	glPushMatrix();
	for (int i = 0; i < 20; i++) {
		float colorxStart = .15f;
		float coloryStart = .60f;
		colorxRange += 0.01;
		coloryRange += 0.07;


		float colorx = colorxStart - colorxRange;
		float colory = coloryStart - coloryRange;

		glBegin(GL_POLYGON);
		glNormal3f(0.0f, 1.0f, 0.0f);
		glColor4f(colorx, colory, 1.0f, 1.0f);
		glVertex3f(-200.0f, ug.WATER_HEIGHT, (i * 10) - 10);		//camera positiv z // vornelinks
		glVertex3f(200.0f, ug.WATER_HEIGHT, (i * 10) - 10);		//vornerechts
		glVertex3f(200.0f, ug.WATER_HEIGHT, i * 10.0f);		//hinten links
		glVertex3f(-200.0f, ug.WATER_HEIGHT, i * 10.0f);      //hinten rechts
		glEnd();
	}
	glPopMatrix();


	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glTranslatef(0, -2, 0);
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, textures[1]);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

	glBegin(GL_QUADS);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);   glVertex3f(-200.0f, 200.0f, -200.0f);
	glTexCoord2f(1.0f, 0.0f);   glVertex3f(200.0f, 200.0f, -200.0f);
	glTexCoord2f(1.0f, 1.0f);   glVertex3f(200.0f, 200.0f, 200.0f);
	glTexCoord2f(0.0f, 1.0f);   glVertex3f(-200.0f, 200.0f, 200.0f);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, textures[2]);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

	glBegin(GL_QUADS);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);   glVertex3f(-200.0f, -200.0f, 200.0f);
	glTexCoord2f(1.0f, 0.0f);   glVertex3f(-200.0f, -200.0f, -200.0f);
	glTexCoord2f(1.0f, 1.0f);   glVertex3f(-200.0f, 200.0f, -200.0f);
	glTexCoord2f(0.0f, 1.0f);   glVertex3f(-200.0f, 200.0f, 200.0f);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, textures[3]);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glBegin(GL_QUADS);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);   glVertex3f(-200.0f, -200.0f, -200.0f);
	glTexCoord2f(1.0f, 0.0f);   glVertex3f(200.0f, -200.0f, -200.0f);
	glTexCoord2f(1.0f, 1.0f);   glVertex3f(200.0f, 200.0f, -200.0f);
	glTexCoord2f(0.0f, 1.0f);   glVertex3f(-200.0f, 200.0f, -200.0f);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, textures[4]);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

	glBegin(GL_QUADS);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);   glVertex3f(200.0f, -200.0f, -200.0f);
	glTexCoord2f(1.0f, 0.0f);   glVertex3f(200.0f, -200.0f, 200.0f);
	glTexCoord2f(1.0f, 1.0f);   glVertex3f(200.0f, 200.0f, 200.0f);
	glTexCoord2f(0.0f, 1.0f);   glVertex3f(200.0f, 200.0f, -200.0f);
	glEnd();
	glPopMatrix();


	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, textures[5]);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

	glBegin(GL_QUADS);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);   glVertex3f(200.0f, -200.0f, 200.0f);
	glTexCoord2f(1.0f, 0.0f);   glVertex3f(-200.0f, -200.0f, 200.0f);
	glTexCoord2f(1.0f, 1.0f);   glVertex3f(-200.0f, 200.0f, 200.0f);
	glTexCoord2f(0.0f, 1.0f);   glVertex3f(200.0f, 200.0f, 200.0f);
	glEnd();
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

}


void mousecallback(int button, int state, int x, int y) {

	if (button == GLUT_RIGHT_BUTTON) {
		if (state == GLUT_DOWN) {
			rightClick = true;
			camera.cameraHotkey = false;
		}
		else {
			rightClick = false;
			camera.firstMouse = true;
		}

	}

}


void mouseMove(int x, int y) {

	// this will only be true when the left button is down

	if (rightClick) {
		camera.cameraMovement(x, y);
	}
}


void processNormalKeys(unsigned char key, int x, int y) {

	//cout << "camx: " << camX << "\tcamy: " << camY << "\tcamz: " << camZ << endl;

	float speed = 100 * deltaTime;	//dt deltatime

	switch (key) {

	case '1':
		camera.cameraPosHotkey = glm::vec3(0, 10, -200);
		camera.cameraLookAtHotkey = glm::vec3(0, 0, 0);
		camera.cameraHotkey = true;

		break;
	case '2':
		camera.cameraPosHotkey = glm::vec3(-200, 30, 50);
		camera.cameraLookAtHotkey = glm::vec3(0, 0, 50);
		camera.cameraHotkey = true;
		break;
	case '3':
		camera.cameraPosHotkey = glm::vec3(180, 180, 180);
		camera.cameraLookAtHotkey = glm::vec3(0, 0, 0);
		camera.cameraHotkey = true;

		break;
	case '4':
		camera.cameraPosHotkey = glm::vec3(200, 20, -200);
		camera.cameraLookAtHotkey = glm::vec3(0, 0, 0);
		camera.cameraHotkey = true;
		break;
	case 'w':
		camera.cameraMoveForward(speed);
		camera.cameraHotkey = false;
		break;
	case 's':
		camera.cameraMoveBackward(speed);
		camera.cameraHotkey = false;
		break;
	case 'a':
		camera.cameraMoveLeft(speed);
		camera.cameraHotkey = false;
		break;
	case 'd':
		camera.cameraMoveRight(speed);
		camera.cameraHotkey = false;
		break;
	case 'y':
		camera.save();
		cout << "Cameraposition gespeichert." << endl;
		break;
	case 'm':
		if (!moving) {
			moving = true;
		}
		else {
			moving = false;
		}
		break;
	default:
		break;
	}

	

}

void initLight()
{
	// Licht
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);

	GLfloat ambientLight[] = { .0, .0, .0, 1.0 };
	GLfloat diffuseLight[] = { 1.0f, 1.0f, .70f, 1.0 };
	GLfloat specularLight[] = { 1, 1, 1, .70 };

	GLfloat mat_ambient[] = { 0.7f, 0.7f, 0.7f, 1.0f };
	GLfloat mat_diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
	GLfloat mat_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat high_shininess[] = { 100.0f };


	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
	GLfloat light_position[] = { lightx, lighty, lightz, 1.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

}


void mainMenu(int item)
{
	switch (item)
	{
	case 1:
		std::cout << "Exit" << std::endl;
		exit(0);
	}
}

void changeFlugzeugTexture(int item)
{
	switch (item)
	{
	case 1:
	{
		flugzeugtexture = textures[0];
		glutPostRedisplay();
		break;
	}
	case 2:
	{
		flugzeugtexture = textures[9];
		// RenderScene aufrufen.
		glutPostRedisplay();
		break;
	}

	}
}
