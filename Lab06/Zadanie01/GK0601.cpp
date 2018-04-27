// Piramida.cpp : Defines the entry point for the console application.
// Ziemowit Juroszek
// Torus


#include "stdafx.h"
#include <GL/glut.h>
#include <stdlib.h>

// sta³e do obs³ugi menu podrêcznego

enum
{
	StylSolid,
	StylWire,
	FULL_WINDOW,       // aspekt obrazu - ca³e okno
	ASPECT_1_1,        // aspekt obrazu 1:1
	EXIT               // wyjœcie
};

enum SHAPES
{
	CONE,
	CUBE,
	CYLINDER,
	DODECAHEDRON,
	COSAHEDON,
	OCTAHEDRON,
	RHOMBICDODECAHEDRON,
	SIERPINSKISPONAGE,
	SHPERE,
	TEAPOT,
	TETRAHEDRON,
	THORUS
};

// aspekt obrazu

int aspect = FULL_WINDOW;

// rozmiary bry³y obcinania

const GLdouble left = -10.0;
const GLdouble right = 10.0;
const GLdouble bottom = -10.0;
const GLdouble top = 10.0;
const GLdouble near_ = 50.0;
const GLdouble far_ = 70.0;

// wspó³czynnik skalowania

GLfloat scale = 1.0;

// k¹ty obrotu

GLfloat rotatex = 0.0;
GLfloat rotatey = 0.0;

// przesuniêcie

GLfloat translatex = 0.0;
GLfloat translatey = 0.0;

// wskaznik naciœniêcia lewego przycisku myszki

int button_state = GLUT_UP;

// polozenie kursora myszki

int button_x, button_y;

GLdouble innerRadius = 0.4;
GLdouble outerRadius = 0.6;
GLint nsides = 50;
GLint rings = 50;
bool status = false;

SHAPES shape;

void Cone()
{
	if (status == true)
		glutSolidCone(1, 1, 10, 10);
	else
		glutWireCone(1, 1, 10, 10);

}

// funkcja rysuj¹ca piramidê z torusow

void Pyramid()

{
	//poziom 6
	for (double i = -2.5; i <= 2.5; i++)
	{
		for (double j = -2.5; j <= 2.5; j++)
		{
			glPushMatrix();

			glTranslatef(i, j, 8.0);
			
			switch (shape)
			{
			case SHAPES::CUBE:
				if (status == true)
					glutSolidCube(1);
				else
					glutWireCube(1);
				break;
			case SHAPES::CONE:
				if (status == true)
					glutSolidCone(1, 1, 10, 10);
				else
					glutWireCone(1, 1, 10, 10);
				break;
			case SHAPES::DODECAHEDRON:
				if (status == true)
					glutSolidDodecahedron();
				else
					glutWireDodecahedron();
				break;
			}

			glPopMatrix();
		}
	}
	//poziom 5

	for (double i = -2; i <= 2; i++)
	{
		for (double j = -2; j <= 2; j++)
		{
			glPushMatrix();

			glTranslatef(i, j, 9.0);

			switch (shape)
			{
			case SHAPES::CUBE:
				if (status == true)
					glutSolidCube(1);
				else
					glutWireCube(1);
				break;
			case SHAPES::CONE:
				if (status == true)
					glutSolidCone(1, 1, 10, 10);
				else
					glutWireCone(1, 1, 10, 10);
				break;
			case SHAPES::DODECAHEDRON:
				if (status == true)
					glutSolidDodecahedron();
				else
					glutWireDodecahedron();
				break;
			}

			glPopMatrix();
		}
	}
	//poziom 4


	for (double i = -1.5; i <= 1.5; i++)
	{
		for (double j = -1.5; j <= 1.5; j++)
		{
			glPushMatrix();

			glTranslatef(i, j, 10.0);

			switch (shape)
			{
			case SHAPES::CUBE:
				if (status == true)
					glutSolidCube(1);
				else
					glutWireCube(1);
				break;
			case SHAPES::CONE:
				if (status == true)
					glutSolidCone(1, 1, 10, 10);
				else
					glutWireCone(1, 1, 10, 10);
				break;
			case SHAPES::DODECAHEDRON:
				if (status == true)
					glutSolidDodecahedron();
				else
					glutWireDodecahedron();
				break;
			}

			glPopMatrix();
		}
	}
	//poziom 3


	for (double i = -1; i <= 1; i++)
	{
		for (double j = -1; j <= 1; j++)
		{
			glPushMatrix();

			glTranslatef(i, j, 11.0);

			switch (shape)
			{
			case SHAPES::CUBE:
				if (status == true)
					glutSolidCube(1);
				else
					glutWireCube(1);
				break;
			case SHAPES::CONE:
				if (status == true)
					glutSolidCone(1, 1, 10, 10);
				else
					glutWireCone(1, 1, 10, 10);
				break;
			case SHAPES::DODECAHEDRON:
				if (status == true)
					glutSolidDodecahedron();
				else
					glutWireDodecahedron();
				break;
			}

			glPopMatrix();
		}
	}
	//poziom2

	for (double i = -0.5; i <= 0.5; i++)
	{
		for (double j = -0.5; j <= 0.5; j++)
		{
			glPushMatrix();

			glTranslatef(i, j, 12.0);

			switch (shape)
			{
			case SHAPES::CUBE:
				if (status == true)
					glutSolidCube(1);
				else
					glutWireCube(1);
				break;
			case SHAPES::CONE:
				if (status == true)
					glutSolidCone(1, 1, 10, 10);
				else
					glutWireCone(1, 1, 10, 10);
				break;
			case SHAPES::DODECAHEDRON:
				if (status == true)
					glutSolidDodecahedron();
				else
					glutWireDodecahedron();
				break;
			}

			glPopMatrix();
		}
	}
	//poziom 1

	glPushMatrix();

	glTranslatef(0, 0, 13.0);

	switch (shape)
	{
	case SHAPES::CUBE:
		if (status == true)
			glutSolidCube(1);
		else
			glutWireCube(1);
		break;
	case SHAPES::CONE:
		if (status == true)
			glutSolidCone(1, 1, 10, 10);
		else
			glutWireCone(1, 1, 10, 10);
		break;
	case SHAPES::DODECAHEDRON:
		if (status == true)
			glutSolidDodecahedron();
		else
			glutWireDodecahedron();
		break;
	}

	glPopMatrix();
}

// funkcja generuj¹ca scenê 3D

void Display()
{
	// kolor t³a - zawartoœæ bufora koloru
	glClearColor(1.0, 1.0, 1.0, 1.0);

	// czyszczenie bufora koloru
	glClear(GL_COLOR_BUFFER_BIT);

	// wybór macierzy modelowania
	glMatrixMode(GL_MODELVIEW);

	// macierz modelowania = macierz jednostkowa
	glLoadIdentity();

	// przesuniêcie uk³adu wspó³rzêdnych obiektu do œrodka bry³y odcinania
	glTranslatef(0, 0, -(near_ + far_) / 2);

	// przesuniêcie obiektu - ruch myszk¹
	glTranslatef(translatex, translatey, 0.0);

	// skalowanie obiektu - klawisze "+" i "-"
	glScalef(scale, scale, scale);

	// obroty obiektu - klawisze kursora
	glRotatef(rotatex, 1.0, 0, 0);
	glRotatef(rotatey, 0, 1.0, 0);

	// kolor krawêdzi obiektu
	glColor3f(0.0, 0.0, 0.0);

	// rysowanie piramidy
	Pyramid();

	// skierowanie poleceñ do wykonania
	glFlush();

	// zamiana buforów koloru
	glutSwapBuffers();
}

// zmiana wielkoœci okna

void Reshape(int width, int height)
{
	// obszar renderingu - ca³e okno
	glViewport(0, 0, width, height);

	// wybór macierzy rzutowania
	glMatrixMode(GL_PROJECTION);

	// macierz rzutowania = macierz jednostkowa
	glLoadIdentity();

	// parametry bry³y obcinania
	if (aspect == ASPECT_1_1)
	{
		// wysokoœæ okna wiêksza od wysokoœci okna
		if (width < height && width > 0)
			glFrustum(left, right, bottom*height / width, top*height / width, near_, far_);
		else

			// szerokoœæ okna wiêksza lub równa wysokoœci okna
			if (width >= height && height > 0)
				glFrustum(left*width / height, right*width / height, bottom, top, near_, far_);
	}
	else
		glFrustum(left, right, bottom, top, near_, far_);

	// generowanie sceny 3D
	Display();
}

// obs³uga klawiatury

void Keyboard(unsigned char key, int x, int y)
{
	// klawisz +
	if (key == '+')
		scale += 0.1;
	else

		// klawisz -
		if (key == '-' && scale > 0.1)
			scale -= 0.1;

	// odrysowanie okna
	Reshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
}

// obs³uga klawiszy funkcyjnych i klawiszy kursora

void SpecialKeys(int key, int x, int y)
{
	switch (key)
	{
		// kursor w lewo
	case GLUT_KEY_LEFT:
		rotatey -= 1;
		break;

		// kursor w górê
	case GLUT_KEY_UP:
		rotatex -= 1;
		break;

		// kursor w prawo
	case GLUT_KEY_RIGHT:
		rotatey += 1;
		break;

		// kursor w dó³
	case GLUT_KEY_DOWN:
		rotatex += 1;
		break;
	}

	// odrysowanie okna
	Reshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
}

// obs³uga przycisków myszki

void MouseButton(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON)
	{
		// zapamiêtanie stanu lewego przycisku myszki
		button_state = state;

		// zapamiêtanie po³o?enia kursora myszki
		if (state == GLUT_DOWN)
		{
			button_x = x;
			button_y = y;
		}
	}
}

// obs³uga ruchu kursora myszki

void MouseMotion(int x, int y)
{
	if (button_state == GLUT_DOWN)
	{
		translatex += 1.1 *(right - left) / glutGet(GLUT_WINDOW_WIDTH) * (x - button_x);
		button_x = x;
		translatey += 1.1 *(top - bottom) / glutGet(GLUT_WINDOW_HEIGHT) * (button_y - y);
		button_y = y;
		glutPostRedisplay();
	}
}

// obs³uga menu podrêcznego

void Menu(int value)
{
	switch (value)
	{
		// obszar renderingu - ca³e okno
	case FULL_WINDOW:
		aspect = FULL_WINDOW;
		Reshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
		break;

	case StylSolid:
		status = true;
		Reshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
		break;

	case StylWire:
		status = false;
		Reshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
		break;

		// obszar renderingu - aspekt 1:1
	case ASPECT_1_1:
		aspect = ASPECT_1_1;
		Reshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
		break;
		// wyjœcie
	case EXIT:
		exit(0);
	}
}

void MaterialStyle(int value)
{
	switch (value)
	{
	case CONE:
		shape = CONE;
		Reshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
		break;

	case CUBE:
		shape = CUBE;
		Reshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
		break;

	case CYLINDER:
		shape = CYLINDER;
		Reshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
		break;

	case DODECAHEDRON:
		shape = DODECAHEDRON;
		Reshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
		break;
	}
}

int main(int argc, char *argv[])
{
	// inicjalizacja biblioteki GLUT
	glutInit(&argc, argv);

	// inicjalizacja bufora ramki
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

	// rozmiary g³ównego okna programu
	glutInitWindowSize(800, 800);

	// utworzenie g³ównego okna programu
	glutCreateWindow("GK06 Cw01");

	// do³¹czenie funkcji generuj¹cej scenê 3D
	glutDisplayFunc(Display);

	// do³¹czenie funkcji wywo³ywanej przy zmianie rozmiaru okna
	glutReshapeFunc(Reshape);

	// do³¹czenie funkcji obs³ugi klawiatury
	glutKeyboardFunc(Keyboard);

	// do³¹czenie funkcji obs³ugi klawiszy funkcyjnych i klawiszy kursora
	glutSpecialFunc(SpecialKeys);

	// obs³uga przycisków myszki
	glutMouseFunc(MouseButton);

	// obs³uga ruchu kursora myszki
	glutMotionFunc(MouseMotion);

	// utworzenie podmenu - styl rysowania
	int DrawinStyle = glutCreateMenu(Menu);
	glutAddMenuEntry("Solid", StylSolid);
	glutAddMenuEntry("Wire", StylWire);

	int MaterialStyle = glutCreateMenu(Menu);

	glutAddMenuEntry("1 Stozek", CONE);
	glutAddMenuEntry("2 Cube", CUBE);
	glutAddMenuEntry("3 Cylinder", CYLINDER);
	glutAddMenuEntry("4 Dodecahedron", DODECAHEDRON);

	// menu g³ówne
	glutCreateMenu(Menu);
	glutAddSubMenu("Styl rysowania", DrawinStyle);
	glutAddSubMenu("Material", MaterialStyle);
	glutAddMenuEntry("Wyjœcie", EXIT);

	// okreœlenie przycisku myszki obs³uguj¹cego menu podrêczne
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	// wprowadzenie programu do obs³ugi pêtli komunikatów
	glutMainLoop();
	return 0;
}
