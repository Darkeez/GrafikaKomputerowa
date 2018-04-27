#include "stdafx.h"
#include <GL\freeglut.h>

/*
Program 2. Zbudowaæ w przestrzeni widocznej sto¿ek wykorzystuj¹c dwa wachlarze trójk¹tów. Pierwszy wachlarz tworzy kszta³t sto¿ka, przy czym pierwszy wierzcho³ek wyznacza czubek sto¿ka, 
a pozosta³e wierzcho³ki tworz¹ ko³o wokó³ osi z. Drugi wachlarz definiuje wilok¹t z werzcho³kami le¿¹cymi na kole na p³aszczyŸnie xy.
Patrz¹c na sto¿ek wzd³u¿ osi z, zobaczymy tylko welok¹t utworzony z wachlarza trójk¹tów. Poszczególne trójk¹ty uwypuklane s¹ poprzez stosowanie zamiennie kolorów czerwonego i zielonego.
Stosowaæ mieszanie ze sob¹ kolorów przez wszystkie  wierzcho³ki.

*/

void RysujStozek();
//Ustalenie wielkosci obrotu
float rotX = 0.0f, rotY = 0.0f;


void Display()
{
	// Wyczyszczenie okna aktualnym kolorem czyszcz¹cym i bufora g³êbi
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// ustawienie stosu macierzy rzutowania
	glMatrixMode(GL_MODELVIEW);
	//s³u¿y do ponownego ustawienia (resetu) uk³adu wspó³rzêdnych, zanim wykonane zostan¹ jakiekolwiek manipulacje na macierzach.
	glLoadIdentity();
	//Obrót realizowany jest w kierunku przeciwnym do ruchu wskazówek zegara w kierunku prostej wyznaczonej przez wektor [x, y, z] zaczepionym w pocz¹tku uk³adu wspó³rzêdnych.
	glRotatef(rotX, 1.0f, 0.0f, 0.0f);
	glRotatef(rotY, 0.0f, 1.0f, 0.0f);
	//Sposób rysowania obiektów ustala siê za pomoc¹ funkcji glPolygonMode 
	//Pierwszy parametr ustala która czêœæ obiektu ma byæ rysowana w sposób okreœlony za pomoc¹ drugiego parametru
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	//Wywolanie funkcji rysujacej
	RysujStozek();
	// Wys³anie poleceñ do wykonania i zamiana buforów
	glutSwapBuffers();
}

void onResize(int w, int h)
{
	if (h == 0)
		h = 1;

	float aspect = (float)w / (float)h;

	// Ustalenie wielkoœci widoku zgodnego z rozmiarami okna
	glViewport(0, 0, w, h);
	// ustawienie stosu macierzy rzutowania
	glMatrixMode(GL_PROJECTION);
	/*
	s³u¿y do ponownego ustawienia (resetu) uk³adu wspó³rzêdnych, zanim wykonane zostan¹  jakiekolwiek
	manipulacje na macierzach. Bez ponownego ustawienia uk³adu wspó³rzêdnych przed ka¿dym wywo³aniem funkcji
	glOrtho ka¿de kolejne wywo³anie powodowa³oby coraz wiêksze zniekszta³cenia planowanej przestrzeni ograniczaj¹cej
	*/
	glLoadIdentity();

	if (w <= h)
	{
		//do przestrzeni ograniczaj¹cej zastosowaliœmy rzutowanie prostopadle. W bibliotece OpenGL funkcjê tworz¹ca takie rzutowanie jest funkcja glOrtho
		glOrtho(-100.0f, 100.0, -100.0f / aspect, 100.0 / aspect, 100.0f, -100.0f);
	}
	else
	{
		//do przestrzeni ograniczaj¹cej zastosowaliœmy rzutowanie prostopadle. W bibliotece OpenGL funkcjê tworz¹ca takie rzutowanie jest funkcja glOrtho
		glOrtho(-100.0 * aspect, 100.0 * aspect, -100.0f, 100.0, 100.0f, -100.0f);
	}

	// ustawienie stosu macierzy rzutowania
	glMatrixMode(GL_MODELVIEW);
	//s³u¿y do ponownego ustawienia (resetu) uk³adu wspó³rzêdnych, zanim wykonane zostan¹ jakiekolwiek manipulacje na macierzach.
	glLoadIdentity();

}

void SetupRenderingContext()
{
	//Funkcja ta ustala kolor stosowany do czyszczenia zawartoœci okna.
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	// Model cieniowania kolorów – p³aski. biblioteka OpenGL bêdzie wype³nia³a wielok¹ty jednolitym kolorem
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

	//S³u¿¹ one do niezale¿nego od pêtli wyœwietlenia zawartoœci okna. Dzia³a na aktywne okno
	// Odœwie¿enie zawartoœci okna
	glutPostRedisplay();
}

void Menu(int value)
{
	switch (value)
	{
	case 1:
		// Model cieniowania kolorów – p³aski. biblioteka OpenGL bêdzie wype³nia³a wielok¹ty jednolitym kolorem
		glShadeModel(GL_FLAT);
		break;
	case 2:
		// miesza ze sob kolory definiowane w aktualnym wielokcie przez wszystkie jego wierzcho³ki.
		glShadeModel(GL_SMOOTH);
		break;
	}
	//S³u¿¹ one do niezale¿nego od pêtli wyœwietlenia zawartoœci okna. Dzia³a na aktywne okno
	// Odœwie¿enie zawartoœci okna
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
	// do³¹czenie funkcji obs³ugi klawiatury
	glutKeyboardFunc(onKeyDown);
	//rejestruj¹ca funkcja zwrotna wywo³ywana przez bibliotek przy ka¿dej zmianie rozmiarów okna.
	glutReshapeFunc(onResize);
	//zdefiniowana wczeœniej funkcja bêdzie funkcja zwrotna {callback function) wyœwietlaj¹ca obraz na ekranie.
	glutDisplayFunc(Display);
	// wprowadzenie programu do obs³ugi pêtli komunikatów
	glutMainLoop();
	/*
	Ta funkcja uruchamia szkielet biblioteki GLUT. Po zdefiniowaniu funkcji zwrotnej obs³uguj¹cej rysowanie na ekranie i
	innych funkcji uruchamiany jest mechanizm biblioteki. Powrót z funkcji
	glutMainLoop nastêpuje dopiero przy zakoñczeniu pracy programu, dlatego wystarczy wywo³aæ j¹ tylko raz. Funkcja ta
	przetwarza wszystkie komunikaty systemu operacyjnego, naciœniêcia klawiszy i inne, do czasu zakoñczenia pracy
	programu.
	*/

	return 0;
}

void RysujStozek()
{
	//Podstawa
	//Wachlarz 6ciu trójk¹tów wype³nionych kolorem
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
	// Zakoñczenie rysowania punktów
	glEnd();



	//Stozek
	//Wachlarz 6ciu trójk¹tów wype³nionych kolorem
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