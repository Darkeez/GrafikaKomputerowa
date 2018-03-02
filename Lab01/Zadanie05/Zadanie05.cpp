#include "stdafx.h"
#include <GL/glut.h>
#include <vector>

float pointColor[] = { 0.0f, 0.0f, 0.0f };
float polygonColor[] = { 0.0f, 178.0f, 235.0f };
bool drawQuads = true;
bool drawPoints = true;

struct myVECTOR
{
	myVECTOR() = default;
	myVECTOR(int x, int y) : x(x), y(y) {}
	int x;
	int y;
};

std::vector<myVECTOR> myPOINTS;

void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	if (drawPoints)
	{
		glColor3fv(pointColor);
		glBegin(GL_POINTS);
		for (int n = 0; n < myPOINTS.size(); n++)
			glVertex2f(myPOINTS[n].x, myPOINTS[n].y);
		glEnd();
	}

	if (drawQuads)
	{
		glColor3fv(polygonColor);
		glBegin(GL_QUADS);
		for (int n = 0; n < myPOINTS.size(); n++)
			glVertex2f(myPOINTS[n].x, myPOINTS[n].y);
		glEnd();
	}

	glFlush();
}

void SetupRenderingContext(void)
{
	glPointSize(10.0f);
	glClearColor(250.00f, 250.00f, 250.00f, 1.0f);
}

void ChangeSize(int w, int h)
{
	if (h == 0)   h = 1;

	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	float aspect = (GLfloat)w / (GLfloat)h;

	if (w <= h)
	{
		glOrtho(0.0f, w, 0.0f / aspect, h / aspect, 1.0f, -1.0f);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glScalef(1.0f, (GLfloat)h / (GLfloat)w, 1.0f);
	}
	else
	{
		glOrtho(0.0 * aspect, w * aspect, 0.0f, h, 1.0f, -1.0f);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glScalef((GLfloat)w / (GLfloat)h, 1.0f, 1.0f);
	}

}

void onMouseDown(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		myPOINTS.push_back(myVECTOR(x, glutGet(GLUT_WINDOW_HEIGHT) - y));
	}

	glutPostRedisplay();
}

void Menu(int value)
{
	switch (value)
	{
	case 1:
		drawQuads = !drawQuads;
		break;
	case 2:
		drawPoints = !drawPoints;
		break;
	}

	glutPostRedisplay();
}

int main(int argc, char* argv[])
{

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(800, 800);
	glutCreateWindow("Program 4");

	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);
	glutMouseFunc(onMouseDown);

	glutCreateMenu(Menu);
	glutAddMenuEntry("Wyswietlenie wielokata", 1);
	glutAddMenuEntry("Wyswietlenie punktow", 2);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	SetupRenderingContext();

	glutMainLoop();

	return 0;

}

