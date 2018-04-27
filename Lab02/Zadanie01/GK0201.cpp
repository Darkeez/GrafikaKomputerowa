#include "stdafx.h"
#include <GL\freeglut.h>
#include <cmath>

/*
Program 1. Stworzyæ w œrodowisku trójwymiarowym korkoci¹g wokó³ osi {x | y | z} zawieraj¹cy 6 obrotów.  
Punkty s¹ stopniowo powiêkszane od najmniejszej mo¿liwej wartoœci, do najwiêkszej.  
W funkcji SetupRC ustaliæ aktualny kolor rysuj¹cy na {zielony | niebieski | br¹zowy | … }.
*/



void RysujKorkociag(int iloscobrotow);
#define GL_PI 3.1415f
//Ustalenie wielkosci obrotu
float wartX = 0.0f, wartY = 0.0f;
//Zdefiniowanie tablicy kolorów rysujacych korkociag tak aby mo¿na by³o zmieniaæ ich wartoœci
float color[3] = { 0.0f, 0.0f, 0.0f };

void Display()
{
	// Wyczyszczenie okna aktualnym kolorem czyszczcym i bufora g³êbi
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// ustawienie stosu macierzy rzutowania
	//Wszystkie przysz³e przekszta³cenia bêd¹ dotyczy³y naszych modeli, czyli tego, co narysujemy
	glMatrixMode(GL_MODELVIEW);
	//s³u¿y do ponownego ustawienia (resetu) uk³adu wspó³rzêdnych, zanim wykonane zostan¹ jakiekolwiek manipulacje na macierzach.
	glLoadIdentity(); 

	glRotatef(wartX, 1.0f, 0.0f, 0.0f);
	glRotatef(wartY, 0.0f, 1.0f, 0.0f);

	//Sposób rysowania obiektów ustala siê za pomoc¹ funkcji glPolygonMode 
	//Pierwszy parametr ustala która czêœæ obiektu ma byæ rysowana w sposób okreœlony za pomoc¹ drugiego parametru
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	//Aktualny kolor rysuj¹cy
	glColor3fv(color);

	//Wywolanie funkcji rysujacej korkociag
	RysujKorkociag(6);
	// Wys³anie poleceñ do wykonania i zamiana buforów
	glutSwapBuffers();
}

void onResize(int w, int h)
{
	if (h == 0)
		h = 1;

	float aspect = (float)w / (float)h;

	// Ustalenie wielkoœci widoku zgodnego z rozmiarami okna
	glViewport(0, 0, w, h);
	// Ponowne ustawienie stosu macierzy rzutowania
	glMatrixMode(GL_PROJECTION);
	/*
	s³u¿y do ponownego ustawienia (resetu) uk³adu wspó³rzêdnych, zanim wykonane zostan¹  jakiekolwiek
	manipulacje na macierzach. Bez ponownego ustawienia uk³adu wspó³rzêdnych przed ka¿dym wywo³aniem funkcji
	glOrtho ka¿de kolejne wywo³anie powodowa³oby coraz wiêksze zniekszta³cenia planowanej przestrzeni ograniczaj¹cej
	*/

	glLoadIdentity();

	// Wyznaczenie przestrzeni ograniczaj¹cej (lewy, prawy, dolny, górny, bliski, odleg³y) 
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
	// Ponowne ustawienie stosu macierzy rzutowania
	//Wszystkie przysz³e przekszta³cenia bêd¹ dotyczy³y naszych modeli, czyli tego, co narysujemy
	glMatrixMode(GL_MODELVIEW);
	//s³u¿y do ponownego ustawienia (resetu) uk³adu wspó³rzêdnych, zanim wykonane zostan¹ jakiekolwiek manipulacje na macierzach
	glLoadIdentity();
}

void SetupRenderingContext()
{
	//Funkcja ta ustala kolor stosowany do czyszczenia zawartoci okna.
	glClearColor(1.0f, 1.0f,1.0f, 1.0f);

}

void onKeyDown(unsigned char key, int x, int y)
{
	if (key == GLUT_KEY_UP)
		wartX += 5.0f;

	if (key == GLUT_KEY_DOWN)
		wartX -= 5.0f;

	if (key == GLUT_KEY_LEFT)
		wartY -= 5.0f;

	if (key == GLUT_KEY_RIGHT)
		wartY += 5.0f;

	//S³u¿¹ one do niezale¿nego od pêtli wyœwietlenia zawartoœci okna. Dzia³a na aktywne okno
	// Odswiezenie zawartosci okna
	glutPostRedisplay();
}

void Menu(int value)
{
	switch (value)
	{
	case 1:
		color[0] = 1.0f;
		color[1] = 0.0f;
		color[2] = 0.0f;
		break;
	case 2:
		color[0] = 0.0f;
		color[1] = 1.0f;
		color[2] = 0.0f;
		break;
	case 3:
		color[0] = 0.0f;
		color[1] = 0.0f;
		color[2] = 1.0f;
		break;
	case 4:
		color[0] = 0.0f;
		color[1] = 0.0f;
		color[2] = 0.0f;
		break;
	}
	//S³u¿¹ one do niezale¿nego od pêtli wyœwietlenia zawartoœci okna. Dzia³a na aktywne okno
	// Odœwie¿enie zawartoœci okna
	glutPostRedisplay();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	//Wszystkie polecenia dzia³aj¹ na buforze niewidocznym.
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutCreateWindow("GK02 Cw01");

	//W tej funkcji wykonujemy wszystkie inicjalizacje biblioteki OpenGL, jakie musz by zakoczone przed rozpoczciem renderowania.
	SetupRenderingContext();

	//GLUT umo¿liwia utworzenie menu tekstowego typu pop-up, czyli takiego, które zostanie ukazane po wciœniêciu klawisza myszki.
	glutCreateMenu(Menu);
	//Dodanie pozycji do menu
	glutAddMenuEntry("Kolor czerwony.", 1);
	glutAddMenuEntry("Kolor zielony.", 2);
	glutAddMenuEntry("Kolor niebieski.", 3);
	glutAddMenuEntry("Kolor czarny.", 4);
	//Do ustalenia klawisza myszki po wciœniêciu którego uruchomi siê menu s³u¿y funkcja
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	//Ustala jaka funkcjê zostanie wywo³ana po wciœniêciu klawisza
	glutKeyboardFunc(onKeyDown);
	//rejestruj¹ca funkcja zwrotna wywo³ywana przez bibliotek przy ka¿dej zmianie rozmiarów okna.
	glutReshapeFunc(onResize);
    //zdefiniowana wczeœniej funkcja bêdzie funkcja zwrotna {callback function) wyœwietlaj¹ca obraz na ekranie.
	glutDisplayFunc(Display);
	/*
	Ta funkcja uruchamia szkielet biblioteki GLUT. Po zdefiniowaniu funkcji zwrotnej obs³uguj¹cej rysowanie na ekranie i
	innych funkcji uruchamiany jest mechanizm biblioteki. Powrót z funkcji
	glutMainLoop nastêpuje dopiero przy zakoczeniu pracy programu, dlatego wystarczy wywo³aæ j¹ tylko raz. Funkcja ta
	przetwarza wszystkie komunikaty systemu operacyjnego, naciœniêcia klawiszy i inne, do czasu zakoñczenia pracy
	programu.
	*/
	glutMainLoop();

	return 0;
}

void RysujKorkociag(int iloscObrotow)
{
	GLfloat z = 0.0f;
	GLfloat x, y;
	GLfloat pointSize = 1.0f;

	for (float i = 0; i < (2 * GL_PI) * iloscObrotow; i += 0.3f)
	{

		x = 10 * sin(i);
		y = 10 * cos(i);
		z += 0.3;

		//powiekszanie kazdego punktu o 0.01 pixela
		glPointSize(pointSize += 0.01);
		//Obiektami podstawowymi bêd¹ punkty
		glBegin(GL_POINTS);
		//Wpisanie wspolrzednych otrzymanych w petli
		glVertex3f(x, y, z);
		// Koniec rysowania punktów
		glEnd();
	}

}