#include "stdafx.h"
#include <GL\freeglut.h>

void Display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glutSwapBuffers();
}

void SetupRenderingContext()
{
	glClearColor(0.5f, 0.35f, 0.05f, 1.0f);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Mój pierwszy program w GLUT");

	SetupRenderingContext();

	glutDisplayFunc(Display);

	glutMainLoop();

	return 0;
}

