#include "stdafx.h"
#include <GL\freeglut.h>

/*Program 1. Opracowaæ program który tworzy w GLUT standardowe okno interfejsu GUI
z nag³ówkiem "Mój pierwszy program w GLUT"  i pustym br¹zowym t³em.
*/


// Funkcja wywo³ywana w celu narysowania sceny
void Display()
{
	// Wyczyszczenie okna aktualnym kolorem czyszcz¹cym
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Wys³anie poleceñ do wykonania
	glutSwapBuffers();
}

void SetupRenderingContext() //ustawienie stanu renderowania
{
	//ustalenie br¹zowego koloru czyszcz¹cego
	glClearColor(0.96f, 0.64f, 0.38f, 1.0f); //kolor sandybrown
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Mój pierwszy program w GLUT");

	SetupRenderingContext();

	// Display bêdzie funkcj¹ zwrotn¹ (callback function) wyœwietlaj¹c¹ obraz na ekranie
	glutDisplayFunc(Display);

	//Ta funkcja uruchamia szkielet biblioteki GLUT. Po zdefiniowaniu funkcji zwrotnej obs³uguj¹cej rysowanie na ekranie i innych funkcji (powiemy o nich w dalszej czêœci) uruchamiany jest mechanizm biblioteki. 
	//Powrót z funkcji glutMainLoop nastêpuje dopiero przy zakoñczeniu pracy programu, dlatego wystarczy wywo³aæ j¹ tylko raz. Funkcja ta przetwarza wszystkie komunikaty systemu operacyjnego, naciœniêcia klawiszy i inne, do czasu zakoñczenia pracy programu.

	glutMainLoop();

	return 0;
}

