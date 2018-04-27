#include "stdafx.h"
#include <GL\freeglut.h>
#include <cmath>

/*
Program 1. Stworzy� w �rodowisku tr�jwymiarowym korkoci�g wok� osi {x | y | z} zawieraj�cy 6 obrot�w.  
Punkty s� stopniowo powi�kszane od najmniejszej mo�liwej warto�ci, do najwi�kszej.  
W funkcji SetupRC ustali� aktualny kolor rysuj�cy na {zielony | niebieski | br�zowy | � }.
*/



void RysujKorkociag(int iloscobrotow);
#define GL_PI 3.1415f
//Ustalenie wielkosci obrotu
float wartX = 0.0f, wartY = 0.0f;
//Zdefiniowanie tablicy kolor�w rysujacych korkociag tak aby mo�na by�o zmienia� ich warto�ci
float color[3] = { 0.0f, 0.0f, 0.0f };

void Display()
{
	// Wyczyszczenie okna aktualnym kolorem czyszczcym i bufora g��bi
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// ustawienie stosu macierzy rzutowania
	//Wszystkie przysz�e przekszta�cenia b�d� dotyczy�y naszych modeli, czyli tego, co narysujemy
	glMatrixMode(GL_MODELVIEW);
	//s�u�y do ponownego ustawienia (resetu) uk�adu wsp�rz�dnych, zanim wykonane zostan� jakiekolwiek manipulacje na macierzach.
	glLoadIdentity(); 

	glRotatef(wartX, 1.0f, 0.0f, 0.0f);
	glRotatef(wartY, 0.0f, 1.0f, 0.0f);

	//Spos�b rysowania obiekt�w ustala si� za pomoc� funkcji glPolygonMode 
	//Pierwszy parametr ustala kt�ra cz�� obiektu ma by� rysowana w spos�b okre�lony za pomoc� drugiego parametru
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	//Aktualny kolor rysuj�cy
	glColor3fv(color);

	//Wywolanie funkcji rysujacej korkociag
	RysujKorkociag(6);
	// Wys�anie polece� do wykonania i zamiana bufor�w
	glutSwapBuffers();
}

void onResize(int w, int h)
{
	if (h == 0)
		h = 1;

	float aspect = (float)w / (float)h;

	// Ustalenie wielko�ci widoku zgodnego z rozmiarami okna
	glViewport(0, 0, w, h);
	// Ponowne ustawienie stosu macierzy rzutowania
	glMatrixMode(GL_PROJECTION);
	/*
	s�u�y do ponownego ustawienia (resetu) uk�adu wsp�rz�dnych, zanim wykonane zostan�  jakiekolwiek
	manipulacje na macierzach. Bez ponownego ustawienia uk�adu wsp�rz�dnych przed ka�dym wywo�aniem funkcji
	glOrtho ka�de kolejne wywo�anie powodowa�oby coraz wi�ksze zniekszta�cenia planowanej przestrzeni ograniczaj�cej
	*/

	glLoadIdentity();

	// Wyznaczenie przestrzeni ograniczaj�cej (lewy, prawy, dolny, g�rny, bliski, odleg�y) 
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
	// Ponowne ustawienie stosu macierzy rzutowania
	//Wszystkie przysz�e przekszta�cenia b�d� dotyczy�y naszych modeli, czyli tego, co narysujemy
	glMatrixMode(GL_MODELVIEW);
	//s�u�y do ponownego ustawienia (resetu) uk�adu wsp�rz�dnych, zanim wykonane zostan� jakiekolwiek manipulacje na macierzach
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

	//S�u�� one do niezale�nego od p�tli wy�wietlenia zawarto�ci okna. Dzia�a na aktywne okno
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
	//S�u�� one do niezale�nego od p�tli wy�wietlenia zawarto�ci okna. Dzia�a na aktywne okno
	// Od�wie�enie zawarto�ci okna
	glutPostRedisplay();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	//Wszystkie polecenia dzia�aj� na buforze niewidocznym.
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutCreateWindow("GK02 Cw01");

	//W tej funkcji wykonujemy wszystkie inicjalizacje biblioteki OpenGL, jakie musz by zakoczone przed rozpoczciem renderowania.
	SetupRenderingContext();

	//GLUT umo�liwia utworzenie menu tekstowego typu pop-up, czyli takiego, kt�re zostanie ukazane po wci�ni�ciu klawisza myszki.
	glutCreateMenu(Menu);
	//Dodanie pozycji do menu
	glutAddMenuEntry("Kolor czerwony.", 1);
	glutAddMenuEntry("Kolor zielony.", 2);
	glutAddMenuEntry("Kolor niebieski.", 3);
	glutAddMenuEntry("Kolor czarny.", 4);
	//Do ustalenia klawisza myszki po wci�ni�ciu kt�rego uruchomi si� menu s�u�y funkcja
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	//Ustala jaka funkcj� zostanie wywo�ana po wci�ni�ciu klawisza
	glutKeyboardFunc(onKeyDown);
	//rejestruj�ca funkcja zwrotna wywo�ywana przez bibliotek przy ka�dej zmianie rozmiar�w okna.
	glutReshapeFunc(onResize);
    //zdefiniowana wcze�niej funkcja b�dzie funkcja zwrotna {callback function) wy�wietlaj�ca obraz na ekranie.
	glutDisplayFunc(Display);
	/*
	Ta funkcja uruchamia szkielet biblioteki GLUT. Po zdefiniowaniu funkcji zwrotnej obs�uguj�cej rysowanie na ekranie i
	innych funkcji uruchamiany jest mechanizm biblioteki. Powr�t z funkcji
	glutMainLoop nast�puje dopiero przy zakoczeniu pracy programu, dlatego wystarczy wywo�a� j� tylko raz. Funkcja ta
	przetwarza wszystkie komunikaty systemu operacyjnego, naci�ni�cia klawiszy i inne, do czasu zako�czenia pracy
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
		//Obiektami podstawowymi b�d� punkty
		glBegin(GL_POINTS);
		//Wpisanie wspolrzednych otrzymanych w petli
		glVertex3f(x, y, z);
		// Koniec rysowania punkt�w
		glEnd();
	}

}