#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <vector>
#include <stdlib.h>

#include "glut.h"

#define LINES 15
#define COLUMNS 15
#define MARGIN 0.1
#define DIM 300
#define PI 3.14

int width = DIM;
int height = DIM;
int radius = 10;

unsigned char prevKey;

class Punct {
public:
	Punct(int x, int y) {
		this->x = x;
		this->y = y;
	}

	int getX() {
		return x;
	}

	void setX(int x) {
		this->x = x;
	}

	int getY() {
		return y;
	}

	void setY(int y) {
		this->y = y;
	}

private:
	int x, y;
};

class GrilaCarteziana {
public:
	GrilaCarteziana(int lines, int columns) {
		this->lines = lines;
		this->columns = columns;
	}

	void display() {
		glColor3f(1, 0.1, 0.1); // rosu

		printf("%d, %d\n", width, height);

		double min = width > height ? height : width;

		double xmax = (double)width / (double)min + MARGIN;
		double ymax = (double)height / (double)min + MARGIN;


		for (double i = 0; i < COLUMNS + 1; i++) {
			glBegin(GL_LINE_STRIP);
			glVertex2f(-1.0 / xmax, (2.0 / (double)COLUMNS * i - 1) / ymax);
			glVertex2f(1.0 / xmax, (2.0 / (double)COLUMNS * i - 1) / ymax);
			glEnd();
		}

		for (double i = 0; i < LINES + 1; i++) {
			glBegin(GL_LINE_STRIP);
			glVertex2f((2.0 / (double)LINES * i - 1) / xmax, -1.0 / ymax);
			glVertex2f((2.0 / (double)LINES * i - 1) / xmax, 1.0 / ymax);
			glEnd();
		}
	}

	void deseneazaPixel(int line, int column)
	{
		if (line > LINES || column > COLUMNS || line < 0 || column < 0) {
			return;
		}
		glColor3f(0.1, 0.1, 0.1); // rosu

		double min = width > height ? height : width;

		double xmax = (double)width / (double)min + MARGIN;
		double ymax = (double)height / (double)min + MARGIN;

		float cx = (2.0 / (double)COLUMNS * line - 1) / xmax;
		float cy = (2.0 / (double)LINES * column - 1) / ymax;

		double xymin = xmax > ymax ? ymax : xmax;

		float r = xymin / (LINES > COLUMNS ? COLUMNS * 2 : LINES * 2);

		int num_segments = 25;

		glBegin(GL_POLYGON);
		for (int ii = 0; ii < num_segments; ii++)
		{
			float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);//get the current angle

			float x = r * cosf(theta);//calculate the x component
			float y = r * sinf(theta);//calculate the y component

			glVertex2f(x / xmax + cx, y / ymax + cy);//output vertex

		}
		glEnd();
	}

	void deseneazaLinie(int x0, int y0, int xn, int yn, int stoke) {
		glColor3f(1.0, 0.1, 0.1); // rosu
		glLineWidth(4.f);

		float cx0, cy0, cxn, cyn, cx, cy;

		getXY(x0, y0, cx0, cy0);
		getXY(xn, yn, cxn, cyn);

		glBegin(GL_LINE_STRIP);
		glVertex2f(cx0, cy0);
		glVertex2f(cxn, cyn);
		glEnd();
		glLineWidth(1.f);

		std::vector<Punct> list = deseneazaLinieAlgoritm(x0, y0, xn, yn, stoke);

		for (std::vector<Punct>::iterator it = list.begin(); it != list.end(); ++it) {
			deseneazaPixel(it->getX(), it->getY());
		}

	}

	std::vector<Punct> deseneazaLinieAlgoritm(int x0, int y0, int xn, int yn, int stoke) {

		double m = ((double)yn - (double)y0) / ((double)xn - (double)x0);
		if (m>0) {
			if (abs(yn - y0) < abs(xn - x0)) {
				if (x0 > xn)
					return deseneazaLinieXPositive(xn, yn, x0, y0, stoke);
				else
					return deseneazaLinieXPositive(x0, y0, xn, yn, stoke);
			}
			else
			{
				if (y0 > yn)
					return deseneazaLinieYPositive(xn, yn, x0, y0, stoke);
				else
					return deseneazaLinieYPositive(x0, y0, xn, yn, stoke);
			}
		}
		else {
			if (abs(yn - y0) < abs(xn - x0)) {
				if (x0 > xn)
					return deseneazaLinieXNegative(xn, yn, x0, y0, stoke);
				else
					return deseneazaLinieXNegative(x0, y0, xn, yn, stoke);
			}
			else
			{
				if (y0 > yn)
					return deseneazaLinieYNegative(x0, y0, xn, yn, stoke);
				else
					return deseneazaLinieYNegative(xn, yn, x0, y0, stoke);
			}
			std::vector<Punct> puncte;
			return puncte;
		}

	}

	std::vector<Punct> deseneazaLinieXPositive(int x0, int y0, int xn, int yn, int stoke)
	{
		std::vector<Punct> puncte;
		int dy = yn - y0;
		int dx = xn - x0;

		int d = 2 * dy - dx;
		int dE = 2 * dy;
		int dNE = 2 * (dy - dx);
		int x = x0, y = y0;

		puncte.push_back(Punct(x, y));
		for (int i = 1; i <= stoke / 2; i++) {
			puncte.push_back(Punct(x, y - i));
			puncte.push_back(Punct(x, y + i));
		}
		while (x < xn)
		{
			if (d <= 0) {
				/* alegem E */
				d += dE;
				x++;
			}
			else {
				/* alegem NE */
				d += dNE;
				x++;
				y++;
			}
			puncte.push_back(Punct(x, y));
			for (int i = 1; i <= stoke / 2; i++) {
				puncte.push_back(Punct(x, y - i));
				puncte.push_back(Punct(x, y + i));
			}
		}

		return puncte;
	}

	std::vector<Punct> deseneazaLinieYPositive(int x0, int y0, int xn, int yn, int stoke)
	{
		std::vector<Punct> puncte;

		int dy = yn - y0;
		int dx = xn - x0;

		int d = dy - 2 * dx;
		int dE = -2 * dx;
		int dNE = 2 * (dy - dx);
		int x = x0, y = y0;

		puncte.push_back(Punct(x, y));
		for (int i = 1; i <= stoke / 2; i++) {
			puncte.push_back(Punct(x - i, y));
			puncte.push_back(Punct(x + i, y)); 
		}
		while (y < yn)
		{
			if (d > 0) {
				/* alegem E */
				d += dE;
				y++;
			}
			else {
				/* alegem NE */
				d += dNE;
				x++;
				y++;
			}

			puncte.push_back(Punct(x, y));
			for (int i = 1; i <= stoke / 2; i++) {
				puncte.push_back(Punct(x - i, y));
				puncte.push_back(Punct(x + i, y));

			}
		}
		return puncte;
	}

	std::vector<Punct> deseneazaLinieXNegative(int x0, int y0, int xn, int yn, int stoke)
	{
		std::vector<Punct> puncte;
		int dy = yn - y0;
		int dx = xn - x0;

		int d = 2 * dy + dx;
		int dE = 2 * dy;
		int dSE = 2 * (dy + dx);
		int x = x0, y = y0;

		puncte.push_back(Punct(x, y));
		for (int i = 1; i <= stoke / 2; i++) {
			puncte.push_back(Punct(x, y - i));
			puncte.push_back(Punct(x, y + i));
		}
		while (x < xn)
		{
			if (d >= 0) {
				/* alegem E */
				d += dE;
				x++;
			}
			else {
				/* alegem SE */
				d += dSE;
				x++;
				y--;
			}
			puncte.push_back(Punct(x, y));
			for (int i = 1; i <= stoke / 2; i++) {
				puncte.push_back(Punct(x, y - i));
				puncte.push_back(Punct(x, y + i));
			}
		}

		return puncte;
	}

	std::vector<Punct> deseneazaLinieYNegative(int x0, int y0, int xn, int yn, int stoke)
	{
		std::vector<Punct> puncte;

		int dy = yn - y0;
		int dx = xn - x0;

		int d = dy + 2 * dx;
		int dS = 2 * dx;
		int dSE = 2 * (dy + dx);
		int x = x0, y = y0;

		puncte.push_back(Punct(x, y));
		for (int i = 1; i <= stoke / 2; i++) {
			puncte.push_back(Punct(x - i, y));
			puncte.push_back(Punct(x + i, y));
		}
		while (y > yn)
		{
			if (d < 0) {
				/* alegem S */
				d += dS;
				y--;
			}
			else {
				/* alegem SE */
				d += dSE;
				x++;
				y--;
			}

			puncte.push_back(Punct(x, y));
			for (int i = 1; i <= stoke / 2; i++) {
				puncte.push_back(Punct(x - i, y));
				puncte.push_back(Punct(x + i, y));

			}
		}
		return puncte;
	}

private:
	int lines;
	int columns;

	void getXY(int line, int column, float& outX, float& outY) {
		double min = width > height ? height : width;

		double xmax = (double)width / (double)min + MARGIN;
		double ymax = (double)height / (double)min + MARGIN;

		outX = (2.0 / (double)COLUMNS * line - 1) / xmax;
		outY = (2.0 / (double)LINES * column - 1) / ymax;
	}
};

void Init(void) {

	glClearColor(1.0, 1.0, 1.0, 1.0);

	glLineWidth(1);

	//glPointSize(4);

	glPolygonMode(GL_FRONT, GL_FILL);
}

void Display(void) {
	glClear(GL_COLOR_BUFFER_BIT);

	GrilaCarteziana grilaCarteziana(LINES, COLUMNS);
	grilaCarteziana.display();
	//grilaCarteziana.deseneazaPixel(5, 5);
	//grilaCarteziana.deseneazaPixel(5, 6);

	grilaCarteziana.deseneazaLinie(0, 15, 15, 10, 3);

	grilaCarteziana.deseneazaLinie(0, 0, 15, 7, 1);

	grilaCarteziana.deseneazaLinie(15, 15, 7, 0, 3);


	glFlush();
}

void Reshape(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);

	width = w;
	height = h;

	glutDisplayFunc(Display);
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

	glutInitWindowSize(width, height);

	glutInitWindowPosition(100, 100);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	glutCreateWindow(argv[0]);

	Init();

	glutReshapeFunc(Reshape);

	glutKeyboardFunc(KeyboardFunc);

	glutMouseFunc(MouseFunc);

	glutDisplayFunc(Display);

	glutMainLoop();

	return 0;
}