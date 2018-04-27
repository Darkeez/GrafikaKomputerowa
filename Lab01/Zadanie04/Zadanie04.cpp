#include "stdafx.h"
#include <GL\freeglut.h>

/*

Program 4. Opracowa� program, w kt�rym wielok�t obraca si� wok� niekt�rej osi

Otrzymany wariant: 6cio k�t
*/


float angle = 0.0f;

void Display()
{

	// Wyczy�� ekran i bufor g��bi 
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Wybor macierzy modeli
	glMatrixMode(GL_MODELVIEW);
	//Zresetuj ja Przy wywo�aniu glLoadIdentity() przmieszczasz si� na �rodek ekranu. O� X biegnie z lewej do prawej, Y z g�ry na d�, a Z do ciebie.
	glLoadIdentity(); 
	//Obr�t w OpenGL wykonuj� funkcje glRotated i glRotatef
	//Obr�t realizowany jest w kierunku przeciwnym do ruchu wskaz�wek zegara w kierunku prostej wyznaczonej przez wektor [x, y, z] zaczepionym w pocz�tku uk�adu wsp�rz�dnych
	glRotatef(angle, 0.0f, 0.0f, 1.0f);
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

	// Rysujemy siatk� metod� 'linii'
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//Pobranie aktualnego koloru rysuj�cego
	glColor3f(0.0f, 0.0f, 0.0f);
	//Wachlarz 6ciu tr�jk�t�w obramowanych
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

	angle += 1.0f;
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
	//Zresetuj macierz Przy wywo�aniu glLoadIdentity() przmieszczasz si� na �rodek ekranu.
	// Wyznaczenie przestrzeni ograniczaj�cej (lewy, prawy, dolny, g�rny, bliski, odleg�y)  
	if (w <= h)
	{
		glOrtho(-100.0f, 100.0, -100.0f / aspect, 100.0 / aspect, 1.0f, -1.0f);
	}
	else
	{
		glOrtho(-100.0 * aspect, 100.0 * aspect, -100.0f, 100.0, 1.0f, -1.0f);
	}
	//Wszystkie przysz�e przekszta�cenia b�d� dotyczy�y naszych modeli, czyli tego, co narysujemy
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//Zresetuj macierz Przy wywo�aniu glLoadIdentity() przmieszczasz si� na �rodek ekranu.

}

void SetupRenderingContext()
{
	//Funkcja ta ustala kolor stosowany do czyszczenia zawarto�ci okna.
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutCreateWindow("GK01 Cw3");

	SetupRenderingContext();
	//Funkcja glutReshapeFunc rejestrujca funkcj� zwrotn� wywo�ywan� przez bibliotek� przy ka�dej zmianie rozmiar�w okna
	glutReshapeFunc(onResize);
	//Funkcja RenderScene b�dzie funkcj� zwrotn� (callback function) wy�wietlaj�c� obraz na ekranie
	glutDisplayFunc(Display);
	//Wprwadzenie do petli
	glutMainLoop();

	return 0;
}

