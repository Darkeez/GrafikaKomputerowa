// Piramida.cpp : Defines the entry point for the console application.
// Ziemowit Juroszek
// Torus


#include "stdafx.h"
#include <GL/glut.h>
#include <stdlib.h>

// sta�e do obs�ugi menu podr�cznego

enum
{
	StylSolid,
	StylWire,
	FULL_WINDOW,       // aspekt obrazu - ca�e okno
	ASPECT_1_1,        // aspekt obrazu 1:1
	EXIT               // wyj�cie
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

// rozmiary bry�y obcinania

const GLdouble left = -10.0;
const GLdouble right = 10.0;
const GLdouble bottom = -10.0;
const GLdouble top = 10.0;
const GLdouble near_ = 50.0;
const GLdouble far_ = 70.0;

// wsp�czynnik skalowania

GLfloat scale = 1.0;

// k�ty obrotu

GLfloat rotatex = 0.0;
GLfloat rotatey = 0.0;

// przesuni�cie

GLfloat translatex = 0.0;
GLfloat translatey = 0.0;

// wskaznik naci�ni�cia lewego przycisku myszki

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

// funkcja rysuj�ca piramid� z torusow

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

// funkcja generuj�ca scen� 3D

void Display()
{
	// kolor t�a - zawarto�� bufora koloru
	glClearColor(1.0, 1.0, 1.0, 1.0);

	// czyszczenie bufora koloru
	glClear(GL_COLOR_BUFFER_BIT);

	// wyb�r macierzy modelowania
	glMatrixMode(GL_MODELVIEW);

	// macierz modelowania = macierz jednostkowa
	glLoadIdentity();

	// przesuni�cie uk�adu wsp�rz�dnych obiektu do �rodka bry�y odcinania
	glTranslatef(0, 0, -(near_ + far_) / 2);

	// przesuni�cie obiektu - ruch myszk�
	glTranslatef(translatex, translatey, 0.0);

	// skalowanie obiektu - klawisze "+" i "-"
	glScalef(scale, scale, scale);

	// obroty obiektu - klawisze kursora
	glRotatef(rotatex, 1.0, 0, 0);
	glRotatef(rotatey, 0, 1.0, 0);

	// kolor kraw�dzi obiektu
	glColor3f(0.0, 0.0, 0.0);

	// rysowanie piramidy
	Pyramid();

	// skierowanie polece� do wykonania
	glFlush();

	// zamiana bufor�w koloru
	glutSwapBuffers();
}

// zmiana wielko�ci okna

void Reshape(int width, int height)
{
	// obszar renderingu - ca�e okno
	glViewport(0, 0, width, height);

	// wyb�r macierzy rzutowania
	glMatrixMode(GL_PROJECTION);

	// macierz rzutowania = macierz jednostkowa
	glLoadIdentity();

	// parametry bry�y obcinania
	if (aspect == ASPECT_1_1)
	{
		// wysoko�� okna wi�ksza od wysoko�ci okna
		if (width < height && width > 0)
			glFrustum(left, right, bottom*height / width, top*height / width, near_, far_);
		else

			// szeroko�� okna wi�ksza lub r�wna wysoko�ci okna
			if (width >= height && height > 0)
				glFrustum(left*width / height, right*width / height, bottom, top, near_, far_);
	}
	else
		glFrustum(left, right, bottom, top, near_, far_);

	// generowanie sceny 3D
	Display();
}

// obs�uga klawiatury

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

// obs�uga klawiszy funkcyjnych i klawiszy kursora

void SpecialKeys(int key, int x, int y)
{
	switch (key)
	{
		// kursor w lewo
	case GLUT_KEY_LEFT:
		rotatey -= 1;
		break;

		// kursor w g�r�
	case GLUT_KEY_UP:
		rotatex -= 1;
		break;

		// kursor w prawo
	case GLUT_KEY_RIGHT:
		rotatey += 1;
		break;

		// kursor w d�
	case GLUT_KEY_DOWN:
		rotatex += 1;
		break;
	}

	// odrysowanie okna
	Reshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
}

// obs�uga przycisk�w myszki

void MouseButton(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON)
	{
		// zapami�tanie stanu lewego przycisku myszki
		button_state = state;

		// zapami�tanie po�o?enia kursora myszki
		if (state == GLUT_DOWN)
		{
			button_x = x;
			button_y = y;
		}
	}
}

// obs�uga ruchu kursora myszki

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

// obs�uga menu podr�cznego

void Menu(int value)
{
	switch (value)
	{
		// obszar renderingu - ca�e okno
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
		// wyj�cie
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

	// rozmiary g��wnego okna programu
	glutInitWindowSize(800, 800);

	// utworzenie g��wnego okna programu
	glutCreateWindow("GK06 Cw01");

	// do��czenie funkcji generuj�cej scen� 3D
	glutDisplayFunc(Display);

	// do��czenie funkcji wywo�ywanej przy zmianie rozmiaru okna
	glutReshapeFunc(Reshape);

	// do��czenie funkcji obs�ugi klawiatury
	glutKeyboardFunc(Keyboard);

	// do��czenie funkcji obs�ugi klawiszy funkcyjnych i klawiszy kursora
	glutSpecialFunc(SpecialKeys);

	// obs�uga przycisk�w myszki
	glutMouseFunc(MouseButton);

	// obs�uga ruchu kursora myszki
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

	// menu g��wne
	glutCreateMenu(Menu);
	glutAddSubMenu("Styl rysowania", DrawinStyle);
	glutAddSubMenu("Material", MaterialStyle);
	glutAddMenuEntry("Wyj�cie", EXIT);

	// okre�lenie przycisku myszki obs�uguj�cego menu podr�czne
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	// wprowadzenie programu do obs�ugi p�tli komunikat�w
	glutMainLoop();
	return 0;
}
