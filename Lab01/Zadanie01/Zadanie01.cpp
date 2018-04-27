#include "stdafx.h"
#include <GL\freeglut.h>

/*Program 1. Opracowa� program kt�ry tworzy w GLUT standardowe okno interfejsu GUI
z nag��wkiem "M�j pierwszy program w GLUT"  i pustym br�zowym t�em.
*/


// Funkcja wywo�ywana w celu narysowania sceny
void Display()
{
	// Wyczyszczenie okna aktualnym kolorem czyszcz�cym
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Wys�anie polece� do wykonania
	glutSwapBuffers();
}

void SetupRenderingContext() //ustawienie stanu renderowania
{
	//ustalenie br�zowego koloru czyszcz�cego
	glClearColor(0.96f, 0.64f, 0.38f, 1.0f); //kolor sandybrown
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutCreateWindow("M�j pierwszy program w GLUT");

	SetupRenderingContext();

	// Display b�dzie funkcj� zwrotn� (callback function) wy�wietlaj�c� obraz na ekranie
	glutDisplayFunc(Display);

	//Ta funkcja uruchamia szkielet biblioteki GLUT. Po zdefiniowaniu funkcji zwrotnej obs�uguj�cej rysowanie na ekranie i innych funkcji (powiemy o nich w dalszej cz�ci) uruchamiany jest mechanizm biblioteki. 
	//Powr�t z funkcji glutMainLoop nast�puje dopiero przy zako�czeniu pracy programu, dlatego wystarczy wywo�a� j� tylko raz. Funkcja ta przetwarza wszystkie komunikaty systemu operacyjnego, naci�ni�cia klawiszy i inne, do czasu zako�czenia pracy programu.

	glutMainLoop();

	return 0;
}

