#include <stdlib.h>

#include <stdio.h>
#include <math.h>

#include "glut.h"

#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#define PI 3.14159265

// dimensiunea ferestrei in pixeli
#define dim 300

unsigned char prevKey;

enum EObiect { cubw, cubs, sferaw, sferas }; 
EObiect ob = cubw;

struct Punct {
	Punct() {
		this->x = 0;
		this->y = 0;
		this->z = 0;
	}


	Punct(float x, float y, float z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}
	
	Punct(const Punct& punct) {
		this->x = punct.x;
		this->y = punct.y;
		this->z = punct.z;
	}

	void draw() {
		glVertex3f(this->x, this->y, this->z);
	}

	float x, y, z;
};

struct Triunghi {
	Triunghi() {
	}

	Triunghi(Punct& p1, Punct& p2, Punct& p3) {
		this->p1 = Punct(p1);
		this->p2 = Punct(p2);
		this->p3 = Punct(p3);
	}

	void draw() {
		glBegin(GL_TRIANGLES);
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(this->p1.x, this->p1.y, this->p1.z);
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(this->p2.x, this->p2.y, this->p2.z);
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(this->p3.x, this->p3.y, this->p3.z);

		glEnd();
	}

	Punct p1, p2, p3;
};

Triunghi triunghi;

void DisplayAxe() {
	int X, Y, Z;
	X = Y = 200;
	Z = 200;

	glLineWidth(2);

	// axa Ox - verde
	glColor3f(0, 1, 0);
	glBegin(GL_LINE_STRIP);
	glVertex3f(0, 0, 0);
	glVertex3f(X, 0, 0);
	glEnd();

	// axa Oy - albastru
	glColor3f(0, 0, 1);
	glBegin(GL_LINE_STRIP);
	glVertex3f(0, 0, 0);
	glVertex3f(0, Y, 0);
	glEnd();

	// axa Oz - rosu
	glColor3f(1, 0, 0);
	glBegin(GL_LINE_STRIP);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, Z);
	glEnd();

	glLineWidth(1);
}

// cub wireframe
void Display1() {
	glColor3f(1, 0, 0);
	glutWireCube(1);
}

// cub solid
void Display2() {
	glColor3f(1, 0, 0);
	glutSolidCube(1);
}

// sfera wireframe
void Display3() {
	glColor3f(0, 0, 1);
	glutWireSphere(1, 10, 10);
}

// sfera solida
void Display4() {
	glColor3f(0, 0, 1);
	glutSolidSphere(1, 10, 10);
}

void random_triangle_coordinates(float& x, float& y, float& z) {
	x = -5 + static_cast <float> (rand()) / static_cast <float> (RAND_MAX/10.0);
	y = -5 + static_cast <float> (rand()) / static_cast <float> (RAND_MAX/10.0);
	z = -5 + static_cast <float> (rand()) / static_cast <float> (RAND_MAX/10.0);
}

void Display51() {
	float x, y, z;

	random_triangle_coordinates(x, y, z);
	Punct p1 = Punct(x, y, z);
	random_triangle_coordinates(x, y, z);
	Punct p2 = Punct(x, y, z);
	random_triangle_coordinates(x, y, z);
	Punct p3 = Punct(x, y, z);

	triunghi = Triunghi(p1, p2, p3);
	triunghi.draw();
}

void Display52() {
	glTranslatef(-triunghi.p1.x, -triunghi.p1.y, -triunghi.p1.z);
	triunghi.draw();
}

void Display53() {
	float d1 = sqrtf(powf(triunghi.p2.x - triunghi.p1.x, 2) + powf(triunghi.p2.z - triunghi.p1.z, 2));
	float cosinus = (triunghi.p2.z - triunghi.p1.z) / d1;
	float sinus = (triunghi.p1.x - triunghi.p2.x) / d1;
	float theta = atan2f(sinus, cosinus) * 180 / PI;
	glRotatef(theta, 0.0, 1.0, 0.0);
	glTranslatef(-triunghi.p1.x, -triunghi.p1.y, -triunghi.p1.z);
	triunghi.draw();
}

void Display54() {
	float d1 = sqrtf(powf(triunghi.p2.x - triunghi.p1.x, 2) + powf(triunghi.p2.z - triunghi.p1.z, 2));
	float cosinus = (triunghi.p2.z - triunghi.p1.z) / d1;
	float sinus = (triunghi.p1.x - triunghi.p2.x) / d1;
	float theta = atan2f(sinus, cosinus) * 180 / PI;

	float d2 = sqrtf(powf((triunghi.p2.y - triunghi.p1.y), 2.0) + powf(d1, 2.0));
	cosinus = d1 / d2;
	sinus = (triunghi.p2.y - triunghi.p1.y) / d2;
	float phi = atan2f(sinus, cosinus) * 180 / PI;
	glRotatef(phi, 1.0, 0.0, 0.0);
	glRotatef(theta, 0.0, 1.0, 0.0);
	glTranslatef(-triunghi.p1.x, -triunghi.p1.y, -triunghi.p1.z);
	triunghi.draw();
}

void Display55() {
	float d1 = sqrtf(powf(triunghi.p2.x - triunghi.p1.x, 2) + powf(triunghi.p2.z - triunghi.p1.z, 2));
	float cosinus = (triunghi.p2.z - triunghi.p1.z) / d1;
	float sinus = (triunghi.p1.x - triunghi.p2.x) / d1;
	float theta = atan2f(sinus, cosinus) * 180 / PI;

	float d2 = sqrtf(powf((triunghi.p2.y - triunghi.p1.y), 2.0) + powf(d1, 2.0));
	cosinus = d1 / d2;
	sinus = (triunghi.p2.y - triunghi.p1.y) / d2;
	float phi = atan2f(sinus, cosinus) * 180 / PI;

	float x3 = ((triunghi.p2.z - triunghi.p1.z)*(triunghi.p3.x - triunghi.p1.x) - (triunghi.p2.x - triunghi.p1.x)*(triunghi.p3.z - triunghi.p1.z)) / d1;
	float y3 = (d1*d1*(triunghi.p3.y - triunghi.p1.y) - (triunghi.p2.y - triunghi.p1.y)*((triunghi.p2.x - triunghi.p1.x)*(triunghi.p3.x - triunghi.p1.x) + (triunghi.p2.z - triunghi.p1.z)*(triunghi.p3.z - triunghi.p1.z))) / (d1*d2);

	float d3 = sqrtf(powf(x3, 2.0) + powf(y3, 2.0));
	cosinus = y3 / d3;
	sinus = x3 / d3;

	float alpha = atan2f(sinus, cosinus) * 180 / PI;

	glRotatef(alpha, 0.0, 0.0, 1.0);
	glRotatef(phi, 1.0, 0.0, 0.0);
	glRotatef(theta, 0.0, 1.0, 0.0);
	glTranslatef(-triunghi.p1.x, -triunghi.p1.y, -triunghi.p1.z);
	triunghi.draw();
}

void DisplayObiect()
{
	switch (ob)
	{
	case cubw:
		Display1();
		break;
	case cubs:
		Display2();
		break;
	case sferaw:
		Display3();
		break;
	case sferas:
		Display4();
		break;
	default:
		break;
	}
}

void DisplayCube() {
	int X, Y, Z;
	X = Y = 10;
	Z = 100;

	glColor3f(0, 1, 0);
	glBegin(GL_QUADS);
	glVertex3f(0, X, 0);
	glVertex3f(X, X, 0);
	glVertex3f(X, X, X);
	glVertex3f(0, X, X);
	glEnd();

	glColor3f(1, 1, 0);
	glBegin(GL_QUADS);
	glVertex3f(X, X, 0);
	glVertex3f(X, 0, 0);
	glVertex3f(X, 0, X);
	glVertex3f(X, X, X);
	glEnd();



	glColor3f(1, 0, 0);
	glBegin(GL_QUADS);
	glVertex3f(0, X, X);
	glVertex3f(X, X, X);
	glVertex3f(X, 0, X);
	glVertex3f(0, 0, X);
	glEnd();
}

// rotatia cu un unghi de 10 grade in raport cu axa x
void DisplayX() {
	glMatrixMode(GL_MODELVIEW);
	glRotated(10, 1, 0, 0);
}

// rotatia cu un unghi de 10 grade in raport cu axa y
void DisplayY() {
	glMatrixMode(GL_MODELVIEW);
	glRotated(10, 0, 1, 0);
}

// rotatia cu un unghi de 10 grade in raport cu axa z
void DisplayZ() {
	glMatrixMode(GL_MODELVIEW);
	glRotated(10, 0, 0, 1);
}

// Translatia cu 0.2, 0.2, 0.2
void DisplayT() {
	glMatrixMode(GL_MODELVIEW);
	glTranslatef(0.2, 0.2, 0.2);
}

// Scalarea cu 1.2, 1.2, 1.2
void DisplayS() {
	glMatrixMode(GL_MODELVIEW);
	glScalef(1.2, 1.2, 1.2);
}

void MakeRotations(float beta) {
	float c = cosf(beta);
	float s = sinf(beta);
	float t = 1 - c;

	float R31 = t / 3.0 - s / sqrt(3);
	float R32  = t / 3.0 + s / sqrt(3);
	float R33 = t / 3.0 + c;

	float R11 = R33;
	float R21 = R32;

	float teta = PI + asinf(R31);
	float cteta = cosf(teta);
	float psi = atan2f(R32 / cteta, R33 / cteta);
	float phi = atan2f(R21 / cteta, R11 / cteta);

	printf("%f %f %f\n", phi * 180 / PI, teta * 180 / PI, psi * 180 / PI);

	glRotatef(phi * 180 / PI, 0, 0, 1);
	glRotatef(teta * 180 / PI, 0, 1, 0);
	glRotatef(psi * 180 / PI, 1, 0, 0);
}

void Init(void) {
	glClearColor(1, 1, 1, 1);
	glLineWidth(2);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-10, 10, -10, 10, 30, -30);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glRotated(20, 1, 0, 0);
	glRotated(-20, 0, 1, 0);


	srand(time(NULL));
}

void Display(void) {
	switch (prevKey)
	{
	case 'a':
		DisplayAxe();
		break;
	case '0':
		glClear(GL_COLOR_BUFFER_BIT);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glRotated(20, 1, 0, 0);
		glRotated(-20, 0, 1, 0);
		break;
	case '1':
		Display1();
		ob = cubw;
		break;
	case '2':
		Display2();
		ob = cubs;
		break;
	case '3':
		Display3();
		ob = sferaw;
		break;
	case '4':
		Display4();
		ob = sferas;
		break;
	case 'x':
		glClear(GL_COLOR_BUFFER_BIT);
		DisplayX();
		DisplayAxe();
		DisplayObiect();
		break;
	case 'y':
		glClear(GL_COLOR_BUFFER_BIT);
		DisplayY();
		DisplayAxe();
		DisplayObiect();
		break;
	case 'z':
		glClear(GL_COLOR_BUFFER_BIT);
		DisplayZ();
		DisplayAxe();
		DisplayObiect();
		break;
	case 't':
		glClear(GL_COLOR_BUFFER_BIT);
		DisplayT();
		DisplayAxe();
		DisplayObiect();
		break;
	case 's':
		glClear(GL_COLOR_BUFFER_BIT);
		DisplayS();
		DisplayAxe();
		DisplayObiect();
		break;
	case 'b':
		glClear(GL_COLOR_BUFFER_BIT);
		glPushMatrix();

		DisplayAxe();
		Display51();
		break;
	case 'c':
		glClear(GL_COLOR_BUFFER_BIT);
		glMatrixMode(GL_MODELVIEW);

		DisplayAxe();
		glPushMatrix();
		Display52();
		break;
	case 'd':
		glClear(GL_COLOR_BUFFER_BIT);
		glMatrixMode(GL_MODELVIEW);
		glPopMatrix();
		glPushMatrix();

		DisplayAxe();
		Display53();
	
		break;
	case 'e':
		glClear(GL_COLOR_BUFFER_BIT);
		glMatrixMode(GL_MODELVIEW);
		glPopMatrix();
		glPushMatrix();

		DisplayAxe();
		Display54();
		break;
	case 'f':
		glClear(GL_COLOR_BUFFER_BIT);
		glMatrixMode(GL_MODELVIEW);
		glPopMatrix();
		glPushMatrix();
		DisplayAxe();

		Display55();

		break;
	case 'g':
		glClear(GL_COLOR_BUFFER_BIT);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glRotated(35, 1, 0, 0);
		glRotated(-42.5, 0, 1, 0);

		DisplayAxe();
		DisplayCube();
		break;
	case 'h':
		glClear(GL_COLOR_BUFFER_BIT);
		glMatrixMode(GL_MODELVIEW);

		DisplayAxe();
		MakeRotations(PI / 4);
		DisplayCube();
		break;

	default:
		break;
	}
	glutSwapBuffers();
}

void Reshape(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
}

void KeyboardFunc(unsigned char key, int x, int y) {
	prevKey = key;
	if (key == 27) // escape
		exit(0);
	glutPostRedisplay();
}

void MouseFunc(int button, int state, int x, int y) {
}

int main(int argc, char** argv) {

	glutInit(&argc, argv);

	glutInitWindowSize(dim, dim);

	glutInitWindowPosition(100, 100);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

	glutCreateWindow(argv[0]);

	Init();

	glutReshapeFunc(Reshape);

	glutKeyboardFunc(KeyboardFunc);

	glutMouseFunc(MouseFunc);

	glutDisplayFunc(Display);

	glutMainLoop();

	return 0;
}