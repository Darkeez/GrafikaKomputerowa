#include "stdafx.h"
#include <GL\freeglut.h>
#include <iostream>
#include "Vectors3D.h"


int button_x;
int button_y;
int button_state = GLUT_UP;
float rotatex;
float rotatey;
float distance = -20.0f;

void DrawInsidePhyramid()
{
	CVector vertices[11] = {
		{ 0.0f, 0.0f, 9.9f }, // Góra figóry
		{ 0.0f, 1.9f, 0.0f }, //                1
		{ 1.4f, 1.4f, 0.0f }, //           10        2
		{ 1.9f, 0.0f, 0.0f }, //          9     0      3
		{ 1.6f, -1.1f, 0.0f }, //          8          4
		{ 0.9f, -1.4f, 0.0f }, //             7    5
		{ 0.0f, -1.9f, 0.0f }, //                6
		{ -0.9f, -1.4f, 0.0f }, //
		{ -1.6f, -1.1f, 0.0f }, //
		{ -1.9f, 0.0f, 0.0f }, //
		{ -1.4f, 1.4f, 0.0f }, //
	};

	void DrawOutsidePhyramid()
	{
		CVector vertices[11] = {
			{ 0.0f, 0.0f, 10.0f }, // Góra figóry
			{ 0.0f, 2.0f, 0.0f }, //                1
			{ 1.5f, 1.5f, 0.0f }, //           10        2
			{ 2.0f, 0.0f, 0.0f }, //          9     0      3
			{ 1.7f, -1.2f, 0.0f }, //          8          4
			{ 1.0f, -1.5f, 0.0f }, //            7      5
			{ 0.0f, -2.0f, 0.0f }, //               6
			{ -1.0f, -1.5f, 0.0f }, //
			{ -1.7f, -1.2f, 0.0f }, //
			{ -2.0f, 0.0f, 0.0f }, //
			{ -1.5f, 1.5f, 0.0f }, //
		};

		CVector normals[11] = {
			{ 0.0f, -1.0f, 0.0f },
			GetNormalFromPoints(vertices[2], vertices[0], vertices[1]),
			GetNormalFromPoints(vertices[3], vertices[0], vertices[2]),
			GetNormalFromPoints(vertices[4], vertices[0], vertices[3]),
			GetNormalFromPoints(vertices[5], vertices[0], vertices[4]),
			GetNormalFromPoints(vertices[6], vertices[0], vertices[5]),
			GetNormalFromPoints(vertices[7], vertices[0], vertices[6]),
			GetNormalFromPoints(vertices[8], vertices[0], vertices[7]),
			GetNormalFromPoints(vertices[9], vertices[0], vertices[8]),
			GetNormalFromPoints(vertices[10], vertices[0], vertices[9]),
			GetNormalFromPoints(vertices[1], vertices[0], vertices[10])
		};

		glBegin(GL_TRIANGLES);

		glNormal3fv(normals[1].vectors);
		glVertex3fv(vertices[0].vectors);
		glNormal3fv(normals[1].vectors);
		glVertex3fv(vertices[1].vectors);
		glNormal3fv(normals[1].vectors);
		glVertex3fv(vertices[2].vectors);

		glNormal3fv(normals[2].vectors);
		glVertex3fv(vertices[0].vectors);
		glNormal3fv(normals[2].vectors);
		glVertex3fv(vertices[2].vectors);
		glNormal3fv(normals[3].vectors);
		glVertex3fv(vertices[3].vectors);

		glNormal3fv(normals[3].vectors);
		glVertex3fv(vertices[0].vectors);
		glNormal3fv(normals[3].vectors);
		glVertex3fv(vertices[3].vectors);
		glNormal3fv(normals[3].vectors);
		glVertex3fv(vertices[4].vectors);

		glNormal3fv(normals[4].vectors);
		glVertex3fv(vertices[0].vectors);
		glNormal3fv(normals[4].vectors);
		glVertex3fv(vertices[4].vectors);
		glNormal3fv(normals[4].vectors);
		glVertex3fv(vertices[5].vectors);

		glNormal3fv(normals[5].vectors);
		glVertex3fv(vertices[0].vectors);
		glNormal3fv(normals[5].vectors);
		glVertex3fv(vertices[5].vectors);
		glNormal3fv(normals[5].vectors);
		glVertex3fv(vertices[6].vectors);

		glNormal3fv(normals[6].vectors);
		glVertex3fv(vertices[0].vectors);
		glNormal3fv(normals[6].vectors);
		glVertex3fv(vertices[6].vectors);
		glNormal3fv(normals[6].vectors);
		glVertex3fv(vertices[7].vectors);

		glNormal3fv(normals[7].vectors);
		glVertex3fv(vertices[0].vectors);
		glNormal3fv(normals[7].vectors);
		glVertex3fv(vertices[7].vectors);
		glNormal3fv(normals[7].vectors);
		glVertex3fv(vertices[8].vectors);

		glNormal3fv(normals[8].vectors);
		glVertex3fv(vertices[0].vectors);
		glNormal3fv(normals[8].vectors);
		glVertex3fv(vertices[8].vectors);
		glNormal3fv(normals[8].vectors);
		glVertex3fv(vertices[9].vectors);

		glNormal3fv(normals[9].vectors);
		glVertex3fv(vertices[0].vectors);
		glNormal3fv(normals[9].vectors);
		glVertex3fv(vertices[9].vectors);
		glNormal3fv(normals[9].vectors);
		glVertex3fv(vertices[10].vectors);

		glNormal3fv(normals[10].vectors);
		glVertex3fv(vertices[0].vectors);
		glNormal3fv(normals[10].vectors);
		glVertex3fv(vertices[10].vectors);
		glNormal3fv(normals[10].vectors);
		glVertex3fv(vertices[1].vectors);

		glEnd();

		glBegin(GL_POLYGON);

		glNormal3fv(normals[0].vectors);
		glVertex3fv(vertices[1].vectors);
		glNormal3fv(normals[0].vectors);
		glVertex3fv(vertices[2].vectors);
		glNormal3fv(normals[0].vectors);
		glVertex3fv(vertices[3].vectors);
		glNormal3fv(normals[0].vectors);
		glVertex3fv(vertices[4].vectors);
		glNormal3fv(normals[0].vectors);
		glVertex3fv(vertices[5].vectors);
		glNormal3fv(normals[0].vectors);
		glVertex3fv(vertices[6].vectors);
		glNormal3fv(normals[0].vectors);
		glVertex3fv(vertices[7].vectors);
		glNormal3fv(normals[0].vectors);
		glVertex3fv(vertices[8].vectors);
		glNormal3fv(normals[0].vectors);
		glVertex3fv(vertices[9].vectors);
		glNormal3fv(normals[0].vectors);
		glVertex3fv(vertices[10].vectors);

		glEnd();
	}

	void DrawFunction()
	{
		DrawInsidePhyramid();

		glColor3f(1, 1, 0.7f);
		glPushMatrix();
		glTranslatef(0.0f, 0.0f, 1.0f);
		glutSolidSphere(0.5, 20, 20);
		glPopMatrix();

		glDrawBuffer(GL_NONE);
		glBegin(GL_QUADS);
		glVertex3f(-1.0, -1.0, -0.001);
		glVertex3f(1.0, -1.0, -0.001);
		glVertex3f(1.0, 1.0, -0.001);
		glVertex3f(-1.0, 1.0, -0.001);
		glEnd();
		glDrawBuffer(GL_BACK);

		glColor3f(1.0f, 0.5f, 0.2f);
		DrawOutsidePhyramid();

	}

	void Display()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		glPushMatrix();

		glTranslatef(0.0f, 0.0f, distance);
		glRotatef(-rotatex, 1.0f, 0.0, 0.0f);
		glRotatef(-rotatey, 0.0f, 1.0f, 0.0f);

		DrawFunction();

		glPopMatrix();

		glutSwapBuffers();
	}

	void Idle()
	{
		glutPostRedisplay();
	}

	void Resize(int w, int h)
	{
		if (h == 0)
			h = 1;

		glViewport(0, 0, w, h);

		float a = (float)w / (float)h;

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		gluPerspective(75.0, a, 0.1, 100);
	}

	void InitScene()
	{
		glClearColor(1, 0, 0, 1);

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		glEnable(GL_COLOR_MATERIAL);
		glFrontFace(GL_CW);
		glShadeModel(GL_FLAT);

	}

	void MouseButton(int button, int state, int x, int y)
	{
		if (button == GLUT_LEFT_BUTTON)
		{
			button_state = state;

			if (state == GLUT_DOWN)
			{
				button_x = x;
				button_y = y;
			}
		}
	}

	void MouseMotion(int x, int y)
	{
		if (button_state == GLUT_DOWN)
		{
			rotatey -= (x - button_x) / 2.0;
			button_x = x;
			rotatex -= (y - button_y) / 2.0;
			button_y = y;
			glutPostRedisplay();
		}
	}

	void Keyboard(unsigned char key, int x, int y)
	{
		if (key == '+')
			distance += 0.5f;
		if (key == '-')
			distance -= 0.5f;
	}

	void Menu(int value)
	{
		switch (value)
		{

		}
	}

	int main(int argc, char** argv)
	{
		glutInit(&argc, argv);
		glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
		glutInitWindowSize(800, 600);
		glutCreateWindow("Program 7");

		InitScene();

		glutDisplayFunc(Display);
		glutIdleFunc(Idle);
		glutReshapeFunc(Resize);
		glutMotionFunc(MouseMotion);
		glutMouseFunc(MouseButton);
		glutKeyboardFunc(Keyboard);



		glutMainLoop();

		return 0;
	}