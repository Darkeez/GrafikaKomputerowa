#include "stdafx.h"
#include <GL\glut.h>
#include <iostream>
#include <SOIL.h>

enum TEXTURES { GROUND, WALL, ROOF, WINDOW, ALL_TEXTURES };
GLuint texture[ALL_TEXTURES];

int button_state;
int old_x = 0;
int old_y = 0;
GLfloat rx = 0.0f;
GLfloat ry = 0.0f;

enum {
	SWITCH_TO_NEAREST,
	SWITCH_TO_LINEAR
};

void Init()
{
	glClearColor(0.7f, 0.2f, 0.3f, 1.0f);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
	//glDepthFunc(GL_GEQUAL);

	GLenum format;
	glGenTextures(TEXTURES::ALL_TEXTURES, texture);

	const char* groundPath = "C:\\Users\\Marek\\Documents\\tekstura\\brick.jpg";
	const char* wallPath = "C:\\Users\\Marek\\Documents\\tekstura\\brick.jpg";
	const char* roofPath = "C:\\Users\\Marek\\Documents\\tekstura\\brick.jpg";
	const char* windowPath = "C:\\Users\\Marek\\Documents\\tekstura\\brick.jpg";

	int width, height, channels;
	unsigned char* data = SOIL_load_image(groundPath, &width, &height, &channels, SOIL_LOAD_AUTO);
	if (data == nullptr)
	{
		std::cout << "Nie udalo sie zaladowac tekstury." << std::endl;
		exit(0);
	}
	switch (channels)
	{
	case 3: format = GL_RGB; break;
	case 4: format = GL_RGBA; break;
	default: break;
	}
	glBindTexture(GL_TEXTURE_2D, texture[TEXTURES::GROUND]);
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, width, height, format, GL_UNSIGNED_BYTE, data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	SOIL_free_image_data(data);

	data = SOIL_load_image(wallPath, &width, &height, &channels, SOIL_LOAD_AUTO);
	if (data == nullptr)
	{
		std::cout << "Nie udalo sie zaladowac tekstury." << std::endl;
		exit(0);
	}
	switch (channels)
	{
	case 3: format = GL_RGB; break;
	case 4: format = GL_RGBA; break;
	default: break;
	}
	glBindTexture(GL_TEXTURE_2D, texture[TEXTURES::WALL]);
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, width, height, format, GL_UNSIGNED_BYTE, data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	SOIL_free_image_data(data);

	data = SOIL_load_image(roofPath, &width, &height, &channels, SOIL_LOAD_AUTO);
	if (data == nullptr)
	{
		std::cout << "Nie udalo sie zaladowac tekstury." << std::endl;
		exit(0);
	}
	switch (channels)
	{
	case 3: format = GL_RGB; break;
	case 4: format = GL_RGBA; break;
	default: break;
	}
	glBindTexture(GL_TEXTURE_2D, texture[TEXTURES::ROOF]);
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, width, height, format, GL_UNSIGNED_BYTE, data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	SOIL_free_image_data(data);

	data = SOIL_load_image(windowPath, &width, &height, &channels, SOIL_LOAD_AUTO);
	if (data == nullptr)
	{
		std::cout << "Nie udalo sie zaladowac tekstury." << std::endl;
		exit(0);
	}
	switch (channels)
	{
	case 3: format = GL_RGB; break;
	case 4: format = GL_RGBA; break;
	default: break;
	}

	glBindTexture(GL_TEXTURE_2D, texture[TEXTURES::WINDOW]);
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, width, height, format, GL_UNSIGNED_BYTE, data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	SOIL_free_image_data(data);
}

void Display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBindTexture(GL_TEXTURE_2D, texture[TEXTURES::GROUND]);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -20.0f);
	glRotatef(rx, 1.0f, 0.0f, 0.0f);
	glRotatef(ry, 0.0f, 1.0f, 0.0f);

	//Ziemia
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);	glVertex3f(-20.0f, 0.0f, 20.0f);
	glTexCoord2f(0.0f, 20.0f);	glVertex3f(-20.0f, 0.0f, -20.0f);
	glTexCoord2f(20.0f, 20.0f);	glVertex3f(20.0f, 0.0f, -20.0f);
	glTexCoord2f(20.0f, 0.0f);	glVertex3f(20.0f, 0.0f, 20.0f);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texture[TEXTURES::WALL]);
	//Przednia sciana
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);	glVertex3f(-2.0f, 0.0f, 2.0f);
	glTexCoord2f(0.0f, 1.0f);	glVertex3f(-2.0f, 2.0f, 2.0f);
	glTexCoord2f(1.0f, 1.0f);	glVertex3f(2.0f, 2.0f, 2.0f);
	glTexCoord2f(1.0f, 0.0f);	glVertex3f(2.0f, 0.0f, 2.0f);
	glEnd();
	//Tylna sciana
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);	glVertex3f(-2.0f, 0.0f, -2.0f);
	glTexCoord2f(0.0f, 1.0f);	glVertex3f(-2.0f, 2.0f, -2.0f);
	glTexCoord2f(1.0f, 1.0f);	glVertex3f(2.0f, 2.0f, -2.0f);
	glTexCoord2f(1.0f, 0.0f);	glVertex3f(2.0f, 0.0f, -2.0f);
	glEnd();
	//Lewa sciana
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);	glVertex3f(-2.0f, 0.0f, -2.0f);
	glTexCoord2f(0.0f, 1.0f);	glVertex3f(-2.0f, 2.0f, -2.0f);
	glTexCoord2f(1.0f, 1.0f);	glVertex3f(-2.0f, 2.0f, 2.0f);
	glTexCoord2f(1.0f, 0.0f);	glVertex3f(-2.0f, 0.0f, 2.0f);
	glEnd();
	//Prawa sciana
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);	glVertex3f(2.0f, 0.0f, -2.0f);
	glTexCoord2f(0.0f, 1.0f);	glVertex3f(2.0f, 2.0f, -2.0f);
	glTexCoord2f(1.0f, 1.0f);	glVertex3f(2.0f, 2.0f, 2.0f);
	glTexCoord2f(1.0f, 0.0f);	glVertex3f(2.0f, 0.0f, 2.0f);
	glEnd();
	//Przedni trojkat
	glBegin(GL_TRIANGLES);
	glTexCoord2f(0.0f, 0.0f);	glVertex3f(-2.0f, 2.0f, 2.0f);
	glTexCoord2f(0.5f, 1.0f);	glVertex3f(0.0f, 4.0f, 2.0f);
	glTexCoord2f(1.0f, 0.0f);	glVertex3f(2.0f, 2.0f, 2.0f);
	glEnd();
	//Tylny trojkat
	glBegin(GL_TRIANGLES);
	glTexCoord2f(0.0f, 0.0f);	glVertex3f(-2.0f, 2.0f, -2.0f);
	glTexCoord2f(0.5f, 1.0f);	glVertex3f(0.0f, 4.0f, -2.0f);
	glTexCoord2f(1.0f, 0.0f);	glVertex3f(2.0f, 2.0f, -2.0f);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texture[TEXTURES::ROOF]);
	//Lewa strona dachu
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);	glVertex3f(-2.0f, 2.0f, -2.0f);
	glTexCoord2f(0.0f, 2.0f);	glVertex3f(0.0f, 4.0f, -2.0f);
	glTexCoord2f(2.0f, 2.0f);	glVertex3f(0.0f, 4.0f, 2.0f);
	glTexCoord2f(2.0f, 0.0f);	glVertex3f(-2.0f, 2.0f, 2.0f);
	glEnd();
	//Prawa strona dachu
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);	glVertex3f(0.0f, 4.0f, -2.0f);
	glTexCoord2f(0.0f, 2.0f);	glVertex3f(2.0f, 2.0f, -2.0f);
	glTexCoord2f(2.0f, 2.0f);	glVertex3f(2.0f, 2.0f, 2.0f);
	glTexCoord2f(2.0f, 0.0f);	glVertex3f(0.0f, 4.0f, 2.0f);
	glEnd();

	//Okna
	//n = 2
	glBindTexture(GL_TEXTURE_2D, texture[TEXTURES::WINDOW]);
	//Okno1 - przód
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);	glVertex3f(-0.5f, 0.5f, 2.01f);
	glTexCoord2f(0.0f, 1.0f);	glVertex3f(-0.5f, 1.5f, 2.01f);
	glTexCoord2f(1.0f, 1.0f);	glVertex3f(0.5f, 1.5f, 2.01f);
	glTexCoord2f(1.0f, 0.0f);	glVertex3f(0.5f, 0.5f, 2.01f);
	glEnd();
	//Okno2 - prawa strona
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);	glVertex3f(2.01f, 0.5f, 0.5f);
	glTexCoord2f(0.0f, 1.0f);	glVertex3f(2.01f, 1.5f, 0.5f);
	glTexCoord2f(1.0f, 1.0f);	glVertex3f(2.01f, 1.5f, -0.5f);
	glTexCoord2f(1.0f, 0.0f);	glVertex3f(2.01f, 0.5f, -0.5f);
	glEnd();

	glutSwapBuffers();
}
void MouseButton(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN)
	{
		button_state = state;
		old_x = x;
		old_y = y;
	}
}

void MouseMotion(int x, int y)
{
	if (button_state == GLUT_DOWN)
	{
		ry += (x - old_x) / 10.0f;
		rx += (y - old_y) / 10.0f;
	}
	old_x = x;
	old_y = y;

	glutPostRedisplay();
}

void Menu(int value)
{
	switch (value)
	{
	case SWITCH_TO_LINEAR:
		glBindTexture(GL_TEXTURE_2D, texture[TEXTURES::GROUND]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glBindTexture(GL_TEXTURE_2D, texture[TEXTURES::WALL]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glBindTexture(GL_TEXTURE_2D, texture[TEXTURES::ROOF]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glBindTexture(GL_TEXTURE_2D, texture[TEXTURES::WINDOW]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		break;
	case SWITCH_TO_NEAREST:
		glBindTexture(GL_TEXTURE_2D, texture[TEXTURES::GROUND]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glBindTexture(GL_TEXTURE_2D, texture[TEXTURES::WALL]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glBindTexture(GL_TEXTURE_2D, texture[TEXTURES::ROOF]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glBindTexture(GL_TEXTURE_2D, texture[TEXTURES::WINDOW]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		break;
	default:
		break;
	}
	glutPostRedisplay();
}

void onReshape(int w, int h)
{
	if (h == 0) h = 1;
	GLfloat a = (GLfloat)w / (GLfloat)h;

	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(75.0, a, 0.1, 100);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutCreateWindow("Okno OpenGL");

	Init();

	glutCreateMenu(Menu);
	glutAddMenuEntry("GL_LINEAR", SWITCH_TO_LINEAR);
	glutAddMenuEntry("GL_NEAREST", SWITCH_TO_NEAREST);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutMotionFunc(MouseMotion);
	glutMouseFunc(MouseButton);
	glutReshapeFunc(onReshape);
	glutDisplayFunc(Display);

	glutMainLoop();

	return 0;
}
