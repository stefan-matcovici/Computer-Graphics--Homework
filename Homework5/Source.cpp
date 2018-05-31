#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <vector>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include "glut.h"
#include <map>
#include <set>
#include <algorithm>    // std::min

#define LINES 15
#define COLUMNS 15
#define MARGIN 0.1
#define DIM 300
#define PI 3.1415926f

using namespace std;

int width = DIM;
int height = DIM;
int radius = 10;

unsigned char prevKey;

class Punct {
public:
	Punct() {
		this->x = 0;
		this->y = 0;
	}

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

struct Muchie {
	Muchie(Punct vi, Punct vf) {
		this->vi = vi;
		this->vf = vf;
	}

	Punct vi, vf;
};

class Poligon {
public:
	vector<Muchie> muchii;
};

struct Intersectie {
	Intersectie(int ymax, double xmin, double ratia) {
		this->ymax = ymax;
		this->xmin = xmin;
		this->ratia = ratia;
	}

	Intersectie(const Intersectie& intersectie) {
		this->ymax = intersectie.ymax;
		this->xmin = intersectie.xmin;
		this->ratia = intersectie.ratia;
	}

	bool operator< (const Intersectie& i) {
		return this->xmin < i.xmin;
	}

	int ymax;
	double xmin;
	double ratia;
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


		for (double i = 0; i < this->columns + 1; i++) {
			glBegin(GL_LINE_STRIP);
			glVertex2f(-1.0 / xmax, (2.0 / (double)this->columns * i - 1) / ymax);
			glVertex2f(1.0 / xmax, (2.0 / (double)this->columns * i - 1) / ymax);
			glEnd();
		}

		for (double i = 0; i < this->lines + 1; i++) {
			glBegin(GL_LINE_STRIP);
			glVertex2f((2.0 / (double)this->lines * i - 1) / xmax, -1.0 / ymax);
			glVertex2f((2.0 / (double)this->lines * i - 1) / xmax, 1.0 / ymax);
			glEnd();
		}
	}

	void deseneazaPixel(int line, int column)
	{
		glColor3f(0.1, 0.1, 0.1); // rosu

		//printf("(%d, %d)\n", line, column);

		double min = width > height ? height : width;

		double xmax = (double)width / (double)min + MARGIN;
		double ymax = (double)height / (double)min + MARGIN;

		float cx = (2.0 / (double)this->columns * line - 1) / xmax;
		float cy = (2.0 / (double)this->lines * column - 1) / ymax;

		double xymin = xmax > ymax ? ymax : xmax;

		//printf("%2f\n", cx);
		//printf("%2f\n", cy);


		float r = xymin / (this->lines > this->columns ? this->lines * 2 : this->columns * 2);

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

	void deseneazaCerc(int x, int y, int raza, int stoke) {
		glColor3f(1.0, 0.1, 0.1); // rosu
		glLineWidth(4.f);

		double min = width > height ? height : width;

		float cx, cy;
		getXY(x, y, cx, cy);

		double xmax = (double)width / (double)min + MARGIN;
		double ymax = (double)height / (double)min + MARGIN;

		double xymin = xmax > ymax ? ymax : xmax;

		float rx = (2.0 / (double)this->columns * (x + raza) - 1) / xmax;
		float ry = (2.0 / (double)this->lines * y - 1) / ymax;


		double r = rx - cx;

		int num_segments = 1000;
		glBegin(GL_LINE_LOOP);
		for (int ii = 0; ii < num_segments; ii++)
		{
			float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);//get the current angle

			float x = r * cosf(theta);//calculate the x component
			float y = r * sinf(theta);//calculate the y component

			glVertex2f((double)x + cx, ((double)y + cy));//output vertex

		}
		glEnd();
		glLineWidth(1.f);

		std::vector<Punct> list = deseneazaCercAlgoritm(x, y, raza, stoke);

		for (std::vector<Punct>::iterator it = list.begin(); it != list.end(); ++it) {
			deseneazaPixel(it->getX(), it->getY());
		}

	}

	std::vector<Punct> deseneazaCercAlgoritm(int x0, int y0, double raza, int stoke) {
		std::vector<Punct> puncte;
		int x = raza;
		int y = 0;

		puncte.push_back(Punct(x, y));
		for (int i = 1; i <= stoke / 2; i++) {
			puncte.push_back(Punct(x - i, y));
			puncte.push_back(Punct(x + i, y));
		}
		int d = 1 - raza;
		int dN = 3;
		int dNW = -2 * raza + 5;

		while (x > y) {
			if (d > 0) {
				// NW
				d += dNW;
				dN += 2;
				dNW += 4;
				x--;
			}
			else {
				// N
				d += dN;
				dN += 2;
				dNW += 2;
			}
			y++;

			puncte.push_back(Punct(x, y));
			for (int i = 1; i <= stoke / 2; i++) {
				puncte.push_back(Punct(x - i, y));
				puncte.push_back(Punct(x + i, y));
			}
		}

		return puncte;
	}

	void deseneazaElipsa(int x, int y, int a, int b, int stoke) {
		glColor3f(1.0, 0.1, 0.1); // rosu
		glLineWidth(4.f);

		double min = width > height ? height : width;

		float cx, cy;
		getXY(x, y, cx, cy);

		double xmax = (double)width / (double)min + MARGIN;
		double ymax = (double)height / (double)min + MARGIN;

		double xymin = xmax > ymax ? ymax : xmax;

		float rx = (2.0 / (double)this->columns * (x + a) - 1) / xmax;
		float ry = (2.0 / (double)this->lines * (y + b) - 1) / ymax;

		double ra = rx - cx;
		double rb = ry - cy;

		int num_segments = 1000;
		glBegin(GL_LINE_LOOP);
		for (int ii = 0; ii < num_segments; ii++)
		{
			float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);//get the current angle

			float x = ra * cosf(theta);//calculate the x component
			float y = rb * sinf(theta);//calculate the y component

			glVertex2f((double)x + cx, ((double)y + cy));//output vertex

		}
		glEnd();
		glLineWidth(1.f);

		std::vector<Punct> list = deseneazaElipsaAlgoritm(y, x, b, a, stoke);

		for (std::vector<Punct>::iterator it = list.begin(); it != list.end(); ++it) {
			deseneazaPixel(it->getX(), it->getY());
		}
	}

	std::vector<Punct> deseneazaElipsaAlgoritm(int x0, int y0, double a, double b, int stoke) {
		std::vector<Punct> puncte;

		int x = -a;
		int y = 0;

		double d2 = b * b * (-a + 0.5) * (-a + 0.5) + a * a - a * a * b * b;
		double d1;

		puncte.push_back(Punct(x + x0, y + y0));
		for (int i = x; i < 0; i++) {
			puncte.push_back(Punct(x + x0 - i, y + y0));
		}
		while (a * a * (y - 1) > b * b * (x + 0.5)) {
			if (d2 > 0) {
				// selectam SE
				d2 += b * b * (2 * x + 2) + a * a * (-2 * y + 3);
				x++;
				y--;
			}
			else {
				// selectam S
				d2 += a * a * (-2 * y + 3);
				y--;
			}

			for (int i = x; i < 0; i++) {
				puncte.push_back(Punct(x + x0 - i, y + y0));
			}
		}

		d1 = b * b * (x + 1) * (x + 1) + a * a * (y - 0.5) * (y - 0.5) - a * a * b * b;
		while (y > -b) {
			if (d1 > 0) {
				// selectam E
				d1 += b * b * (2 * x + 3);
				x++;
			}
			else {
				// selectam SE
				d1 += b * b * (2 * x + 3) + a * a * (-2 * y + 2);
				x++;
				y--;
			}

			for (int i = x; i < 0; i++) {
				puncte.push_back(Punct(x + x0 - i, y + y0));
			}
		}

		return puncte;
	}

	std::vector<Punct> deseneazaLinieAlgoritm(int x0, int y0, int xn, int yn, int stoke) {
		double m = ((double)yn - (double)y0) / ((double)xn - (double)x0);
		if (m > 0) {
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
				/* alegem S */
				d += dE;
				y++;
			}
			else {
				/* alegem SE */
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

	void deseneazaPoligon(const char* fisier) {
		FILE* file;
		Poligon poligon;
		int n;
		int x1, x2;
		file = fopen(fisier, "r");
		if (file) {
			fscanf(file, "%d", &n);
			fscanf(file, "%d %d", &x1, &x2);
			Punct punct1(x1, x2);
			Punct initial(x1, x2);

			for (int i = 1; i < n; i++) {
				fscanf(file, "%d %d", &x1, &x2);

				Punct punct2(x1, x2);
				poligon.muchii.push_back(Muchie(punct1, punct2));
				punct1.setX(x1);
				punct1.setY(x2);
			}

			poligon.muchii.push_back(Muchie(punct1, initial));

		}

		float cx, cy;

		glColor3f(1.0, 0.1, 0.1); // rosu
		glLineWidth(4.f);
		glBegin(GL_LINE_LOOP);
		for (int i = 0; i < poligon.muchii.size(); i++) {
			getXY(poligon.muchii.at(i).vi.getX(), poligon.muchii.at(i).vi.getY(), cx, cy);
			glVertex2f(cx, cy);
		}
		glEnd();
		glLineWidth(1.f);

		map <int, vector<Intersectie>> et, ssms;
		initializareEt(poligon, et);

		/*for (auto it = et.begin(); it != et.end(); it++) {
			printf("[%d]: ", it->first);
			for (auto it2 = it->second.begin(); it2 != it->second.end(); it2++) {
				printf("(%d, %f, %f), ", it2->ymax, it2->xmin, it2->ratia);
			}
			printf("\n");
		}*/

		calculssm(poligon, et, ssms);

		/*for (auto it = ssms.begin(); it != ssms.end(); it++) {
			printf("[%d]: ", it->first);
			for (auto it2 = it->second.begin(); it2 != it->second.end(); it2++) {
				printf("(%d, %f, %f), ", it2->ymax, it2->xmin, it2->ratia);
			}
			printf("\n");
		}*/

		coloreaza(ssms);
	}

	void initializareEt(Poligon poligon, map <int, vector<Intersectie>>& et) {
		int xm, ym, xM, yM;
		bool change;

		for (int i = 0; i < 20; i++) {
			vector<Intersectie> v;
			et.insert(pair<int, vector<Intersectie>>(i, v));
		}

		for (Muchie m : poligon.muchii) {
			if (m.vi.getY() != m.vf.getY()) {
				ym = min(m.vi.getY(), m.vf.getY());
				yM = max(m.vi.getY(), m.vf.getY());
				xm = (ym == m.vi.getY()) ? m.vi.getX() : m.vf.getX();
				xM = (yM == m.vi.getY()) ? m.vi.getX() : m.vf.getX();
				//printf("%d\n", ym);
				et.find(ym)->second.push_back(Intersectie(yM, xm, (double)(xm - xM) / (ym - yM)));
			}
		}

		for (int i = 0; i < 20; i++) {
			vector<Intersectie> curent = et.find(i)->second;
			sort(curent.begin(), curent.end());


			/*do {
				change = false;
				vector<Intersectie> curent = et.find(i)->second;
				if (curent.size() == 0)
					break;

				for (int j = 0; j < curent.size()-1; j++) {
					if (curent.at(j).xmin > curent.at(j + 1).xmin) {
						swap(curent.at(j), curent.at(j + 1));
						change = true;
					}
				}
			} while (change);*/
		}
	}

	void calculssm(Poligon poligon, map <int, vector<Intersectie>>& et, map <int, vector<Intersectie>>& finalET) {
		vector<Intersectie> activeSSM;

		int y, k;

		for (int i = 0; i < 20; i++) {
			vector<Intersectie> v;
			finalET.insert(pair<int, vector<Intersectie>>(i, v));
		}

		y = -1;
		for (int i = 0; i < 20; i++) {
			if (!et.find(i)->second.empty()) {
				y = i;
				break;
			}
		}

		if (y < 0 || y>20) {
			return;
		}

		do {
			activeSSM.insert(activeSSM.end(), et.find(y)->second.begin(), et.find(y)->second.end());
			
			int ii = 0;
			while (ii<activeSSM.size()) {
				if (activeSSM.at(ii).ymax == y) {
					activeSSM.erase(activeSSM.begin() + ii);
				}
				else {
					ii++;
				}
			}

			k = activeSSM.size();

			sort(activeSSM.begin(), activeSSM.end());

			/*while (k >= 1) {
				for (int i = 0; i < k-1; i++) {
					if (activeSSM.at(i).xmin > activeSSM.at(i + 1).xmin) {
						swap(activeSSM.at(i), activeSSM.at(i + 1));
					}
				}

				k--;
			}*/

			for (auto it = activeSSM.begin(); it != activeSSM.end(); it++) {
				Intersectie deepCopy = Intersectie(*it);
				finalET.find(y)->second.push_back(deepCopy);
			}
			y++;

			for (int i = 0; i < activeSSM.size(); i++) {
				if (activeSSM.at(i).ratia != 0) {
					activeSSM.at(i).xmin += activeSSM.at(i).ratia;
				}
			}
		} while ((!activeSSM.empty() || !et.find(y)->second.empty()) && y<20);
	}

	void coloreaza(map <int, vector<Intersectie>> ssms) {
		for (auto it = ssms.begin(); it != ssms.end(); it++) {
			// parcurgem lista de intersectii pentru fiecare dreapta de scanare
			bool paritate = false;

			int y = it->first; // dreapta de scanare y = y
			vector<Intersectie> intersectii = it->second;
			if (intersectii.size() == 0)
				// daca nu intersecteaza in niciun punct continuam
				continue;

			vector<Intersectie>::iterator curent = intersectii.begin();
			// calculam extremitatile, cea din stanga o sa fie interioara, cea din dreapta nu
			int extremitate_stanga = intersectii.begin()->xmin;
			int extremitate_dreapta = next(intersectii.end(), -1)->xmin;

			//printf("%d stanga: %d, dreapta: %d\n", y, extremitate_stanga, extremitate_dreapta);

			for (int i = 0; i < 20 && curent!=intersectii.end(); i++) {
				// parcurgem domeniul

				// puncte de intersectie (Q/Z)xZ
				if ((int)curent->xmin != curent->xmin) {
					if (paritate && (int)floor(curent->xmin) == i-1) {
						// intrare in poligon
						paritate = !paritate;
						curent = next(curent, 1);
					}
					else if (!paritate && (int)ceil((curent->xmin)) == i) {
						// iesire in poligon
						paritate = !paritate;
						curent = next(curent, 1);
					}
				}
				else {
					if (next(curent) != intersectii.end() && curent->xmin == next(curent)->xmin && (y != next(curent)->ymax || y != curent->ymax) && i == curent->xmin) {
						// punctul este varf al poligonului si nu este macar pentru o dreapta ymax
						paritate = 1;
						curent = next(curent, 2);
					}
					// extremitati
					else if (i == extremitate_stanga || i == extremitate_dreapta) {
						paritate = !paritate;
						curent = next(curent, 1);
					}
					
				}

				bool ok = false;
				while (curent != intersectii.end() && i > curent->xmin) {
					// daca punctul este inaintea urmatoarei intersectii
					curent = next(curent);
					ok = true;
				}

				if (ok && curent == intersectii.end()) {
					break;
				}

				if (paritate) {
					deseneazaPixel(i, y);
				}

			}

		}
	}

private:
	int lines;
	int columns;

	void getXY(int line, int column, float& outX, float& outY) {
		double min = width > height ? height : width;

		double xmax = (double)width / (double)min + MARGIN;
		double ymax = (double)height / (double)min + MARGIN;

		outX = (2.0 / (double)this->columns * (double)line - 1) / xmax;
		outY = (2.0 / (double)this->lines * (double)column - 1) / ymax;
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
	GrilaCarteziana grilaCarteziana1(15, 15);
	GrilaCarteziana grilaCarteziana2(26, 26);
	GrilaCarteziana grilaCarteziana3(14, 14);

	switch (prevKey)
	{
	case '0':
		grilaCarteziana1.display();
		grilaCarteziana1.deseneazaCerc(0, 0, 13, 3);
		break;
	case '1':
		grilaCarteziana2.display();
		grilaCarteziana2.deseneazaElipsa(13, 8, 13, 8, 1);
		break;
	case '2':
		grilaCarteziana3.display();
		grilaCarteziana3.deseneazaPoligon("poligon.txt");
		break;
	default:
		break;
	}

	glFlush();

	//grilaCarteziana.deseneazaPixel(5, 5);
	//grilaCarteziana.deseneazaPixel(5, 6);

	//grilaCarteziana.deseneazaLinie(0, 15, 15, 10, 3);

	//grilaCarteziana.deseneazaLinie(0, 0, 15, 7, 1);


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