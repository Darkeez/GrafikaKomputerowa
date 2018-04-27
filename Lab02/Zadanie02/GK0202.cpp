#include "stdafx.h"
#include <GL\freeglut.h>

/*
Program 2. Zbudowa� w przestrzeni widocznej sto�ek wykorzystuj�c dwa wachlarze tr�jk�t�w. Pierwszy wachlarz tworzy kszta�t sto�ka, przy czym pierwszy wierzcho�ek wyznacza czubek sto�ka, 
a pozosta�e wierzcho�ki tworz� ko�o wok� osi z. Drugi wachlarz definiuje wilok�t z werzcho�kami le��cymi na kole na p�aszczy�nie xy.
Patrz�c na sto�ek wzd�u� osi z, zobaczymy tylko welok�t utworzony z wachlarza tr�jk�t�w. Poszczeg�lne tr�jk�ty uwypuklane s� poprzez stosowanie zamiennie kolor�w czerwonego i zielonego.
Stosowa� mieszanie ze sob� kolor�w przez wszystkie  wierzcho�ki.

*/

void RysujStozek();
//Ustalenie wielkosci obrotu
float rotX = 0.0f, rotY = 0.0f;


void Display()
{
	// Wyczyszczenie okna aktualnym kolorem czyszcz�cym i bufora g��bi
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// ustawienie stosu macierzy rzutowania
	glMatrixMode(GL_MODELVIEW);
	//s�u�y do ponownego ustawienia (resetu) uk�adu wsp�rz�dnych, zanim wykonane zostan� jakiekolwiek manipulacje na macierzach.
	glLoadIdentity();
	//Obr�t realizowany jest w kierunku przeciwnym do ruchu wskaz�wek zegara w kierunku prostej wyznaczonej przez wektor [x, y, z] zaczepionym w pocz�tku uk�adu wsp�rz�dnych.
	glRotatef(rotX, 1.0f, 0.0f, 0.0f);
	glRotatef(rotY, 0.0f, 1.0f, 0.0f);
	//Spos�b rysowania obiekt�w ustala si� za pomoc� funkcji glPolygonMode 
	//Pierwszy parametr ustala kt�ra cz�� obiektu ma by� rysowana w spos�b okre�lony za pomoc� drugiego parametru
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	//Wywolanie funkcji rysujacej
	RysujStozek();
	// Wys�anie polece� do wykonania i zamiana bufor�w
	glutSwapBuffers();
}

void onResize(int w, int h)
{
	if (h == 0)
		h = 1;

	float aspect = (float)w / (float)h;

	// Ustalenie wielko�ci widoku zgodnego z rozmiarami okna
	glViewport(0, 0, w, h);
	// ustawienie stosu macierzy rzutowania
	glMatrixMode(GL_PROJECTION);
	/*
	s�u�y do ponownego ustawienia (resetu) uk�adu wsp�rz�dnych, zanim wykonane zostan�  jakiekolwiek
	manipulacje na macierzach. Bez ponownego ustawienia uk�adu wsp�rz�dnych przed ka�dym wywo�aniem funkcji
	glOrtho ka�de kolejne wywo�anie powodowa�oby coraz wi�ksze zniekszta�cenia planowanej przestrzeni ograniczaj�cej
	*/
	glLoadIdentity();

	if (w <= h)
	{
		//do przestrzeni ograniczaj�cej zastosowali�my rzutowanie prostopadle. W bibliotece OpenGL funkcj� tworz�ca takie rzutowanie jest funkcja glOrtho
		glOrtho(-100.0f, 100.0, -100.0f / aspect, 100.0 / aspect, 100.0f, -100.0f);
	}
	else
	{
		//do przestrzeni ograniczaj�cej zastosowali�my rzutowanie prostopadle. W bibliotece OpenGL funkcj� tworz�ca takie rzutowanie jest funkcja glOrtho
		glOrtho(-100.0 * aspect, 100.0 * aspect, -100.0f, 100.0, 100.0f, -100.0f);
	}

	// ustawienie stosu macierzy rzutowania
	glMatrixMode(GL_MODELVIEW);
	//s�u�y do ponownego ustawienia (resetu) uk�adu wsp�rz�dnych, zanim wykonane zostan� jakiekolwiek manipulacje na macierzach.
	glLoadIdentity();

}

void SetupRenderingContext()
{
	//Funkcja ta ustala kolor stosowany do czyszczenia zawarto�ci okna.
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	// Model cieniowania kolor�w � p�aski. biblioteka OpenGL b�dzie wype�nia�a wielok�ty jednolitym kolorem
	glShadeModel(GL_FLAT);
	// Usuwanie ukrytych powierzchni
	glEnable(GL_DEPTH_TEST);
}

void onKeyDown(unsigned char key, int x, int y)
{
	if (key == GLUT_KEY_UP)
		rotX += 5.0f;

	if (key == GLUT_KEY_DOWN)
		rotX -= 5.0f;

	if (key == GLUT_KEY_LEFT)
		rotY -= 5.0f;

	if (key == GLUT_KEY_RIGHT)
		rotY += 5.0f;

	//S�u�� one do niezale�nego od p�tli wy�wietlenia zawarto�ci okna. Dzia�a na aktywne okno
	// Od�wie�enie zawarto�ci okna
	glutPostRedisplay();
}

void Menu(int value)
{
	switch (value)
	{
	case 1:
		// Model cieniowania kolor�w � p�aski. biblioteka OpenGL b�dzie wype�nia�a wielok�ty jednolitym kolorem
		glShadeModel(GL_FLAT);
		break;
	case 2:
		// miesza ze sob kolory definiowane w aktualnym wielokcie przez wszystkie jego wierzcho�ki.
		glShadeModel(GL_SMOOTH);
		break;
	}
	//S�u�� one do niezale�nego od p�tli wy�wietlenia zawarto�ci okna. Dzia�a na aktywne okno
	// Od�wie�enie zawarto�ci okna
	glutPostRedisplay();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutCreateWindow("GK02 Cw02");

	SetupRenderingContext();

	glutCreateMenu(Menu);
	glutAddMenuEntry("Cieniowanie plaskie.", 1);
	glutAddMenuEntry("Cieniowanie Gourauda.", 2);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	// do��czenie funkcji obs�ugi klawiatury
	glutKeyboardFunc(onKeyDown);
	//rejestruj�ca funkcja zwrotna wywo�ywana przez bibliotek przy ka�dej zmianie rozmiar�w okna.
	glutReshapeFunc(onResize);
	//zdefiniowana wcze�niej funkcja b�dzie funkcja zwrotna {callback function) wy�wietlaj�ca obraz na ekranie.
	glutDisplayFunc(Display);
	// wprowadzenie programu do obs�ugi p�tli komunikat�w
	glutMainLoop();
	/*
	Ta funkcja uruchamia szkielet biblioteki GLUT. Po zdefiniowaniu funkcji zwrotnej obs�uguj�cej rysowanie na ekranie i
	innych funkcji uruchamiany jest mechanizm biblioteki. Powr�t z funkcji
	glutMainLoop nast�puje dopiero przy zako�czeniu pracy programu, dlatego wystarczy wywo�a� j� tylko raz. Funkcja ta
	przetwarza wszystkie komunikaty systemu operacyjnego, naci�ni�cia klawiszy i inne, do czasu zako�czenia pracy
	programu.
	*/

	return 0;
}

void RysujStozek()
{
	//Podstawa
	//Wachlarz 6ciu tr�jk�t�w wype�nionych kolorem
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex2f(0.0f, 0.0f);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex2f(12.0f, -22.0f);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex2f(-13.0f, -22.0f);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex2f(-25.0f, 0.0f);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex2f(-12.0f, 22.0f);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex2f(12.0f, 22.0f);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex2f(25.0f, 0.0f);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex2f(12.0f, -22.0f);
	// Zako�czenie rysowania punkt�w
	glEnd();



	//Stozek
	//Wachlarz 6ciu tr�jk�t�w wype�nionych kolorem
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f,-50.0f);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex2f(12.0f, -22.0f);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex2f(-13.0f, -22.0f);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex2f(-25.0f, 0.0f);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex2f(-12.0f, 22.0f);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex2f(12.0f, 22.0f);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex2f(25.0f, 0.0f);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex2f(12.0f, -22.0f);
	glEnd();
}