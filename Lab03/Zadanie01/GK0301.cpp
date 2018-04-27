#include "stdafx.h"
#include <GL\glut.h>
#include <cmath>
#include <iostream>

/*
Program 1. Opracowa� program kt�ry tworzy trzy tekstury jednowymiarowe. Ka�da z nich ma odmienny format danych ale wszystkie 
zawieraj� teksele reprezentuj�ce odcienie szaro�ci. Poza tym tekstury r�ni� si� szeroko�ci�. 
Pierwsza ma 2^{n+2} tekseli, druga 2^{n+1}, a trzecia 2^n.
Dzi�ki temu program umo�liwia por�wnanie jak wp�ywa szczeg�owo�� tekstury na jako�� 
generowanego obrazu i jaki praktyczny efekt daj� metody filtracji tekstur.
Opracowa� mo�liwo�� ustalania dla u�ytkownika filtra pomniejszaj�cego oraz powi�kszaj�cego GL_NEAREST czyli GL_LINEAR
Zwr�ci� uwag� na widoczne wyra�nie r�nice pomi�dzy odcieniami szaro�ci.

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

// Sta�e do obs�ugi menu podr�cznego
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

	// tryb upakowania bajt�w danych tekstury
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	// utworzenie identyfikatora tekstury
	glGenTextures(3, textures);
	// w��czenie teksturowania jednowymiarowego
	glBindTexture(GL_TEXTURE_1D, textures[0]);
	// definiowanie tekstury
	glTexImage1D(GL_TEXTURE_1D, 0, GL_LUMINANCE, N1, 0, GL_LUMINANCE, GL_UNSIGNED_BYTE, tex1);
	// filtr pomniejszaj�cy
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	// filtr powi�kszaj�cy
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//metoda zawijania tekstury w kierunku wsp�rz�dnej S
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	// w��czenie teksturowania jednowymiarowego
	glBindTexture(GL_TEXTURE_1D, textures[1]);
	// definiowanie tekstury
	glTexImage1D(GL_TEXTURE_1D, 0, GL_LUMINANCE, N2, 0, GL_LUMINANCE, GL_UNSIGNED_BYTE, tex2);
	// filtr pomniejszaj�cy
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	// filtr powi�kszaj�cy
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//metoda zawijania tekstury w kierunku wsp�rz�dnej S
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	// w��czenie teksturowania jednowymiarowego
	glBindTexture(GL_TEXTURE_1D, textures[2]);
	// definiowanie tekstury
	glTexImage1D(GL_TEXTURE_1D, 0, GL_LUMINANCE, N3, 0, GL_LUMINANCE, GL_UNSIGNED_BYTE, tex3);
	// filtr pomniejszaj�cy
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	// filtr powi�kszaj�cy
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//metoda zawijania tekstury w kierunku wsp�rz�dnej S
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, GL_CLAMP);
}

void Init()
{
	// kolor t�a - zawarto�� bufora koloru
	glClearColor(0.2f, 0.4f, 0.7f, 1.0f);
	// w��czenie teksturowania jednowymiarowego
	glEnable(GL_TEXTURE_1D);
}

void Display()
{

	// Wyczyszczenie okna aktualnym kolorem czyszcz�cym i bufora g��bi
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// w��czenie teksturowania jednowymiarowego
	glBindTexture(GL_TEXTURE_1D, textures[0]);
	// Rozpocz�cie rysowania kwadratow
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

	// w��czenie teksturowania jednowymiarowego
	glBindTexture(GL_TEXTURE_1D, textures[1]);
	// Rozpocz�cie rysowania kwadratow
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

	// w��czenie teksturowania jednowymiarowego
	glBindTexture(GL_TEXTURE_1D, textures[2]);
	// Rozpocz�cie rysowania kwadratow
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
	// Wys�anie polece� do wykonania i zamiana bufor�w
}

void Menu(int value)
{
	switch (value)
	{
	case SWITCH_TO_NEAREST:
		// w��czenie teksturowania jednowymiarowego
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
		// w��czenie teksturowania jednowymiarowego
		glBindTexture(GL_TEXTURE_1D, textures[0]);
		//GL_LINEAR - Filtrowanie , bez minimap
		glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		// w��czenie teksturowania jednowymiarowego
		glBindTexture(GL_TEXTURE_1D, textures[1]);
		//GL_LINEAR - Filtrowanie , bez minimap
		glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		// w��czenie teksturowania jednowymiarowego
		glBindTexture(GL_TEXTURE_1D, textures[2]);
		//GL_LINEAR - Filtrowanie , bez minimap
		glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		break;
	}
	//S�u�� one do niezale�nego od p�tli wy�wietlenia zawarto�ci okna. Dzia�a na aktywne okno
	// Od�wie�enie zawarto�ci okna
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
