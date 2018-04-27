#include "stdafx.h"
#include <GL\freeglut.h>

/* Opracowa� dla Programu 2 efekt animacji, �eby wielok�t  odbija�by si� od ram okna. 
Przygotowa� p�tl�, w kt�rej zmienia� wsp�rz�dne obiektu przed wywo�aniem funkcji RenderScene.
Obiekt musi sprawia� wra�enie ruchu wewn�trz okna wzd�u� obwodu (zadanie domowe)*

Otrzymany wariant: 6cio k�t
*/


float dX = 0.1f;
float dY = 0.1f;
float moveX = 1.0f;
float moveY = 1.0f;

float viewWidth;
float viewHeight;

void Display()
{

	// Wyczy�� ekran i bufor g��bi 
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Wybor macierzy modeli
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity(); //Zresetuj ja Przy wywo�aniu glLoadIdentity() przmieszczasz si� na �rodek ekranu. O� X biegnie z lewej do prawej, Y z g�ry na d�, a Z do ciebie.
	glTranslatef(moveX, moveY, 0.0f); //przemieszcza obiekt po 3 osiach. (z w g��b ekranu)
	 // Rysujemy siatk� metod� 'wypelnienia' 
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	//Pobranie aktualnego koloru rysuj�cego
	glColor3f(1.0f, 0.0f, 0.0f);
	//Wachlarz 6ciu tr�jk�t�w wype�nionych czerwonym kolorem
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(0.0f, 0.0f);
	glVertex2f(12.0f, -22.0f);
	glVertex2f(-13.0f, -22.0f);
	glVertex2f(-25.0f, 0.0f);
	glVertex2f(-12.0f, 22.0f);
	glVertex2f(12.0f, 22.0f);
	glVertex2f(25.0f, 0.0f);
	glVertex2f(12.0f, -22.0f);
	glEnd();


	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(0.0f, 0.0f);
	glVertex2f(12.0f, -22.0f);
	glVertex2f(-13.0f, -22.0f);
	glVertex2f(-25.0f, 0.0f);
	glVertex2f(-12.0f, 22.0f);
	glVertex2f(12.0f, 22.0f);
	glVertex2f(25.0f, 0.0f);
	glVertex2f(12.0f, -22.0f);
	glEnd();


	if (moveX > viewWidth)
		dX = -dX;
	if (moveX < -viewWidth)
		dX = -dX;

	if (moveY > viewHeight)
		dY = -dY;
	if (moveY < -viewHeight)
		dY = -dY;

	moveX += dX;
	moveY += dY;

	//Ko�cowym elementem tworzenia sceny 3D jest zamiana bufor�w koloru
	glutSwapBuffers();
	// Ponowne rysowanie sceny z nowymi wsp�rz�dnymi
	glutPostRedisplay();

}

void onResize(int w, int h)
{
	if (h == 0)
		h = 1;

	float aspect = (float)w / (float)h;

	// Ustalenie wielko�ci widoku zgodnego z rozmiarami okna
	glViewport(0, 0, w, h);

	// Ustalenie uk�adu wsp�rz�dnych  
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Wyznaczenie przestrzeni ograniczaj�cej (lewy, prawy, dolny, g�rny, bliski, odleg�y)  
	if (w <= h)
	{
		glOrtho(-100.0f, 100.0, -100.0f / aspect, 100.0 / aspect, 1.0f, -1.0f);
		viewWidth = 87.0f;
		viewHeight = 80.0f / aspect;
	}
	else
	{
		glOrtho(-100.0 * aspect, 100.0 * aspect, -100.0f, 100.0, 1.0f, -1.0f);
		viewWidth = 87.0f * aspect;
		viewHeight = 80.0f;
	}

	//Wszystkie przysz�e przekszta�cenia b�d� dotyczy�y naszych modeli, czyli tego, co narysujemy
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}


void SetupRenderingContext()
{
	//Funkcja ta ustala kolor stosowany do czyszczenia zawarto�ci okna.
	glClearColor(0.53f, 0.8f, 0.92f, 1.0f);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutCreateWindow("GK01 Cw03");

	SetupRenderingContext();

	//Funkcja glutReshapeFunc rejestrujca funkcj� zwrotn� wywo�ywan� przez bibliotek� przy ka�dej zmianie rozmiar�w okna
	glutReshapeFunc(onResize);

	//Funkcja RenderScene b�dzie funkcj� zwrotn� (callback function) wy�wietlaj�c� obraz na ekranie
	glutDisplayFunc(Display);

	glutMainLoop();

	return 0;
}

