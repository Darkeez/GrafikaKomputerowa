#include "stdafx.h"
#include <GL\freeglut.h>

/* Program 2. Narysowa� w oknie programu Program1 wielok�t. 
Dodatkowo uzyska� mo�liwo�� zmiany po�o�enia i rozmiaru okna, tak �eby kod renderuj�cy odpowiednio reagowa� na te zmiany.
*/

//Otrzymany wariant: 6cio kat


void Display()
{
	/*Funkcja glClear czy�ci zawarto�� okre�lonego bufora lub kombinacji bufor�w. 
	Bufor jest obszarem w pami�ci przechowuj�cym informacj� o obrazie. Sk�adowe czerwona, zielona i niebieska, 
	tworz�ce rysunek, zazwyczaj opisywane s� terminem bufora koloru (ang. color buffer) lub bufora pikseli (ang. pixel buffer).
	*/
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Spos�b rysowania obiekt�w ustala si� za pomoc� funkcji glPolygonMode 
	//Pierwszy parametr ustala kt�ra cz�� obiektu ma by� rysowana w spos�b okre�lony za pomoc� drugiego parametru
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //GL_FILL rysowanie jako wype�nienie
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

	//Wachlarz 6ciu tr�jk�t�w, rysowanych liniami (szablon)
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //GL_LINE rysowanie jako linia
	glColor3f(0.0f, 0.0f, 0.0f);
	//Wachlarz 6ciu tr�jk�t�w rysowanych krawedziami
	//Rysowanie od dolnego w lewo
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
	glutSwapBuffers();
}

// Wywo�ywana przez bibliotek GLUT w przypadku zmiany rozmiaru okna
void onResize(int w, int h)
{
	if (h == 0)
		h = 1;
	float aspect = (float)w / (float)h;
	// Ustawienie wielko�ci widoku na r�wn� wielko�ci okna     
	glViewport(0, 0, w, h);
	// Ustalenie uk�adu wsp�rz�dnych 
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// Wyznaczenie przestrzeni ograniczaj�cej (lewy, prawy, dolny, g�rny, bliski, odleg�y)
	if (w <= h)
		glOrtho(-100.0f, 100.0, -100.0f / aspect, 100.0 / aspect, 1.0f, -1.0f);
	else
		glOrtho(-100.0 * aspect, 100.0 * aspect, -100.0f, 100.0, 1.0f, -1.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

// Ustalenie stanu rendrowania 
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
	glutCreateWindow("Program1");

	//Wywo�anie funkcji kt�ra ustala stan renderowania
	SetupRenderingContext();
	//Rejstruj�ca funkcja zwrotna wywo�ywan� przez bibliotek� przy ka�dej zmianie rozmiar�w okna.
	glutReshapeFunc(onResize);
	/*
	W tej linii ustalamy, �e zdefiniowana wcze�niej funkcja Display b�dzie funkcj� zwrotn� (callback function) wy�wietlaj�c� obraz na ekranie.
	Oznacza to, �e biblioteka GLUT b�dzie wywo�ywa� wskazan� tu funkcj� za ka�dym razem, gdy okno b�dzie wymaga�o przerysowywania.
	Takie wywo�anie nast�pi przy pierwszym wy�wietleniu okna, a tak�e przy zmianach jego rozmiaru albo ods�oni�ciu.
	W tym w�a�nie miejscu umieszczamy wywo�ania funkcji renderuj�cych biblioteki OpenGL.
	*/
	glutDisplayFunc(Display);

	glutMainLoop();

	return 0;
}

