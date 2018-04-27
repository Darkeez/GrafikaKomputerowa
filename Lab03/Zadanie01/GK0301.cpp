#include "stdafx.h"
#include <GL\glut.h>
#include <cmath>
#include <iostream>

/*
Program 1. Opracowaæ program który tworzy trzy tekstury jednowymiarowe. Ka¿da z nich ma odmienny format danych ale wszystkie 
zawieraj¹ teksele reprezentuj¹ce odcienie szaroœci. Poza tym tekstury ró¿ni¹ siê szerokoœci¹. 
Pierwsza ma 2^{n+2} tekseli, druga 2^{n+1}, a trzecia 2^n.
Dziêki temu program umo¿liwia porównanie jak wp³ywa szczegó³owoœæ tekstury na jakoœæ 
generowanego obrazu i jaki praktyczny efekt daj¹ metody filtracji tekstur.
Opracowaæ mo¿liwoœæ ustalania dla u¿ytkownika filtra pomniejszaj¹cego oraz powiêkszaj¹cego GL_NEAREST czyli GL_LINEAR
Zwróciæ uwagê na widoczne wyraŸnie ró¿nice pomiêdzy odcieniami szaroœci.

*/



//n = 6
/*
N1 = 2^(N+2) --> N1 = 2^8 = 256
N2 = 2^(N+1) --> N2 = 2^7 = 128
N3 = 2^N     --> N3 = 2^6 = 64
*/

#define N1 256
#define N2 128
#define N3 64

GLuint textures[3];

// Sta³e do obs³ugi menu podrêcznego
enum {
	SWITCH_TO_NEAREST,
	SWITCH_TO_LINEAR
};


void Generate1DTextures()
{
	unsigned char tex1[N1];
	unsigned char tex2[N2];
	unsigned char tex3[N3];

	char step = 256 / N1;
	for (int i = 0; i < N1; i++)
		tex1[i] = step * i;

	step = 256 / N2;
	for (int i = 0; i < N2; i++)
		tex2[i] = step * i;

	step = 256 / N3;
	for (int i = 0; i < N3; i++)
		tex3[i] = step * i;

	// tryb upakowania bajtów danych tekstury
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	// utworzenie identyfikatora tekstury
	glGenTextures(3, textures);
	// w³¹czenie teksturowania jednowymiarowego
	glBindTexture(GL_TEXTURE_1D, textures[0]);
	// definiowanie tekstury
	glTexImage1D(GL_TEXTURE_1D, 0, GL_LUMINANCE, N1, 0, GL_LUMINANCE, GL_UNSIGNED_BYTE, tex1);
	// filtr pomniejszaj¹cy
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	// filtr powiêkszaj¹cy
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//metoda zawijania tekstury w kierunku wspó³rzêdnej S
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	// w³¹czenie teksturowania jednowymiarowego
	glBindTexture(GL_TEXTURE_1D, textures[1]);
	// definiowanie tekstury
	glTexImage1D(GL_TEXTURE_1D, 0, GL_LUMINANCE, N2, 0, GL_LUMINANCE, GL_UNSIGNED_BYTE, tex2);
	// filtr pomniejszaj¹cy
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	// filtr powiêkszaj¹cy
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//metoda zawijania tekstury w kierunku wspó³rzêdnej S
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	// w³¹czenie teksturowania jednowymiarowego
	glBindTexture(GL_TEXTURE_1D, textures[2]);
	// definiowanie tekstury
	glTexImage1D(GL_TEXTURE_1D, 0, GL_LUMINANCE, N3, 0, GL_LUMINANCE, GL_UNSIGNED_BYTE, tex3);
	// filtr pomniejszaj¹cy
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	// filtr powiêkszaj¹cy
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//metoda zawijania tekstury w kierunku wspó³rzêdnej S
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, GL_CLAMP);
}

void Init()
{
	// kolor t³a - zawartoœæ bufora koloru
	glClearColor(0.2f, 0.4f, 0.7f, 1.0f);
	// w³¹czenie teksturowania jednowymiarowego
	glEnable(GL_TEXTURE_1D);
}

void Display()
{

	// Wyczyszczenie okna aktualnym kolorem czyszcz¹cym i bufora g³êbi
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// w³¹czenie teksturowania jednowymiarowego
	glBindTexture(GL_TEXTURE_1D, textures[0]);
	// Rozpoczêcie rysowania kwadratow
	glBegin(GL_QUADS);
	glTexCoord1f(0.0f);
	glVertex2f(-1.0f, 0.4f);
	glTexCoord1f(0.0f);
	glVertex2f(-1.0f, 0.9f);
	glTexCoord1f(1.0f);
	glVertex2f(1.0f, 0.9f);
	glTexCoord1f(1.0f);
	glVertex2f(1.0f, 0.4f);
	glEnd();

	// w³¹czenie teksturowania jednowymiarowego
	glBindTexture(GL_TEXTURE_1D, textures[1]);
	// Rozpoczêcie rysowania kwadratow
	glBegin(GL_QUADS);
	glTexCoord1f(0.0f);
	glVertex2f(-1.0f, -0.10f);
	glTexCoord1f(0.0f);
	glVertex2f(-1.0f, 0.25f);
	glTexCoord1f(1.0f);
	glVertex2f(1.0f, 0.25f);
	glTexCoord1f(1.0f);
	glVertex2f(1.0f, -0.10f);
	glEnd();

	// w³¹czenie teksturowania jednowymiarowego
	glBindTexture(GL_TEXTURE_1D, textures[2]);
	// Rozpoczêcie rysowania kwadratow
	glBegin(GL_QUADS);
	glTexCoord1f(0.0f);
	glVertex2f(-1.0f, -0.8f);
	glTexCoord1f(0.0f);
	glVertex2f(-1.0f, -0.4f);
	glTexCoord1f(1.0f);
	glVertex2f(1.0f, -0.4f);
	glTexCoord1f(1.0f);
	glVertex2f(1.0f, -0.8f);
	glEnd();

	glutSwapBuffers();
	// Wys³anie poleceñ do wykonania i zamiana buforów
}

void Menu(int value)
{
	switch (value)
	{
	case SWITCH_TO_NEAREST:
		// w³¹czenie teksturowania jednowymiarowego
		glBindTexture(GL_TEXTURE_1D, textures[0]);
		//GL_NEAREST - Bez filtrowania , bez minimap
		glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glBindTexture(GL_TEXTURE_1D, textures[1]);
		//GL_NEAREST - Bez filtrowania , bez minimap
		glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glBindTexture(GL_TEXTURE_1D, textures[2]);
		//GL_NEAREST - Bez filtrowania , bez minimap
		glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		break;

	case SWITCH_TO_LINEAR:
		// w³¹czenie teksturowania jednowymiarowego
		glBindTexture(GL_TEXTURE_1D, textures[0]);
		//GL_LINEAR - Filtrowanie , bez minimap
		glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		// w³¹czenie teksturowania jednowymiarowego
		glBindTexture(GL_TEXTURE_1D, textures[1]);
		//GL_LINEAR - Filtrowanie , bez minimap
		glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		// w³¹czenie teksturowania jednowymiarowego
		glBindTexture(GL_TEXTURE_1D, textures[2]);
		//GL_LINEAR - Filtrowanie , bez minimap
		glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
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
	glutCreateWindow("GK03 Cw01");

	Init();

	Generate1DTextures();

	glutCreateMenu(Menu);
	glutAddMenuEntry("Opcja GL_LINEAR", SWITCH_TO_LINEAR);
	glutAddMenuEntry("Opcja GL_NEAREST", SWITCH_TO_NEAREST);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutDisplayFunc(Display);

	glutMainLoop();

	return 0;
}
