#include "stdafx.h"
#include <GL\glut.h>
#include <iostream>
#include <SOIL.h>

/*
Program 3. Program ma na celu narysowanie kwadryki pokrytej tekstur¹. 
Program rysuje kulê pokryt¹ tekstur¹ z serwisu http://maps.jpl.nasa.gov/ wed³ug wariantu zadania. 
Zastosowaæ funkcjê gluBuild2DMipmaps która dokonuje skalowanie tekstury do rozmiarów 1024 × 512.
Obs³uga kwadryk bêdzie przedstawiona w odcinku kursu poœwiêconemu oœwietleniu i materia³om. 
W programie do na³o¿enia dwuwymiarowej tekstury na kwadrykê wykorzystaæ funkcjê gluQuadricTexture, 
która jest szczególnie wygodna w u¿yciu bowiem automatycznie definiuje wszystkie wspó³rzêdne tekstur.

Planeta: Jowisz
*/


GLUquadricObj* obj;

GLuint texture;

void Init()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glEnable(GL_TEXTURE_2D);

	obj = gluNewQuadric();
	gluQuadricDrawStyle(obj, GLU_FILL);
	gluQuadricNormals(obj, GLU_SMOOTH);
	gluQuadricTexture(obj, GL_TRUE);


	int width, height, channels;
	const char* str = "C:\\Users\\Marek\\Documents\\tekstura\\1.jpg";
	unsigned char* data = SOIL_load_image(str, &width, &height, &channels, SOIL_LOAD_AUTO);

	if (data == nullptr)
	{
		std::cout << "Nie udalo sie zaladowac tekstury." << std::endl;
		exit(0);
	}

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, width, height, GL_RGB, GL_UNSIGNED_BYTE, data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
}

void Display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glBindTexture(GL_TEXTURE_2D, texture);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glRotatef(90, 1.0f, 0.0f, 0.0f);
	gluSphere(obj, 1.0f, 100, 100);
	glutSwapBuffers();
}

void Menu(int value)
{
	glutPostRedisplay();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutCreateWindow("GK03 Cw03");
	Init();
	glutDisplayFunc(Display);
	glutMainLoop();
	return 0;
}
