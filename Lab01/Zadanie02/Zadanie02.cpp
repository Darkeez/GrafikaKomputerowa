#include "stdafx.h"
#include <GL\freeglut.h>

/* Program 2. Narysowaæ w oknie programu Program1 wielok¹t. 
Dodatkowo uzyskaæ mo¿liwoœæ zmiany po³o¿enia i rozmiaru okna, tak ¿eby kod renderuj¹cy odpowiednio reagowa³ na te zmiany.
*/

//Otrzymany wariant: 6cio kat


void Display()
{
	/*Funkcja glClear czyœci zawartoœæ okreœlonego bufora lub kombinacji buforów. 
	Bufor jest obszarem w pamiêci przechowuj¹cym informacjê o obrazie. Sk³adowe czerwona, zielona i niebieska, 
	tworz¹ce rysunek, zazwyczaj opisywane s¹ terminem bufora koloru (ang. color buffer) lub bufora pikseli (ang. pixel buffer).
	*/
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Sposób rysowania obiektów ustala siê za pomoc¹ funkcji glPolygonMode 
	//Pierwszy parametr ustala która czêœæ obiektu ma byæ rysowana w sposób okreœlony za pomoc¹ drugiego parametru
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //GL_FILL rysowanie jako wype³nienie
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

	//Wachlarz 6ciu trójk¹tów, rysowanych liniami (szablon)
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //GL_LINE rysowanie jako linia
	glColor3f(0.0f, 0.0f, 0.0f);
	//Wachlarz 6ciu trójk¹tów rysowanych krawedziami
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

// Wywo³ywana przez bibliotek GLUT w przypadku zmiany rozmiaru okna
void onResize(int w, int h)
{
	if (h == 0)
		h = 1;
	float aspect = (float)w / (float)h;
	// Ustawienie wielkoœci widoku na równ¹ wielkoœci okna     
	glViewport(0, 0, w, h);
	// Ustalenie uk³adu wspó³rzêdnych 
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// Wyznaczenie przestrzeni ograniczaj¹cej (lewy, prawy, dolny, górny, bliski, odleg³y)
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
	//Funkcja ta ustala kolor stosowany do czyszczenia zawartoœci okna.
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Program1");

	//Wywo³anie funkcji która ustala stan renderowania
	SetupRenderingContext();
	//Rejstruj¹ca funkcja zwrotna wywo³ywan¹ przez bibliotekê przy ka¿dej zmianie rozmiarów okna.
	glutReshapeFunc(onResize);
	/*
	W tej linii ustalamy, ¿e zdefiniowana wczeœniej funkcja Display bêdzie funkcj¹ zwrotn¹ (callback function) wyœwietlaj¹c¹ obraz na ekranie.
	Oznacza to, ¿e biblioteka GLUT bêdzie wywo³ywaæ wskazan¹ tu funkcjê za ka¿dym razem, gdy okno bêdzie wymaga³o przerysowywania.
	Takie wywo³anie nast¹pi przy pierwszym wyœwietleniu okna, a tak¿e przy zmianach jego rozmiaru albo ods³oniêciu.
	W tym w³aœnie miejscu umieszczamy wywo³ania funkcji renderuj¹cych biblioteki OpenGL.
	*/
	glutDisplayFunc(Display);

	glutMainLoop();

	return 0;
}

