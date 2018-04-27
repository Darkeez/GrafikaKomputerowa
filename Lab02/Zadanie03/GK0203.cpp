#include "stdafx.h"
#include <GL\freeglut.h>

/*
Program 3. Narysowa� piramid� zbudowan� z tr�jk�t�w z wielok�tem jako podstawa. 
Na ka�dy z bok�w, jak r�wnie� na podstaw�, nak�ada� tekstur� z obrazem kamienia.
Mo�na obraca� piramid� , naciskaj�c klawisze ze strza�kami.
*/

//Struktura wektoru scharakteryzowana przez wspolrzedne xyz
struct CVector {
	GLfloat x;
	GLfloat y;
	GLfloat z;
};

GLuint texture;

void GetNormal(CVector V1, CVector V2, CVector V3, CVector &N);

//Widocznosc funkcji rysujpiramide
void RysujPiramide();

//Ustalenie wielkosci obrotu
float rotX = 0.0f, rotY = 0.0f;
float color[3] = { 1.0f, 1.0f, 1.0f };

// Warto�ci i wsp�rz�dne �wiat�a
GLfloat whiteLight[4] = { 0.05f, 0.05f, 0.05f, 1.0f };
GLfloat sourceLight[4] = { 0.25f, 0.25f, 0.25f, 1.0f };
GLfloat lightPos[4] = { -10.f, 5.0f, 5.0f, 1.0f };


void Display()
{
	// Wyczyszczenie okna aktualnym kolorem czyszcz�cym i bufora g��bi
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Ponowne ustawienie stosu macierzy rzutowania
	//Wszystkie przysz�e przekszta�cenia b�d� dotyczy�y naszych modeli, czyli tego, co narysujemy
	glMatrixMode(GL_MODELVIEW);
	//s�u�y do ponownego ustawienia (resetu) uk�adu wsp�rz�dnych, zanim wykonane zostan� jakiekolwiek manipulacje na macierzach.
	glLoadIdentity();
	//Obr�t realizowany jest w kierunku przeciwnym do ruchu wskaz�wek zegara w kierunku prostej wyznaczonej przez wektor [x, y, z] zaczepionym w pocz�tku uk�adu wsp�rz�dnych.
	glRotatef(rotX, 1.0f, 0.0f, 0.0f);
	//Obr�t realizowany jest w kierunku przeciwnym do ruchu wskaz�wek zegara w kierunku prostej wyznaczonej przez wektor [x, y, z] zaczepionym w pocz�tku uk�adu wsp�rz�dnych.
	glRotatef(rotY, 0.0f, 1.0f, 0.0f);
	//Spos�b rysowania obiekt�w ustala si� za pomoc� funkcji glPolygonMode 
	//Pierwszy parametr ustala kt�ra cz�� obiektu ma by� rysowana w spos�b okre�lony za pomoc� drugiego parametru
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	//Aktualny kolor rysuj�cy
	glColor3fv(color);
	//Wywolanie funkcji rysujacej piramide
	RysujPiramide();
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
	// Ponowne ustawienie stosu macierzy rzutowania
	glMatrixMode(GL_PROJECTION);
	//s�u�y do ponownego ustawienia (resetu) uk�adu wsp�rz�dnych, zanim wykonane zostan� jakiekolwiek manipulacje na macierzach.
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
	// Ponowne ustawienie stosu macierzy rzutowania
	//Wszystkie przysz�e przekszta�cenia b�d� dotyczy�y naszych modeli, czyli tego, co narysujemy
	glMatrixMode(GL_MODELVIEW);
	//s�u�y do ponownego ustawienia (resetu) uk�adu wsp�rz�dnych, zanim wykonane zostan� jakiekolwiek manipulacje na macierzach.
	glLoadIdentity();
}

void SetupRenderingContext()
{
	//Funkcja ta ustala kolor stosowany do czyszczenia zawarto�ci okna.
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	// Model cieniowania kolor�w � p�aski. biblioteka OpenGL b�dzie wype�nia�a wielok�ty jednolitym kolorem
	glShadeModel(GL_FLAT);
	// Usuwanie ukrytych powierzchni
	glEnable(GL_DEPTH_TEST);
	// Mechanizm odwzorowywania tekstur
	glEnable(GL_TEXTURE_2D);
	// W��czenie �ledzenia kolor�w
	glEnable(GL_COLOR_MATERIAL);
	//W przypadku o�wietlenia, poni�� instrukcja mo�na w��czy� odpowiedni stan
	glEnable(GL_LIGHTING);
	// Konfiguracja i W��czenie �wiat�a numer 0
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_AMBIENT, sourceLight); //glLight � Ustawia parametry �r�d�a �wiat�a
	glLightfv(GL_LIGHT0, GL_DIFFUSE, sourceLight);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

	// W�a�ciwo�ci o�wietlenia otoczenia i rozproszenia b�dzie �ledzi� warto�ci podawane funkcji glColor
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	char pixels[256 * 256];
	for (int x = 0; x < 256; x++)
		for (int y = 0; y < 256; y++)
			pixels[x * 256 + y] = rand() / 256;

	//glGenTextures returns n texture names in textures
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE, 256, 256, 0, GL_LUMINANCE, GL_UNSIGNED_BYTE, pixels);
}

//Zamiana na obsluge strzalek z klawiatury poprzez zmiane na int
void onKeyDown(int key, int x, int y)
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

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	//Wszystkie polecenia dzia�aj� na buforze niewidocznym.
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutCreateWindow("GK02 Cw03");

	SetupRenderingContext();

	glutSpecialFunc(onKeyDown);
	//rejestruj�ca funkcja zwrotna wywo�ywana przez bibliotek przy ka�dej zmianie rozmiar�w okna.
	glutReshapeFunc(onResize);
	//zdefiniowana wcze�niej funkcja b�dzie funkcja zwrotna {callback function) wy�wietlaj�ca obraz na ekranie.
	glutDisplayFunc(Display);
	/*
	Ta funkcja uruchamia szkielet biblioteki GLUT. Po zdefiniowaniu funkcji zwrotnej obs�uguj�cej rysowanie na ekranie i
	innych funkcji uruchamiany jest mechanizm biblioteki. Powr�t z funkcji
	glutMainLoop nast�puje dopiero przy zako�czeniu pracy programu, dlatego wystarczy wywo�a� j� tylko raz. Funkcja ta
	przetwarza wszystkie komunikaty systemu operacyjnego, naci�ni�cia klawiszy i inne, do czasu zako�czenia pracy
	programu.
	*/
	glutMainLoop();

	return 0;
}

void RysujPiramide()
{
	CVector vertices[5] = {
		{ 0.0f, 50.0f,  0.0f },
		{ -20.0f, 0.0f,  20.0f },
		{ -20.0f, 0.0f, -20.0f },
		{ 20.0f, 0.0f, -20.0f },
		{ 20.0f, 0.0f,  20.0f }
	};
	CVector normal;

	// Rozpocz�cie rysowania tr�jk�t�w
	glBegin(GL_TRIANGLES);
	//Podstawa
	glNormal3f(0.0f, -1.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3fv((GLfloat*)&vertices[2]);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3fv((GLfloat*)&vertices[1]);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3fv((GLfloat*)&vertices[4]);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3fv((GLfloat*)&vertices[2]);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3fv((GLfloat*)&vertices[4]);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3fv((GLfloat*)&vertices[3]);
	//Przednia sciana
	GetNormal(vertices[1], vertices[0], vertices[4], normal);
	glNormal3fv((GLfloat*)&normal);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3fv((GLfloat*)&vertices[1]);
	glTexCoord2f(0.5f, 1.0f);
	glVertex3fv((GLfloat*)&vertices[0]);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3fv((GLfloat*)&vertices[4]);
	//Tylna sciana
	GetNormal(vertices[3], vertices[0], vertices[2], normal);
	glNormal3fv((GLfloat*)&normal);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3fv((GLfloat*)&vertices[3]);
	glTexCoord2f(0.5f, 1.0f);
	glVertex3fv((GLfloat*)&vertices[0]);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3fv((GLfloat*)&vertices[2]);
	//Lewa sciana
	GetNormal(vertices[2], vertices[0], vertices[1], normal);
	glNormal3fv((GLfloat*)&normal);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3fv((GLfloat*)&vertices[2]);
	glTexCoord2f(0.5f, 1.0f);
	glVertex3fv((GLfloat*)&vertices[0]);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3fv((GLfloat*)&vertices[1]);
	//Prawa sciana
	GetNormal(vertices[4], vertices[0], vertices[3], normal);
	glNormal3fv((GLfloat*)&normal);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3fv((GLfloat*)&vertices[4]);
	glTexCoord2f(0.5f, 1.0f);
	glVertex3fv((GLfloat*)&vertices[0]);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3fv((GLfloat*)&vertices[3]);

	glEnd();
}

void GetNormal(CVector V1, CVector V2, CVector V3, CVector &N)
{
	V1.x = V1.x - V2.x;
	V1.y = V1.y - V2.y;
	V1.z = V1.z - V2.z;

	V2.x = V2.x - V3.x;
	V2.y = V2.y - V3.y;
	V2.z = V2.z - V3.z;

	N.x = V1.y * V2.z - V1.z * V2.y;
	N.y = V1.z * V2.x - V1.x * V2.z;
	N.z = V1.x * V2.y - V1.y * V2.x;
}