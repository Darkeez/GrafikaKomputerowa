#include "stdafx.h"
#include <GL\freeglut.h>

/*
Program 3. Narysowaæ piramidê zbudowan¹ z trójk¹tów z wielok¹tem jako podstawa. 
Na ka¿dy z boków, jak równie¿ na podstawê, nak³adaæ teksturê z obrazem kamienia.
Mo¿na obracaæ piramidê , naciskaj¹c klawisze ze strza³kami.
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

// Wartoœci i wspó³rzêdne œwiat³a
GLfloat whiteLight[4] = { 0.05f, 0.05f, 0.05f, 1.0f };
GLfloat sourceLight[4] = { 0.25f, 0.25f, 0.25f, 1.0f };
GLfloat lightPos[4] = { -10.f, 5.0f, 5.0f, 1.0f };


void Display()
{
	// Wyczyszczenie okna aktualnym kolorem czyszcz¹cym i bufora g³êbi
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Ponowne ustawienie stosu macierzy rzutowania
	//Wszystkie przysz³e przekszta³cenia bêd¹ dotyczy³y naszych modeli, czyli tego, co narysujemy
	glMatrixMode(GL_MODELVIEW);
	//s³u¿y do ponownego ustawienia (resetu) uk³adu wspó³rzêdnych, zanim wykonane zostan¹ jakiekolwiek manipulacje na macierzach.
	glLoadIdentity();
	//Obrót realizowany jest w kierunku przeciwnym do ruchu wskazówek zegara w kierunku prostej wyznaczonej przez wektor [x, y, z] zaczepionym w pocz¹tku uk³adu wspó³rzêdnych.
	glRotatef(rotX, 1.0f, 0.0f, 0.0f);
	//Obrót realizowany jest w kierunku przeciwnym do ruchu wskazówek zegara w kierunku prostej wyznaczonej przez wektor [x, y, z] zaczepionym w pocz¹tku uk³adu wspó³rzêdnych.
	glRotatef(rotY, 0.0f, 1.0f, 0.0f);
	//Sposób rysowania obiektów ustala siê za pomoc¹ funkcji glPolygonMode 
	//Pierwszy parametr ustala która czêœæ obiektu ma byæ rysowana w sposób okreœlony za pomoc¹ drugiego parametru
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	//Aktualny kolor rysuj¹cy
	glColor3fv(color);
	//Wywolanie funkcji rysujacej piramide
	RysujPiramide();
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
	// Ponowne ustawienie stosu macierzy rzutowania
	glMatrixMode(GL_PROJECTION);
	//s³u¿y do ponownego ustawienia (resetu) uk³adu wspó³rzêdnych, zanim wykonane zostan¹ jakiekolwiek manipulacje na macierzach.
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
	// Ponowne ustawienie stosu macierzy rzutowania
	//Wszystkie przysz³e przekszta³cenia bêd¹ dotyczy³y naszych modeli, czyli tego, co narysujemy
	glMatrixMode(GL_MODELVIEW);
	//s³u¿y do ponownego ustawienia (resetu) uk³adu wspó³rzêdnych, zanim wykonane zostan¹ jakiekolwiek manipulacje na macierzach.
	glLoadIdentity();
}

void SetupRenderingContext()
{
	//Funkcja ta ustala kolor stosowany do czyszczenia zawartoœci okna.
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	// Model cieniowania kolorów – p³aski. biblioteka OpenGL bêdzie wype³nia³a wielok¹ty jednolitym kolorem
	glShadeModel(GL_FLAT);
	// Usuwanie ukrytych powierzchni
	glEnable(GL_DEPTH_TEST);
	// Mechanizm odwzorowywania tekstur
	glEnable(GL_TEXTURE_2D);
	// W³¹czenie œledzenia kolorów
	glEnable(GL_COLOR_MATERIAL);
	//W przypadku oœwietlenia, poni¿¹ instrukcja mo¿na w³¹czyæ odpowiedni stan
	glEnable(GL_LIGHTING);
	// Konfiguracja i W³¹czenie œwiat³a numer 0
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_AMBIENT, sourceLight); //glLight — Ustawia parametry Ÿród³a œwiat³a
	glLightfv(GL_LIGHT0, GL_DIFFUSE, sourceLight);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

	// W³aœciwoœci oœwietlenia otoczenia i rozproszenia bêdzie œledziæ wartoœci podawane funkcji glColor
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
	glutCreateWindow("GK02 Cw03");

	SetupRenderingContext();

	glutSpecialFunc(onKeyDown);
	//rejestruj¹ca funkcja zwrotna wywo³ywana przez bibliotek przy ka¿dej zmianie rozmiarów okna.
	glutReshapeFunc(onResize);
	//zdefiniowana wczeœniej funkcja bêdzie funkcja zwrotna {callback function) wyœwietlaj¹ca obraz na ekranie.
	glutDisplayFunc(Display);
	/*
	Ta funkcja uruchamia szkielet biblioteki GLUT. Po zdefiniowaniu funkcji zwrotnej obs³uguj¹cej rysowanie na ekranie i
	innych funkcji uruchamiany jest mechanizm biblioteki. Powrót z funkcji
	glutMainLoop nastêpuje dopiero przy zakoñczeniu pracy programu, dlatego wystarczy wywo³aæ j¹ tylko raz. Funkcja ta
	przetwarza wszystkie komunikaty systemu operacyjnego, naciœniêcia klawiszy i inne, do czasu zakoñczenia pracy
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

	// Rozpoczêcie rysowania trójk¹tów
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