#pragma warning(push)
#pragma warning(disable: 4244)
#pragma warning(disable: 4305) 
#pragma warning(disable: 4838) 
#pragma warning(disable: 4996)

#include <GL/glut.h>
#include "glext.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "colors.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "materials.h"
#include "Vectors.h"
// sta³e do menu podrêcznego

enum
{
	FULL_WINDOW,    // aspekt obrazu - ca³e okno
	ASPECT_1_1,     // aspekt obrazu 1:1
	EXIT,        // wyjœcie

	AMBIENT_LIGHT,
	DIRECT_LIGHT,
	NORMAL_VECTORS,

	NORMALS_SMOOTH,       // jeden wektor normalny na wierzcho³ek
	NORMALS_FLAT,         // jeden wektor normalny na œcianê
};

bool rescale_normal = false;


// aspekt obrazu
int aspect = FULL_WINDOW;

int currentLigth = AMBIENT_LIGHT;
int normals = NORMALS_FLAT;

// rozmiary bry³y obcinania

const GLdouble left = -2.0;
const GLdouble right = 2.0;
const GLdouble bottom = -2.0;
const GLdouble top = 2.0;
const GLdouble near_ = 3.0;
const GLdouble far_ = 7.0;

// k¹ty obrotu

GLfloat rotatex = 0.0;
GLfloat rotatey = 0.0;
GLfloat scale = 1.0;
// wska?nik naciœniêcia lewego przycisku myszki

int button_state = GLUT_UP;

// po³o?enie kursora myszki

int button_x, button_y;

// sk³adowe globalnego œwiat³a otaczaj¹cego

// wartosc pocz¹tkowa odpowiada wartoœci domyœlnej


// sk³adowych tego œwiat³a

GLfloat ambient_light[4] =
{
	0.396, 0.329, 0.101,0.0
	//0.0,0.0,1.0,0.0
};

const GLfloat *ambient = PolishedGoldAmbient;
const GLfloat *diffuse = PolishedGoldDiffuse;
const GLfloat *specular = PolishedGoldSpecular;
GLfloat shininess = PolishedGoldShininess;

// kierunek Ÿród³a œwiat³a
GLfloat light_position[4] =
{
	0.0,0.0,2.0,0.0
};

// k¹ty obrotu kierunku Ÿród³a œwiat³a
GLfloat light_rotatex = 0.0;
GLfloat light_rotatey = 0.0;

// funkcja rysuj¹ca napis w wybranym miejscu



void DrawString(GLfloat x, GLfloat y, char *string)
{
	// po³o?enie napisu
	glRasterPos2f(x, y);

	// wyœwietlenie napisu
	int len = strlen(string);
	for (int i = 0; i < len; i++)
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, string[i]);
}


constexpr int verticesCount = 6;
constexpr float piramidRadius = 1.0f;
GLTVector3 vCorners[verticesCount];

void FillCorners() {
	GLdouble degree = 2 * M_PI / verticesCount;

	for (int i = 0; i < verticesCount; i++)
	{
		vCorners[i][0] = piramidRadius*cos(i*degree);
		vCorners[i][1] = 0;
		vCorners[i][2] = piramidRadius*sin(i*degree);
	}
}

void CreatePiramidPart(float y) {
	for (int i = 0; i < verticesCount; i++)
	{
		int j = i + 1;
		if (i == verticesCount - 1)
			j = 0;
		GLTVector3 vNormal;
		//glColor3f((double)i / verticesCount, 0, 1);
		GLTVector3 vertex = { 0,y,0 };
		gltGetNormalVector(vertex, vCorners[j], vCorners[i], vNormal);
		glNormal3fv(vNormal);

		glColor3fv(White);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3fv(vertex);

		glTexCoord2f(1.0f, 1.0f);
		glVertex3fv(vCorners[i]);

		glTexCoord2f(0.0f, 1.0f);
		glVertex3fv(vCorners[j]);
	}
}

void RenderPiramid() {

	glPushMatrix();

	glScalef(scale, scale, scale);
	glRotatef(rotatex, 1.0f, 0.0f, 0.0f);
	glRotatef(rotatey, 0.0f, 1.0f, 0.0f);
	//glScalef(scale, scale, scale);
	glBegin(GL_TRIANGLES);

	CreatePiramidPart(0.0f);
	CreatePiramidPart(1.0f);

	glEnd();

	glPopMatrix();
}
void Display()
{
	// kolor t³a - zawartoœ? bufora koloru
	glClearColor(1.0, 1.0, 1.0, 1.0);

	// czyszczenie bufora koloru i bufora g³êbokoœci
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// wybór macierzy modelowania
	glMatrixMode(GL_MODELVIEW);

	// macierz modelowania = macierz jednostkowa
	glLoadIdentity();

	// przesuniêcie uk³adu wspó³rzêdnych szeœcianu do œrodka bry³y odcinania
	glTranslatef(0, 0, -(near_ + far_) / 2);

	// obroty szeœcianu
	glRotatef(rotatex, 1.0, 0, 0);
	glRotatef(rotatey, 0, 1.0, 0);

	// niewielkie powiêkszenie szeœcianu
	glScalef(1.15, 1.15, 1.15);

	// w³¹czenie oœwietlenia
	glEnable(GL_LIGHTING);

	if (currentLigth == AMBIENT_LIGHT)
	{
		glutSetWindowTitle("AMBIENT LIGHT");

		// parametry globalnego œwiat³a otaczaj¹cego
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient_light);

		// w³¹czenie obs³ugi w³aœciwoœci materia³ów
		glEnable(GL_COLOR_MATERIAL);

		// w³aœciwoœci materia³u okreœlone przez kolor wierzcho³ków
		glColorMaterial(GL_FRONT, GL_AMBIENT);

		glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
		glMaterialf(GL_FRONT, GL_SHININESS, shininess);

		// w³¹czenie testu bufora g³êbokoœci
		glEnable(GL_DEPTH_TEST);

		RenderPiramid();

		// wy³¹czenie oœwietlenia
		glDisable(GL_LIGHTING);

		// wy³¹czenie obs³ugi w³aœciwoœci materia³ów
		glDisable(GL_COLOR_MATERIAL);

		// wyœwietlenie sk³adowych globalnego œwiat³a otaczaj¹cego
		char string[100];
		GLfloat rgba[4];
		glColor3fv(Black);

		// pobranie wartoœci sk³adowych œwiat³a otaczaj¹cego
		// (oczywiœcie wartoœci te odpowiadaj¹ tablicy ambient_light)
		glGetFloatv(GL_LIGHT_MODEL_AMBIENT, rgba);
		sprintf(string, "AMBIENT: R=%f G=%f B=%f A=%f", rgba[0], rgba[1], rgba[2], rgba[3]);

		// trzeba odpowiednio przekszta³ci? uk³ad wspó³rzêdnych
		// aby napis znajdowa³ siê na samej "górze" bry³y obcinania
		glLoadIdentity();
		glTranslatef(0, 0, -near_);

		// narysowanie napisu
		DrawString(left, bottom, string);
	}

	else if (currentLigth == DIRECT_LIGHT)
	{
		glutSetWindowTitle("DIRECT LIGHT");

		// w³¹czenie œwiat³a GL_LIGHT0
		glEnable(GL_LIGHT0);

		// w³¹czenie automatycznej normalizacji wektorów normalnych
		glEnable(GL_NORMALIZE);

		// w³aœciwoœci materia³u
		glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
		glMaterialf(GL_FRONT, GL_SHININESS, shininess);

		// zmiana kierunku Ÿród³a œwiat³a jest wykonywana niezale¿nie
		// od obrotów obiektu, st¹d od³o¿enie na stos macierzy modelowania
		glPushMatrix();

		// macierz modelowania = macierz jednostkowa
		glLoadIdentity();

		// obroty kierunku Ÿród³a œwiat³a - klawisze kursora
		glRotatef(light_rotatex, 1.0, 0, 0);
		glRotatef(light_rotatey, 0, 1.0, 0);

		// ustalenie kierunku Ÿród³a œwiat³a
		glLightfv(GL_LIGHT0, GL_POSITION, light_position);

		// przywrócenie pierwotnej macierzy modelowania
		glPopMatrix();

		RenderPiramid();

		glDisable(GL_LIGHT0);
		glDisable(GL_NORMALIZE);

		// informacje o modyfikowanych wartoœciach
		// parametrów Ÿród³a œwiata³a GL_LIGHT0
		char string[200];
		GLfloat vec[4];
		glColor3fv(Black);


		// kierunek Ÿród³a œwiat³a
		glGetLightfv(GL_LIGHT0, GL_POSITION, vec);
		sprintf(string, "GL_POSITION = (%f,%f,%f,%f)", vec[0], vec[1], vec[2], vec[3]);
		DrawString(2, 2, string);

		// k¹ty obrotu kierunku Ÿród³a œwiat³a
		sprintf(string, "light_rotatex = %f", light_rotatex);
		DrawString(2, 16, string);
		sprintf(string, "light_rotatey = %f", light_rotatey);
		DrawString(2, 30, string);

	}

	else if (currentLigth == NORMAL_VECTORS) {
		glutSetWindowTitle("NORMAL VECTORS");

		// w³¹czenie œwiat³a GL_LIGHT0 z parametrami domyœlnymi
		glEnable(GL_LIGHT0);

		// w³aœciwoœci materia³u
		glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
		glMaterialf(GL_FRONT, GL_SHININESS, shininess);

		// w³¹czenie automatycznej normalizacji wektorów normalnych
		// lub automatycznego skalowania jednostkowych wektorów normalnych
		if (rescale_normal == true)
			glEnable(GL_RESCALE_NORMAL);
		else
			glEnable(GL_NORMALIZE);

		RenderPiramid();

		// koniec definicji obiektu
		glEnd();
	}

	// skierowanie polece? do wykonania
	glFlush();

	// zamiana buforów koloru
	glutSwapBuffers();
}

// zmiana wielkoœci okna

void Reshape(int width, int height)
{
	// obszar renderingu - ca³e okno
	glViewport(0, 0, width, height);

	// wybór macierzy rzutowania
	glMatrixMode(GL_PROJECTION);

	// macierz rzutowania = macierz jednostkowa
	glLoadIdentity();

	// parametry bry³y obcinania
	if (aspect == ASPECT_1_1)
	{
		// wysokoœ? okna wiêksza od wysokoœci okna
		if (width < height && width > 0)
			glFrustum(left, right, bottom*height / width, top*height / width, near_, far_);
		else

			// szerokoœ? okna wiêksza lub równa wysokoœci okna
			if (width >= height && height > 0)
				glFrustum(left*width / height, right*width / height, bottom, top, near_, far_);
	}
	else
		glFrustum(left, right, bottom, top, near_, far_);

	// generowanie sceny 3D
	Display();
}

// obs³uga klawiatury

void Keyboard(unsigned char key, int x, int y)
{
	// zmiana wartoœci sk³adowej R
	if (key == 'R' && ambient_light[0] < 1.0)
		ambient_light[0] += 0.05;
	else
		if (key == 'r' && ambient_light[0] > -1.0)
			ambient_light[0] -= 0.05;

	// zmiana wartoœci sk³adowej G
	if (key == 'G' && ambient_light[1] < 1.0)
		ambient_light[1] += 0.05;
	else
		if (key == 'g' && ambient_light[1] > -1.0)
			ambient_light[1] -= 0.05;

	// zmiana wartoœci sk³adowej B
	if (key == 'B' && ambient_light[2] < 1.0)
		ambient_light[2] += 0.05;
	else
		if (key == 'b' && ambient_light[2] > -1.0)
			ambient_light[2] -= 0.05;

	if (key == '+')
		scale += 0.05;
	else

		// klawisz -
		if (key == '-' && scale > 0.05)
			scale -= 0.05;

	// narysowanie sceny
	Display();
}

// obs³uga klawiszy funkcyjnych i klawiszy kursora

void SpecialKeys(int key, int x, int y)
{

	if (currentLigth == AMBIENT_LIGHT || currentLigth == NORMAL_VECTORS)
	{
		switch (key)
		{
			// kursor w lewo
		case GLUT_KEY_LEFT:
			rotatey -= 1;
			break;

			// kursor w górê
		case GLUT_KEY_UP:
			rotatex -= 1;
			break;

			// kursor w prawo
		case GLUT_KEY_RIGHT:
			rotatey += 1;
			break;

			// kursor w dó³
		case GLUT_KEY_DOWN:
			rotatex += 1;
			break;
		}
		// odrysowanie okna
		Reshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
	}

	else if (currentLigth == DIRECT_LIGHT)
	{
		switch (key)
		{
			// kursor w lewo
		case GLUT_KEY_LEFT:
			light_rotatey -= 5;
			break;

			// kursor w prawo
		case GLUT_KEY_RIGHT:
			light_rotatey += 5;
			break;

			// kursor w dó³
		case GLUT_KEY_DOWN:
			light_rotatex += 5;
			break;

			// kursor w górê
		case GLUT_KEY_UP:
			light_rotatex -= 5;
			break;
		}
		//odrysowanie okna
		Display();
	}


}

// obs³uga przycisków myszki

void MouseButton(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON)
	{
		// zapamiêtanie stanu lewego przycisku myszki
		button_state = state;

		// zapamiêtanie po³o?enia kursora myszki
		if (state == GLUT_DOWN)
		{
			button_x = x;
			button_y = y;
		}
	}
}

// obs³uga ruchu kursora myszki

void MouseMotion(int x, int y)
{
	if (button_state == GLUT_DOWN)
	{
		rotatey += 30 * (right - left) / glutGet(GLUT_WINDOW_WIDTH) * (x - button_x);
		button_x = x;
		rotatex -= 30 * (top - bottom) / glutGet(GLUT_WINDOW_HEIGHT) * (button_y - y);
		button_y = y;
		glutPostRedisplay();
	}
}

// obs³uga menu podrêcznego

void Menu(int value)
{
	switch (value)
	{
		// obszar renderingu - ca³e okno
	case FULL_WINDOW:
		aspect = FULL_WINDOW;
		Reshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
		break;

		// obszar renderingu - aspekt 1:1
	case ASPECT_1_1:
		aspect = ASPECT_1_1;
		Reshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
		break;

		// wyjœcie
	case EXIT:
		exit(0);
	}
}

void MenuLigth(int value) {
	switch (value)
	{
	case AMBIENT_LIGHT:
		currentLigth = AMBIENT_LIGHT;
		break;
	case DIRECT_LIGHT:
		currentLigth = DIRECT_LIGHT;
		break;
	case NORMAL_VECTORS:
		currentLigth = NORMAL_VECTORS;
		break;
	}
}

int main(int argc, char *argv[])
{
	// inicjalizacja biblioteki GLUT
	glutInit(&argc, argv);

	// inicjalizacja bufora ramki
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	// rozmiary g³ównego okna programu
	glutInitWindowSize(500, 500);

	// utworzenie g³ównego okna programu
#ifdef WIN32

	glutCreateWindow("Globalne œwiat³o otaczaj¹ce");
#else

	glutCreateWindow("Globalne swiatlo otaczajace");
#endif

	// do³¹czenie funkcji generuj¹cej scenê 3D
	glutDisplayFunc(Display);

	// do³¹czenie funkcji wywo³ywanej przy zmianie rozmiaru okna
	glutReshapeFunc(Reshape);

	// do³¹czenie funkcji obs³ugi klawiatury
	glutKeyboardFunc(Keyboard);

	// do³¹czenie funkcji obs³ugi klawiszy funkcyjnych i klawiszy kursora
	glutSpecialFunc(SpecialKeys);

	// obs³uga przycisków myszki
	glutMouseFunc(MouseButton);

	// obs³uga ruchu kursora myszki
	glutMotionFunc(MouseMotion);

	// utworzenie menu podrêcznego
	glutCreateMenu(Menu);

	int ligthMode = glutCreateMenu(MenuLigth);
	glutAddMenuEntry("AMBIENT LIGTH", AMBIENT_LIGHT);
	glutAddMenuEntry("DIRECT LIGTH", DIRECT_LIGHT);
	glutAddMenuEntry("NORMAL VECTORS", NORMAL_VECTORS);


	// utworzenie podmenu - aspekt obrazu
	int MenuAspect = glutCreateMenu(Menu);
#ifdef WIN32

	glutAddMenuEntry("Aspekt obrazu - ca³e okno", FULL_WINDOW);
#else

	glutAddMenuEntry("Aspekt obrazu - cale okno", FULL_WINDOW);
#endif

	glutAddMenuEntry("Aspekt obrazu 1:1", ASPECT_1_1);

	// menu g³ówne
	glutCreateMenu(Menu);
	glutAddSubMenu("Light Mode", ligthMode);
	glutAddSubMenu("Aspekt obrazu", MenuAspect);

#ifdef WIN32

	glutAddMenuEntry("Wyjœcie", EXIT);
#else

	glutAddMenuEntry("Wyjscie", EXIT);
#endif

	// okreœlenie przycisku myszki obs³uguj¹cej menu podrêczne
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	FillCorners();

	// wprowadzenie programu do obs³ugi pêtli komunikatów
	glutMainLoop();
	return 0;
}

#pragma warning(pop)