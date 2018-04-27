#include "stdafx.h"
#include <GL\freeglut.h>

/*

Program 4. Opracowaæ program, w którym wielok¹t obraca siê wokó³ niektórej osi

Otrzymany wariant: 6cio k¹t
*/


float angle = 0.0f;

void Display()
{

	// Wyczyœæ ekran i bufor g³êbi 
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Wybor macierzy modeli
	glMatrixMode(GL_MODELVIEW);
	//Zresetuj ja Przy wywo³aniu glLoadIdentity() przmieszczasz siê na œrodek ekranu. Oœ X biegnie z lewej do prawej, Y z góry na dó³, a Z do ciebie.
	glLoadIdentity(); 
	//Obrót w OpenGL wykonuj¹ funkcje glRotated i glRotatef
	//Obrót realizowany jest w kierunku przeciwnym do ruchu wskazówek zegara w kierunku prostej wyznaczonej przez wektor [x, y, z] zaczepionym w pocz¹tku uk³adu wspó³rzêdnych
	glRotatef(angle, 0.0f, 0.0f, 1.0f);
	// Rysujemy siatkê metod¹ 'wypelnienia' 
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	//Pobranie aktualnego koloru rysuj¹cego
	glColor3f(1.0f, 0.0f, 0.0f);
	//Wachlarz 6ciu trójk¹tów wype³nionych czerwonym kolorem
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

	// Rysujemy siatkê metod¹ 'linii'
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//Pobranie aktualnego koloru rysuj¹cego
	glColor3f(0.0f, 0.0f, 0.0f);
	//Wachlarz 6ciu trójk¹tów obramowanych
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
	//Koñcowym elementem tworzenia sceny 3D jest zamiana buforów koloru
	glutSwapBuffers();
	// Ponowne rysowanie sceny z nowymi wspó³rzêdnymi
	glutPostRedisplay();
}

void onResize(int w, int h)
{
	if (h == 0)
		h = 1;

	float aspect = (float)w / (float)h;
	// Ustalenie wielkoœci widoku zgodnego z rozmiarami okna
	glViewport(0, 0, w, h);
	// Ustalenie uk³adu wspó³rzêdnych  
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//Zresetuj macierz Przy wywo³aniu glLoadIdentity() przmieszczasz siê na œrodek ekranu.
	// Wyznaczenie przestrzeni ograniczaj¹cej (lewy, prawy, dolny, górny, bliski, odleg³y)  
	if (w <= h)
	{
		glOrtho(-100.0f, 100.0, -100.0f / aspect, 100.0 / aspect, 1.0f, -1.0f);
	}
	else
	{
		glOrtho(-100.0 * aspect, 100.0 * aspect, -100.0f, 100.0, 1.0f, -1.0f);
	}
	//Wszystkie przysz³e przekszta³cenia bêd¹ dotyczy³y naszych modeli, czyli tego, co narysujemy
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//Zresetuj macierz Przy wywo³aniu glLoadIdentity() przmieszczasz siê na œrodek ekranu.

}

void SetupRenderingContext()
{
	//Funkcja ta ustala kolor stosowany do czyszczenia zawartoœci okna.
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutCreateWindow("GK01 Cw3");

	SetupRenderingContext();
	//Funkcja glutReshapeFunc rejestrujca funkcjê zwrotn¹ wywo³ywan¹ przez bibliotekê przy ka¿dej zmianie rozmiarów okna
	glutReshapeFunc(onResize);
	//Funkcja RenderScene bêdzie funkcj¹ zwrotn¹ (callback function) wyœwietlaj¹c¹ obraz na ekranie
	glutDisplayFunc(Display);
	//Wprwadzenie do petli
	glutMainLoop();

	return 0;
}

